#pragma once

#include <vector>
#include <tuple>
#include <algorithm>
#include <memory>

#include "Entity.h"
#include "Components/Position.h"
#include "Components/View.h"
#include "Components/Blocker.h"

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

		template<class T1, class T2>
		using ECTuple2 = vector<tuple<shared_ptr<Entity>, shared_ptr<T1>, shared_ptr<T2>>>;

		template<class T1, class T2>
		ECTuple2<T1, T2> Filter() {
			ECTuple2<T1, T2> result;
			for ( auto& e : _entities ) {
				if ( e ) {
					auto c1 = e->GetComponent<T1>();
					auto c2 = e->GetComponent<T2>();
					if ( c1 && c2 ) {
						auto t = make_tuple(e, c1, c2);
						result.push_back(t);
					}
				}
			}
			return result;
		}

		// TODO: Add more template magic

		void SortEntities() {
			sort(begin(_entities), end(_entities), [](shared_ptr<Entity> x, shared_ptr<Entity> y) {
				if ( x && y ) {
					auto xp = x->GetComponent<Position>();
					auto yp = y->GetComponent<Position>();
					if ( xp && yp ) {
						return *xp < *yp;
					}
				}
				return true;
			});
		}

		// Temp
		vector<shared_ptr<Entity>> GetEntitiesAt(int x, int y) {
			vector<shared_ptr<Entity>> result;
			auto input = Filter<Position>();
			for(auto t : input ){
				shared_ptr<Entity> entity;
				shared_ptr<Position> pos;
				tie(entity, pos) = t;
				if ( (pos->X == x) && (pos->Y == y) ) {
					result.push_back(entity);
				}
			}
			return result;
		}

		void AddWall(int x, int y) {
			auto entity = CreateEntity();
			entity->AddComponent(Position(x, y));
			entity->AddComponent(Blocker());
			entity->AddComponent(View('+'));
		}

	private:
		vector<shared_ptr<Entity>> _entities;
	};
}

