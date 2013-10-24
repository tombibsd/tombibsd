## $NetBSD$

AM_CFLAGS		= $(WARNCFLAGS)

bin_PROGRAMS		= netpgpkeys

netpgpkeys_SOURCES	= netpgpkeys.c

netpgpkeys_CPPFLAGS	= -I$(top_srcdir)/include -I../libmj

netpgpkeys_LDADD	= ../lib/libnetpgp.la ../libmj/libmj.la

dist_man_MANS		= netpgpkeys.1
