#include "cursestk.h"
#include <curses.h>
#include <string.h>
#include <vector>
using namespace std;

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
	
void Window::Put(Label * label,int _hpos,int _wpos) {
	labels.push_back(newwin(3,10,hpos + _hpos , wpos + _wpos ));
	label_instance.push_back(label);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	wbkgd(labels[labels.size() -1], COLOR_PAIR(1));
	mvwprintw(labels[labels.size() -1],-2,-2,label ->Text.c_str());
	wrefresh(labels[labels.size() -1]);
	wrefresh(win);
	}
	
void Window::Put(Button * button,int _hpos,int _wpos) {
	buttons.push_back ( newwin(button -> hsize,button -> vsize,_hpos + hpos +1,_wpos + wpos +1));
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
	
void Window::Put(TextBox * textbox,int _hpos,int _wpos) {
	textboxs.push_back(newwin(textbox -> hsize, textbox -> vsize, hpos + _hpos +1, wpos + _wpos +1)  );
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

Label::Label() {

	}
	
Button::Button() {
	
	}
	
TextBox::TextBox() {
	
	}
