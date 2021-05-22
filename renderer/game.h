#pragma once

#include "win.h"
#include "mem.h"

class game
{
public:
	static float* get_x();
	static float* get_y();
	static float* get_z();
	static int ActorCount();

	static void loop();
private:
	static uintptr_t game_base;
};

