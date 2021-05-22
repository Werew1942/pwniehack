#include "engine.h"

#include "offsets.h"
#include "hook.h"
#include "menu.h"
#include "renderer.h"

namespace engine
{
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	ID3D11RenderTargetView* render_target_view = nullptr;
}

typedef int(__thiscall* t_present_impl_original)(IDXGISwapChain* swap, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
t_present_impl_original present_impl_original = nullptr;
WNDPROC wnd_proc_original = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK wnd_proc_hook(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_KEYUP:
		if (wparam == VK_INSERT)
		{
			menu::toggle_menu();
		}
	}

	if (menu::is_open())
	{
		ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
		return true;
	}

	return CallWindowProc(wnd_proc_original, hwnd, msg, wparam, lparam);
}

int __fastcall present_impl_hook(IDXGISwapChain* swap, void* notUsed, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	if (!engine::device)
	{
		renderer::setup(swap, engine::device, engine::context, engine::render_target_view);
	}

	renderer::begin();
	if (menu::is_open())
	{
		menu::render_menu();
	}
	renderer::draw(swap, engine::device, engine::context, engine::render_target_view);
	renderer::end(engine::context, engine::render_target_view);

	return present_impl_original(swap, a2, a3, a4, a5, a6, a7, a8);
}

void engine::ignite()
{
	AllocConsole();
	FILE* file, * file2;
	freopen_s(&file, "conout$", "w", stdout);
	freopen_s(&file2, "conin$", "r", stdin);

	uintptr_t dxgi_base = reinterpret_cast<uintptr_t>(GetModuleHandleA("dxgi.dll"));
	std::cout << "dxgi.dll base: 0x" << std::hex << dxgi_base << std::dec << std::endl;
	uintptr_t present_impl = dxgi_base + offsets::present_impl_core;
	std::cout << "CDXGISwapChain::PresentImpl: 0x" << std::hex << present_impl << std::dec << std::endl;
	std::cout << "present_impl_hook: 0x" << std::hex << reinterpret_cast<uintptr_t>(present_impl_hook) << std::dec << std::endl;

	hook present;
	present.setup(present_impl, reinterpret_cast<uintptr_t>(present_impl_hook), 5, reinterpret_cast<uintptr_t*&>(present_impl_original));

	std::cout << "Success" << std::endl;

	HWND pwnie_window = FindWindowA("UnrealWindow", nullptr);
	if (pwnie_window == nullptr)
	{
		std::cout << "Cannot find window" << std::endl;
	}

	wnd_proc_original = reinterpret_cast<WNDPROC>(SetWindowLongA(pwnie_window, GWLP_WNDPROC, reinterpret_cast<uintptr_t>(wnd_proc_hook)));
	if (wnd_proc_original == nullptr)
	{
		std::cout << "Failed to hook wndproc" << std::endl;
	}
}