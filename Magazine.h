#pragma once

#include "Item.h"

//класс журнал
class Magazine : public Item
{
public:

	int issue_num;// номер выпуска
	string category;//категория


	Magazine(int id, string name, Author *author, int year, int total, int available, int issue_num, string category) :
		Item(id, name, author, year, total, available), issue_num(issue_num), category(category) {}
	Magazine() {}

	virtual string getName()const override { return this->title; }
	virtual void print() override {


		cout << "ID: " << id << ',' << title << ',' << this->author->full_name
			<< ',' << year << ',' << total_number << ", Доступно :"
			<< number_available << ", Номер выпуска :" << issue_num
			<< ", Категория : " << category << endl;
	}
};