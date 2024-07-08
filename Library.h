#pragma once

#include "Book.h"
#include "Magazine.h"
#include "Reader.h"

const int MIN_NUMBER = 10000;  // Минимальное значение номера читательского билета
const int MAX_NUMBER = 99999;  // Максимальное значение номера читательского билета

class Library
{
private:
	string name;
	int countAuthors = 0;
	int countReaders = 0;
public:
	Library(string name) :name(name) {}

	vector <Book> books;
	vector <Magazine> magazines;
	vector <Reader> readers;
	vector <Author> authors;

	unordered_set<int> issuedNumbers;  // Множество выданных номеров билетов

	int generateUniqueTicketNumber();//уникальный чит билет
	Book *findBook(int year); //посик книги по году
	Book *findBook(string name); //по названию
	Book *findBookAuthor(string name); //по имени автора
	Magazine *findMagazine(int year); 
	Magazine *findMagazine(string name); 
	Magazine *findMagazineAuthor(string nameAuthor); 
	Reader *findReader(int id); 
	Reader *findReader(string full_name); 
	Author *findAuthor(string name); 
	void addBook(const Book &book) { books.push_back(book); }
	void addMagazine(const Magazine &magazine) { magazines.push_back(magazine); }
	void addReader(string name);
	void addAuthor(const string &name, int year);
	bool IsHaveAuthors() const { return authors.size() > 0; }
	void takeItem(Reader &reader, Item &item); 
	void returnItem(Reader &reader, Item &item);
	void printBooksYear(int year); 
	void printMagYear(int year);
	void printBooks(); //список всех книг
	void printMagazine(); //список всех журналов
	void printAuthors(); // список всех авторов
	void printReaders();//список всех читателей
	//LOADSMETHODS
	bool loadBooksFromFile(string filename, vector<Book> &books); 
	bool loadMagazinesFromFile(string filename, vector<Magazine> &mags);
	bool loadAuthorsFromFile(string filename, vector<Author> &authors);
	bool loadReadersFromFile(string filename, vector<Reader> &rders); 

};
//------------------------------------------------------------------------------------------------------------------