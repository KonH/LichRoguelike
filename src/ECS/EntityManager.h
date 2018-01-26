#pragma once

#include <vector>
#include <tuple>
#include <algorithm>
#include <memory>

#include "Entity.h"
#include "Components/Position.h"
#include "Components/View.h"
#include "Components/Blocker.h"
#include "Components/Movable.h"

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
		using ECTuple1Vector = vector<tuple<shared_ptr<Entity>, shared_ptr<T>>>;

		template<class T>
		ECTuple1Vector<T> Filter() {
			ECTuple1Vector<T> result;
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
		using ECTuple2Vector = vector<tuple<shared_ptr<Entity>, shared_ptr<T1>, shared_ptr<T2>>>;

		template<class T1, class T2>
		ECTuple2Vector<T1, T2> Filter() {
			ECTuple2Vector<T1, T2> result;
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

		template<class T1, class T2, class T3>
		using ECTuple3Vector = vector<tuple<shared_ptr<Entity>, shared_ptr<T1>, shared_ptr<T2>, shared_ptr<T3>>>;

		template<class T1, class T2, class T3>
		ECTuple3Vector<T1, T2, T3> Filter() {
			ECTuple3Vector<T1, T2, T3> result;
			for ( auto& e : _entities ) {
				if ( e ) {
					auto c1 = e->GetComponent<T1>();
					auto c2 = e->GetComponent<T2>();
					auto c3 = e->GetComponent<T3>();
					if ( c1 && c2 && c3) {
						auto t = make_tuple(e, c1, c2, c3);
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

		void UpdatePositionCache() {
			_positionCache.clear();
			auto input = Filter<Position>();
			for ( auto t : input ) {
				shared_ptr<Entity> entity;
				shared_ptr<Position> pos;
				tie(entity, pos) = t;
				_positionCache[*pos].push_back(entity);

			}
		}

		vector<shared_ptr<Entity>> GetEntitiesAt(Position targetPos) {
			return _positionCache[targetPos];
		}

		Position GetNextPosition(int x, int y, MoveDirection dir) {
			switch ( dir ) {
			case MoveDirection::Up:
				return {x, y-1};
			case MoveDirection::Down:
				return {x, y+1};
			case MoveDirection::Left:
				return {x-1,y};
			case MoveDirection::Right:
				return {x+1, y};
			default:
				return {x, y};
			}
		}

		shared_ptr<Entity> AddWall(int x, int y, char c) {
			auto entity = CreateEntity();
			entity->AddComponent(Position(x, y));
			entity->AddComponent(Blocker());
			entity->AddComponent(View(c));
			return entity;
		}

	private:
		vector<shared_ptr<Entity>> _entities;
		map<Position, vector<shared_ptr<Entity>>> _positionCache;
	};
}

