#include "cursestk.h"
#include <iostream>
#include <unistd.h>
#include "MyWin.h"

using namespace std;


MyWin * win1;
int main() {
	 win1 = new MyWin();
	win1 -> run();

	return 0;
}

void on_button3_clicked(){
	win1 -> destroy();
	exit(0);
}
