/*	$NetBSD$	*/

/*
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#ifndef lint
#if 0
static char sccsid[] = "@(#)cypher.c	8.2 (Berkeley) 4/28/95";
#else
__RCSID("$NetBSD$");
#endif
#endif				/* not lint */

#include "extern.h"

int
cypher(void)
{
	int     n;
	int     junk;
	int     lflag = -1;
	char    buffer[10];
	char   *filename, *rfilename;
	size_t	filename_len;

	while (wordnumber <= wordcount) {
		if (wordtype[wordnumber] != VERB &&
		    !(wordtype[wordnumber] == OBJECT && 
		    wordvalue[wordnumber] == KNIFE)) {
			printf("%s: How's that?\n",
			    (wordnumber == wordcount) ? words[0] : 
			    words[wordnumber]);
			return (-1);
		}

		switch (wordvalue[wordnumber]) {

		case AUXVERB:
			/*
			 * Take the following word as the verb (e.g.
			 * "make love", "climb up").
			 */
			wordnumber++;
			continue;

		case UP:
			if (location[position].access || wiz || tempwiz) {
				if (!location[position].access) {
					printf("Zap!  A gust of wind lifts ");
					puts("you up.");
				}
				if (!moveplayer(location[position].up, AHEAD))
					return (-1);
			} else {
				puts("There is no way up.");
				return (-1);
			}
			lflag = 0;
			break;

		case DOWN:
			if (!moveplayer(location[position].down, AHEAD))
				return (-1);
			lflag = 0;
			break;

		case LEFT:
			if (!moveplayer(left, LEFT))
				return (-1);
			lflag = 0;
			break;

		case RIGHT:
			if (!moveplayer(right, RIGHT))
				return (-1);
			lflag = 0;
			break;

		case AHEAD:
			if (!moveplayer(ahead, AHEAD))
				return (-1);
			lflag = 0;
			break;

		case BACK:
			if (!moveplayer(back, BACK))
				return (-1);
			lflag = 0;
			break;

		case SHOOT:
			if (wordnumber < wordcount && 
			    wordvalue[wordnumber + 1] == EVERYTHING) {
				int things;
				things = 0;
				for (n = 0; n < NUMOFOBJECTS; n++)
					if (testbit(location[position].objects,
					    n) && objsht[n]) {
						things++;
						wordvalue[wordnumber + 1] = n;
						wordnumber = shoot();
					}
				if (!things)
					puts("Nothing to shoot at!");
				wordnumber++;
				wordnumber++;
			} else
				shoot();
			break;

		case TAKE:
			if (wordnumber < wordcount && 
			    wordvalue[wordnumber + 1] == EVERYTHING) {
				int things;
				things = 0;
				for (n = 0; n < NUMOFOBJECTS; n++)
					if (testbit(location[position].objects,
					    n) && objsht[n]) {
						things++;
						wordvalue[wordnumber + 1] = n;
						/* Some objects (type NOUNS)
						 * have special treatment in
						 * take().  For these we
						 * must set the type to NOUNS.
						 * However for SWORD and BODY
						 * all it does is find which
						 * of many objects is meant,
						 * so we need do nothing here.
						 * BATHGOD must become
						 * NORMGOD as well.  NOUNS
						 * with no special case
						 * must be included here to
						 * get the right error.  DOOR
						 * cannot occur as an object
						 * so need not be included.  */
						switch(n) {
						case BATHGOD:
							wordvalue[wordnumber + 1] = NORMGOD;
							/* FALLTHROUGH */
						case NORMGOD:
						case AMULET:
						case MEDALION:
						case TALISMAN:
						case MAN:
						case TIMER:
						case NATIVE:
							wordtype[wordnumber + 1] = NOUNS;
							break;
						default:
							wordtype[wordnumber + 1] = OBJECT;
						}
						wordnumber = take(location[position].objects);
					}
				wordnumber++;
				wordnumber++;
				if (!things)
					puts("Nothing to take!");
			} else
				take(location[position].objects);
			break;

		case DROP:
			if (wordnumber < wordcount && 
			    wordvalue[wordnumber + 1] == EVERYTHING) {
				int things;
				things = 0;
				for (n = 0; n < NUMOFOBJECTS; n++)
					if (testbit(inven, n)) {
						things++;
						wordvalue[wordnumber + 1] = n;
						wordnumber = drop("Dropped");
					}
				wordnumber++;
				wordnumber++;
				if (!things)
					puts("Nothing to drop!");
			} else
				drop("Dropped");
			break;

		case KICK:
		case THROW:
			if (wordnumber < wordcount && 
			    wordvalue[wordnumber + 1] == EVERYTHING) {
				int things, wv;
				things = 0;
				wv = wordvalue[wordnumber];
				for (n = 0; n < NUMOFOBJECTS; n++)
					if (testbit(inven, n) ||
					    (testbit(location[position].objects, n) && objsht[n])) {
						things++;
						wordvalue[wordnumber + 1] = n;
						wordnumber = throw(wordvalue[wordnumber] == KICK ? "Kicked" : "Thrown");
					}
				wordnumber += 2;
				if (!things)
					printf("Nothing to %s!\n", 
					    wv == KICK ? "kick" : "throw");
			} else
				throw(wordvalue[wordnumber] == 
				    KICK ? "Kicked" : "Thrown");
			break;

		case TAKEOFF:
			if (wordnumber < wordcount && 
			    wordvalue[wordnumber + 1] == EVERYTHING) {
				int things;
				things = 0;
				for (n = 0; n < NUMOFOBJECTS; n++)
					if (testbit(wear, n)) {
						things++;
						wordvalue[wordnumber + 1] = n;
						wordnumber = takeoff();
					}
				wordnumber += 2;
				if (!things)
					puts("Nothing to take off!");
			} else
				takeoff();
			break;

		case DRAW:
			if (wordnumber < wordcount && 
			    wordvalue[wordnumber + 1] == EVERYTHING) {
				int things;
				things = 0;
				for (n = 0; n < NUMOFOBJECTS; n++)
					if (testbit(wear, n)) {
						things++;
						wordvalue[wordnumber + 1] = n;
						wordnumber = draw();
					}
				wordnumber += 2;
				if (!things)
					puts("Nothing to draw!");
			} else
				draw();
			break;

		case PUTON:
			if (wordnumber < wordcount && 
			    wordvalue[wordnumber + 1] == EVERYTHING) {
				int things;
				things = 0;
				for (n = 0; n < NUMOFOBJECTS; n++)
					if (testbit(location[position].objects,
					    n) && objsht[n]) {
						things++;
						wordvalue[wordnumber + 1] = n;
						wordnumber = puton();
					}
				wordnumber += 2;
				if (!things)
					puts("Nothing to put on!");
			} else
				puton();
			break;

		case WEARIT:
			if (wordnumber < wordcount && 
			    wordvalue[wordnumber + 1] == EVERYTHING) {
				int things;
				things = 0;
				for (n = 0; n < NUMOFOBJECTS; n++)
					if (testbit(inven, n)) {
						things++;
						wordvalue[wordnumber + 1] = n;
						wordnumber = wearit();
					}
				wordnumber += 2;
				if (!things)
					puts("Nothing to wear!");
			} else
				wearit();
			break;

		case EAT:
			if (wordnumber < wordcount && 
			    wordvalue[wordnumber + 1] == EVERYTHING) {
				int things;
				things = 0;
				for (n = 0; n < NUMOFOBJECTS; n++)
					if (testbit(inven, n)) {
						things++;
						wordvalue[wordnumber + 1] = n;
						wordnumber = eat();
					}
				wordnumber += 2;
				if (!things)
					puts("Nothing to eat!");
			} else
				eat();
			break;

		case PUT:
			put();
			break;

		case INVEN:
			if (ucard(inven)) {
				puts("You are holding:\n");
				for (n = 0; n < NUMOFOBJECTS; n++)
					if (testbit(inven, n))
						printf("\t%s\n", objsht[n]);
				if (WEIGHT == 0) {
					printf("\n= %d kilogram%s",
					    carrying,
					    (carrying == 1 ? "." : "s."));
					printf(" (can't lift any weight%s)\n",
					    (carrying ? 
					    " or move with what you have" : 
					    ""));
				} else
					printf("\n= %d kilogram%s (%d%%)\n",
					    carrying,
					    (carrying == 1 ? "." : "s."),
					    carrying * 100 / WEIGHT);
				if (CUMBER == 0) {
					printf("Your arms can't pick ");
					printf("anything up.\n");
				} else
					printf("Your arms are %d%% full.\n",
					    encumber * 100 / CUMBER);
			} else
				puts("You aren't carrying anything.");

			if (ucard(wear)) {
				puts("\nYou are wearing:\n");
				for (n = 0; n < NUMOFOBJECTS; n++)
					if (testbit(wear, n))
						printf("\t%s\n", objsht[n]);
			} else
				puts("\nYou are stark naked.");
			if (card(injuries, NUMOFINJURIES)) {
				puts("\nYou have suffered:\n");
				for (n = 0; n < NUMOFINJURIES; n++)
					if (injuries[n])
						printf("\t%s\n", ouch[n]);
				printf("\nYou can still carry up to ");
				printf("%d kilogram%s\n", WEIGHT, 
				    (WEIGHT == 1 ? "." : "s."));
			} else
				puts("\nYou are in perfect health.");
			wordnumber++;
			break;

		case USE:
			lflag = use();
			break;

		case OPEN:
			if (wordnumber < wordcount && 
			    wordvalue[wordnumber + 1] == EVERYTHING) {
				int things;
				things = 0;
				for (n = 0; n < NUMOFOBJECTS; n++)
					if (testbit(inven, n)) {
						things++;
						wordvalue[wordnumber + 1] = n;
						dooropen();
					}
				wordnumber += 2;
				if (!things)
					puts("Nothing to open!");
			} else
				dooropen();
			break;

		case LOOK:
			if (!notes[CANTSEE] || testbit(inven, LAMPON) ||
			    testbit(location[position].objects, LAMPON)
			    || matchlight) {
				beenthere[position] = 2;
				writedes();
				printobjs();
				if (matchlight) {
					puts("\nYour match splutters out.");
					matchlight = 0;
				}
			} else
				puts("I can't see anything.");
			return (-1);
			break;

		case SU:
			if (wiz || tempwiz) {
				printf("\nRoom (was %d) = ", position);
				fgets(buffer, 10, stdin);
				if (*buffer != '\n')
					sscanf(buffer, "%d", &position);
				printf("Time (was %d) = ", ourtime);
				fgets(buffer, 10, stdin);
				if (*buffer != '\n')
					sscanf(buffer, "%d", &ourtime);
				printf("Fuel (was %d) = ", fuel);
				fgets(buffer, 10, stdin);
				if (*buffer != '\n')
					sscanf(buffer, "%d", &fuel);
				printf("Torps (was %d) = ", torps);
				fgets(buffer, 10, stdin);
				if (*buffer != '\n')
					sscanf(buffer, "%d", &torps);
				printf("CUMBER (was %d) = ", CUMBER);
				fgets(buffer, 10, stdin);
				if (*buffer != '\n')
					sscanf(buffer, "%d", &CUMBER);
				printf("WEIGHT (was %d) = ", WEIGHT);
				fgets(buffer, 10, stdin);
				if (*buffer != '\n')
					sscanf(buffer, "%d", &WEIGHT);
				printf("Clock (was %d) = ", ourclock);
				fgets(buffer, 10, stdin);
				if (*buffer != '\n')
					sscanf(buffer, "%d", &ourclock);
				printf("Wizard (was %d, %d) = ", wiz, tempwiz);
				fgets(buffer, 10, stdin);
				if (*buffer != '\n') {
					sscanf(buffer, "%d", &junk);
					if (!junk)
						tempwiz = wiz = 0;
				}
				printf("\nDONE.\n");
				return (0);
			} else
				puts("You aren't a wizard.");
			break;

		case SCORE:
			printf("\tPLEASURE\tPOWER\t\tEGO\n");
			printf("\t%3d\t\t%3d\t\t%3d\n\n", pleasure, power, ego);
			printf("This gives you the rating of ");
			printf("%s in %d turns.\n", rate(), ourtime);
			printf("You have visited %d out of %d rooms ",
			    card(beenthere, NUMOFROOMS), NUMOFROOMS);
			printf("this run (%d%%).\n", 
			    card(beenthere, NUMOFROOMS) * 100 / NUMOFROOMS);
			break;

		case KNIFE:
		case KILL:
			murder();
			break;

		case UNDRESS:
		case RAVAGE:
			ravage();
			break;

		case SAVE:
			printf("\nSave file name (default %s): ",
			       DEFAULT_SAVE_FILE);
			filename = fgetln(stdin, &filename_len);
			if (filename_len == 0
			    || (filename_len == 1 && filename[0] == '\n'))
				rfilename = save_file_name(DEFAULT_SAVE_FILE,
				    strlen(DEFAULT_SAVE_FILE));
			else {
				if (filename[filename_len - 1] == '\n')
					filename_len--;
				rfilename = save_file_name(filename,
							   filename_len);
			}
			save(rfilename);
			free(rfilename);
			break;

		case VERBOSE:
			verbose = 1;
			printf("[Maximum verbosity]\n");
			break;

		case BRIEF:
			verbose = 0;
			printf("[Standard verbosity]\n");
			break;

		case FOLLOW:
			lflag = follow();
			break;

		case GIVE:
			give();
			break;

		case KISS:
			kiss();
			break;

		case LOVE:
			love();
			break;

		case RIDE:
			lflag = ride();
			break;

		case DRIVE:
			lflag = drive();
			break;

		case LIGHT:
			light();
			break;

		case LAUNCH:
			if (!launch())
				return (-1);
			else
				lflag = 0;
			break;

		case LANDIT:
			if (!land())
				return (-1);
			else
				lflag = 0;
			break;

		case TIME:
			chime();
			break;

		case SLEEP:
			zzz();
			break;

		case DIG:
			dig();
			break;

		case JUMP:
			lflag = jump();
			break;

		case BURY:
			bury();
			break;

		case SWIM:
			puts("Surf's up!");
			break;

		case DRINK:
			drink();
			break;

		case QUIT:
			die();

		default:
			puts("How's that?");
			return (-1);
			break;

		}
		if (wordnumber < wordcount && *words[wordnumber++] == ',')
			continue;
		else
			return (lflag);
	}
	return (lflag);
}
