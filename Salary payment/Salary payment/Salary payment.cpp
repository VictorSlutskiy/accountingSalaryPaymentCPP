#include"libraries.h"
#include"struct.h"
vector <Employee> EmployeeInfo;
void menuAdmin();
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}
void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show; 
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
void BackBlue() {
	SetConsoleTextAttribute(hStdOut, BACKGROUND_INTENSITY |BACKGROUND_BLUE);
}
void White() {
	SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void Grey() {
	SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY);
}
void BackBlack() {
	SetConsoleTextAttribute(hStdOut, 0);
}

void SignUp()
{
	string username;
	string password;
	string space;
	ofstream fout("accounts.txt", ios::app);
	while (1)
	{
		bool isCorrect = 1;
		cout << "Введите логин" << endl;
		cin >> username;
		getline(cin, space);
		if (space == "")
		{
			for (int i = 0; i < UserArr.size(); i++)
			{
				if (UserArr[i].username == username)
				{
					cout << "Пользователь с таким именем уже зарегистрирован" << endl;
					isCorrect = 0;
					break;
				}
			}
			if (isCorrect == 1)
				break;
		}
		else
		{
			cout << "Логин не должен содержать пробелов" << endl;
		}
	}
	 password = "";
	char ch;
	bool ctrlPressed = false;
	cout << "Введите пароль: ";
	while (true) {
		ch = _getch();
		if (ch == 13)
		{
			break;
		}
		if (ch == 8 || ch == 127)
		{
			if (password.length() > 0) {
				password.erase(password.length() - 1);
				cout << "\b \b";
			}
		}
		else if (ch >= 32 && ch <= 126 && ch != 224 && ch != 0)
		{
			if (ctrlPressed)
			{
				if (ch == 'c' || ch == 'C' || ch == 'v' || ch == 'V')
				{
					continue;
				}
			}
			password += ch;
			cout << '*';
		}
		else if (ch == -32)
		{
			_getch();
		}
		else if (ch == 0)
		{
			_getch();
		}
		else if (ch == 3 || ch == 22 || ch == 24)
		{
			ctrlPressed = true;
		}
		else {
			ctrlPressed = false;
		}
	}
	while (1) 
	{
		if (space != "")
		{
			cout << "Пароль не должен содержать пробелов" << endl;
		}
		else if (size(password) < 8)
		{
			cout << "Пароль должен содержать не менее 8 символов" << endl;
		}
		else
			break;
	}
	UserArr.push_back({ username,password,0,0 });
	fout << username << endl;
	fout << password << endl;
	fout << 0 << endl;
	fout << 0 << endl;
	cout << "Вы успешно зарегистрировались!" << endl;
}
int Entrance()
{
	string space;
	string username;
	string password;
	bool isLogCorrect = 0;
	bool isPassCorrect = 1;
	bool isLogged = 0;
	char choice = 0;
	int numOfUser = 0;
	string garbage;
	cout << "Введите логин" << endl;
	getline(cin, username);
	for (; numOfUser < UserArr.size()-1; numOfUser++)
	{
		if (UserArr[numOfUser].username == username)
		{
			isLogCorrect = 1;
			password = "";
			char ch;
			bool ctrlPressed = false;
			cout << "Введите пароль: " << endl;;
			while (true) {
				ch = _getch();
				if (ch == 13)
				{
					break;
				}
				if (ch == 8 || ch == 127)
				{
					if (password.length() > 0) {
						password.erase(password.length() - 1);
						cout << "\b \b";
					}
				}
				else if (ch >= 32 && ch <= 126 && ch != 224 && ch != 0)
				{
					if (ctrlPressed)
					{
						if (ch == 'c' || ch == 'C' || ch == 'v' || ch == 'V')
						{
							continue;
						}
					}
					password += ch;
					cout << '*';
				}
				else if (ch == -32)
				{
					_getch();
				}
				else if (ch == 0)
				{
					_getch();
				}
				else if (ch == 3 || ch == 22 || ch == 24)
				{
					ctrlPressed = true;
				}
				else {
					ctrlPressed = false;
				}
			}
			if (UserArr[numOfUser].password != password)
			{
				isPassCorrect = 0;
				cout << "Неверный пароль" << endl;
			}
			else
			{
				isLogged = 1;
			}
		}
	}
	if (!isLogCorrect)
		cout << "Пользователь с таким именем не зарегистрирован" << endl;
	if (!isLogCorrect || !isPassCorrect)
	{

		while (choice != '2')
		{
			cout << "1.Войти" << endl;
			cout << "2.Вернуться в меню" << endl;
			choice = getchar();
			getline(cin, garbage);
			if (garbage == "")
			{
				switch (choice)
				{
				case'1':
					Entrance();
					break;
				case'2':
					break;
				default:
				{
					cout << "Выбран неверный пункт " << endl;
				}
				}
			}
		}
	}
				if (isLogged == 1)
		return numOfUser;
	else
		return -1;
}
void overwritingFromFileToVector()
{
	ifstream fin("accounts.txt");
	string username;
	string password;
	bool isAdmin = 0;
	bool isBanned = 0;
	if (!fin.is_open())
		cout << "Не удалось открыть файл" << endl;
	else
	{
		while (!fin.eof())
		{
			fin >> username;
			fin >> password;
			fin >> isAdmin;
			fin >> isBanned;
			UserArr.push_back({ username,password,isAdmin,isBanned });
		}
	}
	fin.close();
}
void overwritingEmployees()
{
	ifstream fin("employees.txt");
	string name;
	string surname;
	string patronymic;
	string department;
	string post;
	float salary;
	if (!fin.is_open())
		cout << "Не удалось открыть файл" << endl;
	else
	{
		while (fin>>name)
		{
			fin >>surname;
			fin>> patronymic;
			fin>>department;
		    fin >>post;
			fin >> salary;
			EmployeeInfo.push_back({ name,surname,patronymic,department,post,salary });
		}
	}
	fin.close();
}
void putEmployeeInfo()
{
	string name;
	string surname;
	string patronymic;
	string department;
	string post;
	string salary_str;
	float salary;
	ofstream fout("employees.txt", ios::app);
	string space;
	while (1)
	{
		cout << "Имя" << endl;
		cin >> name;
		getline(cin, space);
		if (space != "")
			cout << "Имя не должно содержать пробелов" << endl;
		else
			break;
	}
	while (1)
	{
		cout << "Фамилия" << endl;
		cin >> surname;
		getline(cin, space);
		if (space != "")
			cout << "Фамилия не должна содержать пробелов" << endl;
		else
			break;
	}
	while (1)
	{
		cout << "Отчество" << endl;
		cin >> patronymic;
		getline(cin, space);
		if (space != "")
			cout << "Отчество не должно содержать пробелов" << endl;
		else
			break;
	}
	cout << "Отдел" << endl;
	cin >> department;
	cout << "Должность" << endl;
	cin >> post;
	while (1)
	{
		cout << "Зарплата" << endl;
		while (!(cin >> salary) || cin.peek() != '\n') {
			cin.clear();
			while (cin.get() != '\n');
			cout << "Ошибка! Введите зарплату (только цифры): " << endl;
		}
		break;
	}
	fout << name << endl;
	fout << surname << endl;
	fout << patronymic << endl;
	fout << department << endl;
	fout << post << endl;
	fout << salary << endl;
	cout << "Вы успешно добавили сотрудника!" << endl;
	EmployeeInfo.push_back({ name,surname,patronymic,department,post, salary });
}
void deleteEmployee()
{
	int activeMenu = 0;
	char choice;
	bool end = 0;
	while (!end)
	{
		int activeProof = 0;
		int x = 50, y = 10;
		system("cls");
		GoToXY(x, y++);
		cout << "Выберите сотрудника, данные о котором хотите удалить"  <<endl;
		y++;
		for (int i = 0; i < EmployeeInfo.size(); i++)
		{
			if (i == activeMenu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE| FOREGROUND_INTENSITY);
			else SetConsoleTextAttribute(hStdOut, 0x0007);
			GoToXY(x, y++);
			cout << EmployeeInfo[i].surname << " " << EmployeeInfo[i].name << " " << EmployeeInfo[i].patronymic;
		}
		SetConsoleTextAttribute(hStdOut, 0x0007);
		choice = _getch();
		if (choice == -32)
			choice = _getch();
		switch (choice)
		{
		case DOWN:
			if (activeMenu < EmployeeInfo.size() - 1)
				activeMenu++;
			break;
		case UP:
			if (activeMenu > 0)
				activeMenu--;
			break;
		case ESC:
			system("cls");
			menuAdmin();
		case ENTER:
		{
			while (!end)
			{
				system("cls");
				x = 30, y = 12;
				GoToXY(x, y);
				y += 6;
				x = 50;
				cout << "Вы точно хотите удалить данные сотрудника " << EmployeeInfo[activeMenu].surname << "?" << endl;
				string proof[] = { "Да","Нет" };
				for (int i = 0; i < size(proof); i++)
				{
					if (i == activeProof)
						SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					else SetConsoleTextAttribute(hStdOut, 0x0007);
					GoToXY(x, y);
					x += 20;
					cout << proof[i];
				}
				SetConsoleTextAttribute(hStdOut, 0x0007);
				choice = _getch();
				if (choice == -32)
					choice = _getch();
				switch (choice)
				{
				case RIGHT:
					if (activeProof < size(proof) - 1)
						activeProof++;
					break;
				case LEFT:
					if (activeProof > 0)
						activeProof--;
					break;
				case ENTER:
					switch (activeProof)
					{
					case 0: {
						EmployeeInfo.erase(EmployeeInfo.begin() + activeMenu);
						ofstream file("employees.txt", ios::out | ios::trunc);
						for (int i = 0; i < EmployeeInfo.size(); i++)
						{
							file << EmployeeInfo[i].name << " "
								<< EmployeeInfo[i].surname << " "
								<< EmployeeInfo[i].patronymic << " "
								<< EmployeeInfo[i].department << " "
								<< EmployeeInfo[i].post << " "
								<< EmployeeInfo[i].salary << endl;
						}
						file.close();
						break;
					}
					case 1:
						break;
					}
					end++;
					break;
				}
			}
		}
		}
	}
}
void displayEmployeeInfo()
{
	int length = 120;
	system("cls");
	cout<<" " << setfill('_') << setw(length - 2) << "" << setfill(' ') <<" " << endl;
	cout << "| " << setw(13) << "Имя" << " |"
		<< setw(13) << "Фамилия" << " |"
		<< setw(13) << "Отчество" << " |"
		<< setw(15) << "Отдел" << setw(10) << " |"
		<< setw(16) << "Должность" << setw(8) << " |"
		<< setw(20) << "Заработная плата" << setw(4) << " |"<<endl;
	cout << "|" << setfill('=') << setw(length -2) << "" << setfill(' ') << "|" << endl;
	for (int i = 0; i < EmployeeInfo.size(); i++)
	{
		cout << "|" <<setw(14) << EmployeeInfo[i].name << " |"
			<< setw(13) << EmployeeInfo[i].surname << " |"
			<< setw(13) << EmployeeInfo[i].patronymic << " |"
			<< setw(23) << EmployeeInfo[i].department<<" |"
			<< setw(22) << EmployeeInfo[i].post << " |"
			<< setw(22) << EmployeeInfo[i].salary << " |" << endl
			<< "|" << setfill('=') << setw(length - 2) << "" << setfill(' ') << "|" << endl;
	}
}
void searchSurname()
{
	string surname;
	bool first = 1;
	int length = 120;
	int numOfResult = 0;
	string search;
	cout << "Введите строку для поиска: ";
	cin >> search;
	for (int i = 0; i < EmployeeInfo.size(); i++)
	{
		if (EmployeeInfo[i].surname.find(search) != string::npos)
		{
			if (first == 1)
			{
				cout << " " << setfill('_') << setw(length - 2) << "" << setfill(' ') << " " << endl;
				cout << "| " << setw(13) << "Имя" << " |"
					<< setw(13) << "Фамилия" << " |"
					<< setw(13) << "Отчество" << " |"
					<< setw(15) << "Отдел" << setw(10) << " |"
					<< setw(16) << "Должность" << setw(8) << " |"
					<< setw(20) << "Заработная плата" << setw(4) << " |" << endl;
				cout << "|" << setfill('=') << setw(length - 2) << "" << setfill(' ') << "|" << endl;
				first = 0;
			}
			cout << "|" << setw(14) << EmployeeInfo[i].name << " |"
				<< setw(13) << EmployeeInfo[i].surname << " |"
				<< setw(13) << EmployeeInfo[i].patronymic << " |"
				<< setw(23) << EmployeeInfo[i].department << " |"
				<< setw(22) << EmployeeInfo[i].post << " |"
				<< setw(22) << EmployeeInfo[i].salary << " |" << endl;
			numOfResult++;
		}
	}
	if (numOfResult == 0)
		cout << "По вашему запросу ничего не найдено" << endl;
	else
		cout << "|" << setfill('_') << setw(length - 2) << "" << setfill(' ') << "|" << endl;
	system("pause");

}
void searchPost()
{
	string post;
	bool first = 1;
	int length = 120;
	int numOfResult = 0;
	string search;
	cout << "Введите строку для поиска: ";
	cin >> search;
	for (int i = 0; i < EmployeeInfo.size(); i++)
	{
		if (EmployeeInfo[i].post.find(search) != string::npos)
		{
			if (first == 1)
			{
				cout << " " << setfill('_') << setw(length - 2) << "" << setfill(' ') << " " << endl;
				cout << "| " << setw(13) << "Имя" << " |"
					<< setw(13) << "Фамилия" << " |"
					<< setw(13) << "Отчество" << " |"
					<< setw(15) << "Отдел" << setw(10) << " |"
					<< setw(16) << "Должность" << setw(8) << " |"
					<< setw(20) << "Заработная плата" << setw(4) << " |" << endl;
				cout << "|" << setfill('=') << setw(length - 2) << "" << setfill(' ') << "|" << endl;
				first = 0;
			}
			cout << "|" << setw(14) << EmployeeInfo[i].name << " |"
				<< setw(13) << EmployeeInfo[i].surname << " |"
				<< setw(13) << EmployeeInfo[i].patronymic << " |"
				<< setw(23) << EmployeeInfo[i].department << " |"
				<< setw(22) << EmployeeInfo[i].post << " |"
				<< setw(22) << EmployeeInfo[i].salary << " |" << endl;
			numOfResult++;
		}
	}
	if (numOfResult == 0)
		cout << "По вашему запросу ничего не найдено" << endl;
	else
		cout << "|" << setfill('_') << setw(length - 2) << "" << setfill(' ') << "|" << endl;
	system("pause");

}
void searchDepartment()
{
	string department;
	bool first = 1;
	int length = 120;
	int numOfResult = 0;
	string search;
	cout << "Введите строку для поиска: ";
	cin >> search;
	for (int i = 0; i < EmployeeInfo.size(); i++)
	{
		if (EmployeeInfo[i].department.find(search) != string::npos)
		{
			if (first == 1)
			{
				cout << " " << setfill('_') << setw(length - 2) << "" << setfill(' ') << " " << endl;
				cout << "| " << setw(13) << "Имя" << " |"
					<< setw(13) << "Фамилия" << " |"
					<< setw(13) << "Отчество" << " |"
					<< setw(15) << "Отдел" << setw(10) << " |"
					<< setw(16) << "Должность" << setw(8) << " |"
					<< setw(20) << "Заработная плата" << setw(4) << " |" << endl;
				cout << "|" << setfill('=') << setw(length - 2) << "" << setfill(' ') << "|" << endl;
				first = 0;
			}
			cout << "|" << setw(14) << EmployeeInfo[i].name << " |"
				<< setw(13) << EmployeeInfo[i].surname << " |"
				<< setw(13) << EmployeeInfo[i].patronymic << " |"
				<< setw(23) << EmployeeInfo[i].department << " |"
				<< setw(22) << EmployeeInfo[i].post << " |"
				<< setw(22) << EmployeeInfo[i].salary << " |" << endl;
			numOfResult++;
		}
	}
	if (numOfResult == 0)
		cout << "По вашему запросу ничего не найдено" << endl;
	else
		cout << "|" << setfill('_') << setw(length - 2) << "" << setfill(' ') << "|" << endl;
	system("pause");

}
int sortOrder = 1;
void sortName()
	{
		if(sortOrder==1)
		{
			for (int i = 0; i < EmployeeInfo.size() - 1; i++)
			{
				for (int j = 0; j < EmployeeInfo.size() - i - 1; j++)
				{
					if (EmployeeInfo[j].surname > EmployeeInfo[j + 1].surname)
						swap(EmployeeInfo[j], EmployeeInfo[j + 1]);
				}
			}
			sortOrder = -1;
		}
		else
		{
			for (int i = 0; i < EmployeeInfo.size() - 1; i++)
			{
				for (int j = 0; j < EmployeeInfo.size() - i - 1; j++)
				{
					if (EmployeeInfo[j].surname < EmployeeInfo[j + 1].surname)
						swap(EmployeeInfo[j], EmployeeInfo[j + 1]);
				}
			}
			sortOrder = 1;
		}
		displayEmployeeInfo();
	}
