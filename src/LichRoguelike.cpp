#include <iostream>

#include "ECS/Engine.h"
#include "ECS/Tests.h"
#include "ECS/Systems/RenderSystem.h"

using namespace ECS;
using namespace std;

int main() {
	TestAll();

	// Temp
	auto entities = make_shared<EntityManager>();

	auto e0 = entities->CreateEntity();
	e0->AddComponent(View('x'));
	e0->AddComponent(Position(0, 1));

	auto e1 = entities->CreateEntity();
	e1->AddComponent(View('y'));
	e1->AddComponent(Position(2, 0));

	auto e2 = entities->CreateEntity();
	e2->AddComponent(View('z'));
	e2->AddComponent(Position(3, 3));

	auto eN = entities->CreateEntity();
	eN->AddComponent(View('w'));
	eN->AddComponent(Position(-1, -1));

	Engine engine(entities);
	auto render = make_shared<RenderSystem>(cout);
	engine.AddSystem(render);

	engine.Update();

	return 0;
}
