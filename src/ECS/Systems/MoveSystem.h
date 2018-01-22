#pragma once

#include <iostream>
#include <memory>

#include "../EntityManager.h"
#include "../System.h"
#include "../Components/Movable.h"
#include "../Components/Position.h"

using namespace std;

namespace ECS {
	class MoveSystem: public System {
	public:
		void Update(shared_ptr<EntityManager> entities) override {
			auto input = entities->Filter<Movable, Position>();
			for ( auto item : input ) {
				shared_ptr<Movable> mov;
				shared_ptr<Position> pos;
				tie(ignore, mov, pos) = item;
				auto newPos = UpdatePosition(pos->X, pos->Y, mov->Direction);
				pos->X = newPos.X;
				pos->Y = newPos.Y;
			}
		}

		Position UpdatePosition(int x, int y, MoveDirection dir) {
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
	};
}

