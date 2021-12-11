#pragma once

#include <stdint.h>

#include "Renderer/ImageBuffer.h"

class RenderBuffer : public ImageBuffer
{
public:
	RenderBuffer(int32_t width, int32_t height, InternalImageFormat format);
	~RenderBuffer();

	void Bind();

	virtual void Reallocate(int32_t width, int32_t height);

private:
	InternalImageFormat m_Format;

	static uint32_t m_BoundRendererID;
};