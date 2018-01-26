#pragma once

#include <memory>

#include "../../Utils/Console.h"

#include "../EntityManager.h"
#include "../System.h"

using namespace std;
using namespace Utils;

namespace ECS {
	class ClearScreenSystem: public System {
	public:
		void Update(shared_ptr<EntityManager> entities) override {
			_console.Clear();
		}

	private:
		Console _console;
	};
}

