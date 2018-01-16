#include "Console.h"
#include <cstdlib>

using namespace std;

namespace Utils {

	void Console::Clear() {
#ifdef WIN32
		system("cls");
#else
		system("clear");
#endif
	}

}
