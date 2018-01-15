#pragma once
#include <string>
#include <vector>
#include "Entity.h"
#include "../Utils/TestRunner.h"
using namespace Utils;

namespace ECS {
	void TestAdd() {
		Entity e;
		Component c;
		e.AddComponent("Test", c);
		AssertEqual(e.GetComponentCount(), 1u, "");
	}

	void TestHas() {
		Entity e;
		Component c;
		string key = "Test";
		e.AddComponent(key, c);
		Assert(e.HasComponent(key), "");
	}

	void TestAll() {
		TestRunner tr;
		tr.RunTest(TestAdd, "TestAdd");
		tr.RunTest(TestHas, "TestHas");
	}
}



