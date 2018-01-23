#pragma once

#include <vector>
#include <memory>

#include "EntityManager.h"
#include "System.h"
#include "EngineDebugger.h"

using namespace std;

namespace ECS {
	class Engine {
	public:
		Engine(shared_ptr<EntityManager> entities) {
			_entities = entities;
		}

		void AddDebugger(shared_ptr<EngineDebugger> debug) {
			_debug = debug;
			_systems.push_back(dynamic_pointer_cast<System>(debug));
		}

		void AddSystem(shared_ptr<System> system) {
			_systems.push_back(system);
		}

		void Update() {
			for ( auto& s : _systems ) {
				if ( s ) {
					if ( _debug ) _debug->StartSystem(s);
					s->Update(_entities);
					if ( _debug ) _debug->EndSystem();
				}
			}
		}

	private:
		shared_ptr<EntityManager> _entities;
		vector<shared_ptr<System>> _systems;
		shared_ptr<EngineDebugger> _debug;
	};
}

