#include "File.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Color.h"
using namespace std;

File::File()
{
	cout << "--> Pick File <--\n";
	cout << "Path: "; getline(cin, path, '\n');
	cout << "Title: "; getline(cin, title, '\n');
}
void File::mainpulator()
{
	string p = "";
	for (int i = 0; i < path.length(); i++) {
		if (path[i] == '\\')
			p += '\\';
		p += path[i];
	}
	path = p;
}

vector<vector<string>> File::getData()
{
	ifstream file(path);
	int row = 0;
	int col = 0;
	string line = "";
	linesData();
	vector<vector<string>> data(numberOfRows, vector<string>(numberOfCols, ""));
	for (int i = 0; i < numberOfRows; i++) {
		col = 0;
		getline(file, line, '\n');
		for (int j = 0; j < line.length(); j++) {
			if (line[j] == '|') {
				col++;
				continue;
			}
			data[i][col] += line[j];
		}
	}

	return data;
}
void File::linesData()
{
	string line;
	ifstream myfile(path);
	int rows = 0;
	if (myfile.is_open()) {
		while (!myfile.eof()) {
			getline(myfile, line);
			numberOfCols = count(line.begin(), line.end(), '|') + 1;
			rows++;
		}
		myfile.close();
	}
	numberOfRows = rows;
}

int File::getOccOfWord(string word)
{
	vector<vector<string>> data = getData();
	int counter = 0;
	for (int i = 0; i < numberOfRows; i++) {
		for (int j = 0; j < numberOfCols; j++) {
			if (word.compare(data[i][j]) == 0)
				counter++;
		}
	}
	return counter;
}

void File::generate()
{
	vector<vector<string>> data = getData();
	struct Day
	{
		string name;
		string code;

	};
	Day day[7] = {
		{"SAT", "6"},
		{"SUN", "0"},
		{"MON", "1"},
		{"TUE", "2"},
		{"WED", "3"},
		{"THU", "4"},
		{"FRI", "5"}
	};
	Color::getColors();
	ofstream htmlFile(title+".html");
	htmlFile << "<!DOCTYPE html>\n<html>\n";
	htmlFile << "	<head><meta charset='UTF-8' /><meta name='viewport' content='width = device - width, initial - scale = 1' /> \n";
	htmlFile << "	<style id='webmakerstyle'>:root { --first: " + Color::first + "; --second: " + Color::second + "; --third: " + Color::third + "; --font-color: " + Color::fourth + "; } #body { text-align: center; background-color: var(--first); font-size: 20px; font-family: sans-serif; } table { left: 50%; top: 50%; transform: translate(-50%, -50%); background-color: var(--first); border-collapse: collapse; color: var(--font-color); table-layout: auto; position: absolute; width: 100%; } th { background-color: var(--second); padding: 20px; } td { font-size: 20px; padding: 7px; height: 50px; }</style>\n";
	htmlFile << "	</head>\n";
	htmlFile <<
		"	<body id='body'>\n"
		"		<table id='table'>\n"
		"			<caption id='cb'>"  +title+  "</caption>\n"
		"			<tr>\n";
	
	for (int i = 0; i < numberOfCols; i++)
	{// put headers
		htmlFile << "					<th>" << data[0][i] << "</th>\n";
	}
	htmlFile << "				</tr>\n";
	
	int row = 1;
	for (int i = 0; i < 7; i++)
	{
		int numberOfLectures = getOccOfWord(day[i].name);
		if (numberOfLectures > 0)
		{
			int j = row;
			for (; j < numberOfLectures + row && j < numberOfRows; j++) {
				int start = locateStartTime();
				int finish = locateFinishTime();
				if (j == numberOfLectures + row - 1) {
					htmlFile << "				<tr style='border-bottom: 1px solid #323232;' id=\'" + day[i].code + data[j][start] + "\' class=\'" + day[i].code + "\'>\n";
				}
				else
					htmlFile << "				<tr id=\'" + day[i].code + data[j][start] + "\' class=\'" + day[i].code + "\'>\n";
				if (j == row) {
					htmlFile <<
						"					<th rowspan=" + to_string(numberOfLectures) + ">" + data[j][0] + "</th>\n";
				}
				for (int k = 1; k < numberOfCols; k++)
				{
					if (k == start || k == finish)
						htmlFile <<
							"					<td class=\'" + day[i].code + data[j][start] + " font " + to_string(stoi(day[i].code) + 10) + "\'>" + base12(data[j][k]) + "</td>\n";
					else 
						htmlFile <<
							"					<td class=\'" + day[i].code + data[j][start] + " font " + to_string(stoi(day[i].code) + 10) + "\'>" + data[j][k] + "</td>\n";

				}
				htmlFile << "				</tr>\n";
			}
			row = j;
		}
	}

	htmlFile <<
		"		</table>\n"
		"	</body>\n"
		"</html>\n";
	htmlFile <<
		"<script>\n"
		"setInterval(myTimer, 1000);var second = '" + Color::fourth + "';var third = '" + Color::third + "'; var fourth = '" + Color::fourth + "'; var first = '" + Color::first + "'; var d = new Date(); tday = new Array('Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'); var t = d.toLocaleTimeString(); var day = d.getDay(); var hours = d.getHours() + d.getMinutes() / 100; function daySelector() { var galleries = document.getElementsByClassName(day); var len = galleries.length; for (var i = 0; i < len; i++) { galleries[i].style.backgroundColor = third; } var it = 0; while (document.getElementsByClassName(day + 10)[it]) document.getElementsByClassName(day + 10)[it++].style.color = second; }"
		"\nfunction myTimer() {\n"
		"	var sDate = new Date();\n";
	int ROW = 1;
	for (int i = 0; i < 7; i++)
	{
		int numberOfLectures = getOccOfWord(day[i].name);
		if (numberOfLectures > 0)
		{
			htmlFile <<
				"	if (day == " + day[i].code + ") {\n"
				"		daySelector();\n";
			for (int j = 0; j < numberOfLectures; j++)
			{
				int startPos = locateStartTime();
				int finishPos = locateFinishTime();

				float start = changeTime(changeToProperTime(data[ROW][startPos]));

				float finish = changeTime(changeToProperTime(data[ROW][finishPos]));

				htmlFile <<
					"		if (hours >= " + to_string(start) + " && hours < " + to_string(finish) + ") {\n"
					"			document.getElementById(\'" + day[i].code + data[ROW][startPos] + "\').style.backgroundColor = fourth;\n"
					"			for (var i = 0; i < "+to_string(numberOfCols-1)+"; i++)\n"
					"				document.getElementsByClassName(\"" + day[i].code + data[ROW][startPos] + " font\")[i].style.color = first;\n"
					"		}\n";
				ROW++;
			}
			htmlFile <<
				"	}\n";
		}
	}
	htmlFile <<
		"}\n</script>";
}

