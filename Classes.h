#pragma once

//������� ����� ������� ������������ � ������

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

const int MIN_NUMBER = 10000;  // ����������� �������� ������ ������������� ������
const int MAX_NUMBER = 99999;  // ������������ �������� ������ ������������� ������

// ����� �����
class Author
{
public:
	string full_name;
	int year_of_birth;

	Author(string full_name, int year_of_birth) : full_name(full_name), year_of_birth(year_of_birth) {}
	Author() {};

	void printName() { cout << "�����: " << full_name << endl; }

	vector <Item *> list_of_books;//������ ������������


};
//����������� ����� ����
class Item
{
public:

	int id;//�����������
	string title;//��������
	shared_ptr<Author>author;// ��������� �� ������ ������ �����
	int year;//��� �������
	int total_number;//����� ����������
	int number_available;//���������� ���������


	Item() {}//gos constructor
	// �����������
	Item(int id, string name, Author *author, int year, int total, int available) :
		id(id), title(name), author(author), year(year),
		total_number(total), number_available(available) {};

	void setName(string name) { this->title = name; }

	virtual string getName()const = 0;

	virtual void print() = 0;

	virtual ~Item() = 0 {};
};
//����� �����
class Book :public Item
{

public:
	string ISBN;//������� �����
	int pages;//���������� �������



	Book(int id, string name, Author *author, int year, int total, int available, string ibsn, int pages) :
		Item(id, name, author, year, total, available), ISBN(ibsn), pages(pages) {}//������� ����������;
	Book() {}

	virtual string getName()const override { return this->title; }

	virtual void print() override {
		cout << "ID: " << id << ',' << title
			<< ',' << this->author->full_name << ','
			<< year << ',' << total_number << ", �������� :"
			<< number_available << ",ISBN :" << ISBN
			<< ", ������� : " << pages << endl;
	}

};

//����� ������
class Magazine : public Item
{
public:

	int issue_num;// ����� �������
	string category;//���������


	Magazine(int id, string name, Author *author, int year, int total, int available, int issue_num, string category) :
		Item(id, name, author, year, total, available), issue_num(issue_num), category(category) {}
	Magazine() {}

	virtual string getName()const override { return this->title; }
	virtual void print() override {


		cout << "ID: " << id << ',' << title << ',' << this->author->full_name
			<< ',' << year << ',' << total_number << ", �������� :"
			<< number_available << ", ����� ������� :" << issue_num
			<< ", ��������� : " << category << endl;
	}
};



// ����� ����������
class Reader
{
public:
	string name;
	int id;//����� ������������� ������ ��������� �� 5 ���� � ����������

	Reader() {}
	Reader(string name) : name(name)
	{
	}
	void print() { cout << "���: " << name << "\nid: " << id << endl; }
	vector<Item *> list_of_books;//������ ���������� ��������
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
	//����������� ������� ������ ����� ������� �� ���������


	unordered_set<int> issuedNumbers;  // ��������� �������� ������� �������

	int generateUniqueTicketNumber() {
		random_device rd;  // ���������� ��������� ���� �� ���������� �����
		mt19937 gen(rd());  // ������� ��������� ��������� ����� Mersenne Twister

		while (true) {
			// ���������� ��������� ����� � ��������� [MIN_NUMBER, MAX_NUMBER]
			int number = MIN_NUMBER + (gen() % (MAX_NUMBER - MIN_NUMBER + 1));

			// ���������, �� ��� �� ��� ����� ���� ����� ������
			if (issuedNumbers.find(number) == issuedNumbers.end()) {
				issuedNumbers.insert(number);  // ��������� ����� ����� � ���������
				return number;  // ���������� ���������� ����� ������
			}
		}
	}
	//������� ������

