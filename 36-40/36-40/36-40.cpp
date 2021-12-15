#include <iostream>
#include <stdio.h>
#include <Windows.h>

using std::endl;
using std::cin;
using std::cout;

#pragma warning(disable : 4996)

struct Restaurant {
	char PIB[21];
	int section = 0;//
	int name = 0;//
	int service = 0;//
	int amount = 0;
	float price = 0;
	char overprice[4];
}order;

FILE* file;
char string_section[9];
char string_name[16];
char string_service[10];
int size = sizeof(struct Restaurant);

void add();
int all_orders();
void request();
void table_top();
void table_bottom();
void string(int);
void section();
void str_section();
int file_valid();
void str_name();
void kanape();
void OZ();
void Shashliki();
void service();

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int ans;
	do {
		system("cls");
		cout << endl << endl << "Головне меню программи" << endl;
		cout << endl << "1. Додати замовлення";
		cout << endl << "2. Перегляд усiх замовлень";
		cout << endl << "3. Пошук замовлень за обраним сервісом";
		cout << endl << "4. Вихiд з программи";
		cout << endl << "Оберіть: ";
		cin >> ans;
		switch (ans) {
		case 1: { add(); break; }
		case 2: { all_orders(); break; }
		case 3: { request(); break; }
		case 4: { cout << endl << "Кiнець роботи."; break; }
		default: { cout << endl << "Обрано невiрно!" << endl; system("pause"); }
		}
	} while (ans != 4);
	cout << endl;
	system("pause");
	return 0;
}

int file_valid() {
	if ((file = fopen("file", "rb")) == NULL) {
		return 1; //Файла нету(
	}
	else if (fread(&order, size, 1, file) == 0) {
		return 2; //Файл есть, он пустой
	}
	else {
		rewind(file);
		return 0; //Файл есть, есть записи, указатель в начало
	}
}

void add() {
	int ans(1), p, i(0);
	char buf[999];
	file = fopen("file", "ab");
	while (ans == 1) {
		//ПИБ
		cout << endl << "Введіть ПІБ: ";
		cin.clear();
		cin.ignore();
		gets_s(buf);
		buf[21] = '\0';
		strcpy(order.PIB, buf);
		//РАЗДЕЛ
		p = 1;
		while (p) {
			section();
			cin >> order.section;
			if (1 <= order.section and order.section <= 3) p = 0;
			else cout << endl << "Невiрно!";
		}
		//БЛЮДО
		p = 1;
		while (p) {
			switch (order.section)
			{
			case 1: {kanape(); cin >> order.name; p = 0; break; }
			case 2: {OZ(); cin >> order.name; p = 0; break; }
			case 3: {Shashliki(); cin >> order.name; p = 0; break; }
			default: {cout << endl << "Невiрно!"; break; }
			}
		}
		//КОЛИЧЕСТВО БЛЮД
		p = 1;
		while (p) {
			cout << endl << "Кiлькiсть блюд: ";
			cin >> order.amount;
			if (order.amount > 0 and order.amount <= 5) p = 0;
			else cout << endl << "Невiрно! Введіть кількість від 1 до 5 блюд!";
		}
		//СЕРВИС
		p = 1;
		while (p) {
			service();
			cin >> order.service;
			if (1 <= order.service and order.service <= 4) p = 0;
			else cout << endl << "Невiрно!";
		}
		//ЗАПИСЬ В ФАЙЛ И ЕГО ЗАКРЫТИЕ
		fwrite(&order, size, 1, file);
		cout << endl << "Бажаєте продовжити? 1 - так 2 - ні: ";
		cin >> ans;
	}
	fclose(file);
	cout << endl;
	system("pause");
}

//ЧИСТО ПОД ВЫВОД

void section() {
	cout << endl << "Оберіть розділ: 1. - Канапе";
	cout << endl << "                2. - Овочеві закуски";
	cout << endl << "                3. - Шашлики";
	cout << endl << "        Уведіть: ";
}

void str_section() {
	switch (order.section) {
	case 1: {strcpy_s(string_section, "Канапе"); break; }
	case 2: {strcpy_s(string_section, "Ов.Зак."); break; }
	case 3: {strcpy_s(string_section, "Шашлики"); break; }
	}
}

void kanape() {
	cout << endl << "Оберіть Канапе: 1 - Із сиру";
	cout << endl << "                2 - З шинкою";
	cout << endl << "                3 - Із сьомги";
	cout << endl << "                4 - З червоною ікрою";
	cout << endl << "       Уведіть: ";
}

void OZ() {
	cout << endl << "Оберіть Овочеву закуску:";
	cout << endl << "                         1 - Шампіньони фаршировані";
	cout << endl << "                         2 - Рулетики із цукіні";
	cout << endl << "                         3 - Ассорті овочеве";
	cout << endl << "                Уведіть: ";
}

