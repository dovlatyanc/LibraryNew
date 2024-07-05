#pragma once

#include"Classes.h"

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

void addAutor(Library &lib) {//���������� �� �������������

	int year;
	cout << "������� ���  �������� ������: " << endl;
	cin >> year;

	string nameAuthor;
	cout << "������� ��� ������: " << endl;
	cin >> nameAuthor;

	lib.addAuthor(nameAuthor, year);

	cout << " ����� " << nameAuthor << " ������� ��������!" << endl;

	Sleep(1000);


}

bool compareAuthors(const Author &a, const Author &b) { return a.full_name < b.full_name; }

void LibraryMenu(Library &lib) {


	if (!lib.IsHaveAuthors()) {
		int addAuthors;

		do {
			cout << "� ���������� ���� ��� ��� �������! ����� �������� ������� ������� - [1] ! " << endl;
			cin >> addAuthors;

		} while (addAuthors != 1);


		addAutor(lib);

		Sleep(1000);


	}

	int menu_item_d;

	while (true) {

		system("cls");

		cout << "�������� �����: " << endl;
		cout << "1. ���������� ������� " << endl;
		cout << "2. ���������� ��������� " << endl;
		cout << "3. ���������� �������� " << endl;
		cout << "4. ���������� ���������� " << endl;
		cout << "5. ������ ��������� ��������� " << endl;
		cout << "6. �������  ��������� �� ��������� " << endl;
		cout << "7. ����� ����� �� ������ � �������� " << endl;
		cout << "8. �������� ������ " << endl;
		cout << "9. ����� " << endl;

		///�������� ������� ������� ����� ������

		cin >> menu_item_d;


		switch (menu_item_d)
		{
		case Books:
		{
			string menu_itemf;

			cout << "\t1.1. �������� �����\n" <<
				"\t1.2. ����� ����\n" <<
				"\t1.3. ������ ���� ����\n";
			int add;

			do {
				cin >> menu_itemf;
				if (menu_itemf == "1.1")
				{
					do {

						Sleep(1000);
						system("cls");

						int id;
						cout << "\t\t������� ID �����: " << endl;
						cin >> id;
						string title;
						cout << "\t\t������� �������� �����: " << endl;
						cin >> title;

						string nameAuthor;
						cout << "\t\t������� ������ ����� : " << endl;
						cin >> nameAuthor;

						if (!lib.findAuthor(nameAuthor))
						{
							cout << "\t\t\t������� �������� ������!" << endl;
							Sleep(1000);

							break;
						}
						Author *author;
						author = lib.findAuthor(nameAuthor);


						int year;
						cout << "\t\t������� ��� ������� ����� : " << endl;
						cin >> year;

						int total;
						cout << "\t\t������� ����� ���������� ���� : " << endl;
						cin >> total;

						string IBSN;
						cout << "\t\t������� ISBN ����� : " << endl;
						cin >> IBSN;

						int pages;
						cout << "\t\t������� ���������� ������� ����� : " << endl;
						cin >> pages;

						Book book(id, title, author, year, total, total, IBSN, pages);

						author->list_of_books.push_back(&book);// ��������� ������ ������ ������ � ������ ������������

						lib.addBook(book);

						cout << "����� ������� ���������. ������ �������� ����� �����?-[1] ," <<
							"��� - [9]" << endl;
						cin >> add;
						if (add == Exit)
							break;//����� �� �����
					} while (add == 1);//���������� ����� ������ 

					break;
				}

				else if (menu_itemf == "1.2")
				{
					string findMenu;
					cout << "������� �������� ������:\n \t\t1. �� ��������\n\t\t2. �� ������\n \t\t3. �� ���� �������\n";
					cin >> findMenu;
					if (findMenu == "1") {
						string name;

						cout << "\t\t������� �������� ����� :" << endl;

						cin >> name;


						lib.findBook(name);

						system("pause");
						break;

					}
					else if (findMenu == "2") {
						string name, surname;
						cout << "\t\t������� ��� ������ ����� :" << endl;
						cin >> name;

						cout << "\t\t������� ������� ������ ����� :" << endl;
						cin >> surname;

						lib.findBook(name, surname);

						break;

					}
					else if (findMenu == "3") {
						int year;
						cout << "\t\t\t������� ��� ������� ����� : " << endl;
						cin >> year;

						lib.findBook(year);
						if (lib.findBook(year)) {

							lib.printBooksYear(year);

							system("pause");
							break;
						}

					}
					break;// ������� �����
				}
				else if (menu_itemf == "1.3")
				{
					lib.printBooks();

					system("pause");

					break;// ������� �����
				}
				else
					cout << "������������ ��������! ������� ������!" << endl;

			} while (menu_itemf != "1.1" || menu_itemf != "1.2" || menu_itemf != "1.3");

			break;
		}
		case Magazines:
		{
			string menu_itemf;

			cout << "\t2.1. �������� ������\n" <<
				"\t2.2. ����� ��������\n" <<
				"\t2.3. ������ ���� ��������\n";
			int add;
			do {


				cin >> menu_itemf;
				if (menu_itemf == "2.1")
				{
					do {
						Sleep(1000);
						system("cls");

						int id;
						cout << "\t\t������� ID �������:  " << endl;
						cin >> id;

						string title;
						cout << "\t\t������� �������� ������� " << endl;
						cin >> title;

						string nameAuthor;
						cout << "\t\t������� ������ ������� : " << endl;
						cin >> nameAuthor;

						if (!lib.findAuthor(nameAuthor))
						{
							cout << "\t\t\t������� �������� ������! ����� � ����� ������ �� ������" << endl;
							break;
						}

						Author *author;
						author = lib.findAuthor(nameAuthor);

						int year;
						cout << "\t\t������� ��� ������� ������� : " << endl;
						cin >> year;
						int total;
						cout << "\t\t������� ����� ���������� �������� :  " << endl;
						cin >> total;
						int num;
						cout << "\t\t������� ����� ������� ������� :  " << endl;
						cin >> num;
						string category;
						cout << "\t\t������� ��������� ������� : " << endl;
						cin >> category;

						Magazine mag(id, title, author, year, total, total, num, category);
						lib.addMagazine(mag);

						author->list_of_books.push_back(&mag);// ��������� ������ ������ ������ � ������ ������������

						cout << "������ ������� ��������. ������ �������� �����? -[1] ," <<
							"��� - [9]" << endl;
						cin >> add;
						if (add == Exit)
							break;//����� �� �����
					} while (add == 1);// �������� ���  + �������� �� �������
					break;
				}
				else if (menu_itemf == "2.2")
				{
					string findMenu;
					cout << "������� �������� ������:\n \t\t1. �� ��������\n\t\t2. �� ������\n \t\t3. �� ���� �������\n";
					cin >> findMenu;
					if (findMenu == "1") {
						string name;
						cout << "\t\t������� �������� ������� :" << endl;
						cin >> name;
						lib.findMagazine(name);

						system("pause");

						break;

					}
					else if (findMenu == "2") {
						string name;
						cout << "\t\t������� �������� �������� :" << endl;
						cin >> name;

						lib.findMagazineAuthor(name);

						break;

					}
					else if (findMenu == "3") {
						int year;
						cout << "\t\t\t������� ��� ������� �������: " << endl;
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
					cout << "������������ ��������! ������� ������!" << endl;

			} while (menu_itemf != "2.1" || menu_itemf != "2.2" || menu_itemf != "2.3");
			break;
		}
		case Authors:
		{
			string menu_itemf;

			cout << "\t3.1. �������� ������\n" <<
				"\t3.2. ������ ���� �������\n";
			do {


				cin >> menu_itemf;
				system("cls");
				if (menu_itemf == "3.1")
				{
					int add;
					do {

						addAutor(lib);

						cout << "������ �������� ������ ������?-[1] ," <<
							"��� - [9]" << endl;
						cin >> add;
						if (add == Exit)
							break;//����� �� �����
					} while (add == 1);
					break;
				}

				else if (menu_itemf == "3.2")
				{
					// ��������� ������ ������� � ������������������ �������
					sort(lib.authors.begin(), lib.authors.end(), compareAuthors);
					// ������� ��������������� ������ �������
					for (const Author &author : lib.authors) {
						cout << author.full_name << endl;
					}
					system("pause");
					break;
				}
				else
					cout << "������������ ��������! ������� ������!" << endl;

			} while (menu_itemf != "3.1" || menu_itemf != "3.2");

			break;
		}
		case Readers:
		{
			string menu_itemf;

			cout << "\t4.1. �������� ��������\n" <<
				"\t4.2. ����� ��������\n" <<
				"\t4.3. ������ ���� ���������\n";
			do {

				cin >> menu_itemf;

				if (menu_itemf == "4.1")
				{
					int add;
					do {
						system("cls");

						string name;
						cout << "������� ��� ��������: " << endl;
						cin >> name;

						lib.addReader(name);

						system("pause");

						cout << "������ �������� ������?-[1] ," <<
							"��� - [9]" << endl;
						cin >> add;
						if (add == Exit)
							break;//����� �� �����
					} while (add == 1);
					break;
				}
				else if (menu_itemf == "4.2")
				{
					string menu_item;
					cout << "\t\t������� �������� ������:\n \t\t4.2.1. �� ��� - �������\n \t\t4.2.2. �� ������ ������������� ������\n";
					cin >> menu_item;
					if (menu_item == "4.2.1")
					{
						string name;
						cout << "������� ��� � ������� �������� ����� \"_\": " << endl;
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
						cout << "������� ID ��������: " << endl;
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
					cout << "������������ ��������! ������� ������!" << endl;

			} while (menu_itemf != "4.1" || menu_itemf != "4.2" || menu_itemf != "4.3");

			break;
		}
		case BorrowItems:
		{
			string menu_itemf;

			cout << "\t5.1. ������ ������� ��������\n";
			do {
				cin >> menu_itemf;

				Sleep(1000);
				system("cls");

				if (menu_itemf == "5.1")
				{
					// ��������� � ������������ ����� ������������� ������
					cout << "������� ����� ������������� ������: ";
					int reader_id;
					cin >> reader_id;

					// ��������� � ������������ �������� ��������
					cout << "������� �������� ��������: ";
					string item_name;
					cin >> item_name;

					if (lib.findBook(item_name)) {
						if (lib.findReader(reader_id)) {
							//���� ������� ����� 
							Reader *tempReader = lib.findReader(reader_id);
							Book *tempBook = lib.findBook(item_name);
							lib.takeItem(*tempReader, *tempBook);
						}
					}
					else if (lib.findMagazine(item_name)) {
						if (lib.findReader(reader_id)) {
							//���� ������� magazine
							Reader *tempReader = lib.findReader(reader_id);
							Magazine *tempMag = lib.findMagazine(item_name);
							lib.takeItem(*tempReader, *tempMag);
						}
					}
					break;
				}
				else
					cout << "������������ ��������! ������� ������!" << endl;

			} while (menu_itemf != "5.1");

			break;
		}
		case returnItems:
		{
			string menu_itemf;

			cout << "\t6.1. ������� ��������(����� ���� �������)\n";
			do {

				cin >> menu_itemf;

				Sleep(1000);
				system("cls");

				if (menu_itemf == "6.1")
				{// ��������� � ������������ ����� ������������� ������
					cout << "������� ����� ������������� ������: ";
					int reader_id;
					cin >> reader_id;

					// ��������� � ������������ �������� ��������
					cout << "������� �������� ��������: ";
					string item_name;
					cin >> item_name;
					if (lib.findBook(item_name)) {
						if (lib.findReader(reader_id)) {
							//���� ������� ����� 
							Reader *tempReader = lib.findReader(reader_id);
							Book *tempBook = lib.findBook(item_name);
							lib.returnItem(*tempReader, *tempBook);
						}
					}
					else if (lib.findMagazine(item_name)) {
						if (lib.findReader(reader_id)) {
							//���� ������� magazine
							Reader *tempReader = lib.findReader(reader_id);
							Magazine *tempMag = lib.findMagazine(item_name);
							lib.returnItem(*tempReader, *tempMag);
						}
					}
					break;

				}
				else
					cout << "������������ ��������! ������� ������!" << endl;

			} while (menu_itemf != "6.1");

			break;
		}
		case Find:
		{
			string menu_itemf;

			cout << "\t 7.1. ����� �� ���� ������\n";
			do {
				cin >> menu_itemf;

				Sleep(1000);
				system("cls");

				if (menu_itemf == "7.1")
				{
					int year;
					cout << "\t\t������� ��� �������: " << endl;
					cin >> year;

					lib.findMagazine(year);
					lib.findBook(year);
				}
				else
					cout << "������������ ��������! ������� ������!" << endl;

			} while (menu_itemf != "7.1");

			break;
		}
		case loadFiles:
		{
			LoadFileMenu choice;

			cout << "������� ����� ������� �������� :\n" <<
				"[1]-��������� ������ ����" << endl <<
				"[2]-��������� ������ ��������" << endl <<
				"[3]-��������� ������ �������" << endl <<
				"[4]-��������� ������ ���������" << endl;

			cin >> choice;

			switch (choice)
			{
			case LoadBooks:lib.loadBooksFromFile("books.txt", lib.books);
				break;
			case LoadMagazines:lib.loadMagazinesFromFile("magazines.txt", lib.magazines);
				break;
			case LoadAuthors:lib.loadAuthorsFromFile("authors.txt", lib.authors);
				break;
			case LoadReaders:lib.loadReadersFromFile("readers.txt", lib.readers);
				break;
			default: {
				cout << "�� ���������� ��������� ��������� ����" << endl;
				Sleep(1000);
			}
				   break;
			}
		}
		break;

		case Exit: {
			char ex;
			cout << "�� ����� ������� ��� ������ ����� ? [Y/y][N/n]" << endl;
			cin >> ex;
			if (ex == 'Y' || ex == 'y')
				return;
			else if (ex == 'N' || ex == 'n')
				break;
			else {
				cout << "�� ���������� ����������� ��������� ����" << endl;
				Sleep(1000);
				break;
			}
		}

		default: {
			cout << "�� ���������� ������� �� ��� B� ������(((" << endl;
			Sleep(1000);
		}
			   break;
		}
	}
}








