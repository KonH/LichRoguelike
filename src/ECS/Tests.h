#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include "../Utils/TestRunner.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Components/Position.h"
#include "Components/View.h"
#include "Systems/RenderSystem.h"

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

	void AddComponent1() {
		Entity e;
		Test::Text t("TestAdd1");
		e.AddComponent(t);
		AssertEqual(e.GetComponentCount(), 1u);
	}

	void AddComponent2() {
		Entity e;
		auto t = make_shared<Test::Text>("AddComponent2");
		e.AddComponent(t);
		AssertEqual(e.GetComponentCount(), 1u);
	}

	void HasComponent() {
		Entity e;
		Test::Text t("TestHas");
		e.AddComponent(t);
		Assert(e.HasComponent<Test::Text>());
	}

	void HasntComponent() {
		Entity e;
		Assert(!e.HasComponent<Test::Text>());
		Assert(!e.GetComponent<Test::Text>().get());
	}

	void GetComponent() {
		Entity e;
		Test::Text t("test");
		e.AddComponent(t);
		auto result = e.GetComponent<Test::Text>();
		Assert((bool) result);
		AssertEqual(t.text, result->text);
	}

	void AddComponentWithText(Entity& e, const string& text) {
		e.AddComponent(make_shared<Test::Text>(text));
	}

	void HoldComponent1() {
		Entity e;
		AddComponentWithText(e, "HoldComponent1");
		auto result = e.GetComponent<Test::Text>();
		Assert((bool) result);
		AssertEqual(result->text, "HoldComponent1");
	}

	shared_ptr<Test::Text> GetComponentFromLocalEntity() {
		Entity e;
		AddComponentWithText(e, "HoldComponent2");
		return e.GetComponent<Test::Text>();
	}

	void HoldComponent2() {
		auto t = GetComponentFromLocalEntity();
		Assert((bool) t);
		AssertEqual(t->text, "HoldComponent2");
	}

	void TestComponent() {
		TestRunner tr("Component");
		tr.RunTest(AddComponent1, "Add1");
		tr.RunTest(AddComponent2, "Add2");
		tr.RunTest(HasComponent, "Has");
		tr.RunTest(HasntComponent, "Hasn't");
		tr.RunTest(GetComponent, "Get");
		tr.RunTest(HoldComponent1, "Hold1");
		tr.RunTest(HoldComponent2, "Hold2");
	}

	void AddEntity() {
		EntityManager em;
		AssertEqual(em.GetEntitesCount(), 0u);
		em.AddEntity(make_shared<Entity>());
		AssertEqual(em.GetEntitesCount(), 1u);
	}

	void CreateEntity() {
		EntityManager em;
		AssertEqual(em.GetEntitesCount(), 0u);
		auto entity = em.CreateEntity();
		Assert((bool) entity);
		AssertEqual(em.GetEntitesCount(), 1u);
	}

	void RemoveEntity() {
		auto e = make_shared<Entity>();
		EntityManager em;
		em.AddEntity(e);
		AssertEqual(em.GetEntitesCount(), 1u);
		em.RemoveEntity(e);
		AssertEqual(em.GetEntitesCount(), 0u);
	}

	void FilterEntities1() {
		auto e1 = make_shared<Entity>();
		auto e2 = make_shared<Entity>();
		Position p(3, 5);
		e2->AddComponent(make_shared<Position>(p));

		EntityManager em;
		em.AddEntity(e1);
		em.AddEntity(e2);
		AssertEqual(em.GetEntitesCount(), 2u);

		auto result = em.Filter<Position>();
		AssertEqual(result.size(), 1u);

		auto firstItem = result[0];
		shared_ptr<Entity> re;
		shared_ptr<Position> rc;
		tie(re, rc) = firstItem;
		Assert((bool) re);
		Assert((bool) rc);
		AssertEqual(rc->X, p.X);
	}

	void FilterEntities2() {
		auto e1 = make_shared<Entity>();
		auto e2 = make_shared<Entity>();
		Position p(3, 5);
		View v('x');
		e2->AddComponent(p);
		e2->AddComponent(v);

		EntityManager em;
		em.AddEntity(e1);
		em.AddEntity(e2);
		AssertEqual(em.GetEntitesCount(), 2u);

		auto result = em.Filter<Position, View>();
		AssertEqual(result.size(), 1u);

		auto firstItem = result[0];
		shared_ptr<Entity> re;
		shared_ptr<Position> rp;
		shared_ptr<View> rv;
		tie(re, rp, rv) = firstItem;
		Assert((bool) re);
		Assert((bool) rp);
		AssertEqual(rp->X, p.X);
		Assert((bool) rv);
		AssertEqual(rv->Content, v.Content);
	}

	void ComparePositions() {
		// X 0 1 .. Xn
		// Y
		// 0
		// 1
		// ..
		// Yn
		Position x1(0, 1), y1(0, 0);
		Assert(x1 > y1, "#1");
		Position x2(3, 0), y2(1, 0);
		Assert(x2 > y2, "#2");
		Position x3(0, 0), y3(0, 2);
		Assert(x3 < y3, "#3");
		Position x4(-1, 0), y4(1, 0);
		Assert(x4 < y4, "#4");
		vector<Position> expected =
		        { { -1, -1 }, { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 }, { 10, 1 }, { 1, 10 } };
		vector<Position> input =
		        { { 1, 1 }, { 1, 10 }, { 1, 0 }, { 0, 1 }, { -1, -1 }, { 10, 1 }, { 0, 0 } };
		sort(begin(input), end(input));
		AssertEqual(input, expected, "#5");
	}

	void SortEntities() {
		EntityManager em;
		Position p0(0, 0);
		Position p1(2, 0);
		Position p2(0, 1);
		em.CreateEntity()->AddComponent(p2);
		em.CreateEntity()->AddComponent(p0);
		em.CreateEntity()->AddComponent(p1);

		em.SortEntities();

		auto result = em.Filter<Position>();
		AssertEqual(result.size(), 3u);

		shared_ptr<Position> rp0, rp1, rp2;
		tie(ignore, rp0) = result[0];
		AssertEqual(p0, *rp0);
		tie(ignore, rp1) = result[1];
		AssertEqual(p1, *rp1);
		tie(ignore, rp2) = result[2];
		AssertEqual(p2, *rp2);
	}

	void TestEntityManager() {
		TestRunner tr("EntityManager");
		tr.RunTest(AddEntity, "Add");
		tr.RunTest(CreateEntity, "Create");
		tr.RunTest(RemoveEntity, "Remove");
		tr.RunTest(ComparePositions, "Compare");
		tr.RunTest(FilterEntities1, "Filter1");
		tr.RunTest(FilterEntities2, "Filter2");
		tr.RunTest(SortEntities, "Sort");
	}

	void Render() {
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

		ostringstream actual;
		auto render = make_shared<RenderSystem>(4, 4, actual, '_', ';');
		render->Update(entities);

		ostringstream expected;
		expected << "_ _ y _ ;";
		expected << "x _ _ _ ;";
		expected << "_ _ _ _ ;";
		expected << "_ _ _ z ;";

		string actualStr = actual.str();
		string expectedStr = expected.str();
		AssertEqual("\"" + actualStr + "\"", "\"" + expectedStr + "\"");
	}

	void TestSystems() {
		TestRunner tr("Systems");
		tr.RunTest(Render, "Render");
	}

	void TestAll() {
		cerr << "Unit tests:" << endl;
		TestComponent();
		TestEntityManager();
		TestSystems();
	}
}

