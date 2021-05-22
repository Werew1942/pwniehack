#include "game.h"
#include "offsets.h"
#include "game_structs.h"

uintptr_t game::game_base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
static int actorCount = 0;

float* game::get_x()
{
	float* x = reinterpret_cast<float*>(mem::get_ptr(game_base + 0x18FFDE4, { 0x4, 0x4, 0x1BC, 0x228, 0x410, 0xD4, 0x90 }));
	return x;
}

float* game::get_y()
{
	float* y = reinterpret_cast<float*>(mem::get_ptr(game_base + 0x18FFDE4, { 0x4, 0x4, 0x1BC, 0x228, 0x410, 0xD4, 0x94 }));
	return y;
}

float* game::get_z()
{
	float* z = reinterpret_cast<float*>(mem::get_ptr(game_base + 0x18FFDE4, { 0x4, 0x4, 0x1BC, 0x228, 0x410, 0xD4, 0x98 }));
	return z;
}

int game::ActorCount()
{
	return actorCount;
}

void game::loop()
{
	uintptr_t UWorldProxy = game_base + offsets::UWorld;
	uintptr_t UWorld = *(uintptr_t*)(UWorldProxy);
	uintptr_t PersistentLevel = *(uintptr_t*)(UWorld + offsets::PersistentLevel);

	TArray* Actors = (TArray*)(PersistentLevel + offsets::Actors);

	actorCount = Actors->Num;
}
