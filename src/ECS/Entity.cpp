#include "Entity.h"

namespace ECS {
	void Entity::AddComponent(const string& name, Component& comp) {
		components[name] = comp;
	}

	bool Entity::HasComponent(const string& name) const {
		return components.count(name) == 1;
	}

	size_t Entity::GetComponentCount() const {
		return components.size();
	}
}
