#pragma once
#include "Singleton.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		static bool ProcessInput();
	};

}
