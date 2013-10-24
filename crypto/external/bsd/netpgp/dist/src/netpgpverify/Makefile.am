## $NetBSD$

AM_CFLAGS		= $(WARNCFLAGS)

bin_PROGRAMS		= netpgpverify

netpgpverify_SOURCES	= verify.c

netpgpverify_CPPFLAGS	= -I$(top_srcdir)/include

netpgpverify_LDADD	= ../lib/libnetpgp.la ../libmj/libmj.la

dist_man_MANS		= netpgpverify.1
