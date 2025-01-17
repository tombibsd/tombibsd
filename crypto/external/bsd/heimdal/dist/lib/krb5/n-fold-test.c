/*	$NetBSD$	*/

/*
 * Copyright (c) 1999 - 2001 Kungliga Tekniska Högskolan
 * (Royal Institute of Technology, Stockholm, Sweden).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of KTH nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY KTH AND ITS CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL KTH OR ITS CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "krb5_locl.h"

enum { MAXSIZE = 24 };

static struct testcase {
    const char *str;
    unsigned n;
    unsigned char res[MAXSIZE];
} tests[] = {
    {"012345",		8,
     {0xbe, 0x07, 0x26, 0x31, 0x27, 0x6b, 0x19, 0x55}
    },
    {"basch",		24,
     {0x1a, 0xab, 0x6b, 0x42, 0x96, 0x4b, 0x98, 0xb2, 0x1f, 0x8c, 0xde,
      0x2d, 0x24, 0x48, 0xba, 0x34, 0x55, 0xd7, 0x86, 0x2c, 0x97, 0x31,
      0x64, 0x3f}
    },
    {"eichin",		24,
     {0x65, 0x69, 0x63, 0x68, 0x69, 0x6e, 0x4b, 0x73, 0x2b, 0x4b,
      0x1b, 0x43, 0xda, 0x1a, 0x5b, 0x99, 0x5a, 0x58, 0xd2, 0xc6, 0xd0,
      0xd2, 0xdc, 0xca}
    },
    {"sommerfeld",	24,
     {0x2f, 0x7a, 0x98, 0x55, 0x7c, 0x6e, 0xe4, 0xab, 0xad, 0xf4,
      0xe7, 0x11, 0x92, 0xdd, 0x44, 0x2b, 0xd4, 0xff, 0x53, 0x25, 0xa5,
      0xde, 0xf7, 0x5c}
    },
    {"MASSACHVSETTS INSTITVTE OF TECHNOLOGY", 24,
     {0xdb, 0x3b, 0x0d, 0x8f, 0x0b, 0x06, 0x1e, 0x60, 0x32, 0x82,
      0xb3, 0x08, 0xa5, 0x08, 0x41, 0x22, 0x9a, 0xd7, 0x98, 0xfa, 0xb9,
      0x54, 0x0c, 0x1b}
    },
    {"assar@NADA.KTH.SE", 24,
     {0x5c, 0x06, 0xc3, 0x4d, 0x2c, 0x89, 0x05, 0xbe, 0x7a, 0x51,
      0x83, 0x6c, 0xd6, 0xf8, 0x1c, 0x4b, 0x7a, 0x93, 0x49, 0x16, 0x5a,
      0xb3, 0xfa, 0xa9}
    },
    {"testKRBTEST.MIT.EDUtestkey", 24,
     {0x50, 0x2c, 0xf8, 0x29, 0x78, 0xe5, 0xfb, 0x1a, 0x29, 0x06,
      0xbd, 0x22, 0x28, 0x91, 0x56, 0xc0, 0x06, 0xa0, 0xdc, 0xf5, 0xb6,
      0xc2, 0xda, 0x6c}
    },
    {"password", 7,
     {0x78, 0xa0, 0x7b, 0x6c, 0xaf, 0x85, 0xfa}
    },
    {"Rough Consensus, and Running Code", 8,
     {0xbb, 0x6e, 0xd3, 0x08, 0x70, 0xb7, 0xf0, 0xe0},
    },
    {"password", 21,
     {0x59, 0xe4, 0xa8, 0xca, 0x7c, 0x03, 0x85, 0xc3, 0xc3, 0x7b, 0x3f,
      0x6d, 0x20, 0x00, 0x24, 0x7c, 0xb6, 0xe6, 0xbd, 0x5b, 0x3e},
    },
    {"MASSACHVSETTS INSTITVTE OF TECHNOLOGY", 24,
     {0xdb, 0x3b, 0x0d, 0x8f, 0x0b, 0x06, 0x1e, 0x60, 0x32, 0x82, 0xb3,
      0x08, 0xa5, 0x08, 0x41, 0x22, 0x9a, 0xd7, 0x98, 0xfa, 0xb9, 0x54,
      0x0c, 0x1b}
    },
    {NULL, 0}
};

int
main(int argc, char **argv)
{
    unsigned char data[MAXSIZE];
    struct testcase *t;
    int ret = 0;

    for (t = tests; t->str; ++t) {
	int i;

	ret = _krb5_n_fold (t->str, strlen(t->str), data, t->n);
	if (ret)
	    errx(1, "out of memory");
	if (memcmp (data, t->res, t->n) != 0) {
	    printf ("n-fold(\"%s\", %d) failed\n", t->str, t->n);
	    printf ("should be: ");
	    for (i = 0; i < t->n; ++i)
		printf ("%02x", t->res[i]);
	    printf ("\nresult was: ");
	    for (i = 0; i < t->n; ++i)
		printf ("%02x", data[i]);
	    printf ("\n");
	    ret = 1;
	}
    }
    return ret;
}
