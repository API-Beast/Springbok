//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "RenderContext2D.h"
#include "GLES2.h"
#include "BatchRenderer.h"

template<typename T, typename... Args, class U, class V>
void RenderContext2D::draw(const T& object, Transform2D transformation, Args... args, const V& vinit, const U& uinit)
{
	static BatchRenderer<U, V> b(32768); // 32kB
	b.DefaultVertex  = vinit;
	b.DefaultElement = uinit;
	b.startBatching(*this);
	b.addToBatch(object, transformation, args...);
	b.flushBatches();
};