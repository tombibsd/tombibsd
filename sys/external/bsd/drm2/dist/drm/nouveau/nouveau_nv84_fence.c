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

#include <core/object.h>
#include <core/client.h>
#include <core/class.h>

#include <engine/fifo.h>

#include "nouveau_drm.h"
#include "nouveau_dma.h"
#include "nouveau_fence.h"

#include "nv50_display.h"

u64
nv84_fence_crtc(struct nouveau_channel *chan, int crtc)
{
	struct nv84_fence_chan *fctx = chan->fence;
	return fctx->dispc_vma[crtc].offset;
}

static int
nv84_fence_emit32(struct nouveau_channel *chan, u64 virtual, u32 sequence)
{
	int ret = RING_SPACE(chan, 8);
	if (ret == 0) {
		BEGIN_NV04(chan, 0, NV11_SUBCHAN_DMA_SEMAPHORE, 1);
		OUT_RING  (chan, chan->vram);
		BEGIN_NV04(chan, 0, NV84_SUBCHAN_SEMAPHORE_ADDRESS_HIGH, 5);
		OUT_RING  (chan, upper_32_bits(virtual));
		OUT_RING  (chan, lower_32_bits(virtual));
		OUT_RING  (chan, sequence);
		OUT_RING  (chan, NV84_SUBCHAN_SEMAPHORE_TRIGGER_WRITE_LONG);
		OUT_RING  (chan, 0x00000000);
		FIRE_RING (chan);
	}
	return ret;
}

static int
nv84_fence_sync32(struct nouveau_channel *chan, u64 virtual, u32 sequence)
{
	int ret = RING_SPACE(chan, 7);
	if (ret == 0) {
		BEGIN_NV04(chan, 0, NV11_SUBCHAN_DMA_SEMAPHORE, 1);
		OUT_RING  (chan, chan->vram);
		BEGIN_NV04(chan, 0, NV84_SUBCHAN_SEMAPHORE_ADDRESS_HIGH, 4);
		OUT_RING  (chan, upper_32_bits(virtual));
		OUT_RING  (chan, lower_32_bits(virtual));
		OUT_RING  (chan, sequence);
		OUT_RING  (chan, NV84_SUBCHAN_SEMAPHORE_TRIGGER_ACQUIRE_GEQUAL);
		FIRE_RING (chan);
	}
	return ret;
}

static int
nv84_fence_emit(struct nouveau_fence *fence)
{
	struct nouveau_channel *chan = fence->channel;
	struct nv84_fence_chan *fctx = chan->fence;
	struct nouveau_fifo_chan *fifo = (void *)chan->object;
	u64 addr = fifo->chid * 16;

	if (fence->sysmem)
		addr += fctx->vma_gart.offset;
	else
		addr += fctx->vma.offset;

	return fctx->base.emit32(chan, addr, fence->sequence);
}

static int
nv84_fence_sync(struct nouveau_fence *fence,
		struct nouveau_channel *prev, struct nouveau_channel *chan)
{
	struct nv84_fence_chan *fctx = chan->fence;
	struct nouveau_fifo_chan *fifo = (void *)prev->object;
	u64 addr = fifo->chid * 16;

	if (fence->sysmem)
		addr += fctx->vma_gart.offset;
	else
		addr += fctx->vma.offset;

	return fctx->base.sync32(chan, addr, fence->sequence);
}

static u32
nv84_fence_read(struct nouveau_channel *chan)
{
	struct nouveau_fifo_chan *fifo = (void *)chan->object;
	struct nv84_fence_priv *priv = chan->drm->fence;
	return nouveau_bo_rd32(priv->bo, fifo->chid * 16/4);
}

static void
nv84_fence_context_del(struct nouveau_channel *chan)
{
	struct drm_device *dev = chan->drm->dev;
	struct nv84_fence_priv *priv = chan->drm->fence;
	struct nv84_fence_chan *fctx = chan->fence;
	int i;

	for (i = 0; i < dev->mode_config.num_crtc; i++) {
		struct nouveau_bo *bo = nv50_display_crtc_sema(dev, i);
		nouveau_bo_vma_del(bo, &fctx->dispc_vma[i]);
	}

	nouveau_bo_vma_del(priv->bo, &fctx->vma_gart);
	nouveau_bo_vma_del(priv->bo, &fctx->vma);
	nouveau_fence_context_del(&fctx->base);
	chan->fence = NULL;
	kfree(fctx);
}

