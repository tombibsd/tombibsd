/*	$NetBSD$ */

extern const char *qfextension[MAXQUOTAS];
extern const char *qfname;
struct fstab;
int hasquota(char *, size_t, struct fstab *, int);
int oneof(const char *, char *[], int);
