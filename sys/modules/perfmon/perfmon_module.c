/****************************************************************************/

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

/****************************************************************************/

#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/module.h>

void	perfmon_init(void);
void	perfmon_fini(void);

MODULE(MODULE_CLASS_MISC, perfmon, NULL);

static int
perfmon_modcmd(modcmd_t cmd, void *arg)
{

	switch (cmd) {
	case MODULE_CMD_INIT:
		perfmon_init();
		return 0;

	case MODULE_CMD_FINI:
		perfmon_fini();
		return 0;

	case MODULE_CMD_STAT:
	default:
		return ENOTTY;
	}
}

/****************************************************************************/