int
nv84_fence_context_new(struct nouveau_channel *chan)
{
	struct nouveau_fifo_chan *fifo = (void *)chan->object;
	struct nouveau_client *client = nouveau_client(fifo);
	struct nv84_fence_priv *priv = chan->drm->fence;
	struct nv84_fence_chan *fctx;
	int ret, i;

	fctx = chan->fence = kzalloc(sizeof(*fctx), GFP_KERNEL);
	if (!fctx)
		return -ENOMEM;

	nouveau_fence_context_new(&fctx->base);
	fctx->base.emit = nv84_fence_emit;
	fctx->base.sync = nv84_fence_sync;
	fctx->base.read = nv84_fence_read;
	fctx->base.emit32 = nv84_fence_emit32;
	fctx->base.sync32 = nv84_fence_sync32;

	ret = nouveau_bo_vma_add(priv->bo, client->vm, &fctx->vma);
	if (ret == 0) {
		ret = nouveau_bo_vma_add(priv->bo_gart, client->vm,
					&fctx->vma_gart);
	}

	/* map display semaphore buffers into channel's vm */
	for (i = 0; !ret && i < chan->drm->dev->mode_config.num_crtc; i++) {
		struct nouveau_bo *bo = nv50_display_crtc_sema(chan->drm->dev, i);
		ret = nouveau_bo_vma_add(bo, client->vm, &fctx->dispc_vma[i]);
	}

	nouveau_bo_wr32(priv->bo, fifo->chid * 16/4, 0x00000000);

	if (ret)
		nv84_fence_context_del(chan);
	return ret;
}

static bool
nv84_fence_suspend(struct nouveau_drm *drm)
{
	struct nouveau_fifo *pfifo = nouveau_fifo(drm->device);
	struct nv84_fence_priv *priv = drm->fence;
	int i;

	priv->suspend = vmalloc((pfifo->max + 1) * sizeof(u32));
	if (priv->suspend) {
		for (i = 0; i <= pfifo->max; i++)
			priv->suspend[i] = nouveau_bo_rd32(priv->bo, i*4);
	}

	return priv->suspend != NULL;
}

static void
nv84_fence_resume(struct nouveau_drm *drm)
{
	struct nouveau_fifo *pfifo = nouveau_fifo(drm->device);
	struct nv84_fence_priv *priv = drm->fence;
	int i;

	if (priv->suspend) {
		for (i = 0; i <= pfifo->max; i++)
			nouveau_bo_wr32(priv->bo, i*4, priv->suspend[i]);
		vfree(priv->suspend);
		priv->suspend = NULL;
	}
}

static void
nv84_fence_destroy(struct nouveau_drm *drm)
{
	struct nv84_fence_priv *priv = drm->fence;

#ifdef __NetBSD__
	spin_lock_destroy(&priv->base.waitlock);
	DRM_DESTROY_WAITQUEUE(&priv->base.waitqueue);
#endif

	nouveau_bo_unmap(priv->bo_gart);
	if (priv->bo_gart)
		nouveau_bo_unpin(priv->bo_gart);
	nouveau_bo_ref(NULL, &priv->bo_gart);
	nouveau_bo_unmap(priv->bo);
	if (priv->bo)
		nouveau_bo_unpin(priv->bo);
	nouveau_bo_ref(NULL, &priv->bo);
	drm->fence = NULL;
	kfree(priv);
}

int
nv84_fence_create(struct nouveau_drm *drm)
{
	struct nouveau_fifo *pfifo = nouveau_fifo(drm->device);
	struct nv84_fence_priv *priv;
	int ret;

	priv = drm->fence = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->base.dtor = nv84_fence_destroy;
	priv->base.suspend = nv84_fence_suspend;
	priv->base.resume = nv84_fence_resume;
	priv->base.context_new = nv84_fence_context_new;
	priv->base.context_del = nv84_fence_context_del;

#ifdef __NetBSD__
	spin_lock_init(&priv->base.waitlock);
	DRM_INIT_WAITQUEUE(&priv->base.waitqueue, "nvfenceq");
#else
	init_waitqueue_head(&priv->base.waiting);
#endif
	priv->base.uevent = true;

	ret = nouveau_bo_new(drm->dev, 16 * (pfifo->max + 1), 0,
			     TTM_PL_FLAG_VRAM, 0, 0, NULL, &priv->bo);
	if (ret == 0) {
		ret = nouveau_bo_pin(priv->bo, TTM_PL_FLAG_VRAM);
		if (ret == 0) {
			ret = nouveau_bo_map(priv->bo);
			if (ret)
				nouveau_bo_unpin(priv->bo);
		}
		if (ret)
			nouveau_bo_ref(NULL, &priv->bo);
	}

	if (ret == 0)
		ret = nouveau_bo_new(drm->dev, 16 * (pfifo->max + 1), 0,
				     TTM_PL_FLAG_TT, 0, 0, NULL,
				     &priv->bo_gart);
	if (ret == 0) {
		ret = nouveau_bo_pin(priv->bo_gart, TTM_PL_FLAG_TT);
		if (ret == 0) {
			ret = nouveau_bo_map(priv->bo_gart);
			if (ret)
				nouveau_bo_unpin(priv->bo_gart);
		}
		if (ret)
			nouveau_bo_ref(NULL, &priv->bo_gart);
	}

	if (ret)
		nv84_fence_destroy(drm);
	return ret;
}
