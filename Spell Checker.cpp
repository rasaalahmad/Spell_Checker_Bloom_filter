#include<iostream>
#include<fstream>
#include<string>
#include"BloomFilter.h"
#include <windows.h>
#include<iomanip>
using namespace std;



void gotoxy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}



string filterString(string &key)
{
	string temp = "";
	int i = 0;
	while (key[i] != '\0')
	{
		if (key[i] >= 'A' && key[i] <= 'Z')
		{
			temp += (key[i] + 32);
		}
		else if(key[i] >= 'a' && key[i] <= 'z')
		{
			temp += key[i];
		}
		i++;
	}

	return temp;
}


int main()
{
	BloomFilter bfilter;
	string key;

	fstream file("dict.txt");

	int i = 0;
	double percent = 0.0;
	while (file >> key)
	{
		gotoxy(0, 0);
		i++;
		percent = ((i / 91000.0) * 100.0);
		cout << fixed;
		cout << setprecision(2) <<"Dictionary Loading:" << percent<<"%";
		bfilter.insert(key);
	}

	file.close();

	cout << "\nEnter text:";
	getline(cin, key);

	i = 0;

	string temp = "";

	string temp2;

	while (key[i] != '\0')
	{
		if (key[i + 1] == '\0' || key[i] == ' ')
		{
			if (key[i + 1] == '\0')
			{
				temp += key[i];
			}

			temp2 = filterString(temp);

			if (bfilter.lookUp(temp2))
			{
				cout << temp<<" ";
			}
			else
			{
				cout << "[" << temp2 << "] ";
			}
			temp2 = "";
			temp = "";
		}
		else
		{
			temp += key[i];
		}
		i++;
	}




}