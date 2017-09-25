#include "MyWin.h"

MyWin::MyWin() {
	InitializeComponents();
}


Label * label1;
TextBox * textbox1;
Button * button1;
Button * button2;

void on_button1_clicked() {
		textbox1 -> Text = "hello";
	}
void on_button2_clicked() {
		label1 -> Text = textbox1 -> Text;
	}

void MyWin::InitializeComponents(){
	label1 = new Label();
	textbox1 = new TextBox();
	button1 = new Button();
	button2 = new Button();

	this -> set_pos(10,10);
	this -> title = "Main Title";

	label1 -> Text = "labe1";

	button1 -> Text = "SetTxtB";

	button2 -> Text = "SetLbl";
	button2 -> vsize = 10;
	button2 -> hsize = 3;
	button1 -> connect(on_button1_clicked);
	button2 -> connect(on_button2_clicked);

	textbox1 -> vsize += 3;
	textbox1 -> Text = "sample";
}

void MyWin::run()
{

		this -> show();
		this -> Put(label1,3,12);
		this -> Put( button1,5,0);
		this -> Put( button2,5,12);
		this -> Put( textbox1, 0,0);
		this -> ctkInit();
		this -> destroy();
	}





