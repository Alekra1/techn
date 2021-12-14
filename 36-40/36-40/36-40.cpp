#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

using std::endl;
using std::cin;
using std::cout;

#pragma warning(disable : 4996)

struct games {
	char name[50];
	char author[50];
	float price;
}mvg;

int main() {
	int ans, wh(1);
start:
	while (wh) {
		cout << endl << "1 - Write 2 - Read: ";
		cin >> ans;
		cin.clear();
		cin.ignore();
		FILE* file;
		int size = sizeof(mvg);
		if (ans == 1) {
			file = fopen("FILE1", "ab");
			cout << "Enter name of the game: ";
			gets_s(mvg.name);
			cout << endl << "Enter author of the game: ";
			gets_s(mvg.author);
			cout << endl << "Enter price of the game: ";
			cin >> mvg.price;
			fwrite(&mvg, size, 1, file);
			fclose(file);
		}
		else if (ans == 2) {
			file = fopen("FILE1", "rb");
			fread(&mvg, size, 1, file);
			puts(mvg.name);
			puts(mvg.author);
			cout << mvg.price;
			fclose(file);
		}
		else {
			cout << endl << "Error!";
			goto start;
		}
		cout << endl << "Continue? no - 0, yes - do nothing:";
		cin >> wh;
		if (wh != 0) wh = 1;
		cin.clear();
		cin.ignore();
	}
	cout << endl;
	system("pause");
	return 0;
}