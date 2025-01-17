/*	$NetBSD$	*/

/*
 * Copyright (c) 2001, 2002 Wasabi Systems, Inc.
 * All rights reserved.
 *
 * Written by Frank van der Linden and Jason R. Thorpe for
 * Wasabi Systems, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed for the NetBSD Project by
 *	Wasabi Systems, Inc.
 * 4. The name of Wasabi Systems, Inc. may not be used to endorse
 *    or promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY WASABI SYSTEMS, INC. ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL WASABI SYSTEMS, INC
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__RCSID("$NetBSD$");

#include <sys/param.h>
#include <pmc.h>

#include <machine/specialreg.h>

#include "pmc_private.h"

static const struct pmc_event i586_pmc_evids[] = {
	{ "tlb-data-miss",		PMC5_DATA_TLB_MISS },
	{ "tlb-ins-miss",		PMC5_INST_TLB_MISS },
	{ "l1cache-ins-miss",		PMC5_INST_CACHE_MISS },
	{ "l1cache-data-miss",		PMC5_DATA_RW_MISS },
	{ "l1cache-data-miss-read",	PMC5_DATA_READ_MISS },
	{ "l1cache-data-miss-write",	PMC5_DATA_WRITE_MISS },
	{ "l1cache-writeback",		PMC5_DATA_LINES_WBACK },
	{ "l1cache-writeback-hit",	PMC5_WRITE_M_E },
	{ "l2cache-data-snoop",		PMC5_DATA_CACHE_SNOOP },
	{ "l2cache-data-snoop-hit",	PMC5_DATA_CACHE_SNOOP_HIT },
	{ "mem-read",			PMC5_DATA_READ },
	{ "mem-write",			PMC5_DATA_WRITE },
	{ "mem-access",			PMC5_DATA_RW },
	{ "mem-access-both-pipes",	PMC5_MEM_ACCESS_BOTH_PIPES },
	{ "mem-bank-conflicts",		PMC5_BANK_CONFLICTS },
	{ "mem-misalign-ref",		PMC5_MISALIGNED_DATA },
	{ "mem-uncached-read",		PMC5_NONCACHE_MEM_READ },
	{ "seg-load-any",		PMC5_SEGMENT_REG_LOAD },
	{ "branch",			PMC5_BRANCHES },
	{ "branch-btb-hit",		PMC5_BTB_HITS },
	{ "branch-taken",		PMC5_BRANCH_TAKEN },
	{ "ins-read",			PMC5_INST_READ },
	{ "ins-pipeline-flush",		PMC5_PIPELINE_FLUSH },
	{ "ins-executed",		PMC5_INST_EXECUTED },
	{ "ins-executed-vpipe",		PMC5_INST_EXECUTED_V_PIPE },
	{ "ins-stall-agi",		PMC5_AGI_STALL },
	{ "ins-stall-write",		PMC5_WRITE_BACKUP_STALL },
	{ "ins-stall-data",		PMC5_DATA_READ_STALL },
	{ "ins-stall-writeline",	PMC5_WRITE_E_M_STALL },
	{ "bus-utilization",		PMC5_BUS_UTILIZATION },
	{ "bus-locked",			PMC5_LOCKED_BUS },
	{ "bus-io-cycle",		PMC5_IO_CYCLE },
	{ "fpu-flops",			PMC5_FLOPS },
	{ "int-hw",			PMC5_HARDWARE_INTR },
	{ "break-match0",		PMC5_BP0_MATCH },
	{ "break-match1",		PMC5_BP1_MATCH },
	{ "break-match2",		PMC5_BP2_MATCH },
	{ "break-match3",		PMC5_BP3_MATCH },

	{ NULL,				0 },
};

static const struct pmc_event i686_pmc_evids[] = {
	{ "mem-refs",			PMC6_DATA_MEM_REFS },
	{ "l1cache-lines",		PMC6_DCU_LINES_IN },
	{ "l1cache-mlines",		PMC6_DCU_M_LINES_IN },
	{ "l1cache-mlines-evict",	PMC6_DCU_M_LINES_OUT },
	{ "l1cache-miss-wait",		PMC6_DCU_MISS_OUTSTANDING },
	{ "ins-fetch",			PMC6_IFU_IFETCH },
	{ "ins-fetch-misses",		PMC6_IFU_IFETCH_MISS },
	{ "itlb-misses",		PMC6_IFU_IFETCH_MISS },
	{ "insfetch-mem-stall",		PMC6_IFU_MEM_STALL },
	{ "insfetch-decode-stall",	PMC6_ILD_STALL },
	{ "l2cache-insfetch",
	  PMC6_L2_IFETCH | __PMC_UNIT(0x0f) },
	{ "l2cache-data-loads",
	  PMC6_L2_LD | __PMC_UNIT(0x0f) },
	{ "l2cache-data-stores",
	  PMC6_L2_ST | __PMC_UNIT(0x0f) },
	{ "l2cache-lines",		PMC6_L2_LINES_IN },
	{ "l2cache-lines-evict",	PMC6_L2_LINES_OUT },
	{ "l2cache-mlines",		PMC6_L2_M_LINES_INM },
	{ "l2cache-mlines-evict",
	  PMC6_L2_M_LINES_OUTM | __PMC_UNIT(0x0f) },
	{ "l2cache-reqs",		PMC6_L2_RQSTS },
	{ "l2cache-addr-strobes",	PMC6_L2_ADS },
	{ "l2cache-data-busy",		PMC6_L2_DBUS_BUSY },
	{ "l2cache-data-busy-read",	PMC6_L2_DBUS_BUSY_RD },
	{ "bus-drdy-clocks-self",	PMC6_BUS_DRDY_CLOCKS },
	{ "bus-drdy-clocks-any",
	  PMC6_BUS_DRDY_CLOCKS | __PMC_UNIT(0x20) },
	{ "bus-lock-clocks-self",	PMC6_BUS_LOCK_CLOCKS },
	{ "bus-lock-clocks-any",
	  PMC6_BUS_LOCK_CLOCKS | __PMC_UNIT(0x20) },
	{ "bus-req-outstanding-self",	PMC6_BUS_REQ_OUTSTANDING },
	{ "bus-req-outstanding-any",
	  PMC6_BUS_REQ_OUTSTANDING | __PMC_UNIT(0x20) },
	{ "bus-burst-reads-self",	PMC6_BUS_TRAN_BRD },
	{ "bus-burst-reads-any",
	  PMC6_BUS_TRAN_BRD | __PMC_UNIT(0x20) },
	{ "bus-read-for-ownership-self",PMC6_BUS_TRAN_RFO },
	{ "bus-read-for-ownership-any",
	  PMC6_BUS_TRAN_RFO | __PMC_UNIT(0x20) },
	{ "bus-write-back-self",	PMC6_BUS_TRANS_WB },
	{ "bus-write-back-any",
	  PMC6_BUS_TRANS_WB | __PMC_UNIT(0x20) },
	{ "bus-ins-fetches-self",	PMC6_BUS_TRAN_IFETCH },
	{ "bus-ins-fetches-any",
	  PMC6_BUS_TRAN_IFETCH | __PMC_UNIT(0x20) },
	{ "bus-invalidates-self",	PMC6_BUS_TRAN_INVAL },
	{ "bus-invalidates-any",
	  PMC6_BUS_TRAN_INVAL | __PMC_UNIT(0x20) },
	{ "bus-partial-writes-self",	PMC6_BUS_TRAN_PWR },
	{ "bus-partial-writes-any",
	  PMC6_BUS_TRAN_PWR | __PMC_UNIT(0x20) },
	{ "bus-partial-trans-self",	PMC6_BUS_TRANS_P },
	{ "bus-partial-trans-any",
	  PMC6_BUS_TRANS_P | __PMC_UNIT(0x20) },
	{ "bus-io-trans-self",		PMC6_BUS_TRANS_IO },
	{ "bus-io-trans-any",
	  PMC6_BUS_TRANS_IO | __PMC_UNIT(0x20) },
	{ "bus-deferred-trans-self",	PMC6_BUS_TRAN_DEF },
	{ "bus-deferred-trans-any",
	  PMC6_BUS_TRAN_DEF | __PMC_UNIT(0x20) },
	{ "bus-burst-trans-self",	PMC6_BUS_TRAN_BURST },
	{ "bus-burst-trans-any",
	  PMC6_BUS_TRAN_BURST | __PMC_UNIT(0x20) },
	{ "bus-total-trans-self",	PMC6_BUS_TRAN_ANY },
	{ "bus-total-trans-any",
	  PMC6_BUS_TRAN_ANY | __PMC_UNIT(0x20) },
	{ "bus-mem-trans-self",		PMC6_BUS_TRAN_MEM },
	{ "bus-mem-trans-any",
	  PMC6_BUS_TRAN_MEM | __PMC_UNIT(0x20) },
	{ "bus-recv-cycles",		PMC6_BUS_DATA_RCV },
	{ "bus-bnr-cycles",		PMC6_BUS_BNR_DRV },
	{ "bus-hit-cycles",		PMC6_BUS_HIT_DRV },
	{ "bus-hitm-cycles",		PMC6_BUS_HITM_DRDV },
	{ "bus-snoop-stall",		PMC6_BUS_SNOOP_STALL },
	{ "fpu-flops",			PMC6_FLOPS },
	{ "fpu-comp-ops",		PMC6_FP_COMP_OPS_EXE },
	{ "fpu-except-assist",		PMC6_FP_ASSIST },
	{ "fpu-mul",			PMC6_MUL },
	{ "fpu-div",			PMC6_DIV },
	{ "fpu-div-busy",		PMC6_CYCLES_DIV_BUSY },
	{ "mem-sb-blocks",		PMC6_LD_BLOCKS },
	{ "mem-sb-drains",		PMC6_SB_DRAINS },
	{ "mem-misalign-ref",		PMC6_MISALIGN_MEM_REF },
	{ "ins-pref-dispatch-nta",
	  PMC6_EMON_KNI_PREF_DISPATCHED | __PMC_UNIT(0x01) },
	{ "ins-pref-dispatch-t1",
	  PMC6_EMON_KNI_PREF_DISPATCHED | __PMC_UNIT(0x01) },
	{ "ins-pref-dispatch-t2",
	  PMC6_EMON_KNI_PREF_DISPATCHED | __PMC_UNIT(0x02) },
	{ "ins-pref-dispatch-weak",
	  PMC6_EMON_KNI_PREF_DISPATCHED | __PMC_UNIT(0x03) },
	{ "ins-pref-miss-nta",
	  PMC6_EMON_KNI_PREF_MISS | __PMC_UNIT(0x01) },
	{ "ins-pref-miss-t1",
	  PMC6_EMON_KNI_PREF_MISS | __PMC_UNIT(0x01) },
	{ "ins-pref-miss-t2",
	  PMC6_EMON_KNI_PREF_MISS | __PMC_UNIT(0x02) },
	{ "ins-pref-miss-weak",
	  PMC6_EMON_KNI_PREF_MISS | __PMC_UNIT(0x03) },
	{ "ins-retired",		PMC6_INST_RETIRED },
	{ "uops-retired",		PMC6_UOPS_RETIRED },
	{ "ins-decoded",		PMC6_INST_DECODED },
	{ "ins-stream-retired-packed-scalar",
	    PMC6_EMON_KNI_INST_RETIRED },
	{ "ins-stream-retired-scalar",
	    PMC6_EMON_KNI_INST_RETIRED | __PMC_UNIT(0x01) },
	{ "ins-stream-comp-retired-packed-scalar",
	    PMC6_EMON_KNI_COMP_INST_RET },
	{ "ins-stream-comp-retired-scalar",
	    PMC6_EMON_KNI_COMP_INST_RET | __PMC_UNIT(0x01) },
	{ "int-hw",			PMC6_HW_INT_RX },
	{ "int-cycles-masked",		PMC6_CYCLES_INT_MASKED },
	{ "int-cycles-masked-pending",
	    PMC6_CYCLES_INT_PENDING_AND_MASKED },
	{ "branch-retired",		PMC6_BR_INST_RETIRED },
	{ "branch-miss-retired",	PMC6_BR_MISS_PRED_RETIRED },
	{ "branch-taken-retired",	PMC6_BR_TAKEN_RETIRED },
	{ "branch-taken-mispred-retired", PMC6_BR_MISS_PRED_TAKEN_RET },
	{ "branch-decoded",		PMC6_BR_INST_DECODED },
	{ "branch-btb-miss",		PMC6_BTB_MISSES },
	{ "branch-bogus",		PMC6_BR_BOGUS },
	{ "branch-baclear",		PMC6_BACLEARS },
	{ "stall-resource",		PMC6_RESOURCE_STALLS },
	{ "stall-partial",		PMC6_PARTIAL_RAT_STALLS },
	{ "seg-loads",			PMC6_SEGMENT_REG_LOADS },
	{ "unhalted-cycles",		PMC6_CPU_CLK_UNHALTED },
	{ "mmx-exec",			PMC6_MMX_INSTR_EXEC },
	{ "mmx-sat-exec",		PMC6_MMX_SAT_INSTR_EXEC },
	{ "mmx-uops-exec",
	  PMC6_MMX_UOPS_EXEC | __PMC_UNIT(0x0f) },
	{ "mmx-exec-packed-mul",
	  PMC6_MMX_INSTR_TYPE_EXEC | __PMC_UNIT(0x01) },
	{ "mmx-exec-packed-shift",
	  PMC6_MMX_INSTR_TYPE_EXEC | __PMC_UNIT(0x02) },
	{ "mmx-exec-pack-ops",
	  PMC6_MMX_INSTR_TYPE_EXEC | __PMC_UNIT(0x04) },
	{ "mmx-exec-unpack-ops",
	  PMC6_MMX_INSTR_TYPE_EXEC | __PMC_UNIT(0x08) },
	{ "mmx-exec-packed-logical",
	  PMC6_MMX_INSTR_TYPE_EXEC | __PMC_UNIT(0x10) },
	{ "mmx-exec-packed-arith",
	  PMC6_MMX_INSTR_TYPE_EXEC | __PMC_UNIT(0x20) },
	{ "mmx-trans-mmx-float",	PMC6_FP_MMX_TRANS },
	{ "mmx-trans-float-mmx",
	  PMC6_FP_MMX_TRANS | __PMC_UNIT(0x01) },
	{ "mmx-assist",			PMC6_MMX_ASSIST },
	{ "mmx-retire",			PMC6_MMX_INSTR_RET },
	{ "seg-rename-stalls-es",
	  PMC6_SEG_RENAME_STALLS | __PMC_UNIT(0x01) },
	{ "seg-rename-stalls-ds",
	  PMC6_SEG_RENAME_STALLS | __PMC_UNIT(0x02) },
	{ "seg-rename-stalls-fs",
	  PMC6_SEG_RENAME_STALLS | __PMC_UNIT(0x04) },
	{ "seg-rename-stalls-gs",
	  PMC6_SEG_RENAME_STALLS | __PMC_UNIT(0x08) },
	{ "seg-rename-stalls-all",
	  PMC6_SEG_RENAME_STALLS | __PMC_UNIT(0x0f) },
	{ "seg-rename-es",
	  PMC6_SEG_REG_RENAMES | __PMC_UNIT(0x01) },
	{ "seg-rename-ds",
	  PMC6_SEG_REG_RENAMES | __PMC_UNIT(0x02) },
	{ "seg-rename-fs",
	  PMC6_SEG_REG_RENAMES | __PMC_UNIT(0x04) },
	{ "seg-rename-gs",
	  PMC6_SEG_REG_RENAMES | __PMC_UNIT(0x08) },
	{ "seg-rename-all",
	  PMC6_SEG_REG_RENAMES | __PMC_UNIT(0x0f) },
	{ "seg-rename-retire",		PMC6_RET_SEG_RENAMES },

	{ NULL,				0 },
};

static const struct pmc_event k7_pmc_evids[] = {
	{ "seg-load-all",
	  K7_SEGMENT_REG_LOADS | __PMC_UNIT(0x7f) },
	{ "seg-load-es",
	  K7_SEGMENT_REG_LOADS | __PMC_UNIT(0x01) },
	{ "seg-load-cs",
	  K7_SEGMENT_REG_LOADS | __PMC_UNIT(0x02) },
	{ "seg-load-ss",
	  K7_SEGMENT_REG_LOADS | __PMC_UNIT(0x04) },
	{ "seg-load-ds",
	  K7_SEGMENT_REG_LOADS | __PMC_UNIT(0x08) },
	{ "seg-load-fs",
	  K7_SEGMENT_REG_LOADS | __PMC_UNIT(0x10) },
	{ "seg-load-gs",
	  K7_SEGMENT_REG_LOADS | __PMC_UNIT(0x20) },
	{ "seg-load-hs",
	  K7_SEGMENT_REG_LOADS | __PMC_UNIT(0x40) },
	{ "seg-load-stall",		K7_SEGMENT_LOAD_STALL },
	{ "l1cache-access",		K7_DATA_CACHE_ACCESS },
	{ "l1cache-miss",		K7_DATA_CACHE_MISS },
	{ "l1cache-refill",
	  K7_DATA_CACHE_REFILL | __PMC_UNIT(0x1f) },
	{ "l1cache-refill-invalid",
	  K7_DATA_CACHE_REFILL | __PMC_UNIT(0x01) },
	{ "l1cache-refill-shared",
	  K7_DATA_CACHE_REFILL | __PMC_UNIT(0x02) },
	{ "l1cache-refill-exclusive",
	  K7_DATA_CACHE_REFILL | __PMC_UNIT(0x04) },
	{ "l1cache-refill-owner",
	  K7_DATA_CACHE_REFILL | __PMC_UNIT(0x08) },
	{ "l1cache-refill-modified",
	  K7_DATA_CACHE_REFILL | __PMC_UNIT(0x10) },
	{ "l1cache-load",
	  K7_DATA_CACHE_REFILL_SYSTEM | __PMC_UNIT(0x1f) },
	{ "l1cache-load-invalid",
	  K7_DATA_CACHE_REFILL_SYSTEM | __PMC_UNIT(0x01) },
	{ "l1cache-load-shared",
	  K7_DATA_CACHE_REFILL_SYSTEM | __PMC_UNIT(0x02) },
	{ "l1cache-load-exclusive",
	  K7_DATA_CACHE_REFILL_SYSTEM | __PMC_UNIT(0x04) },
	{ "l1cache-load-owner",
	  K7_DATA_CACHE_REFILL_SYSTEM | __PMC_UNIT(0x08) },
	{ "l1cache-load-modified",
	  K7_DATA_CACHE_REFILL_SYSTEM | __PMC_UNIT(0x10) },
	{ "l1cache-writeback",
	  K7_DATA_CACHE_WBACK | __PMC_UNIT(0x1f) },
	{ "l1cache-writeback-invalid",
	  K7_DATA_CACHE_WBACK | __PMC_UNIT(0x01) },
	{ "l1cache-writeback-shared",
	  K7_DATA_CACHE_WBACK | __PMC_UNIT(0x02) },
	{ "l1cache-writeback-exclusive",
	  K7_DATA_CACHE_WBACK | __PMC_UNIT(0x04) },
	{ "l1cache-writeback-owner",
	  K7_DATA_CACHE_WBACK | __PMC_UNIT(0x08) },
	{ "l1cache-writeback-modified",
	  K7_DATA_CACHE_WBACK | __PMC_UNIT(0x10) },
	{ "l2cache-access",
	  K7_L2_REQUEST | __PMC_UNIT(0xff) },
	{ "l2cache-tag-read",
	  K7_L2_REQUEST | __PMC_UNIT(0x01) },
	{ "l2cache-tag-write",
	  K7_L2_REQUEST | __PMC_UNIT(0x02) },
	{ "l2cache-inst-read",
	  K7_L2_REQUEST | __PMC_UNIT(0x04) },
	{ "l2cache-inst-load",
	  K7_L2_REQUEST | __PMC_UNIT(0x08) },
	{ "l2cache-data-store",
	  K7_L2_REQUEST | __PMC_UNIT(0x10) },
	{ "l2cache-data-loadmem",
	  K7_L2_REQUEST | __PMC_UNIT(0x20) },
	{ "l2cache-data-write",
	  K7_L2_REQUEST | __PMC_UNIT(0x40) },
	{ "l2cache-data-move",
	  K7_L2_REQUEST | __PMC_UNIT(0x80) },
	{ "l2cache-access-busy",	K7_L2_REQUEST_BUSY },
	{ "l2cache-hit",		K7_L2_DTLB_HIT },
	{ "l2cache-miss",		K7_L2_DTLB_MISS },
	{ "mem-misalign-ref",		K7_MISALIGNED_DATA_REF },
	{ "mem-access",			K7_SYSTEM_REQUEST },
	{ "mem-access-uc",
	  K7_SYSTEM_REQUEST_TYPE | __PMC_UNIT(0x01) },
	{ "mem-access-wc",
	  K7_SYSTEM_REQUEST_TYPE | __PMC_UNIT(0x04) },
	{ "mem-access-wt",
	  K7_SYSTEM_REQUEST_TYPE | __PMC_UNIT(0x10) },
	{ "mem-access-wp",
	  K7_SYSTEM_REQUEST_TYPE | __PMC_UNIT(0x20) },
	{ "mem-access-wb",
	  K7_SYSTEM_REQUEST_TYPE | __PMC_UNIT(0x40) },
	{ "ins-fetch",			K7_IFU_IFETCH },
	{ "ins-fetch-miss",		K7_IFU_IFETCH_MISS },
	{ "ins-refill-l2",		K7_IFU_REFILL_FROM_L2 },
	{ "ins-refill-mem",		K7_IFU_REFILL_FROM_SYSTEM },
	{ "ins-fetch-stall",		K7_IFU_STALL },
	{ "ins-retired",		K7_RETIRED_INST },
	{ "ins-empty",			K7_INSTRUCTION_DECODER_EMPTY },
	{ "itlb-miss-l1",		K7_ITLB_L1_MISS },
	{ "itlb-miss-l2",		K7_ITLB_L2_MISS },
	{ "ops-retired",		K7_RETIRED_OPS },
	{ "branch-retired",		K7_RETIRED_BRANCHES },
	{ "branch-miss-retired",	K7_RETIRED_BRANCH_MISPREDICTED },
	{ "branch-taken-retired",	K7_RETIRED_TAKEN_BRANCH },
	{ "branch-taken-miss-retired",
	    K7_RETIRED_TAKEN_BRANCH_MISPREDICTED },
	{ "branch-far-retired",
	    K7_RETIRED_FAR_CONTROL_TRANSFER },
	{ "branch-resync-retired",	K7_RETIRED_RESYNC_BRANCH },
	{ "branch-near-retired",	K7_RETIRED_NEAR_RETURNS },
	{ "branch-near-miss-retired",   
	    K7_RETIRED_NEAR_RETURNS_MISPREDICTED },
	{ "branch-indirect-miss-retired",
	    K7_RETIRED_INDIRECT_MISPREDICTED },
	{ "int-hw",			K7_HW_INTR_RECV },
	{ "int-cycles-masked",		K7_CYCLES_INT_MASKED },
	{ "int-cycles-masked-pending",  
	    K7_CYCLES_INT_PENDING_AND_MASKED },
	{ "break-match0",		K7_BP0_MATCH },
	{ "break-match1",		K7_BP1_MATCH },
	{ "break-match2",		K7_BP2_MATCH },
	{ "break-match3",		K7_BP3_MATCH },

	{ NULL,				0 },
};

static const struct pmc_class2evid i386_pmc_classes[] = {
	{ PMC_CLASS_I586,		"i586",
	  i586_pmc_evids },
	{ PMC_TYPE_I586_TSC,		"i586 cycle counter",
	  NULL },
	{ PMC_TYPE_I586_PMCx,		"i586 performance counter",
	  NULL },

	{ PMC_CLASS_I686,		"i686",
	  i686_pmc_evids },
	{ PMC_TYPE_I686_TSC,		"i686 cycle counter",
	  NULL },
	{ PMC_TYPE_I686_PMCx,		"i686 performance counter",
	  NULL },

	{ PMC_CLASS_K7,			"K7",
	  k7_pmc_evids },
	{ PMC_TYPE_K7_TSC,		"K7 cycle counter",
	  NULL },
	{ PMC_TYPE_K7_PMCx,		"K7 performance counter",
	  NULL },

	{ 0,				NULL,
	  NULL },
};

const struct pmc_class2evid *_pmc_md_classes = i386_pmc_classes;