int File::locateStartTime()
{
	vector<vector<string>> data = getData();
	for (int i = 0; i < numberOfCols; i++) {
		if (data[0][i].compare("START") == 0)
			return i;
	}
}

int File::locateFinishTime()
{
	vector<vector<string>> data = getData();
	for (int i = 0; i < numberOfCols; i++) {
		if (data[0][i].compare("FINISH") == 0)
			return i;
	}
}


float changeToProperTime(string time)
{
	string strHours = "", strMinutes = "";
	bool reachedToMinutes = false;

	for (int i = 0; i < 5; i++) {
		if (!isdigit(time[i])) {
			reachedToMinutes = true;
			continue;
		}
		if (!reachedToMinutes)
			strHours += time[i];
		else
			strMinutes += time[i];
	}
	if (reachedToMinutes == false)
		strMinutes += '0';

	float hours = stof(strHours);
	float minutes = stof(strMinutes);

	return hours + (minutes / 100);
}
float changeTime(float t)
{
	return t - ((float)(40 + 20) / 100);
}
string base12(string time)
{
	float hours = changeToProperTime(time);
	bool isPM = false;
	if (hours > 12) {
		hours -= 12;
		isPM = true;
	}
	string timeStr = "";
	if (hours < 10) {
		timeStr += "0";
		timeStr += to_string((int)hours);
	}
	else {
		timeStr += to_string((int)hours);
	}
	timeStr += ":";

	int minutes = round(hours * 100 - (int)hours * 100);
	if (minutes < 10) {
		timeStr += "0";
		timeStr += to_string(minutes);
	}
	else {
		timeStr += to_string(minutes);
	}
	if (isPM)
		timeStr += " PM";
	else
		timeStr += " AM";
	return timeStr;
}