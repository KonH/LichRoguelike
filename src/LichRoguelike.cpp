#include <iostream>

#include "ECS/Engine.h"
#include "ECS/Tests.h"
#include "ECS/Systems/EngineDebugger.h"
#include "ECS/Systems/DebugSystem.h"
#include "ECS/Systems/PlayerMoveSystem.h"
#include "ECS/Systems/MoveSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/ClearScreenSystem.h"
#include "ECS/Systems/CollisionSystem.h"

#include "Game/Components/Bones.h"
#include "Game/Components/BonesContainer.h"
#include "Game/Systems/TopUiSystem.h"
#include "Game/Systems/BonesCollectSystem.h"

using namespace std;

using namespace ECS;
using namespace Game;

int main() {
	ECS::TestAll();

	auto entities = make_shared<EntityManager>();

	auto player = entities->CreateEntity();
	player->AddComponent(Position(5, 5));
	player->AddComponent(Movable());
	player->AddComponent(Player());
	player->AddComponent(View('@'));
	player->AddComponent(BonesContainer());

	for ( int x = 0; x <= 10; ++x ) {
		entities->AddWall(x, 0, '#');
		entities->AddWall(x, 10, '#');
	}

	for ( int y = 1; y <= 9; ++y ) {
		entities->AddWall(0, y, '#');
		entities->AddWall(10, y, '#');
	}

	for ( int x = 1; x <= 9; ++x ) {
		for ( int y = 1; y <= 9; ++y ) {
			if ( x != y ) {
				auto e = entities->CreateEntity();
				e->AddComponent(Position(x, y));
				e->AddComponent(Bones(1));
				e->AddComponent(View('%'));
			}
		}
	}

	Engine engine(entities);

	engine.AddSystem(make_shared<ClearScreenSystem>());
	engine.AddSystem(make_shared<TopUiSystem>(cout));
	engine.AddSystem(make_shared<RenderSystem>(11, 11, cout));
	engine.AddDebugger(make_shared<EngineDebugger>(cerr));
	//engine.AddSystem(make_shared<DebugSystem>(cerr));

	engine.AddSystem(make_shared<PlayerMoveSystem>());
	engine.AddSystem(make_shared<CollisionSystem>());
	engine.AddSystem(make_shared<MoveSystem>());
	engine.AddSystem(make_shared<BonesCollectSystem>());

	while ( true ) {
		engine.Update();
	}

	return 0;
}
