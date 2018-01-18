#pragma once
#include <string>
using namespace std;

namespace ECS {
	struct Component {
		virtual ~Component() = default;
	};
}

