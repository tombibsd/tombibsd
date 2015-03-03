/****************************************************************************/

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

/****************************************************************************/

#include <sys/param.h>
#include <sys/systm.h>

#include <x86/cpufunc.h>

void	perfmon_init(void);
void	perfmon_fini(void);

static void	test(void);
static void	dump(void);
static void	dumpcpuids(void);
static void	dumpcpuid(int, int);
static void	dumpmsrs(void);

/****************************************************************************/

void
perfmon_init(void)
{
	printf("hello perfmon!\n");
	test();
}

void
perfmon_fini(void)
{
	test();
	printf("bye perfmon!\n");
}

/****************************************************************************/

#if 0
void
perfmon_probe(void)
{
}
#endif

/****************************************************************************/

__attribute__((constructor))
static void
test(void)
{
	dump();
}

static void
dump(void)
{
	dumpcpuids();
	dumpmsrs();
}

static void
dumpcpuids(void)
{
	dumpcpuid(0xa, 0);
	dumpcpuid(0x80000001, 0);
	dumpcpuid(0x80000002, 0);
	dumpcpuid(0x80000003, 0);
	dumpcpuid(0x80000004, 0);
	dumpcpuid(0x80000005, 0);
	dumpcpuid(0x80000006, 0);
	dumpcpuid(0x80000007, 0);
	dumpcpuid(0x80000008, 0);
}

static void
dumpcpuid(int eax, int ecx)
{
	uint32_t regs[4];

	x86_cpuid2(eax, ecx, regs);
	printf("cpuid[%x:%x]=[%x:%x:%x:%x]\n", eax, ecx, regs[0], regs[1], regs[2], regs[3]);
}

static void
dumpmsrs(void)
{
#define	DUMP(msr) \
do { \
	uint64_t tmp; \
	tmp = rdmsr(msr); \
	printf("%30s: 0x%016"PRIx64"\n", #msr, tmp); \
} while (0)

	DUMP(MSR_MISC_ENABLE);
	DUMP(MSR_THERM_STATUS);
	DUMP(MSR_PERF_STATUS);
	DUMP(MSR_TSC);
}

/****************************************************************************/
