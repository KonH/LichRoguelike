#pragma once

#include "../../ECS/Component.h"

#include "../Components/BonesContainer.h"

using namespace ECS;

namespace Game {
	struct Bones: Component {
		int Count = 0;

		Bones(int count) :
				Count(count) {
			Name = "Bones";
		}
	};
}