	Book *findBook(int year) {
		{

			for (Book &book : books) {
				if (book.year == year) {
					cout << "����� " << book.getName() << " �������! " << endl;
					return &book;
				}
			}

			cout << "�����, ���������� � ���� ����  �� �������." << endl;
			Sleep(1000);
			return nullptr;

		}
	}
	//����� �� ��������
	Book *findBook(string name) {
		{

			for (Book &book : books) {
				if (book.title == name) {
					cout << "����� " << book.getName() << " �������! " << endl;
					return &book;
				}
			}

			cout << "����� � ����� ��������� �� �������." << endl;
			Sleep(1000);
			return nullptr;

		}
	}
	//����� �� ������
	Book *findBook(string name, string surname) {
		{

			for (Book &book : books) {
				if (book.author->full_name == (name + "_" + surname)) {
					cout << "����� " << book.getName() << " �������! " << endl;
					return &book;
				}
			}

			cout << "�����, ����� ������ �� �������." << endl;
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
		cout << "�������, ���������� � ���� ����  �� �������." << endl;
		Sleep(1000);
		return nullptr;
	}
	//����� �� ����� 
	Magazine *findMagazine(string name) {
		for (Magazine &mag : magazines) {
			if (mag.title == name) {
				cout << "������ " << mag.getName() << "������! " << endl;
				return &mag;
			}

		}
		cout << "������� � ����� ��������� �� �������." << endl;
		Sleep(1000);
		return nullptr;
	}

	Magazine *findMagazineAuthor(string nameAuthor) {
		for (Magazine &mag : magazines) {
			if (mag.author->full_name == nameAuthor) {
				cout << "������ " << mag.getName() << "������! " << endl;
				return &mag;
			}

		}
		cout << "������� ����� ������ �� �������.." << endl;
		Sleep(1000);
		return nullptr;
	}

	Reader *findReader(int id) {
		for (Reader &reader : readers) {
			if (reader.id == id) {
				return &reader;
			}
		}
		cout << "�������� � ����� ��������������� �� ������" << endl;
		Sleep(1000);
		return nullptr;
	}

	Reader *findReader(string full_name) {
		for (Reader &reader : readers) {
			if (reader.name == full_name) {
				return &reader;
			}
		}
		cout << "�������� � ����� ������ �� ������" << endl;
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
		cout << "����� � ����� ������ �� ������" << endl;
		Sleep(1000);
		return nullptr;
	}

	//������ ����������

	void addBook(const Book &book) { books.push_back(book); }
	void addMagazine(const Magazine &magazine) { magazines.push_back(magazine); }

	void addReader(string name) {
		Reader reader(name);
		reader.id = generateUniqueTicketNumber();

		readers.push_back(reader);
		cout << " �������� ������� ��������!����� ������������� ������: " << reader.id << endl;
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

	bool IsHaveAuthors() const { return authors.size() > 0; }//������� �������� ������ �� ����������


	//������� ������ 

	void takeItem(Reader &reader, Item &item) {
		if (item.number_available > 0) {
			item.number_available--;
			reader.list_of_books.push_back(&item);
			cout << "������� " << item.getName() << " ����� �������� " << reader.name << endl;
			Sleep(1000);
		}
		else {
			cout << "���������� ��� ������" << endl;
			Sleep(1000);
		}
	}



	//void returnItem(Reader &reader, Item &item) //������� ���������
	//{
	//	for (Item *&Items : reader.list_of_books)
	//	{
	//		if (Items == &item) {//���� �����
	//			item.number_available++;//������� ��������� � ���� ��������� � ����������
	//			reader.list_of_books.erase(remove(reader.list_of_books.begin(),
	//			reader.list_of_books.end(), &item), reader.list_of_books.end());//�������� �������� �� ������� ��������
	//			cout << "������� " << item.getName() << " ������� ��������� ��������� "
	//			<< reader.name << endl;
	//			Sleep(1000);
	//			break;
	//		}
	//		 else { 
	//			cout << "������� " << item.getName() << " �� ������ � ������ �������� " 
	//			<< reader.name << endl;
	//	}
	//	}

	//}
	void returnItem(Reader &reader, Item &item) {
		auto it = find(reader.list_of_books.begin(), reader.list_of_books.end(), &item);
		if (it != reader.list_of_books.end()) { // item �������
			item.number_available++;
			reader.list_of_books.erase(it);
			cout << "������� " << item.getName() << " ������� ��������� ��������� " << reader.name << endl;
		}
		else { // item ����������
			cout << "������� " << item.getName() << " �� ������ � ������ �������� " << reader.name << endl;
		}
	}

	//vivod po godu
	void printBooksYear(int year) {
		cout << endl;
		cout << "����� ���������� � " << year << " ����" << endl;

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
		cout << "������� ���������� � " << year << " ����" << endl;

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
		cout << "������ ���� ����:\n";
		for (size_t i = 0; i < books.size(); i++)
		{
			cout << "����� � " << i + 1 << ' ';
			books[i].print();


		}
		cout << endl;
		Sleep(1000);
	}
	//������ ���� ��������
	void printMagazine() {
		cout << endl;
		cout << "������ ���� �������� :\n";
		for (size_t i = 0; i < magazines.size(); i++)
		{
			cout << "������  � " << i + 1 << ' ';
			magazines[i].print();

		}
		cout << endl;
		Sleep(1000);
	}

	// ������ ���� �������
	void printAuthors() {
		cout << endl;
		cout << "������ ���� ������� :\n";
		for (size_t i = 0; i < authors.size(); i++)
		{
			cout << i + 1 << ") " << authors[i].full_name << endl;
		}
		cout << endl;
		Sleep(1000);
	}
	//������ ���� ���������
	void printReaders() {
		cout << endl;
		cout << "������ ���� ��������� :\n";
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
			book.author = make_shared<Author>(); // ���������� make_shared ��� �������� shared_ptr
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

		//int i=0;//������� ������� ������������
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