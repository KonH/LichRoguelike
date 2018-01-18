#pragma once

#include "../Component.h"

namespace ECS {
	struct View: Component {
		char Content;

		View(char c):Component() {
			Content = c;
		}
	};
}

