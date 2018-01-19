#pragma once

#include <vector>
#include <memory>

#include "EntityManager.h"
#include "System.h"

using namespace std;

namespace ECS {
	class Engine {
	public:
		Engine(shared_ptr<EntityManager> entities) {
			_entities = entities;
		}

		void AddSystem(shared_ptr<System> system) {
			_systems.push_back(system);
		}

		void Update() {
			for ( auto& s : _systems ) {
				if ( s ) {
					s->Update(_entities);
				}
			}
		}
	private:
		shared_ptr<EntityManager> _entities;
		vector<shared_ptr<System>> _systems;
	};
}

