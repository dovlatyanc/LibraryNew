#pragma once

#include "Item.h"

//класс книга
class Book :public Item
{
public:
	string ISBN;//книжный номер
	int pages;//количество страниц

	Book(int id, string name, Author *author, int year, int total, int available, string ibsn, int pages) :
		Item(id, name, author, year, total, available), ISBN(ibsn), pages(pages) {}//сделать уникальным;
	Book() {}

	virtual string getName()const override { return this->title; }

	virtual void print() override {
		cout << "ID: " << id << ',' << title
			<< ',' << this->author->full_name << ','
			<< year << ',' << total_number << ", Доступно :"
			<< number_available << ",ISBN :" << ISBN
			<< ", Страниц : " << pages << endl;
	}

};