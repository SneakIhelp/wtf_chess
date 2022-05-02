#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

long randomize(long raz){       // рандом
    return rand() % raz + 1;
}

int convert_for_matrix (string per) // из A - 0
{
    if(per == "A")
        return 0;
    else if (per == "B")
        return 1;
    else if (per == "C")
        return 2;
    else if (per == "D")
        return 3;
    else if (per == "E")
        return 4;
    else if (per == "F")
        return 5;
    else if (per == "G")
        return 6;
    else
        return 7;
}

string convert_for_fig (long per) // из 1 - P, для рандома
{
    if(per == 1)
        return "P";
    else if (per == 2)
        return "B";
    else if (per == 3)
        return "N";
    else if (per == 4)
        return "R";
    else if (per == 5)
        return "Q";
    else
        return "K";
}

string convert_for_pos (long per) // из 0 - A
{
    if(per == 0)
        return "A";
    else if (per == 1)
        return "B";
    else if (per == 2)
        return "C";
    else if (per == 3)
        return "D";
    else if (per == 4)
        return "E";
    else if (per == 5)
        return "F";
    else if (per == 6)
        return "G";
    else
        return "H";
}

int stoimost_figuri(string str) // ценность фигуры
{
    if(str == "P")
        return 1;
    else if (str == "B" or str == "N")
        return 3;
    else if (str == "R")
        return 5;
    else if (str == "Q")
        return 8;
    else
        return 9;
}


