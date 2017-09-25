#include <curses.h>
#include <string>
#include <vector>

class Label {

public:
	std::string Text;
	Label();
};

class Button {
public:
	std::string Text;
	Button();
	int hsize=3,vsize=10,sel=0;

};

class TextBox{
public:
	TextBox();
	std::string Text;
	int hsize=1,vsize=6,sel=0;
	bool editing=false;
	void edit(bool tf);
};

class Window
{

private:
	std::vector<Button*>  button_instance;
	std::vector<TextBox*>  textbox_instance;
	std::vector<Label*> label_instance;

	std::vector<WINDOW*> buttons;
	std::vector<WINDOW*> textboxs;
	std::vector<WINDOW*> labels;

	int hsize=30,wsize=60,hpos=0,wpos=0;
	WINDOW * win = NULL;



public:
	Window();
	std::string title;
	bool editlock = false;
	void set_size(int _hsize,int _wsize);
	void set_pos(int _hpos,int _wpos);
	void show();
	void destroy();
	void Put(Label * label,int _hpos,int _wpos);
	void Put(Button * button,int _hpos,int _wpos);
	void Put(TextBox * textbox,int _hpos,int _wpos);
	void Update();
	int getwinchar();
	void DeselAll();

};
