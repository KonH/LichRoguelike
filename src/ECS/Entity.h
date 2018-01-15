#pragma once
#include <map>
#include <string>
#include "Component.h"
using namespace std;

namespace ECS {
	class Entity {
	public:
		void AddComponent(const string& name, Component& comp);
		bool HasComponent(const string& name) const;
		size_t GetComponentCount() const;
	private:
		map<string, Component> components;
	};
}
