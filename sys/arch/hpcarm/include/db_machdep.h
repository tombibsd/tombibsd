/* $NetBSD$ */

#include <arm/db_machdep.h>

/* hpcarm uses ELF for kernel */
#define DB_ELF_SYMBOLS
#define DB_ELFSIZE      32
