/*	$NetBSD$	*/

/* In MEMC space: */
#define OAK_NCR5380_OFFSET	0x0000
#define OAK_PDMA_OFFSET		0x0200

/* Registers in the PDMA engine (in bus_size_t units) */
#define OAK_PDMA_WRITE		0x00 /* This is a guess! */
#define OAK_PDMA_READ		0x08
#define OAK_PDMA_STATUS		0x10
