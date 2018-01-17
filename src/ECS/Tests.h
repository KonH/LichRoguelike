#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Entity.h"
#include "../Utils/TestRunner.h"
using namespace std;
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

	void TestAdd1() {
		Entity e;
		Test::Text t("TestAdd1");
		e.AddComponent(t);
		AssertEqual(e.GetComponentCount(), 1u);
	}

	void TestAdd2() {
		Entity e;
		auto t = make_shared<Test::Text>("TestAdd2");
		e.AddComponent(t);
		AssertEqual(e.GetComponentCount(), 1u);
	}

	void TestHas() {
		Entity e;
		Test::Text t("TestHas");
		e.AddComponent(t);
		Assert(e.HasComponent<Test::Text>());
	}

	void TestGet() {
		Entity e;
		Test::Text t("test");
		e.AddComponent(t);
		auto result = e.GetComponent<Test::Text>();
		Assert(result);
		AssertEqual(t.text, result->text);
	}

	void AddComponentWithText(Entity& e, const string& text) {
		e.AddComponent(make_shared<Test::Text>(text));
	}

	void TestHold() {
		Entity e;
		AddComponentWithText(e, "TestHold");
		auto result = e.GetComponent<Test::Text>();
		Assert(result);
		AssertEqual(result->text, "TestHold");
	}

	void TestAll() {
		cerr << "Unit tests:" << endl;
		TestRunner c("Component");
		c.RunTest(TestAdd1, "Add1");
		c.RunTest(TestAdd2, "Add2");
		c.RunTest(TestHas, "Has");
		c.RunTest(TestGet, "Get");
		c.RunTest(TestHold, "Hold");
	}
}

