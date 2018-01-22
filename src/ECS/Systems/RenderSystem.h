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
				_out(outStream), _space(' '), _nextLine(' ') {
		}

		RenderSystem(ostream& outStream, char space) :
				_out(outStream), _space(space), _nextLine(' ') {
		}

		RenderSystem(ostream& outStream, char space, char nextLine) :
				_out(outStream), _space(space), _nextLine(nextLine) {
		}

		void Update(shared_ptr<EntityManager> entities) override {
			entities->SortEntities();
			auto input = entities->Filter<Position, View>();
			int x0 = 0, y0 = 0;
			int x = x0, y = y0;
			for ( auto item : input ) {
				shared_ptr<Position> pos;
				shared_ptr<View> view;
				tie(ignore, pos, view) = item;

				while ( y < pos->Y ) {
					NextLine();
					y++;
					x = x0;
				}
				while ( x < pos->X ) {
					x++;
					Space();
				}

				Print(view->Content);
			}
			NextLine();
		}

		void Print(const char& c) {
			_out << ' ' << c;
		}

		void Space() {
			Print(_space);
		}

		void NextLine() {
			if ( _nextLine != ' ' ) {
				_out << _nextLine;
			} else {
				_out << endl;
			}
		}

	private:
		ostream& _out;
		const char _space;
		const char _nextLine;
	};
}

