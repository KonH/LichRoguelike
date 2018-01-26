#pragma once

#include "../Component.h"

namespace ECS {
	struct View: Component {
		char Content;

		View(char c) :
				Content(c) {
			Name = "View";
		}
	};
}

