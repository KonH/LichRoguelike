#pragma once
#include <vector>
#include <tuple>
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


		template<class T>
		using ECTuple1 = vector<tuple<shared_ptr<Entity>, shared_ptr<T>>>;

		template<class T>
		ECTuple1<T> Filter() {
			ECTuple1<T> result;
			for ( auto& e : _entities ) {
				if ( e ) {
					auto c = e->GetComponent<T>();
					if ( c ) {
						auto t = make_tuple(e, c);
						result.push_back(t);
					}
				}
			}
			return result;
		}
	private:
		vector<shared_ptr<Entity>> _entities;
	};
}

