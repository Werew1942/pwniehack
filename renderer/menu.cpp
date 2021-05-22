#include "menu.h"

#include "game.h"

bool menu::open = false;
int menu::width = 0, menu::height = 0;

namespace config
{
	constexpr int menu_width = 450;
	constexpr int menu_height = 300;
	constexpr int menu_pos_x = 10;
	constexpr int menu_pos_y = 200;
}

void menu::render_menu()
{
	ImGui::SetNextWindowSize({ config::menu_width, config::menu_height });
	ImGui::Begin("Chair", nullptr, ImGuiWindowFlags_NoCollapse);

	ImGui::Text("Actor Count: %d", game::ActorCount());

	if (game::get_z() != nullptr)
	{
		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		ImGui::SliderFloat("X", game::get_x(), -100000.0f, 1000000.0f);
		ImGui::SliderFloat("Y", game::get_y(), -100000.0f, 1000000.0f);
		ImGui::SliderFloat("Z", game::get_z(), -100000.0f, 1000000.0f);
	}

	ImGui::End();
}

void menu::toggle_menu()
{
	open = !open;
	ImGui::GetIO().WantCaptureMouse = open;
}

bool menu::is_open()
{
	return open;
}
