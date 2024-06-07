//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#include <stdlib.h>
#include "DetourAlloc.h"

static void *dtAllocDefault(size_t size, dtAllocHint)
{
	return malloc(size);
}

static void* dtReAllocDefault(void *ptr, size_t size, dtAllocHint)
{
	return realloc(ptr, size);
}

static void dtFreeDefault(void *ptr)
{
	free(ptr);
}

static dtAllocFunc* sAllocFunc = dtAllocDefault;
static dtReAllocFunc* sReAllocFunc = dtReAllocDefault;
static dtFreeFunc* sFreeFunc = dtFreeDefault;

void dtAllocSetCustom(dtAllocFunc *allocFunc, dtFreeFunc *freeFunc, dtReAllocFunc *reallocFunc)
{
	sAllocFunc = allocFunc ? allocFunc : dtAllocDefault;
	sFreeFunc = freeFunc ? freeFunc : dtFreeDefault;
	sReAllocFunc = reallocFunc ? reallocFunc : dtReAllocDefault;
}

void* dtAlloc(size_t size, dtAllocHint hint)
{
	return sAllocFunc(size, hint);
}

void* dtReAlloc(void* ptr, size_t size, dtAllocHint hint)
{
	return sReAllocFunc(ptr, size, hint);
}


void dtFree(void* ptr)
{
	if (ptr)
		sFreeFunc(ptr);
}