void sortPost()
	{
		if (sortOrder == 1)
		{
			for (int i = 0; i < EmployeeInfo.size() - 1; i++)
			{
				for (int j = 0; j < EmployeeInfo.size() - i - 1; j++)
				{
					if (EmployeeInfo[j].post > EmployeeInfo[j + 1].post)
						swap(EmployeeInfo[j], EmployeeInfo[j + 1]);
				}
			}
			sortOrder = -1;
		}
		else
		{
			for (int i = 0; i < EmployeeInfo.size() - 1; i++)
			{
				for (int j = 0; j < EmployeeInfo.size() - i - 1; j++)
				{
					if (EmployeeInfo[j].post < EmployeeInfo[j + 1].post)
						swap(EmployeeInfo[j], EmployeeInfo[j + 1]);
				}
			}
			sortOrder = 1;
		}
		displayEmployeeInfo();
	}
void sortSalary()
	{
		if (sortOrder == 1)
		{
			for (int i = 0; i < EmployeeInfo.size() - 1; i++)
			{
				for (int j = 0; j < EmployeeInfo.size() - i - 1; j++)
				{
					if (EmployeeInfo[j].salary < EmployeeInfo[j + 1].salary)
						swap(EmployeeInfo[j], EmployeeInfo[j + 1]);
				}
			}
			sortOrder = -1;
		}
		else
		{
			for (int i = 0; i < EmployeeInfo.size() - 1; i++)
			{
				for (int j = 0; j < EmployeeInfo.size() - i - 1; j++)
				{
					if (EmployeeInfo[j].salary > EmployeeInfo[j + 1].salary)
						swap(EmployeeInfo[j], EmployeeInfo[j + 1]);
				}
			}
			sortOrder = 1;
		}
		displayEmployeeInfo();
	}
