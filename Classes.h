#pragma once

//сделать через принцип инкапсуляции в идеале

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

const int MIN_NUMBER = 10000;  // Минимальное значение номера читательского билета
const int MAX_NUMBER = 99999;  // Максимальное значение номера читательского билета

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
//абстрактный класс Итем
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

class Library
{

	string name;

	int countAuthors = 0;
	int countReaders = 0;

public:

	Library(string name) :name(name) {}

	vector <Book> books;
	vector <Magazine> magazines;
	vector <Reader> readers;
	vector <Author> authors;
	//реализовать очистку памяти перед выходом из программы


	unordered_set<int> issuedNumbers;  // Множество выданных номеров билетов

	int generateUniqueTicketNumber() {
		random_device rd;  // Генерируем случайное семя из аппаратной части
		mt19937 gen(rd());  // Создаем генератор случайных чисел Mersenne Twister

		while (true) {
			// Генерируем случайное число в диапазоне [MIN_NUMBER, MAX_NUMBER]
			int number = MIN_NUMBER + (gen() % (MAX_NUMBER - MIN_NUMBER + 1));

			// Проверяем, не был ли уже выдан этот номер билета
			if (issuedNumbers.find(number) == issuedNumbers.end()) {
				issuedNumbers.insert(number);  // Добавляем новый номер в множество
				return number;  // Возвращаем уникальный номер билета
			}
		}
	}
	//ФуНкции поиска

	Book *findBook(int year) {
		{

			for (Book &book : books) {
				if (book.year == year) {
					cout << "Книга " << book.getName() << " найдена! " << endl;
					return &book;
				}
			}

			cout << "Книги, выпущенные в этом году  не найдены." << endl;
			Sleep(1000);
			return nullptr;

		}
	}
	//поиск по названию
	Book *findBook(string name) {
		{

			for (Book &book : books) {
				if (book.title == name) {
					cout << "Книга " << book.getName() << " найдена! " << endl;
					return &book;
				}
			}

			cout << "Книги с таким названием не найдены." << endl;
			Sleep(1000);
			return nullptr;

		}
	}
	//поиск по автору
	Book *findBook(string name, string surname) {
		{

			for (Book &book : books) {
				if (book.author->full_name == (name + "_" + surname)) {
					cout << "Книга " << book.getName() << " найдена! " << endl;
					return &book;
				}
			}

			cout << "Книги, этого автора не найдены." << endl;
			Sleep(1000);
			return nullptr;

		}
	}


	Magazine *findMagazine(int year) {
		for (Magazine &mag : magazines) {
			if (mag.year == year) {
				return &mag;
			}

		}
		cout << "Журналы, выпущенные в этом году  не найдены." << endl;
		Sleep(1000);
		return nullptr;
	}
	//поиск по имени 
	Magazine *findMagazine(string name) {
		for (Magazine &mag : magazines) {
			if (mag.title == name) {
				cout << "Журнал " << mag.getName() << "найден! " << endl;
				return &mag;
			}

		}
		cout << "Журналы с таким названием не найдены." << endl;
		Sleep(1000);
		return nullptr;
	}

	Magazine *findMagazineAuthor(string nameAuthor) {
		for (Magazine &mag : magazines) {
			if (mag.author->full_name == nameAuthor) {
				cout << "Журнал " << mag.getName() << "найден! " << endl;
				return &mag;
			}

		}
		cout << "Журналы этого автора не найдены.." << endl;
		Sleep(1000);
		return nullptr;
	}

	Reader *findReader(int id) {
		for (Reader &reader : readers) {
			if (reader.id == id) {
				return &reader;
			}
		}
		cout << "Читатель с таким идентификатором не найден" << endl;
		Sleep(1000);
		return nullptr;
	}

	Reader *findReader(string full_name) {
		for (Reader &reader : readers) {
			if (reader.name == full_name) {
				return &reader;
			}
		}
		cout << "Читатель с таким именем не найден" << endl;
		Sleep(1000);
		return nullptr;
	}


