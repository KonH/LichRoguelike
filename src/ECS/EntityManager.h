#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include "Entity.h"
using namespace std;

namespace ECS {
	class EntityManager {
	public:
		shared_ptr<Entity> CreateEntity() {
			auto entity = make_shared<Entity>();
			AddEntity(entity);
			return entity;
		}

		void AddEntity(shared_ptr<Entity> entity) {
			_entities.push_back(entity);
		}

		bool RemoveEntity(shared_ptr<Entity> entity) {
			auto it = find(_entities.begin(), _entities.end(), entity);
			if ( it != _entities.end() ) {
				_entities.erase(it);
				return true;
			}
			return false;
		}

		size_t GetEntitesCount() const {
			return _entities.size();
		}
	private:
		vector<shared_ptr<Entity>> _entities;
	};
}

