#pragma once

#include "win.h"
#include "imgui.h"

class menu
{
public:
	static void render_menu();
	static void toggle_menu();
	static bool is_open();
private:
	static bool open;
	static int width, height;
};