void Shashliki() {
	cout << endl << "Оберіть Шашлички: 1 - Рибні";
	cout << endl << "                  2 - М'ясні";
	cout << endl << "                  3 - Курині";
	cout << endl << "         Уведіть: ";
}

void str_name() {
	switch (order.section)
	{
	case 1: {
		switch (order.name) {
		case 1: {strcpy_s(string_name, "Із сиру"); order.price = 25; break; }
		case 2: {strcpy_s(string_name, "З шинкою"); order.price = 20; break; }
		case 3: {strcpy_s(string_name, "Із сьомги"); order.price = 35; break; }
		case 4: {strcpy_s(string_name, "З червоною ікр."); order.price = 55; break; }
		}
		break;
	}
	case 2: {
		switch (order.name) {
		case 1: {strcpy_s(string_name, "Шампіньони фарш"); order.price = 15; break; }
		case 2: {strcpy_s(string_name, "Рулетики із цук"); order.price = 12; break; }
		case 3: {strcpy_s(string_name, "Ассорті овочеве"); order.price = 10; break; }
		}
		break;
	}
	case 3: {
		switch (order.name) {
		case 1: {strcpy_s(string_name, "Рибні"); order.price = 40; break; }
		case 2: {strcpy_s(string_name, "М'ясні"); order.price = 45; break; }
		case 3: {strcpy_s(string_name, "Курині"); order.price = 35; break; }
		}
		break;
	}
	}
}

void service() {
	cout << endl << "Оберіть сервісне обслуговування:";
	cout << endl << "1 - Офіціанти      ";
	cout << endl << "2 - Оренда         ";
	cout << endl << "3 - Транспортування";
	cout << endl << "4 - Без сервісного обслуговування" << endl << "Оберіть: ";
}

void str_service() {
	switch (order.service)
	{
	case 1: {strcpy_s(string_service, "Офіціанти"); break; }
	case 2: {strcpy_s(string_service, "Оренда"); break; }
	case 3: {strcpy_s(string_service, "Транспорт"); break; }
	case 4: {strcpy_s(string_service, "-"); break; }
	}
}

int all_orders() {
	int n(1), valid;
	valid = file_valid();
	if (valid == 1) {
		cout << "Файлу не існує!" << endl;
		system("pause");
		return -1;
	}
	else if (valid == 2) {
		cout << "Нажаль в нашій базі, ще немає замовлень, але ви можете створити їх!" << endl;
		system("pause");
		return 0;
	}
	else {
		table_top();
		while (fread(&order, size, 1, file) == 1) {
			string(n);
			n++;
		}
		fclose(file);
		table_bottom();
		cout << endl;
		system("pause");
		return (n - 1);
	}
}

void overprice() {
	switch (order.service)
	{
	case 1: {order.price += order.price * 0.2; strcpy_s(order.overprice, "20%"); break; }
	case 2: {order.price += order.price * 0.3; strcpy_s(order.overprice, "30%"); break; }
	case 3: {order.price += order.price * 0.1; strcpy_s(order.overprice, "10%"); break; }
	case 4: {order.price += order.price * 0.05; strcpy_s(order.overprice, "5%"); break; }
	}
}

void string(int n) {
	printf("\n|%-3i|%-21s|", n, order.PIB);
	str_section();
	str_name();
	str_service();
	overprice();
	printf("%-9s", string_section);
	printf("|%-16s|%-5i|%-9s|%-6s|%-10.2f|", string_name, order.amount, string_service, order.overprice, order.price);
}

void request() {
	int p(1), search_service, valid, n(1), flag(0);
	valid = file_valid();
	if (valid == 1) {
		cout << "Файлу не існує!";
	}
	else if (valid == 2) {
		cout << "Нажаль в нашій базі, ще немає замовлень, але ви можете створити їх!";
	}
	else {
		service();
		cin >> search_service;
		rewind(file);
		while (fread(&order, size, 1, file) == 1) {
			if (search_service == order.service) {
				flag = 1;
			}
		}
		rewind(file);
		if (flag == 1) {
			table_top();
			while (fread(&order, size, 1, file) == 1) {
				if (search_service == order.service) {
					string(n);
					n++;
				}
			}
			table_bottom();
		}
		else {
			cout << "Не знайдено жодного замовлення за обраним вами сервісом!";
		}
		fclose(file);
	}
	cout << endl;
	system("pause");
}

//TABLE
void table_top() {
	cout << endl << "----------------------------------------------------------------------------------------";
	cout << endl << "| № |         ПІБ         | Ввiддiл |     Назва      |Кiль-|  Сервіс |Надба-|Загальна  |";
	cout << endl << "|   |       замовника     |         |     страви     |кiсть|         |вки % |ціна (грн)|";
	cout << endl << "----------------------------------------------------------------------------------------";
}
void table_bottom() {
	cout << endl << "----------------------------------------------------------------------------------------" << endl;
}