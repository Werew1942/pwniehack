#pragma once

#include "win.h"
#include <d3d11.h>
#include <sstream>
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"

class renderer
{
public:
	static void draw(IDXGISwapChain*& swap, ID3D11Device*& device, ID3D11DeviceContext*& context, ID3D11RenderTargetView*& render_target_view);
	static void setup(IDXGISwapChain*& swap, ID3D11Device*& device, ID3D11DeviceContext*& context, ID3D11RenderTargetView*& render_target_view);
	static void begin();
	static void end(ID3D11DeviceContext*& context, ID3D11RenderTargetView*& render_target_view);
private:
	static int width, height;
};

