#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Console.h"

#include "../EntityManager.h"
#include "../System.h"
#include "../Components/Movable.h"
#include "../Components/Player.h"

using namespace std;
using namespace Utils;

namespace ECS {
	class PlayerMoveSystem: public System {
	public:
		void Update(shared_ptr<EntityManager> entities) override {
			auto input = entities->Filter<Movable, Player>();
			for ( auto item : input ) {
				shared_ptr<Movable> mov;
				shared_ptr<Player> player;
				tie(ignore, mov, player) = item;
				mov->Direction = GetDirection();
			}
		}

		MoveDirection GetDirection() {
			char c = _console.GetChar();
			switch ( c ) {
			case 'w':
				return MoveDirection::Up;
			case 's':
				return MoveDirection::Down;
			case 'a':
				return MoveDirection::Left;
			case 'd':
				return MoveDirection::Right;
			}
			return MoveDirection::None;
		}

	private:
		Console _console;
	};
}

