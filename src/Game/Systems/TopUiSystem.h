#pragma once

#include <iostream>
#include <tuple>

#include "../../ECS/System.h"
#include "../../ECS/EntityManager.h"
#include "../../ECS/Components/Player.h"

#include "../Components/BonesContainer.h"

using namespace std;
using namespace ECS;

namespace Game {
	class TopUiSystem: public System {
	public:
		TopUiSystem(ostream& outStream) :
				_out(outStream) {
		}

		void Update(shared_ptr<EntityManager> entities) override {
			auto players = entities->Filter<Player, BonesContainer>();
			for ( auto player : players ) {
				shared_ptr<BonesContainer> container;
				tie(ignore, ignore, container) = player;
				_out << "% " << container->Count << endl;
			}
		}

	private:
		ostream& _out;
	};
}

