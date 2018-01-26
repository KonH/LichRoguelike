#pragma once

#include "../../ECS/Component.h"

#include "../Components/BonesContainer.h"

using namespace ECS;

namespace Game {
	struct BonesContainer : Component {
		int Count = 0;
	};
}

