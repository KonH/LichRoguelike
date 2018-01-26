#pragma once

#include "../Component.h"

namespace ECS {
	enum MoveDirection {
		None, Up, Down, Left, Right
	};

	struct Movable: Component {
		MoveDirection Direction = MoveDirection::None;

		Movable() {
			Name = "Movable";
		}
	};
}

