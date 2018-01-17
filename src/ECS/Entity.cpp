#include "Entity.h"

namespace ECS {
	size_t Entity::GetComponentCount() const {
		return _components.size();
	}
}
