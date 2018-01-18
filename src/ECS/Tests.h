#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Components/Position.h"
#include "Components/View.h"
#include "Entity.h"
#include "EntityManager.h"
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

	void TestEntityManager() {
		TestRunner tr("EntityManager");
		tr.RunTest(AddEntity, "Add");
		tr.RunTest(CreateEntity, "Create");
		tr.RunTest(RemoveEntity, "Remove");
		tr.RunTest(FilterEntities1, "Filter1");
		tr.RunTest(FilterEntities2, "Filter2");
	}

	void TestAll() {
		cerr << "Unit tests:" << endl;
		TestComponent();
		TestEntityManager();
	}
}

