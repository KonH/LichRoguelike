#include "Entity.h"

namespace ECS {
	void Entity::AddComponent(Component& comp) {
		auto key = typeid(comp).name();
		_components[key] = &comp;
	}

	size_t Entity::GetComponentCount() const {
		return _components.size();
	}
}
