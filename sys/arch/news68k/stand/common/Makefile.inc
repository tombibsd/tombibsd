# $NetBSD$

# MD libsa files shared among each SA program

.PATH.c: ${SA_EXTRADIR}
.PATH.S: ${SA_EXTRADIR}

SRCS+=	getchar.c putchar.c romcalls.S
