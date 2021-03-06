#ifndef CURSEST_H
#define CURSEST_H

#include <curses.h>
#include <string>
#include <vector>
#include "events.h"

namespace cursestk {
class Label {

public:
	std::string Text;
	Label();
	int hpos,vpos;
};


class Button {
public:
	std::string Text;
	Button();
	bool connected=true;
	int hsize=3,vsize=10,sel=0,hpos,vpos;

	Event * ButtonClickEvent = new Event();
	void click() {
		ButtonClickEvent -> Invoke();
	}


};

class TextBox{
public:
	TextBox();
	std::string Text;
	int hsize=1,vsize=6,sel=0,vpos,hpos;
	bool editing=false;
	void edit(bool tf);
};

class Window : public Object
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
	~Window();
	std::string title;
	bool editlock = false;
	void set_size(int _hsize,int _wsize);
	void set_pos(int _hpos,int _wpos);
	void show();
	void destroy();
	void Put(Label * label,int _hpos,int _vpos);
	void Put(Button * button,int _hpos,int _vpos);
	void Put(TextBox * textbox,int _hpos,int _vpos);
	void Update();
	int getwinchar();
	void DeselAll();
	void ctkInit();
	void dummy() {

	}


};
}


#endif
