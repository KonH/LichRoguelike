#pragma once
#include <map>
#include <string>
#include <memory>
#include "Component.h"
using namespace std;

namespace ECS {
	class Entity {
	public:
		template<class T>
		void AddComponent(const T& comp) {
			AddComponent(make_shared<T>(comp));
		}

		template<class T>
		void AddComponent(shared_ptr<T> comp) {
			auto key = typeid(T).name();
			_components[key] = comp;
		}

		size_t GetComponentCount() const;

		// TODO: Use shared_ptr too?
		template<class T>
		T* GetComponent() const {
			auto key = typeid(T).name();
			if ( _components.count(key) == 1 ) {
				auto basePointer = _components.at(key);
				auto baseComp = basePointer.get();
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
		map<string, shared_ptr<Component>> _components;
	};
}
