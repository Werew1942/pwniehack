#pragma once

namespace offsets
{
	// DirectX
	constexpr auto present_impl_core = 0x24370;
	constexpr auto resize_buffers = 0x2d920;

	// Game
	constexpr auto UWorld = 0x1900600;
	constexpr auto PersistentLevel = 0x20;
	constexpr auto GNames = 0x1900600;
	constexpr auto UObjects = 0x1900600;

	constexpr auto Actors = 0x64;
}