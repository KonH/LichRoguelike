#pragma once

#include <iostream>
#include <memory>

#include "../EntityManager.h"
#include "../System.h"
#include "../Components/Movable.h"
#include "../Components/Position.h"

using namespace std;

namespace ECS {
	class CollisionSystem: public System {
	public:
		void Update(shared_ptr<EntityManager> entities) override {
			auto input = entities->Filter<Movable, Position>();
			for ( auto item : input ) {
				shared_ptr<Movable> mov;
				shared_ptr<Position> pos;
				tie(ignore, mov, pos) = item;
				auto newPos = entities->GetNextPosition(pos->X, pos->Y, mov->Direction);
				auto destEntities = entities->GetEntitiesAt(newPos.X, newPos.Y);
				for ( auto dest : destEntities ) {
					if ( dest->HasComponent<Blocker>() ) {
						mov->Direction = MoveDirection::None;
					}
				}
			}
		}
	};
}

