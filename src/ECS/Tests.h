#pragma once
#include <string>
#include <vector>
#include "Entity.h"
#include "../Utils/TestRunner.h"
using namespace Utils;

namespace ECS {
	namespace Test {
		class Text: public Component {
		public:
			const string text;
			Text(const string& t) :
					text(t) {
			}
			;
		};
	}

	void TestAdd() {
		Entity e;
		Component c;
		e.AddComponent(c);
		AssertEqual(e.GetComponentCount(), 1u);
	}

	void TestHas() {
		Entity e;
		Component c;
		e.AddComponent(c);
		Assert(e.HasComponent<Component>());
	}

	void TestGet() {
		Entity e;
		Test::Text t("test");
		e.AddComponent(t);
		auto result = e.GetComponent<Test::Text>();
		Assert(result, "");
		AssertEqual(t.text, result->text);
	}

	void TestAll() {
		cerr << "Unit tests:" << endl;
		TestRunner c("Component");
		c.RunTest(TestAdd, "Add");
		c.RunTest(TestHas, "Has");
		c.RunTest(TestGet, "Get");
	}
}

