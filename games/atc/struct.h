/*	$NetBSD$	*/

/*-
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ed James.
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
 *
 *	@(#)struct.h	8.1 (Berkeley) 5/31/93
 */

/*
 * Copyright (c) 1987 by Ed James, UC Berkeley.  All rights reserved.
 *
 * Copy permission is hereby granted provided that this notice is
 * retained on all partial or complete copies.
 *
 * For more info on this and all of my stuff, mail edjames@berkeley.edu.
 */

#include <stdbool.h>

typedef struct {
	int	x, y;
	int	dir;	/* used only sometimes */
} SCREEN_POS;

typedef struct {
	SCREEN_POS	p1, p2;
} LINE;

typedef SCREEN_POS	EXIT;
typedef SCREEN_POS	BEACON;
typedef SCREEN_POS	AIRPORT;

typedef struct {
	int	width, height;
	int	update_secs;
	int	newplane_time;
	unsigned num_exits;
	unsigned num_lines;
	unsigned num_beacons;
	unsigned num_airports;
	EXIT	*exit;
	LINE	*line;
	BEACON	*beacon;
	AIRPORT	*airport;
} C_SCREEN;

enum places {
	T_NODEST = 0,
	T_BEACON = 1,
	T_EXIT = 2,
	T_AIRPORT = 3
};

typedef struct plane {
	struct plane	*next, *prev;
	int		status;
	int		plane_no;
	int		plane_type;
	unsigned orig_no;
	enum places orig_type;
	unsigned dest_no;
	enum places dest_type;
	int		altitude;
	int		new_altitude;
	int		dir;
	int		new_dir;
	int		fuel;
	int		xpos;
	int		ypos;
	bool delayd;
	unsigned delayd_no;
} PLANE;

typedef struct {
	PLANE	*head, *tail;
} LIST;

typedef struct {
	char	name[33];
	char	host[256];
	char	game[256];
	int	planes;
	int	time;
	int	real_time;
} SCORE;

#define SCORE_SCANF_FMT	"%9s %255s %255s %d %d %d"
#define SCORE_NAME_LEN 33
#define SCORE_GAME_LEN 256

typedef struct displacement {
	int	dx;
	int	dy;
} DISPLACEMENT;
