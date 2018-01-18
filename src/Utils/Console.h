#pragma once

#include <cstdlib>

using namespace std;

namespace Utils {

	class Console {
	public:
		void Clear() {
#ifdef WIN32
			system("cls");
#else
			system("clear");
#endif
		}
	};

}