	Author *findAuthor(string name) {
		for (Author &author : authors) {
			if (author.full_name == name) {
				//author.printName();
				Sleep(1000);
				return &author;
			}
		}
		cout << "Автор с таким именем не найден" << endl;
		Sleep(1000);
		return nullptr;
	}

	//фунции добавления

	void addBook(const Book &book) { books.push_back(book); }
	void addMagazine(const Magazine &magazine) { magazines.push_back(magazine); }

	void addReader(string name) {
		Reader reader(name);
		reader.id = generateUniqueTicketNumber();

		readers.push_back(reader);
		cout << " Читатель успешно добавлен!Номер читательского билета: " << reader.id << endl;
		countReaders++;
		Sleep(1000);
	}
	void addAuthor(const string &name, int year)
	{
		Author author;

		author.full_name = name;
		author.year_of_birth = year;

		authors.push_back(author);


		countAuthors++;
	}

	bool IsHaveAuthors() const { return authors.size() > 0; }//сменить название метода на нормальное


	//функции выдачи 

	void takeItem(Reader &reader, Item &item) {
		if (item.number_available > 0) {
			item.number_available--;
			reader.list_of_books.push_back(&item);
			cout << "Предмет " << item.getName() << " выдан читателю " << reader.name << endl;
			Sleep(1000);
		}
		else {
			cout << "Недоступно для выдачи" << endl;
			Sleep(1000);
		}
	}



	//void returnItem(Reader &reader, Item &item) //возврат предметов
	//{
	//	for (Item *&Items : reader.list_of_books)
	//	{
	//		if (Items == &item) {//если нашли
	//			item.number_available++;//предмет вернуолся и стал доступным в библиотеке
	//			reader.list_of_books.erase(remove(reader.list_of_books.begin(),
	//			reader.list_of_books.end(), &item), reader.list_of_books.end());//удаление предмета из смписка читателя
	//			cout << "Предмет " << item.getName() << " успешно возвращен читателем "
	//			<< reader.name << endl;
	//			Sleep(1000);
	//			break;
	//		}
	//		 else { 
	//			cout << "Предмет " << item.getName() << " не найден в списке читателя " 
	//			<< reader.name << endl;
	//	}
	//	}

	//}
	void returnItem(Reader &reader, Item &item) {
		auto it = find(reader.list_of_books.begin(), reader.list_of_books.end(), &item);
		if (it != reader.list_of_books.end()) { // item нашелся
			item.number_available++;
			reader.list_of_books.erase(it);
			cout << "Предмет " << item.getName() << " успешно возвращен читателем " << reader.name << endl;
		}
		else { // item отсутсвует
			cout << "Предмет " << item.getName() << " не найден в списке читателя " << reader.name << endl;
		}
	}

	//vivod po godu
	void printBooksYear(int year) {
		cout << endl;
		cout << "Книги выпущенные в " << year << " году" << endl;

		for (Book &book : books) {
			if (book.year == year) {

				book.print();

				cout << endl;

			}
		}
		Sleep(1000);

	}



	void printMagYear(int year) {
		cout << endl;
		cout << "Журналы выпущенные в " << year << " году" << endl;

		for (Magazine &mag : magazines) {
			if (mag.year == year) {

				mag.print();

				cout << endl;
			}
		}
		Sleep(1000);

	}

	// vivod vsex knig
	void printBooks() {
		cout << endl;
		cout << "Список всех книг:\n";
		for (size_t i = 0; i < books.size(); i++)
		{
			cout << "Книга № " << i + 1 << ' ';
			books[i].print();


		}
		cout << endl;
		Sleep(1000);
	}
	//список всех журналов
	void printMagazine() {
		cout << endl;
		cout << "Список всех журналов :\n";
		for (size_t i = 0; i < magazines.size(); i++)
		{
			cout << "Журнал  № " << i + 1 << ' ';
			magazines[i].print();

		}
		cout << endl;
		Sleep(1000);
	}

