/*	$NetBSD$	*/

/* Implementation of the dcgettext(3) function.
   Copyright (C) 1995-1999, 2000, 2001 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "gettextP.h"
#ifdef _LIBC
# include <libintl.h>
#else
# include "libgnuintl.h"
#endif

/* @@ end of prolog @@ */

/* Names for the libintl functions are a problem.  They must not clash
   with existing names and they should follow ANSI C.  But this source
   code is also used in GNU C Library where the names have a __
   prefix.  So we have to make a difference here.  */
#ifdef _LIBC
# define DCGETTEXT __dcgettext
# define DCIGETTEXT __dcigettext
#else
# define DCGETTEXT dcgettext__
# define DCIGETTEXT dcigettext__
#endif

/* Look up MSGID in the DOMAINNAME message catalog for the current CATEGORY
   locale.  */
char *
DCGETTEXT (domainname, msgid, category)
     const char *domainname;
     const char *msgid;
     int category;
{
  return DCIGETTEXT (domainname, msgid, NULL, 0, 0, category);
}

#ifdef _LIBC
/* Alias for function name in GNU C Library.  */
weak_alias (__dcgettext, dcgettext);
#endif
