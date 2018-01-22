#pragma once

#include <cstdlib>
#include <conio.h>

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

		char GetChar() {
			return getch();
		}
	};

}
