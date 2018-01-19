#pragma once

#include <iostream>
#include <memory>

#include "../EntityManager.h"
#include "../System.h"
#include "../Components/View.h"
#include "../Components/Position.h"

using namespace std;

namespace ECS {
	class RenderSystem: public System {
	public:
		RenderSystem(ostream& outStream) :
				out(outStream) {
		}

		void Update(shared_ptr<EntityManager> entities) override {
			entities->SortEntities();
			auto input = entities->Filter<Position, View>();
			int x = 0, y = 0;
			for ( auto item : input ) {
				shared_ptr<Position> pos;
				shared_ptr<View> view;
				tie(ignore, pos, view) = item;

				while ( y < pos->Y ) {
					NextLine();
					y++;
					x = 0;
				}
				while ( x < pos->X ) {
					x++;
					Space();
				}

				Print(view->Content);
			}
		}

		void Print(const char& c) {
			out << ' ' << c;
		}

		void Space() {
			Print(' ');
		}

		void NextLine() {
			out << endl;
		}

	private:
		ostream& out;
	};
}

