#pragma once

#include "../Component.h"

namespace ECS {
	struct Player: Component {

		Player() {
			Name = "Player";
		}
	};
}

