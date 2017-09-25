#include "cursestk.h"
#include <iostream>
#include <unistd.h>
#include "MyWin.h"

using namespace std;



int main() {
	MyWin * win1 = new MyWin();
	win1 -> run();
	return 0;
}

