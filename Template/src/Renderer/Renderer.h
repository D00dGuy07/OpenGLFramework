#pragma once

#include <utility>

#include "glad/glad.h"

#include "Renderer/RenderCommandQueue.h"
#include "Renderer/Mesh.h"
#include "Renderer/Shader.h"

class Renderer
{
public:
	// This function is copied from the Hazel game engine
	template<typename FuncT>
	static void Submit(FuncT&& func)
	{
		auto renderCmd = [](void* ptr) {
			auto pFunc = (FuncT*)ptr;
			(*pFunc)();
			pFunc->~FuncT();
		};
		auto storageBuffer = m_CommandQueue.Allocate(renderCmd, sizeof(func));
		new (storageBuffer) FuncT(std::forward<FuncT>(func));
	}

	static void SubmitMesh(Mesh& mesh, Shader& shader);
	static void SubmitMeshInstanced(Mesh& mesh, Shader& shader, uint32_t instanceCount);

	static void Clear();
	static void DrawFrame();

private:
	static RenderCommandQueue m_CommandQueue;
};
