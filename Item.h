#pragma once

#include "author.h"

// абстрактный класс Итем
class Item
{
public:

	int id;//индефикатор
	string title;//название
	shared_ptr<Author>author;// указатель на объект класса автор
	int year;//год издания
	int total_number;//общее количество
	int number_available;//количество доступных


	Item() {}//gos constructor
	// конструктор
	Item(int id, string name, Author *author, int year, int total, int available) :
		id(id), title(name), author(author), year(year),
		total_number(total), number_available(available) {};

	void setName(string name) { this->title = name; }

	virtual string getName()const = 0;

	virtual void print() = 0;

	virtual ~Item() = 0 {};
};