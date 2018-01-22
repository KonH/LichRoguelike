#include <iostream>

#include "ECS/Engine.h"
#include "ECS/Tests.h"
#include "ECS/Systems/PlayerMoveSystem.h"
#include "ECS/Systems/MoveSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/DebugSystem.h"

using namespace ECS;
using namespace std;

int main() {
	TestAll();

	auto entities = make_shared<EntityManager>();

	auto player = entities->CreateEntity();
	player->AddComponent(Position(5, 5));
	player->AddComponent(Movable());
	player->AddComponent(Player());
	player->AddComponent(View('@'));

	for ( int x = 0; x <= 10; ++x ) {
		entities->AddWall(x, 0);
		entities->AddWall(x, 10);
	}

	for ( int y = 1; y <= 9; ++y ) {
		entities->AddWall(0, y);
		entities->AddWall(10, y);
	}

	Engine engine(entities);
	engine.AddSystem(make_shared<RenderSystem>(11, 11, cout));
	engine.AddSystem(make_shared<DebugSystem>(cout));
	engine.AddSystem(make_shared<PlayerMoveSystem>());
	engine.AddSystem(make_shared<MoveSystem>());

	while ( true ) {
		engine.Update();
	}

	return 0;
}
