#include "Library.h"

int Library::generateUniqueTicketNumber()
{
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

Book *Library::findBook(int year)
{
	{
		for (Book &book : books) {
			if (book.year == year) {
				return &book;
			}
		}
		cout << "Книги, выпущенные в этом году  не найдены." << endl;
		Sleep(1000);
		return nullptr;

	}
}

Book *Library::findBook(string name)
{
	{
		for (Book &book : books) {
			if (book.title == name) {

				return &book;
			}
		}
		cout << "Книги с таким названием не найдены." << endl;
		Sleep(1000);
		return nullptr;
	}
}

Book *Library::findBookAuthor(string name)
{
	{
		for (Book &book : books) {
			if (book.author->full_name == name) {

				return &book;
			}
		}
		cout << "Книги, этого автора не найдены." << endl;
		Sleep(1000);
		return nullptr;
	}
}

Magazine *Library::findMagazine(int year)
{
	for (Magazine &mag : magazines) {
		if (mag.year == year) {
			return &mag;
		}

	}
	cout << "Журналы, выпущенные в этом году  не найдены." << endl;
	Sleep(1000);
	return nullptr;
}

Magazine *Library::findMagazine(string name)
{
	for (Magazine &mag : magazines) {
		if (mag.title == name) {

			return &mag;
		}

	}
	cout << "Журналы с таким названием не найдены." << endl;
	Sleep(1000);
	return nullptr;
}

Magazine *Library::findMagazineAuthor(string nameAuthor)
{
	for (Magazine &mag : magazines) {
		if (mag.author->full_name == nameAuthor) {

			return &mag;
		}

	}
	cout << "Журналы этого автора не найдены.." << endl;
	Sleep(1000);
	return nullptr;
}

Reader *Library::findReader(int id)
{
	for (Reader &reader : readers) {
		if (reader.id == id) {
			return &reader;
		}
	}
	cout << "Читатель с таким идентификатором не найден" << endl;
	Sleep(1000);
	return nullptr;
}

Reader *Library::findReader(string full_name)
{
	for (Reader &reader : readers) {
		if (reader.name == full_name) {
			return &reader;
		}
	}
	cout << "Читатель с таким именем не найден" << endl;
	Sleep(1000);
	return nullptr;
}

Author *Library::findAuthor(string name)
{
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

void Library::addReader(string name)
{
	Reader reader(name);
	reader.id = generateUniqueTicketNumber();

	readers.push_back(reader);
	cout << " Читатель успешно добавлен!Номер читательского билета: " << reader.id << endl;
	countReaders++;
	Sleep(1000);
}

void Library::addAuthor(const string &name, int year)
{
	Author author;

	author.full_name = name;
	author.year_of_birth = year;

	authors.push_back(author);


	countAuthors++;
}

void Library::takeItem(Reader &reader, Item &item)
{
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

void Library::returnItem(Reader &reader, Item &item)
{
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

void Library::printBooksYear(int year)
{
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

void Library::printMagYear(int year)
{
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

void Library::printBooks()
{
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

void Library::printMagazine()
{
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

void Library::printAuthors()
{
	cout << endl;
	cout << "Список всех авторов :\n";
	for (size_t i = 0; i < authors.size(); i++)
	{
		cout << i + 1 << ") " << authors[i].full_name << endl;
	}
	cout << endl;
	Sleep(1000);
}

void Library::printReaders()
{
	cout << endl;
	cout << "Список всех читателей :\n";
	for (size_t i = 0; i < readers.size(); i++)
	{
		cout << i + 1 << ") " << readers[i].name << endl;
	}
	cout << endl;
	Sleep(1000);
}

bool Library::loadBooksFromFile(string filename, vector<Book> &books)
{
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
			book.ISBN = fields[6];
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

bool Library::loadMagazinesFromFile(string filename, vector<Magazine> &mags)
{
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

bool Library::loadAuthorsFromFile(string filename, vector<Author> &authors)
{
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

bool Library::loadReadersFromFile(string filename, vector<Reader> &rders)
{
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
