/*	$NetBSD$	*/

#include <arm/db_machdep.h>

/* zaurus uses ELF for kernel */
#define DB_ELF_SYMBOLS
#define DB_ELFSIZE      32
