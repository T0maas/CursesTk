#include "cursestk.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
	Window mywin;
	//mywin.set_size(10,30);
	mywin.set_pos(10,10);
	mywin.title = "Hello";
	Label label1;
	label1.Text = "labe1";
	Button button1;
	button1.Text = "tlac1";
	Button button2;
	button2.Text = "tlac2";
	button2.vsize = 10;
	button2.hsize = 3;
	button2.sel = true;
	TextBox textbox1;
	textbox1.vsize += 3;
	textbox1.Text = "sample";
	//textbox1.sel = true;
	
	mywin.show();
	mywin.Put(& label1,3,12);
	mywin.Put(& button1,5,0);
	mywin.Put(& button2,5,12);
	mywin.Put(& textbox1, 1,0);
	int c;
	int selection = 2;
	
	while (true) {
		mywin.Update();
		c= mywin.getwinchar();
		if (!mywin.editlock)
		switch (c) {
			case KEY_LEFT:
				mywin.DeselAll();
				button1.sel= true;
				mywin.Update();
				selection = 1;
				break;
			case KEY_RIGHT:
				mywin.DeselAll();
				button2.sel = true;
				mywin.Update();
				selection = 2;
				break;
			case KEY_UP:
				selection = 3;
				mywin.DeselAll();
				textbox1.sel = true;
				mywin.Update();
			break;
			}
		else {
			if (c == KEY_BACKSPACE){

				string myString  = textbox1.Text;
				myString.pop_back();
				textbox1.Text = myString;
			}
			else
				textbox1.Text += c;
		}
		
		if (c == 10) { 
		switch (selection) {
			case 1: 
			textbox1.Text = "hello     ";
			break;
			
			case 2: 
			label1.Text =  textbox1.Text;
			break;

			case 3:
				if (!textbox1.editing)
				{
					textbox1.edit(true);
					mywin.editlock = true;
					textbox1.Text = "ed";
				}
				else {
					textbox1.edit(false);
					mywin.editlock = false;
				}
			break;
			}
			}
		}
	
	
	mywin.destroy();
	return 0;
	 }
