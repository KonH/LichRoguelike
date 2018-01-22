#include <iostream>

#include "ECS/Engine.h"
#include "ECS/Tests.h"
#include "ECS/Systems/PlayerMoveSystem.h"
#include "ECS/Systems/MoveSystem.h"
#include "ECS/Systems/RenderSystem.h"

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

	Engine engine(entities);
	engine.AddSystem(make_shared<PlayerMoveSystem>());
	engine.AddSystem(make_shared<MoveSystem>());
	engine.AddSystem(make_shared<RenderSystem>(cout));

	while(true){
		engine.Update();
	}

	return 0;
}
