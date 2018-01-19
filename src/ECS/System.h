#pragma once

#include <memory>

#include "EntityManager.h"

using namespace std;

namespace ECS {
	class System {
	public:
		virtual ~System() = default;
		virtual void Update(shared_ptr<EntityManager> entities) = 0;
	};
}


