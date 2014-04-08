//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(RenderTarget* target)
:
Context(target)
{
	Batcher.startBatching(Context);
}

void SpriteRenderer::clear(Vec3F color)
{
	Context.clear(color);
}

void SpriteRenderer::flush()
{
	Batcher.flushBatches();	
}

void SpriteRenderer::drawRenderpass(const Framebuffer& buffer)
{
	Batcher.flushBatches();
	Batcher.drawRect(RectF(-1, 2), RectF(0, 1), buffer.ColorAttachment->Index);
	Batcher.flushBatches();
}