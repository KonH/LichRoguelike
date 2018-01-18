#pragma once
#include "../Component.h"

namespace ECS {
	struct Position: Component {
		int X;
		int Y;

		Position(int x, int y):Component() {
			X = x;
			Y = y;
		}
	};
}

