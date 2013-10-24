/* $NetBSD$ */

#if defined(_STANDALONE)
#ifdef __thumb__
#include "strcpy_thumb.S"
#else
#include "strcpy_naive.S"
#endif
#else
#include "strcpy_arm.S"
#endif
