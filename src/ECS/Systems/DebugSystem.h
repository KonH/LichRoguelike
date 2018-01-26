#pragma once

#include <iostream>
#include <memory>

#include "../EntityManager.h"
#include "../System.h"
#include "../Components/Position.h"

using namespace std;

namespace ECS {
	class DebugSystem: public System {
	public:
		DebugSystem(ostream& out) :
				_out(out) {
		}

		void Update(shared_ptr<EntityManager> entities) override {
			entities->SortEntities();
			auto input = entities->Filter<Position>();
			int y = 0;
			for ( auto item : input ) {
				shared_ptr<Entity> e;
				shared_ptr<Position> pos;
				tie(e, pos) = item;
				_out << *pos << " {";
				auto comps = e->GetComponents();
				for ( auto c : comps ) {
					_out << c->Name << ";";
				}
				_out << "} ";
				if ( pos->Y > y ) {
					y = pos->Y;
					_out << endl;
				}
			}
		}

	private:
		ostream& _out;
	};
}

