#include "renderer.h"
#include "consolas.h"
#include "game.h"

#include <iomanip>
#include <d2d1.h>

int renderer::width = 0, renderer::height = 0;

void renderer::draw(IDXGISwapChain*& swap, ID3D11Device*& device, ID3D11DeviceContext*& context, ID3D11RenderTargetView*& render_target_view)
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
	ImGui::Begin("BackBuffer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

	ImGui::SetWindowPos({ 0, 0 }, ImGuiCond_Always);

	game::loop();

	// ActorCount
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	std::stringstream text;
	text << game::ActorCount();
	
	window->DrawList->AddText({ 10.0f, 10.0f }, ImColor(235, 64, 52), text.str().c_str());
	
	// FPS
	std::stringstream fps;
	fps << std::setprecision(4) << ImGui::GetIO().Framerate;
	window->DrawList->AddText({ 10.0f, 25.0f }, ImColor(235, 64, 52), fps.str().c_str());

	window->DrawList->PushClipRectFullScreen();

	ImGui::End();
	ImGui::PopStyleColor();
}

void renderer::setup(IDXGISwapChain*& swap, ID3D11Device*& device, ID3D11DeviceContext*& context, ID3D11RenderTargetView*& render_target_view)
{
	swap->GetDevice(__uuidof(device), reinterpret_cast<PVOID*>(&device));
	device->GetImmediateContext(&context);

	ID3D11Texture2D* renderTarget = nullptr;
	swap->GetBuffer(0, __uuidof(renderTarget), reinterpret_cast<PVOID*>(&renderTarget));
	device->CreateRenderTargetView(renderTarget, nullptr, &render_target_view);
	renderTarget->Release();

	DXGI_SWAP_CHAIN_DESC desc;
	swap->GetDesc(&desc);
	width = desc.BufferDesc.Width;
	height = desc.BufferDesc.Height;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = NULL;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(FindWindowA("UnrealWindow", nullptr));
	ImGui_ImplDX11_Init(device, context);

	// io.Fonts->AddFontFromMemoryTTF(consolas_data, sizeof(consolas_data), 16.0f);
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 16.0f);

	// D2D
	ID2D1Factory* factory;
	D2D1_FACTORY_OPTIONS options;
	options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
}

void renderer::begin()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void renderer::end(ID3D11DeviceContext*& context, ID3D11RenderTargetView*& render_target_view)
{
	ImGui::Render();
	context->OMSetRenderTargets(1, &render_target_view, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
