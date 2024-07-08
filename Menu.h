#pragma once

#include "Library.h"

enum Menu {
	Books = 1,
	Magazines,
	Authors,
	Readers,
	BorrowItems,
	returnItems,
	Find,
	loadFiles,
	Exit
};

enum LoadFileMenu {
	LoadBooks = 1,
	LoadMagazines,
	LoadAuthors,
	LoadReaders
};

istream &operator>>(istream &is, LoadFileMenu &menu) {
	int a;
	is >> a;
	menu = static_cast<LoadFileMenu>(a);
	return is;
}

void addAutor(Library &lib) {//избавление от дуболирования

	int year;
	cout << "Введите год  рождения автора: " << endl;
	cin >> year;

	string nameAuthor;
	cout << "Введите имя автора: " << endl;
	cin >> nameAuthor;

	lib.addAuthor(nameAuthor, year);

	cout << " Автор " << nameAuthor << " успешно добавлен!" << endl;

	Sleep(1000);


}

bool compareAuthors(const Author &a, const Author &b) { return a.full_name < b.full_name; }

void LibraryMenu(Library &lib) {


	if (!lib.IsHaveAuthors()) {
		int addAuthors;

		do {
			cout << "В библиотеке пока что нет авторов! Чтобы добавить авторов нажмите - [1] ! " << endl;
			cin >> addAuthors;

		} while (addAuthors != 1);


		addAutor(lib);

		Sleep(1000);


	}

	int menu_item_d;

	while (true) {

		system("cls");

		cout << "Выберите пункт: " << endl;
		cout << "1. Управление книгами " << endl;
		cout << "2. Управление журналами " << endl;
		cout << "3. Управление авторами " << endl;
		cout << "4. Управление читателями " << endl;
		cout << "5. Выдача предметов читателям " << endl;
		cout << "6. Возврат  предметов от читателей " << endl;
		cout << "7. Общий поиск по книгам и журналам " << endl;
		cout << "8. Загрузка данных " << endl;
		cout << "9. Выход " << endl;

		///добавить очистки консоли после выбора

		cin >> menu_item_d;


		switch (menu_item_d)
		{
		case Books:
		{
			string menu_itemf;

			cout << "\t1.1. Добавить книгу\n" <<
				"\t1.2. Поиск книг\n" <<
				"\t1.3. Список всех книг\n";
			int add;

			do {
				cin >> menu_itemf;
				if (menu_itemf == "1.1")
				{
					do {

						Sleep(1000);
						system("cls");

						int id;
						cout << "\t\tВведите ID книги: " << endl;
						cin >> id;
						string title;
						cout << "\t\tВведите название книги: " << endl;
						cin >> title;

						string nameAuthor;
						cout << "\t\tВведите автора книги : " << endl;
						cin >> nameAuthor;

						if (!lib.findAuthor(nameAuthor))
						{
							cout << "\t\t\tСначала добавьте автора!" << endl;
							Sleep(1000);

							break;
						}
						Author *author;
						author = lib.findAuthor(nameAuthor);


						int year;
						cout << "\t\tВведите год издания книги : " << endl;
						cin >> year;

						int total;
						cout << "\t\tВведите общее количество книг : " << endl;
						cin >> total;

						string IBSN;
						cout << "\t\tВведите ISBN книги : " << endl;
						cin >> IBSN;

						int pages;
						cout << "\t\tВведите количество страниц книги : " << endl;
						cin >> pages;

						Book book(id, title, author, year, total, total, IBSN, pages);

						author->list_of_books.push_back(&book);// добавляем нашему автору книжку в список произведений

						lib.addBook(book);

						cout << "Книга успешно добавлена. Хотите добавить новую книгу?-[1] ," <<
							"Нет - [9]" << endl;
						cin >> add;
						if (add == Exit)
							break;//выход из блока
					} while (add == 1);//магические числа убрать 

					break;
				}

				else if (menu_itemf == "1.2")
				{
					string findMenu;
					cout << "Введите критерий поиска:\n \t\t1. По названию\n\t\t2. По автору\n \t\t3. По году издания\n";
					cin >> findMenu;
					if (findMenu == "1") {
						string name;

						cout << "\t\tВведите название книги :" << endl;

						cin >> name;


						lib.findBook(name)->print();

						system("pause");
						break;

					}
					else if (findMenu == "2") {
						string name;
						cout << "\t\tВведите полное имя автора книги через \"_\" :" << endl;
						cin >> name;
						lib.findBookAuthor(name)->print();
						system("pause");
						break;

					}
					else if (findMenu == "3") {
						int year;
						cout << "\t\t\tВведите год издания книги : " << endl;
						cin >> year;
						if (lib.findBook(year)) {

							lib.printBooksYear(year);

							system("pause");
							break;
						}

					}
					break;// сделать выход
				}
				else if (menu_itemf == "1.3")
				{
					lib.printBooks();

					system("pause");

					break;// сделать выход
				}
				else
					cout << "Некорректное значение! Введите заново!" << endl;

			} while (menu_itemf != "1.1" || menu_itemf != "1.2" || menu_itemf != "1.3");

			break;
		}
		case Magazines:
		{
			string menu_itemf;

			cout << "\t2.1. Добавить журнал\n" <<
				"\t2.2. Поиск журналов\n" <<
				"\t2.3. Список всех журналов\n";
			int add;
			do {


				cin >> menu_itemf;
				if (menu_itemf == "2.1")
				{
					do {
						Sleep(1000);
						system("cls");

						int id;
						cout << "\t\tВведите ID журнала:  " << endl;
						cin >> id;

						string title;
						cout << "\t\tВведите название журнала " << endl;
						cin >> title;

						string nameAuthor;
						cout << "\t\tВведите автора журнала : " << endl;
						cin >> nameAuthor;

						if (!lib.findAuthor(nameAuthor))
						{
							cout << "\t\t\tСначала добавьте автора! Автор с таким именем не найден" << endl;
							break;
						}

						Author *author;
						author = lib.findAuthor(nameAuthor);

						int year;
						cout << "\t\tВведите год издания журнала : " << endl;
						cin >> year;
						int total;
						cout << "\t\tВведите общее количество журналов :  " << endl;
						cin >> total;
						int num;
						cout << "\t\tВведите номер выпуска журнала :  " << endl;
						cin >> num;
						string category;
						cout << "\t\tВведите категорию журнала : " << endl;
						cin >> category;

						Magazine mag(id, title, author, year, total, total, num, category);
						lib.addMagazine(mag);

						author->list_of_books.push_back(&mag);// добавляем нашему автору журнал в список произведений

						cout << "Журнал успешно добавлен. Хотите добавить новый? -[1] ," <<
							"Нет - [9]" << endl;
						cin >> add;
						if (add == Exit)
							break;//выход из блока
					} while (add == 1);// добавить еще  + проверка от дураков
					break;
				}
				else if (menu_itemf == "2.2")
				{
					string findMenu;
					cout << "Введите критерий поиска:\n \t\t1. По названию\n\t\t2. По автору\n \t\t3. По году издания\n";
					cin >> findMenu;
					if (findMenu == "1") {
						string name;
						cout << "\t\tВведите название журнала :" << endl;
						cin >> name;
						lib.findMagazine(name)->print();

						system("pause");

						break;

					}
					else if (findMenu == "2") {
						string name;
						cout << "\t\tВведите название редакции :" << endl;
						cin >> name;

						lib.findMagazineAuthor(name)->print();
						system("pause");
						break;

					}
					else if (findMenu == "3") {
						int year;
						cout << "\t\t\tВведите год издания журнала: " << endl;
						cin >> year;


						if (lib.findMagazine(year)) {

							lib.printMagYear(year);

							system("pause");
							break;
						}

					}
					break;

				}
				else if (menu_itemf == "2.3")
				{
					lib.printMagazine();
					system("pause");
					break;
				}
				else
					cout << "Некорректное значение! Введите заново!" << endl;

			} while (menu_itemf != "2.1" || menu_itemf != "2.2" || menu_itemf != "2.3");
			break;
		}
		case Authors:
		{
			string menu_itemf;

			cout << "\t3.1. Добавить автора\n" <<
				"\t3.2. Список всех авторов\n";
			do {


				cin >> menu_itemf;
				system("cls");
				if (menu_itemf == "3.1")
				{
					int add;
					do {

						addAutor(lib);

						cout << "Хотите добавить нового автора?-[1] ," <<
							"Нет - [9]" << endl;
						cin >> add;
						if (add == Exit)
							break;//выход из блока
					} while (add == 1);
					break;
				}

				else if (menu_itemf == "3.2")
				{
					// Сортируем вектор авторов в лексикографическом порядке
					sort(lib.authors.begin(), lib.authors.end(), compareAuthors);
					// Выводим отсортированный список авторов
					for (const Author &author : lib.authors) {
						cout << author.full_name << endl;
					}
					system("pause");
					break;
				}
				else
					cout << "Некорректное значение! Введите заново!" << endl;

			} while (menu_itemf != "3.1" || menu_itemf != "3.2");

			break;
		}
		case Readers:
		{
			string menu_itemf;

			cout << "\t4.1. Добавить читателя\n" <<
				"\t4.2. Поиск читателя\n" <<
				"\t4.3. Список всех читателей\n";
			do {

				cin >> menu_itemf;

				if (menu_itemf == "4.1")
				{
					int add;
					do {
						system("cls");

						string name;
						cout << "Введите имя читателя: " << endl;
						cin >> name;

						lib.addReader(name);

						system("pause");

						cout << "Хотите добавить нового?-[1] ," <<
							"Нет - [9]" << endl;
						cin >> add;
						if (add == Exit)
							break;//выход из блока
					} while (add == 1);
					break;
				}
				else if (menu_itemf == "4.2")
				{
					string menu_item;
					cout << "\t\tВведите критерий поиска:\n \t\t4.2.1. По имя - фамилия\n \t\t4.2.2. По номеру читательского билета\n";
					cin >> menu_item;
					if (menu_item == "4.2.1")
					{
						string name;
						cout << "Введите имя и фамилию читателя через \"_\": " << endl;
						cin >> name;
						lib.findReader(name);

						if (lib.findReader(name)) {
							Reader *reader = lib.findReader(name);
							reader->print();
						}
						Sleep(1500);
						break;

					}
					else if (menu_item == "4.2.2")
					{
						int id;
						cout << "Введите ID читателя: " << endl;
						cin >> id;

						lib.findReader(id);
						if (lib.findReader(id)) {
							Reader *reader = lib.findReader(id);
							reader->print();

						}
						Sleep(1500);
						break;
					}
				}
				else if (menu_itemf == "4.3")
				{
					lib.printReaders();
					system("pause");
					break;
				}
				else
					cout << "Некорректное значение! Введите заново!" << endl;

			} while (menu_itemf != "4.1" || menu_itemf != "4.2" || menu_itemf != "4.3");

			break;
		}
		case BorrowItems:
		{
			string menu_itemf;

			cout << "\t5.1. Выдать предмет читателю\n";
			do {
				cin >> menu_itemf;

				Sleep(1000);
				system("cls");

				if (menu_itemf == "5.1")
				{
					// Запросить у пользователя номер читательского билета
					cout << "Введите номер читательского билета: ";
					int reader_id;
					cin >> reader_id;

					// Запросить у пользователя название предмета
					cout << "Введите название предмета: ";
					string item_name;
					cin >> item_name;

					if (lib.findBook(item_name)) {
						if (lib.findReader(reader_id)) {
							//если предмет книга 
							Reader *tempReader = lib.findReader(reader_id);
							Book *tempBook = lib.findBook(item_name);
							lib.takeItem(*tempReader, *tempBook);
						}
					}
					else if (lib.findMagazine(item_name)) {
						if (lib.findReader(reader_id)) {
							//если предмет magazine
							Reader *tempReader = lib.findReader(reader_id);
							Magazine *tempMag = lib.findMagazine(item_name);
							lib.takeItem(*tempReader, *tempMag);
						}
					}
					break;
				}
				else
					cout << "Некорректное значение! Введите заново!" << endl;

			} while (menu_itemf != "5.1");

			break;
		}
		case returnItems:
		{
			string menu_itemf;

			cout << "\t6.1. Возврат предмета(книги либо журнала)\n";
			do {

				cin >> menu_itemf;

				Sleep(1000);
				system("cls");

				if (menu_itemf == "6.1")
				{// Запросить у пользователя номер читательского билета
					cout << "Введите номер читательского билета: ";
					int reader_id;
					cin >> reader_id;

					// Запросить у пользователя название предмета
					cout << "Введите название предмета: ";
					string item_name;
					cin >> item_name;
					if (lib.findBook(item_name)) {
						if (lib.findReader(reader_id)) {
							//если предмет книга 
							Reader *tempReader = lib.findReader(reader_id);
							Book *tempBook = lib.findBook(item_name);
							lib.returnItem(*tempReader, *tempBook);
						}
					}
					else if (lib.findMagazine(item_name)) {
						if (lib.findReader(reader_id)) {
							//если предмет magazine
							Reader *tempReader = lib.findReader(reader_id);
							Magazine *tempMag = lib.findMagazine(item_name);
							lib.returnItem(*tempReader, *tempMag);
						}
					}
					break;

				}
				else
					cout << "Некорректное значение! Введите заново!" << endl;

			} while (menu_itemf != "6.1");

			break;
		}
		case Find:
		{
			string menu_itemf;

			cout << "\t 7.1. Поиск по году выхода\n";
			do {
				cin >> menu_itemf;

				Sleep(1000);
				system("cls");

				if (menu_itemf == "7.1")
				{
					int year;
					cout << "\t\tВведите год издания: " << endl;
					cin >> year;

					lib.findMagazine(year);
					lib.findBook(year);
				}
				else
					cout << "Некорректное значение! Введите заново!" << endl;

			} while (menu_itemf != "7.1");

			break;
		}
		case loadFiles:
		{
			LoadFileMenu choice;

			cout << "Нажмите чтобы выбрать критерий :\n" <<
				"[1]-загрузить список книг" << endl <<
				"[2]-загрузить список журналов" << endl <<
				"[3]-загрузить список авторов" << endl <<
				"[4]-загрузить список читателей" << endl;

			cin >> choice;

			switch (choice)
			{
			case LoadBooks:lib.loadBooksFromFile("books.csv", lib.books);
				break;
			case LoadMagazines:lib.loadMagazinesFromFile("magazines.csv", lib.magazines);
				break;
			case LoadAuthors:lib.loadAuthorsFromFile("authors.csv", lib.authors);
				break;
			case LoadReaders:lib.loadReadersFromFile("readers.csv", lib.readers);
				break;
			default: {
				cout << "Не получается загрузить выбранное Вами" << endl;
				Sleep(1000);
				break;
			}
				   break;
			}
		}
		break;

		case Exit: {
			char ex;
			cout << "Вы точно уверены что хотите выйти ? [Y/y][N/n]" << endl;
			cin >> ex;
			if (ex == 'Y' || ex == 'y')
				return;
			else if (ex == 'N' || ex == 'n')
				break;
			else {
				cout << "Не получается осуществить выбранное Вами" << endl;
				Sleep(1000);
				break;
			}
		}

		default: {
			cout << "Не получается сделать то что Bы хотите(((" << endl;
			Sleep(1000);

			break;
			}
		}
	}
}








