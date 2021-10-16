#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Color
{
protected:
	/*
		first  -> background color
		second -> background color of header of the table
		third  -> background color of all lectures in the current day
		fourth -> background color of the current lecture
		color5 -> font color of selected day
		color6 -> font color of the lectures
		color7 -> font color of the headers
		color8 -> font color of the data
		color9 -> font color of the title
	*/
	string first, second, third, fourth, color5, color6, color7, color8, color9;
public:
	void getColors();
	void putColors();
	void changeColor();
};

