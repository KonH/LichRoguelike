#pragma once

#include <string>

using namespace std;

namespace ECS {
	struct Component {
		string Name = "Unknown";

		virtual ~Component() = default;
	};
}

