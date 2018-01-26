#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include <chrono>
#include <thread>

#include "../Engine.h"
#include "../System.h"

using namespace std;
using namespace std::chrono;

namespace ECS {
	class EngineDebugger : public System {
	public:
		EngineDebugger(ostream& outStream) :
				_outStream(outStream) {
		}

		void Update(shared_ptr<EntityManager> entities) {
			_outStream << endl;
			_outStream << "STATS:" << endl;
			for ( const auto& item : _measures ) {
				if ( item.second.empty() ) {
					continue;
				}
				auto sum = 0;
				for ( auto measure : item.second ) {
					sum += measure;
				}
				auto avg = sum / item.second.size();
				_outStream << item.first << " avg: " << avg << " ms" << endl;
			}
			_outStream << endl;
		}

		void StartSystem(shared_ptr<System> system) {
			_systemStart = steady_clock::now();
			_startedSystem = system;
		}

		void EndSystem() {
			if ( !_startedSystem ) {
				return;
			}
			auto now = steady_clock::now();
			auto elapsed = duration_cast<milliseconds>(now - _systemStart);
			_measures[typeid(*_startedSystem).name()].push_back(elapsed.count());
			_startedSystem.reset();
		}

	private:
		ostream& _outStream;
		time_point<steady_clock> _systemStart;
		shared_ptr<System> _startedSystem;
		map<string, vector<int>> _measures;
	};
}