	// список всех авторов
	void printAuthors() {
		cout << endl;
		cout << "Список всех авторов :\n";
		for (size_t i = 0; i < authors.size(); i++)
		{
			cout << i + 1 << ") " << authors[i].full_name << endl;
		}
		cout << endl;
		Sleep(1000);
	}
	//список всех читателей
	void printReaders() {
		cout << endl;
		cout << "Список всех читателей :\n";
		for (size_t i = 0; i < readers.size(); i++)
		{
			cout << i + 1 << ") " << readers[i].name << endl;
		}
		cout << endl;
		Sleep(1000);
	}

	bool loadBooksFromFile(string filename, vector<Book> &books) {
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Could not open file: " << filename << endl;
			Sleep(1000);
			return false;
		}

		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string field;
			vector<string> fields;
			while (getline(ss, field, ',')) {
				fields.push_back(field);
			}

			if (fields.size() != 8) {
				cerr << "Invalid line: " << line << endl;
				Sleep(1000);
				continue;
			}

			Book book;
			book.author = make_shared<Author>(); // Используем make_shared для создания shared_ptr
			try {
				book.id = stoi(fields[0]);
				book.title = fields[1];
				book.author->full_name = fields[2];
				book.year = stoi(fields[3]);
				book.total_number = stoi(fields[4]);
				book.number_available = stoi(fields[5]);
				book.ISBN = stoi(fields[6]);
				book.pages = stoi(fields[7]);
			}
			catch (invalid_argument &e) {
				cerr << e.what() << endl;
				continue;
			}

			books.push_back(book);
		}

		file.close();
		return true;
	}


	bool loadMagazinesFromFile(string filename, vector<Magazine> &mags) {
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Could not open file: " << filename << endl;
			Sleep(1000);
			return false;
		}

		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string field;
			vector<string> fields;
			while (getline(ss, field, ',')) {
				fields.push_back(field);
			}

			if (fields.size() != 8) {
				cerr << "Invalid line: " << line << endl;
				Sleep(1000);
				continue;
			}

			Magazine mag;
			mag.author = make_shared<Author>();
			try {
				mag.id = stoi(fields[0]);
				mag.title = fields[1];
				mag.author->full_name = fields[2];
				mag.year = stoi(fields[3]);
				mag.total_number = stoi(fields[4]);
				mag.number_available = stoi(fields[5]);
				mag.issue_num = stoi(fields[6]);
				mag.category = fields[7];
			}
			catch (invalid_argument &e) {
				cerr << e.what() << endl;
				continue;
			}

			mags.push_back(mag);
		}

		file.close();
		return true;
	}


	bool loadAuthorsFromFile(string filename, vector<Author> &authors) {
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Could not open file: " << filename << endl;
			Sleep(1000);
			return false;
		}

		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string field;
			vector<string> fields;
			while (getline(ss, field, ',')) {
				fields.push_back(field);
			}

			if (fields.size() != 2) {
				cerr << "Invalid line: " << line << endl;
				Sleep(1000);
				continue;
			}

			Author author;
			try {
				author.full_name = fields[0];
				author.year_of_birth = stoi(fields[1]);
			}
			catch (const invalid_argument &e) {
				cerr << e.what() << endl;
				Sleep(1000);
				continue;
			}

			authors.push_back(author);
		}

		file.close();
		return true;
	}


	bool loadReadersFromFile(string filename, vector<Reader> &rders) {
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Could not open file: " << filename << endl;
			Sleep(1000);
			return false;
		}

		//int i=0;//счетчик считать произведения
		string line;

		while (getline(file, line)) {
			stringstream ss(line);
			string field;
			vector<string> fields;
			while (getline(ss, field, ',')) {
				fields.push_back(field);
			}

			if (fields.size() != 2) {
				cerr << "Invalid line: " << line << endl;
				Sleep(1000);
				continue;
			}

			Reader reader;
			try {
				reader.name = fields[0];
				reader.id = stoi(fields[1]);
			}
			catch (invalid_argument &e) {
				cerr << e.what() << endl;
				continue;
			}

			rders.push_back(reader);
			//i++;
		}

		file.close();
		return true;
	}
};
//------------------------------------------------------------------------------------------------------------------