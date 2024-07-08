#pragma once

#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<stdlib.h>
#include <algorithm>
#include <random>
#include <unordered_set>
#include<windows.h>
#include <string>
#include <sstream>
#include <memory>

using namespace std;

class Item;

// класс автор
class Author
{
public:
	string full_name;
	int year_of_birth;

	Author(string full_name, int year_of_birth) : full_name(full_name), year_of_birth(year_of_birth) {}
	Author() {};

	void printName() { cout << "Автор: " << full_name << endl; }

	vector <Item *> list_of_books;//список произведений


};
