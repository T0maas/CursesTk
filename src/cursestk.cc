#include "cursestk.h"
#include <curses.h>
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;
using namespace cursestk;

Window::Window() {
	initscr();
	noecho();
	curs_set(0);
	}
	
void Window::set_size(int _hsize,int _wsize) {
	hsize = _hsize;
	wsize = _wsize;
	}
	
void Window::set_pos(int _hpos,int _wpos){
	hpos = _hpos;
	wpos = _wpos;
	}

void Window::show() {
	this->win = newwin(hsize, wsize, hpos, wpos);
	keypad(win, TRUE);
	start_color();			/* Start color 			*/
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	wbkgd(win, COLOR_PAIR(1));
	box(win,0,0);
	mvwprintw(win,0,(wsize/2.0)-(strlen(title.c_str())/2.0),title.c_str());
	//vline(0,1);
	
	wrefresh(this->win);
	
	}
void Window::destroy() {
	endwin();
	}
	
void Window::Put(Label * label,int _vpos,int _hpos) {
	labels.push_back(newwin(3,10,hpos + _vpos , wpos + _hpos ));
	label->hpos = _hpos;
	label->vpos = _vpos;
	label_instance.push_back(label);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	wbkgd(labels[labels.size() -1], COLOR_PAIR(1));
	mvwprintw(labels[labels.size() -1],0,0,label ->Text.c_str());
	wrefresh(labels[labels.size() -1]);
	wrefresh(win);
	}
	
void Window::Put(Button * button,int _vpos,int _hpos) {
	buttons.push_back ( newwin(button -> hsize,button -> vsize,_vpos + wpos +1,_hpos + hpos +1));
	button->hpos = _hpos;
	button->vpos = _vpos;
	button_instance.push_back(button);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	wbkgd(buttons[buttons.size() -1], COLOR_PAIR(2));
	
	mvwprintw(buttons[buttons.size() -1],1,1,button -> Text.c_str());
	wrefresh(buttons[buttons.size() -1]);
	wrefresh(win);
	if (button -> sel)
		{
			box(buttons[buttons.size() -1],0,0);
			mvwprintw(buttons[buttons.size() -1],1,1,button -> Text.c_str());
			wrefresh(buttons[buttons.size() -1]);
			}
	}
	
void Window::Put(TextBox * textbox,int _vpos,int _hpos) {
	textboxs.push_back(newwin(textbox -> hsize, textbox -> vsize, hpos + _vpos +1, wpos + _hpos +1)  );
	textbox->hpos = _hpos;
	textbox->vpos = _vpos;
	textbox_instance.push_back(textbox);
	init_pair(3,COLOR_BLACK,COLOR_BLUE);
	wbkgd( textboxs[textboxs.size() -1 ] ,COLOR_PAIR(3) );
	
	mvwprintw(textboxs[textboxs.size() -1 ] , 0,0, textbox -> Text.c_str() );
	wrefresh(textboxs[textboxs.size() -1 ]);
	wrefresh(win);
	
	if (textbox -> sel) 
	{
		init_pair(4,COLOR_BLACK,COLOR_YELLOW);
		wbkgd( textboxs[textboxs.size() -1 ] ,COLOR_PAIR(4) );
		mvwprintw(textboxs[textboxs.size() -1 ] , 0,0, textbox -> Text.c_str() );
		wrefresh(textboxs[textboxs.size() -1 ]);
		}
	
	}
	
	
void Window::Update() {
	for (int i=0;i < buttons.size();i++ ){
		mvwprintw(buttons[i],1,1,(button_instance[i] ->Text).c_str() );
		if(button_instance[i] -> sel)
			box(buttons[i],0,0);
		else {
			werase(buttons[i]);
			mvwprintw(buttons[i],1,1,(button_instance[i] ->Text).c_str() );
			}
		wrefresh(buttons[i]);
		wrefresh(win);
	}
	

	for (int i=0;i < labels.size();i++ ){
			werase(labels[i]);
			mvwprintw(labels[i],1,1,(label_instance[i] ->Text).c_str() );
			wrefresh(labels[i]);
			wrefresh(win);
		}

	for (int i=0;i< textboxs.size();i++) {
		werase(textboxs[i]);
		mvwprintw(textboxs[i],0,0, (textbox_instance[i] -> Text).c_str() );

		if (textbox_instance[i] -> sel){
			if (textbox_instance[i] -> editing == true)
				init_pair(4,COLOR_BLACK,COLOR_GREEN);
			else
				init_pair(4,COLOR_BLACK,COLOR_YELLOW);
			wbkgd( textboxs[i] ,COLOR_PAIR(4) );
			}
			else {
				init_pair(3,COLOR_BLACK,COLOR_BLUE);
				wbkgd( textboxs[i] ,COLOR_PAIR(3) );
				}
				wrefresh(textboxs[i]);
				wrefresh(win);
		}
	}

int Window::getwinchar() {
	return wgetch(win);
	}


