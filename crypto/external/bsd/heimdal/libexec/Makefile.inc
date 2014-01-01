# $NetBSD$

BINDIR=/usr/libexec

LDADD+= -lheimntlm -lkrb5 -lhx509 -lheimbase
LDADD+= -lasn1 -lcom_err -lroken ${LIBVERS}
LDADD+= -lwind
LDADD+= -lcrypto -lcrypt

DPADD+= ${LIBKRB5} ${LIBHX509}
DPADD+= ${LIBASN1} ${LIBCOM_ERR} ${LIBROKEN} ${LIBVERS}
DPADD+= ${LIBHEIMBASE} ${LIBHEIMNTLM} ${LIBWIND}
DPADD+= ${LIBCRYPTO} ${LIBCRYPT}
