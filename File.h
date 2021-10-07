#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Color.h"
using namespace std;
class File: private Color
{
protected:
	string path;
	int numberOfRows;
	int numberOfCols;
	void mainpulator();
public:
	File();
	vector<vector<string>> getData();
	void linesData();
	int getOccOfWord(string word);
	void generate();
	int locateStartTime();
	int locateFinishTime();
};


float changeToProperTime(string time);
float changeTime(float t);
string base12(string time);