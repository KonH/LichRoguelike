#pragma once

#include <iostream>

#include "../Component.h"

namespace ECS {
	enum MoveDirection {
		None,
		Up,
		Down,
		Left,
		Right
	};

	struct Movable: Component {
		MoveDirection Direction = MoveDirection::None;
	};
}

