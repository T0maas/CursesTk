#include "cursestk.h"

using namespace cursestk;
#ifndef MYWIN_H
#define MYWIN_H


class MyWin : public Window {
private:
	Label * label1;
	TextBox * textbox1;
	Button * button1;
	Button * button2;
	Button * button3;
	


public:
	MyWin();
	void InitializeComponents() ;
	void run();

	void on_button1_clicked() {
			this -> textbox1 -> Text = "hello";
		}
	void on_button2_clicked() {
			this -> label1 -> Text = textbox1 -> Text;
		}

	void on_button3_clicked(){
		this -> destroy();
		exit(0);
	}

};

#endif
