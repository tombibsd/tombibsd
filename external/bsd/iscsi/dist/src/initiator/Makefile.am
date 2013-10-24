## $NetBSD$

AM_CFLAGS		= $(WARNCFLAGS)

bin_PROGRAMS		= iscsi-initiator

iscsi_initiator_SOURCES	= iscsi-initiator.c libkmod.c virtdir.c

iscsi_initiator_CPPFLAGS= -I$(top_srcdir)/include

iscsi_initiator_LDADD	= ../lib/libiscsi.la -lrefuse

man8_MANS		= iscsi-initiator.8

dist_man_MANS		= iscsi-initiator.8