void Window::DeselAll() {
	for (int i=0;i<buttons.size();i++)
		button_instance[i] -> sel = false;
	for (int i=0;i<textboxs.size();i++)
		textbox_instance[i] -> sel = false;
	}
	
void TextBox::edit(bool tf) {
	if (tf == true)
		editing = true;
	else
		editing = false;
}

void Window::ctkInit()
{
	int c;
		int selection;
		int x=0;
		int lastx=0;
		int y=0;
		int lasty=0;
		int editId;
		while (true)
		{
			bool selected;
			this->Update();
			c= this->getwinchar();
			if (!this -> editlock)
			switch (c)
			{
				case KEY_LEFT:
					lastx--;
					selected = false;
					for (y = lasty;y >= 0;y--)
						for (x = lastx  ;x >= 0;x--)
						{	if (!selected)
							for (int i=0;i < button_instance.size();i++)
								if (x == button_instance[i]-> hpos && y == button_instance[i]->vpos)
								{
									this->DeselAll();
									button_instance[i]->sel = true;
									this -> Update();
									selected = true;
									lastx = x;
									lasty = y;
									break;
								}
						if (!selected)
							for (int i=0;i < textbox_instance.size();i++)
								if (x == textbox_instance[i]-> hpos && y == textbox_instance[i]->vpos)
								{
									this->DeselAll();
									textbox_instance[i]->sel = true;
									selected = true;
									lastx = x;
									lasty = y;
									break;
								}

						}
				break;

				case KEY_RIGHT:
					lastx++;
					selected = false;
					for (y = lasty;y < this->hsize;y++)
					for (x = lastx  ;x<this->wsize;x++)
					{	if (!selected)
						for (int i=0;i < button_instance.size();i++)
							if (x == button_instance[i]-> hpos && y == button_instance[i]->vpos)
							{
								this->DeselAll();
								button_instance[i]->sel = true;
								this -> Update();
								selected = true;
								lastx = x;
								lasty = y;
								break;
							}
						if (!selected)
						for (int i=0;i < textbox_instance.size();i++)
							if (x == textbox_instance[i]-> hpos && y == textbox_instance[i]->vpos)
							{
								this->DeselAll();
								textbox_instance[i]->sel = true;
								selected = true;
								lastx = x;
								lasty = y;
								break;
							}

					}
					break;
				case KEY_UP:
					selected = false;
					lasty--;
					for (x = lastx ;x >= 0 ;x--)
					for (y = lasty;y >=0;y--)
						{
							if (!selected)
								for (int i=0;i < button_instance.size();i++)
									if (x == button_instance[i]-> hpos && y == button_instance[i]->vpos)
									{
										this->DeselAll();
										button_instance[i]->sel = true;
										this -> Update();

										selected = true;
										lasty = y;
										lastx = x;
										break;
									}
							if (!selected)lasty = y-1;
								for (int i=0;i < textbox_instance.size();i++)
									if (x == textbox_instance[i]-> hpos && y == textbox_instance[i]->vpos)
									{
										this->DeselAll();
										textbox_instance[i]->sel = true;
										selected = true;
										lasty = y;
										lastx = x;
										break;
									}
						}
					break;


				case KEY_DOWN:
					lasty++;
					selected = false;
					for (x = lastx  ;x<this->wsize;x++)
					for (y = lasty;y < this->hsize;y++)
					{	if (!selected)
						for (int i=0;i < button_instance.size();i++)
							if (x == button_instance[i]-> hpos && y == button_instance[i]->vpos)
							{
								this->DeselAll();
								button_instance[i]->sel = true;
								this -> Update();
								selected = true;
								lasty = y;
								lastx = x;
								break;
							}
						if (!selected)
						for (int i=0;i < textbox_instance.size();i++)
							if (x == textbox_instance[i]-> hpos && y == textbox_instance[i]->vpos)
							{
								this->DeselAll();
								textbox_instance[i]->sel = true;
								selected = true;
								lasty = y;
								lastx = x;
								break;
							}

					}
					break;
				case 10:
					for (int i=0;i < button_instance.size();i++)
						if (button_instance[i] -> sel == true && button_instance[i] -> connected == true )
							button_instance[i] -> funct();
					for (int i=0;i < textbox_instance.size();i++)
					{
						if (textbox_instance[i] -> sel == true)
						{
							textbox_instance[i]->editing = true;
							editlock = true;
							editId = i;
						}
					}

				break;
			}
			else //editing
			{
				if (c == KEY_BACKSPACE)
				{
					string myString  = textbox_instance[editId] -> Text;
					if (myString.length() > 0) {
					myString.pop_back();
					textbox_instance[editId] -> Text = myString;}
				}
				else
					textbox_instance[editId] -> Text += c;
				if (c == 10)
				{
					textbox_instance[editId]->editing = false;
					editlock = false;
				}

			}
		}
}

Label::Label() {

	}
	
Button::Button() {
	
	}
	
TextBox::TextBox() {
	
	}


void Button::connect(void fcn(void))
{
	connected = true;
	funct = fcn;
}
