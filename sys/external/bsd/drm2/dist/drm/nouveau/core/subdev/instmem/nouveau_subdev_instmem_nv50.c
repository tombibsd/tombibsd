/*	$NetBSD$	*/

/*
 * Copyright 2012 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#include <subdev/fb.h>
#include <core/mm.h>

#include "priv.h"

struct nv50_instmem_priv {
	struct nouveau_instmem base;
	spinlock_t lock;
	u64 addr;
};

struct nv50_instobj_priv {
	struct nouveau_instobj base;
	struct nouveau_mem *mem;
};

/******************************************************************************
 * instmem object implementation
 *****************************************************************************/

static u32
nv50_instobj_rd32(struct nouveau_object *object, u64 offset)
{
	struct nv50_instmem_priv *priv = (void *)object->engine;
	struct nv50_instobj_priv *node = (void *)object;
	unsigned long flags;
	u64 base = (node->mem->offset + offset) & 0xffffff00000ULL;
	u64 addr = (node->mem->offset + offset) & 0x000000fffffULL;
	u32 data;

	spin_lock_irqsave(&priv->lock, flags);
	if (unlikely(priv->addr != base)) {
		nv_wr32(priv, 0x001700, base >> 16);
		priv->addr = base;
	}
	data = nv_rd32(priv, 0x700000 + addr);
	spin_unlock_irqrestore(&priv->lock, flags);
	return data;
}

static void
nv50_instobj_wr32(struct nouveau_object *object, u64 offset, u32 data)
{
	struct nv50_instmem_priv *priv = (void *)object->engine;
	struct nv50_instobj_priv *node = (void *)object;
	unsigned long flags;
	u64 base = (node->mem->offset + offset) & 0xffffff00000ULL;
	u64 addr = (node->mem->offset + offset) & 0x000000fffffULL;

	spin_lock_irqsave(&priv->lock, flags);
	if (unlikely(priv->addr != base)) {
		nv_wr32(priv, 0x001700, base >> 16);
		priv->addr = base;
	}
	nv_wr32(priv, 0x700000 + addr, data);
	spin_unlock_irqrestore(&priv->lock, flags);
}

static void
nv50_instobj_dtor(struct nouveau_object *object)
{
	struct nv50_instobj_priv *node = (void *)object;
	struct nouveau_fb *pfb = nouveau_fb(object);
	pfb->ram->put(pfb, &node->mem);
	nouveau_instobj_destroy(&node->base);
}

static int
nv50_instobj_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		  struct nouveau_oclass *oclass, void *data, u32 size,
		  struct nouveau_object **pobject)
{
	struct nouveau_fb *pfb = nouveau_fb(parent);
	struct nouveau_instobj_args *args = data;
	struct nv50_instobj_priv *node;
	int ret;

	args->size  = max((args->size  + 4095) & ~4095, (u32)4096);
	args->align = max((args->align + 4095) & ~4095, (u32)4096);

	ret = nouveau_instobj_create(parent, engine, oclass, &node);
	*pobject = nv_object(node);
	if (ret)
		return ret;

	ret = pfb->ram->get(pfb, args->size, args->align, 0, 0x800, &node->mem);
	if (ret)
		return ret;

	node->base.addr = node->mem->offset;
	node->base.size = node->mem->size << 12;
	node->mem->page_shift = 12;
	return 0;
}

static struct nouveau_instobj_impl
nv50_instobj_oclass = {
	.base.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv50_instobj_ctor,
		.dtor = nv50_instobj_dtor,
		.init = _nouveau_instobj_init,
		.fini = _nouveau_instobj_fini,
		.rd32 = nv50_instobj_rd32,
		.wr32 = nv50_instobj_wr32,
	},
};

/******************************************************************************
 * instmem subdev implementation
 *****************************************************************************/

static int
nv50_instmem_fini(struct nouveau_object *object, bool suspend)
{
	struct nv50_instmem_priv *priv = (void *)object;
	priv->addr = ~0ULL;
	return nouveau_instmem_fini(&priv->base, suspend);
}

static int
nv50_instmem_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		  struct nouveau_oclass *oclass, void *data, u32 size,
		  struct nouveau_object **pobject)
{
	struct nv50_instmem_priv *priv;
	int ret;

	ret = nouveau_instmem_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	spin_lock_init(&priv->lock);
	return 0;
}

struct nouveau_oclass *
nv50_instmem_oclass = &(struct nouveau_instmem_impl) {
	.base.handle = NV_SUBDEV(INSTMEM, 0x50),
	.base.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv50_instmem_ctor,
		.dtor = _nouveau_instmem_dtor,
		.init = _nouveau_instmem_init,
		.fini = nv50_instmem_fini,
	},
	.instobj = &nv50_instobj_oclass.base,
}.base;
