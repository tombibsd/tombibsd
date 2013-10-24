/*	$NetBSD$ */

const char *intprt(char *, size_t, uint64_t, int, int);
const char *timeprt(char *, size_t, time_t, time_t);
const char *timepprt(char *, size_t, time_t, int);
int timeprd(const char *, time_t *);
int intrd(char *str, uint64_t *val, u_int);
int alldigits(const char *);
