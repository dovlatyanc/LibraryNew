#pragma once

#include "Item.h"

// класс читатетель
class Reader
{
public:
	string name;
	int id;//номер читательского билета рандомный из 5 цифр и уникальный

	Reader() {}
	Reader(string name) : name(name)
	{
	}
	void print() { cout << "ФИО: " << name << "\nid: " << id << endl; }
	vector<Item *> list_of_books;//список литературы читателя
};