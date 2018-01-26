#pragma once

#include <iostream>
#include <memory>

#include "../../Utils/Console.h"

#include "../EntityManager.h"
#include "../System.h"
#include "../Components/View.h"
#include "../Components/Position.h"

using namespace std;
using namespace Utils;

namespace ECS {
	class RenderSystem: public System {
	public:
		RenderSystem(int w, int h, ostream& outStream) :
				_width(w), _height(h), _out(outStream), _space(' '), _nextLine(' ') {
		}

		RenderSystem(int w, int h, ostream& outStream, char space, char nextLine) :
				_width(w), _height(h), _out(outStream), _space(space), _nextLine(nextLine) {
		}

		void Update(shared_ptr<EntityManager> entities) override {
			entities->UpdatePositionCache();
			for ( int y = 0; y < _height; ++y ) {
				for ( int x = 0; x < _width; ++x ) {
					auto input = entities->GetEntitiesAt(Position(x, y));
					if ( input.empty() ) {
						_out << _space;
					} else {
						auto lastEntity = input.back();
						auto view = lastEntity->GetComponent<View>();
						if ( view ) {
							_out << view->Content;
						} else {
							_out << _space;
						}
					}
					_out << ' ';
				}
				NextLine();
			}
		}

		void NextLine() {
			if ( _nextLine != ' ' ) {
				_out << _nextLine;
			} else {
				_out << endl;
			}
		}

	private:
		const char _width;
		const char _height;
		ostream& _out;
		const char _space;
		const char _nextLine;
	};
}

