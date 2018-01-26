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

		vector<shared_ptr<Component>> GetComponents() {
			vector<shared_ptr<Component>> result;
			for ( auto pair : _components ) {
				result.push_back(pair.second);
			}
			return result;
		}

		size_t GetComponentCount() const {
			return _components.size();
		}

		template<class T>
		shared_ptr<T> GetComponent() const {
			auto key = typeid(T).name();
			if ( _components.count(key) == 1 ) {
				auto basePtr = _components.at(key);
				shared_ptr<T> derivedPtr = dynamic_pointer_cast<T>(basePtr);
				return derivedPtr;
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
