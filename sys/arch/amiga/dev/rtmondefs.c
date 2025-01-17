/*	$NetBSD$ */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

static struct MonDef monitor_defs[] = {
  /*       FQ, FLG,   MW,   MH
    HBS, HSS, HSE, HBE,  HT, VBS, VSS, VSE, VBE,  VT
    Depth,           PAL,  TX,  TY,    XY, FX, FY,     FontData, FLo, FHi*/

 /* 80x50 (640x400) 31.5kHz 60Hz */
  {  28322000,  16,  640,  400,
     80,  91,  99, 110, 110, 401, 445, 504, 522, 522,
        4, NCRStdPalette,  80,  50,  4000,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 80x50 (640x400) 35.0kHz 72Hz */
  {  63000000,  16,  640,  400,
     80,  89,  98, 110, 110, 401, 411, 483, 483, 483,
        4, NCRStdPalette,  80,  50,  4000,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 80x50 (640x400) 37.1kHz 69Hz */
  {  65000000,  16,  640,  400,
     80,  88,  94, 107, 107, 401, 411, 530, 530, 530,
        4, NCRStdPalette,  80,  50,  4000,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 100x75 (800x600) 31.5kHz 50Hz */
  {  80000000,  16,  800,  600,
    100, 113, 148, 156, 156, 601, 602, 612, 628, 628,
        4, NCRStdPalette, 100,  75,  7500,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 100x75 (800x600) 35.0kHz 57Hz */
  {  75000000,  16,  800,  600,
    100, 110, 120, 132, 131, 601, 602, 603, 603, 603,
        4, NCRStdPalette, 100,  75,  7500,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 100x75 (800x600) 37.2kHz 60Hz */
  {  80000000,  16,  800,  600,
    100, 110, 121, 132, 132, 601, 603, 613, 613, 613,
        4, NCRStdPalette, 100,  75,  7500,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 100x75 (800x600) 57.1kHz 90Hz */
  {  56644000,  16,  800,  600,
    100, 106, 107, 122, 121, 601, 607, 617, 629, 629,
        4, NCRStdPalette, 100,  75,  7500,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x96 (1024x768) 31.5kHz 78Hz interlace */
  {  80000000,  22, 1024,  768,
    128, 134, 140, 156, 156, 385, 385, 386, 401, 401,
        4, NCRStdPalette, 128,  96, 12288,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x96 (1024x768) 35.0kHz 86Hz interlace */
  {  90000000,  22, 1024,  768,
    128, 135, 143, 158, 158, 385, 385, 386, 401, 401,
        4, NCRStdPalette, 128,  96, 12288,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x96 (1024x768) 38.1kHz 89Hz interlace */
  {  50000000,  18, 1024,  768,
    128, 135, 146, 162, 161, 385, 399, 400, 423, 423,
        4, NCRStdPalette, 128,  96, 12288,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x96 (1024x768) 57.0kHz 71Hz */
  {  75000000,  16, 1024,  768,
    128, 129, 141, 162, 162, 769, 770, 771, 798, 798,
        4, NCRStdPalette, 128,  96, 12288,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x96 (1024x768) 71.2kHz 85Hz */
  {  90000000,  16, 1024,  768,
    128, 136, 141, 156, 155, 769, 793, 806, 832, 832,
        4, NCRStdPalette, 128,  96, 12288,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 80x100 (640x800) 31.9kHz 75Hz interlace */
  {  28322000,  18,  640,  800,
     80,  81,  88, 109, 108, 401, 402, 409, 418, 418,
        4, NCRStdPalette,  80, 100,  8000,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 80x100 (640x800) 35.5kHz 84Hz interlace */
  {  63000000,  22,  640,  800,
     80,  81,  88, 109, 108, 401, 402, 409, 418, 418,
        4, NCRStdPalette,  80, 100,  8000,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 80x50 (640x400) 36.6kHz 87Hz */
  {  65000000,  16,  640,  400,
     80,  88,  95, 109, 108, 401, 402, 409, 418, 418,
        4, NCRStdPalette,  80,  50,  4000,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 96x64 (768x512) 36.9kHz 68Hz */
  {  36000000,  16,  768,  512,
     96, 103, 111, 120, 119, 513, 521, 529, 535, 535,
        4, NCRStdPalette,  96,  64,  6144,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 96x64 (768x512) 38.4kHz 71Hz */
  {  75000000,  16,  768,  512,
     96, 103, 111, 120, 119, 513, 521, 529, 535, 535,
        4, NCRStdPalette,  96,  64,  6144,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 96x64 (768x512) 41.0kHz 76Hz */
  {  80000000,  16,  768,  512,
     96, 103, 111, 120, 119, 513, 521, 529, 535, 535,
        4, NCRStdPalette,  96,  64,  6144,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 96x64 (768x512) 46.0kHz 85Hz */
  {  44900000,  16,  768,  512,
     96, 103, 110, 120, 119, 513, 522, 530, 535, 535,
        4, NCRStdPalette,  96,  64,  6144,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 96x64 (768x512) 46.1kHz 85Hz */
  {  90000000,  16,  768,  512,
     96, 103, 110, 120, 119, 513, 522, 530, 535, 535,
        4, NCRStdPalette,  96,  64,  6144,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 100x75 (800x600) 47.3kHz 75Hz */
  {  50000000,  16,  800,  600,
    100, 108, 116, 130, 129, 601, 602, 612, 628, 628,
        4, NCRStdPalette, 100,  75,  7500,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 100x75 (800x600) 53.6kHz 85Hz */
  {  56644000,  16,  800,  600,
    100, 109, 118, 130, 129, 601, 602, 612, 628, 628,
        4, NCRStdPalette, 100,  75,  7500,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x96 (1024x768) 48.5kHz 60Hz */
  {  63000000,  16, 1024,  768,
    128, 129, 139, 160, 160, 769, 774, 787, 805, 805,
        4, NCRStdPalette, 128,  96, 12288,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x96 (1024x768) 50.0kHz 61Hz */
  {  65000000,  16, 1024,  768,
    128, 129, 139, 160, 160, 769, 774, 787, 805, 805,
        4, NCRStdPalette, 128,  96, 12288,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x96 (1024x768) 55.4kHz 68Hz */
  {  72000000,  16, 1024,  768,
    128, 137, 147, 160, 160, 769, 785, 798, 805, 805,
        4, NCRStdPalette, 128,  96, 12288,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x96 (1024x768) 57.7kHz 71Hz */
  {  75000000,  16, 1024,  768,
    128, 128, 138, 160, 160, 769, 780, 793, 805, 805,
        4, NCRStdPalette, 128,  96, 12288,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x96 (1024x768) 61.5kHz 76Hz */
  {  80000000,  16, 1024,  768,
    128, 131, 141, 160, 160, 769, 780, 793, 805, 805,
        4, NCRStdPalette, 128,  96, 12288,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x96 (1024x768) 69.2kHz 85Hz */
  {  90000000,  16, 1024,  768,
    128, 138, 148, 160, 160, 769, 780, 793, 805, 805,
        4, NCRStdPalette, 128,  96, 12288,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x128 (1024x1024) 71.8kHz 66Hz ***EXCEEDS CHIP LIMIT!!!*** */
  { 100000000,  16, 1024, 1024,
    128, 129, 140, 172, 171, 1025, 1026, 1043, 1073, 1073,
        4, NCRStdPalette, 128, 128, 16384,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x128 (1024x1024) 79.0kHz 73Hz ***EXCEEDS CHIP LIMIT!!!*** */
  { 110000000,  16, 1024, 1024,
    128, 129, 140, 172, 171, 1025, 1026, 1043, 1073, 1073,
        4, NCRStdPalette, 128, 128, 16384,  8,  8,  kernel_font_8x8,  32, 255 },

 /* 128x128 (1024x1024) 86.2kHz 80Hz ***EXCEEDS CHIP LIMIT!!!*** */
  { 120000000,  16, 1024, 1024,
    128, 129, 140, 172, 171, 1025, 1026, 1043, 1073, 1073,
        4, NCRStdPalette, 128, 128, 16384,  8,  8,  kernel_font_8x8,  32, 255 },

};

static const char *monitor_descr[] = {
  "80x50 (640x400) 31.5kHz 60Hz",
  "80x50 (640x400) 35.0kHz 72Hz",
  "80x50 (640x400) 37.1kHz 69Hz",
  "100x75 (800x600) 31.5kHz 50Hz",
  "100x75 (800x600) 35.0kHz 57Hz",
  "100x75 (800x600) 37.2kHz 60Hz",
  "100x75 (800x600) 57.1kHz 90Hz",
  "128x96 (1024x768) 31.5kHz 78Hz interlace",
  "128x96 (1024x768) 35.0kHz 86Hz interlace",
  "128x96 (1024x768) 38.1kHz 89Hz interlace",
  "128x96 (1024x768) 57.0kHz 71Hz",
  "128x96 (1024x768) 71.2kHz 85Hz",
  "80x100 (640x800) 31.9kHz 75Hz interlace",
  "80x100 (640x800) 35.5kHz 84Hz interlace",
  "80x50 (640x400) 36.6kHz 87Hz",
  "96x64 (768x512) 36.9kHz 68Hz",
  "96x64 (768x512) 38.4kHz 71Hz",
  "96x64 (768x512) 41.0kHz 76Hz",
  "96x64 (768x512) 46.0kHz 85Hz",
  "96x64 (768x512) 46.1kHz 85Hz",
  "100x75 (800x600) 47.3kHz 75Hz",
  "100x75 (800x600) 53.6kHz 85Hz",
  "128x96 (1024x768) 48.5kHz 60Hz",
  "128x96 (1024x768) 50.0kHz 61Hz",
  "128x96 (1024x768) 55.4kHz 68Hz",
  "128x96 (1024x768) 57.7kHz 71Hz",
  "128x96 (1024x768) 61.5kHz 76Hz",
  "128x96 (1024x768) 69.2kHz 85Hz",
  "128x128 (1024x1024) 71.8kHz 66Hz ***EXCEEDS CHIP LIMIT!!!***",
  "128x128 (1024x1024) 79.0kHz 73Hz ***EXCEEDS CHIP LIMIT!!!***",
  "128x128 (1024x1024) 86.2kHz 80Hz ***EXCEEDS CHIP LIMIT!!!***",
};

