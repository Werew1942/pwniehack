#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <d3d11.h>

namespace engine
{
	extern ID3D11Device* device;
	extern ID3D11DeviceContext* context;
	extern ID3D11RenderTargetView* render_target_view;

	void ignite();
}

