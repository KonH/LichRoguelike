#pragma once
#include <map>
#include <string>
#include "Component.h"
using namespace std;

namespace ECS {
	class Entity {
	public:
		void AddComponent(Component& comp);
		size_t GetComponentCount() const;

		template<class T>
		T* GetComponent() const {
			auto key = typeid(T).name();
			if ( _components.count(key) == 1 ) {
				Component* baseComp = _components.at(key);
				T* derivedComp = dynamic_cast<T*>(baseComp);
				return derivedComp;
			}
			return nullptr;
		}

		template<class T>
		bool HasComponent() const {
			return GetComponent<T>() != nullptr;
		}

	private:
		map<string, Component*> _components;
	};
}
