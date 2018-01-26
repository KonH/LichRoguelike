#pragma once

#include <tuple>

#include "../../ECS/System.h"
#include "../../ECS/EntityManager.h"
#include "../../ECS/Components/Player.h"
#include "../../ECS/Components/Position.h"

#include "../Components/Bones.h"
#include "../Components/BonesContainer.h"

using namespace std;
using namespace ECS;

namespace Game {
	class BonesCollectSystem: public System {
	public:
		void Update(shared_ptr<EntityManager> entities) override {
			auto players = entities->Filter<Player, Position, BonesContainer>();
			for ( auto player : players ) {
				shared_ptr<Position> pos;
				shared_ptr<BonesContainer> container;
				tie(ignore, ignore, pos, container) = player;
				auto entitiesAt = entities->GetEntitiesAt(*pos);
				for ( auto e : entitiesAt ) {
					auto bones = e->GetComponent<Bones>();
					if ( bones ) {
						container->Count += bones->Count;
						entities->RemoveEntity(e);
					}
				}
			}
		}
	};
}

