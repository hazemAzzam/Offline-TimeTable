#include "Color.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void Color::getColors()
{
	ifstream colors("Colors.txt");
	if (colors >> first >> second >> third >> fourth >> color5 >> color6 >> color7 >> color8 >> color9);
	else {
		colors.close();
		putColors();
	}
}

void Color::putColors()
{
	cout << "Background Color: "; cin >> first;
	cout << "Background Color - Headers: "; cin >> second;
	cout << "Background Color - Lectures in the day: "; cin >> third;
	cout << "Background Color - Current Lectures: "; cin >> fourth;
	cout << "Font Color - Selected Day: "; cin >> color5;
	cout << "Font Color - Selected Lectures: "; cin >> color6;
	cout << "Font Color - Headers: "; cin >> color7;
	cout << "Font Color - data: "; cin >> color8;
	cout << "Font Color - Title: "; cin >> color9;
	ofstream file("Colors.txt");
	file << first << endl
		<< second << endl
		<< third << endl
		<< fourth << endl
		<< color5 << endl
		<< color6 << endl
		<< color7 << endl
		<< color8 << endl
		<< color9;
	file.close();
}

void Color::changeColor()
{
	system("cls");
	cout << "### Change Color ###\n\n";
	cout << "1) All.\n"
		"2) Backgrounds.\n"
		"3) Fonts.\n";
	int choice;
	cout << "[?]> "; cin >> choice;
	if (choice == 1)
		putColors();
	else if (choice == 2) {
		cout << "\n1) HTML.\n"
			"2) Headers.\n"
			"3) Lectures in Current Day.\n"
			"4) Selected Lectures.\n";
		cout << "[?]> ";  cin >> choice;
		cout << "[#color?]: ";
		switch (choice)
		{
		case 1:
			cin >> first;
			break;
		case 2:
			cin >> second;
			break;
		case 3:
			cin >> third;
		case 4:
			cin >> fourth;
		default:
			break;
		}
	}
	else if (choice == 3) {
		cout << "\n1) Selected Day.\n"
			"2) Selected Lectures.\n"
			"3) Headers\n"
			"4) Data\n"
			"5) Title\n";
		cout << "[?]> ";  cin >> choice;
		cout << "[#color?]: ";
		switch (choice)
		{
		case 1:
			cin >> color5;
			break;
		case 2:
			cin >> color6;
			break;
		case 3:
			cin >> color7;
			break;
		case 4:
			cin >> color8;
			break;
		case 5:
			cin >> color9;
			break;
		default:
			break;
		}
	}
	ofstream file("Colors.txt");
	file << first << endl
		<< second << endl
		<< third << endl
		<< fourth << endl
		<< color5 << endl
		<< color6 << endl
		<< color7 << endl
		<< color8 << endl
		<< color9;
	file.close();
}