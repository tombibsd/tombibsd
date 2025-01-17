/*	$NetBSD$	*/

/*
 * Copyright 2012 Nouveau Community
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Martin Peres <martin.peres@labri.fr>
 *          Ben Skeggs
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#include <subdev/timer.h>

#include "nv04.h"

static int
nv50_bus_hwsq_exec(struct nouveau_bus *pbus, u32 *data, u32 size)
{
	struct nv50_bus_priv *priv = (void *)pbus;
	int i;

	nv_mask(pbus, 0x001098, 0x00000008, 0x00000000);
	nv_wr32(pbus, 0x001304, 0x00000000);
	for (i = 0; i < size; i++)
		nv_wr32(priv, 0x001400 + (i * 4), data[i]);
	nv_mask(pbus, 0x001098, 0x00000018, 0x00000018);
	nv_wr32(pbus, 0x00130c, 0x00000003);

	return nv_wait(pbus, 0x001308, 0x00000100, 0x00000000) ? 0 : -ETIMEDOUT;
}

void
nv50_bus_intr(struct nouveau_subdev *subdev)
{
	struct nouveau_bus *pbus = nouveau_bus(subdev);
	u32 stat = nv_rd32(pbus, 0x001100) & nv_rd32(pbus, 0x001140);

	if (stat & 0x00000008) {
		u32 addr = nv_rd32(pbus, 0x009084);
		u32 data = nv_rd32(pbus, 0x009088);

		nv_error(pbus, "MMIO %s of 0x%08x FAULT at 0x%06x\n",
			 (addr & 0x00000002) ? "write" : "read", data,
			 (addr & 0x00fffffc));

		stat &= ~0x00000008;
		nv_wr32(pbus, 0x001100, 0x00000008);
	}

	if (stat & 0x00010000) {
		subdev = nouveau_subdev(pbus, NVDEV_SUBDEV_THERM);
		if (subdev && subdev->intr)
			subdev->intr(subdev);
		stat &= ~0x00010000;
		nv_wr32(pbus, 0x001100, 0x00010000);
	}

	if (stat) {
		nv_error(pbus, "unknown intr 0x%08x\n", stat);
		nv_mask(pbus, 0x001140, stat, 0);
	}
}

int
nv50_bus_init(struct nouveau_object *object)
{
	struct nv04_bus_priv *priv = (void *)object;
	int ret;

	ret = nouveau_bus_init(&priv->base);
	if (ret)
		return ret;

	nv_wr32(priv, 0x001100, 0xffffffff);
	nv_wr32(priv, 0x001140, 0x00010008);
	return 0;
}

struct nouveau_oclass *
nv50_bus_oclass = &(struct nv04_bus_impl) {
	.base.handle = NV_SUBDEV(BUS, 0x50),
	.base.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv04_bus_ctor,
		.dtor = _nouveau_bus_dtor,
		.init = nv50_bus_init,
		.fini = _nouveau_bus_fini,
	},
	.intr = nv50_bus_intr,
	.hwsq_exec = nv50_bus_hwsq_exec,
	.hwsq_size = 64,
}.base;