void sortDepartment()
	{
		if (sortOrder == 1)
		{
			for (int i = 0; i < EmployeeInfo.size() - 1; i++)
			{
				for (int j = 0; j < EmployeeInfo.size() - i - 1; j++)
				{
					if (EmployeeInfo[j].department > EmployeeInfo[j + 1].department)
						swap(EmployeeInfo[j], EmployeeInfo[j + 1]);
				}
			}
			sortOrder = -1;
		}
		else
		{
			for (int i = 0; i < EmployeeInfo.size() - 1; i++)
			{
				for (int j = 0; j < EmployeeInfo.size() - i - 1; j++)
				{
					if (EmployeeInfo[j].department < EmployeeInfo[j + 1].department)
						swap(EmployeeInfo[j], EmployeeInfo[j + 1]);
				}
			}
			sortOrder = 1;
		}
		displayEmployeeInfo();
	}
void calculateSalary()
{
	float forhour;
	int time;
	float tax;
	float salary;
	cout << "Введите ставку за час работы: " << endl;
	while (!(cin >> forhour) || cin.peek() != '\n') {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка! Введите ставку за час работы (только цифры): " << endl;
	}
	cout << "Введите количество отработанных часов: " << endl;
	while (!(cin >> time) || cin.peek() != '\n') {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка! Введите количество отработанных часов (только цифры): " << endl;
	}
	cout << "Введите сумму налогов и вычетов: " << endl;
	while (!(cin >> tax) || cin.peek() != '\n') {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка! Введите сумму налогов и вычетов (только цифры): " << endl;
	}
	salary = forhour * time - tax;
	cout << "Заработная плата рассчитана: " << salary << endl;
}
void searchMenu() 
{
	string choice_s;
	bool isCorrect = 0;
	string menu[] = { "Поиск по сотрудника по фамилии", "Поиск сотрудников по отделу", "Поиск сотрудников по должности"};
	int active_menu = 0;
	while (isCorrect == 0) {

		int x = 50, y = 10;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)
				BackBlue();
			else White();
			
				GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu > 0)
				--active_menu;
		}
			   break;
		case DOWN: {
			if (active_menu < size(menu) - 1)
				++active_menu;
		}
				 break;
		case ESC:
			system("cls");
			menuAdmin();
		case ENTER:
			switch (active_menu)
			{
			case 0:
				system("cls");
				searchSurname();
				_getch();
				system("cls");
				break;
			case 1: {
				system("cls");
				searchDepartment();
				_getch();
				system("cls");
			}
				  break;
			case 2:
				system("cls");
				searchPost();
				system("cls");
				break;
			
			}
			break;
		}
	}
}
void sortmenu()
{
	string choice_s;
	bool isCorrect = 0;
	string menu[] = { "Сортировать по фамилии","Сортировать по должности","Сортировать по отделу","Сортировать по зарплате" };
	int active_menu = 0;
	while (isCorrect == 0) {

		int x = 50, y = 10;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)
				BackBlue();
			else White();
			
				GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu > 0)
				--active_menu;
		}
			   break;
		case DOWN: {
			if (active_menu < size(menu) - 1)
				++active_menu;
		}
				 break;
		case ESC:
			system("cls");
			menuAdmin();
		case ENTER:
			switch (active_menu)
			{
			case 0:
				system("cls");
				sortName();
				_getch();
				system("cls");
				break;
			case 1: {
				system("cls");
				sortPost();
				_getch();
				system("cls");
			}
				  break;
			case 2: {
				system("cls");
				sortDepartment();
				_getch();
				system("cls");
			}
			case 3: {
				system("cls");
				sortSalary();
				_getch();
				system("cls");
			}

				  break;
			}
		}
	}
}
void menuAdmin()
{
	string choice_s;
	bool isCorrect = 0;
	string menu[] = { "Вывести список сотрудников", "Добавить сотрудника", "Удалить сотрудника","Сортировка сотрудников" , "Поиск сотрудников" ,"Рассчитать заработную плату","Завершить работу программы" };
	int active_menu = 0;
	while (isCorrect == 0) {

		int x = 50, y = 10;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)
				BackBlue();
			else White();
			if (i == size(menu) - 1)
				GoToXY(x, y += 2);
			else
				GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu > 0)
				--active_menu;
		}
			   break;
		case DOWN: {
			if (active_menu < size(menu) - 1)
				++active_menu;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				system("cls");
				displayEmployeeInfo();
				_getch();
				system("cls");
				break;
			case 1: {
				system("cls");
				putEmployeeInfo();
				_getch();
				system("cls");
			}
				  break;
			case 2: {
				system("cls");
				deleteEmployee();
				_getch();
				system("cls");
			}
				  break;
			case 3:
				system("cls");
				sortmenu();
				break;

			case 4: {
				system("cls");
				searchMenu();
				_getch();
				system("cls");
			}
				  break;
			case 5: {
				system("cls");
				calculateSalary();
				system("pause");
				system("cls");
			}
				break;
			
			case 6: {
				
				system("cls");
				isCorrect = 1;
			}
				  break;
			}
			break;
		}
	}
}
void menu()
{

	overwritingFromFileToVector();
	overwritingEmployees();
	string choice_s;
	bool isCorrect = 0;
	string menu[] = { "Войти в программу", "Зарегестрироваться", "Завершить работу программы" };
	int active_menu = 0;
	while (isCorrect == 0) {

		int x = 50, y = 10;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)
				BackBlue();
			else White();
			if (i == size(menu) - 1)
				GoToXY(x, y += 2);
			else
				GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu > 0)
				--active_menu;
		}
			   break;
		case DOWN: {
			if (active_menu < size(menu) - 1)
				++active_menu;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				system("cls");
				if (Entrance() == -1)
					break;
				else {
					system("cls");
					menuAdmin();
				}
				_getch();
				system("cls");
				break;
			case 1: {
				system("cls");
				SignUp();
				_getch();
				system("cls");
			}
				  break;
			case 2: {

				system("cls");
				isCorrect = 1;
			}
				  break;
			}
			break;
		}
	}
}
