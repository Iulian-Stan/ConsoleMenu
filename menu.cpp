#include <iostream>
#include <conio.h>
#include <string.h>
#include "global.h"
#include "menu.h"
using namespace std;

/****** MenuItem class methods ******/

MenuItem::MenuItem(char *name) {
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->parent = NULL;
}

void MenuItem::printHelper() {
	if (parent != NULL) {
		parent->printHelper();
		cout << " -> " << name;
	}
	else {
		cout << name;
	}
}

void MenuItem::printTitle() {
	printHelper();
	cout << ":" << endl << endl;
}

char *MenuItem::getName() {
	return this->name;
}

MenuItem::~MenuItem() {
	cout << "remove item : " << name << endl;
	delete[] name;	
}

/****** Action class methods ******/

Action::Action(char *name) : MenuItem(name) {}

void Action::execute() {
	clrscr();
	this->printTitle();
	this->executeAction();
}

/****** Menu class methods ******/

Menu::Menu(char *name) : MenuItem(name) {
	this->items = new MenuItem*[maxSize];
	this->size = 0;	
}

Menu::~Menu() {
	for (int i=0; i<size; i++) {
		delete items[i];
	}
	delete[] items;
}

void Menu::addItem(MenuItem *item) {
	size++;
	items[size - 1] = item;
	item->parent = this;
}

void Menu::print() {
	for (int i = 0; i < this->size; i++) {
		cout << "\t" << i + 1 << " - " << items[i]->getName();
		cout << endl <<endl;
	}
	cout << "\t" << "ESC or 0 - Quit" << endl << endl;
}

//returns selected item index, otherwise -1 to quit
int Menu::readCommand() {
	while (1) {
		char ch; 

		cout << "Enter a command : ";		
		ch = _getch();
		cout << endl;
		if (ch > '0' && (ch - '0') <= this->size) {
			//menu item
			int comanda = ch - '1';// 0 based index

			return comanda;
		} else  if (ch == '0' || ch == 0x1B) {
			//0 or ESC - quit the menu
			return -1;
		} else {
			//invalid input
			cout << "Invalid input : " << ch
				<< " Valid options '0' - '" << size <<"'" 
				<< endl << endl;
		}
	}
}

void Menu::execute() {
	for (;;) {
		int command;

		clrscr();
		printTitle();
		print();
		command = readCommand();
		if (command >=0 && command < size) {
			items[command]->execute();
		} else {
			//or quit
			return;
		}
	}
}
