# $NetBSD$

BINDIR=/usr/bin

LDADD+= -lkrb5 -lhx509 -lasn1 -lroken -lcom_err -lwind
LDADD+= -lheimbase ${LIBVERS}
LDADD+= -lcrypto -lcrypt

DPADD+= ${LIBKRB5} ${LIBHX509} ${LIBASN1} ${LIBROKEN} ${LIBCOM_ERR} ${LIBWIND}
DPADD+= ${LIBHEIMBASE} ${LIBVERS}
DPADD+= ${LIBCRYPTO} ${LIBCRYPT}
