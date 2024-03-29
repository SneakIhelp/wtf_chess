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

int main()
{
    srand(time(nullptr));
    bool for_random = false;
    string str,figura="",posicia_bukva="",posicia_4islo="",bar;
    int numb,pos,prov,prov2,color=0;
    vector<string> hodi;
    vector<int> figuri {8,2,2,2,1,1};
    vector<vector<string>> matrix(8,vector<string>(8,".."));
    vector<vector<string>> dumai(8,vector<string>(8,".."));

    ifstream CHITKA("cond.txt");
    getline(CHITKA,str);                //запись номера хода, для понятия стороны
    numb = stoi(str);                   //запись номера хода, для понятия стороны
    while(getline(CHITKA,str))
        hodi.push_back(str);
    CHITKA.close();

    ifstream for_matrix("cond.txt");
    getline(for_matrix,bar);
    while(getline(for_matrix,bar)) // заполнение матрицы как шахм. доски
    {
        if(color%2==0){
            matrix[8-stoi(bar.substr(2,1))][convert_for_matrix(bar.substr(1,1))] = "W"+bar.substr(0,1);
            dumai[8-stoi(bar.substr(2,1))][convert_for_matrix(bar.substr(1,1))] = "W"+bar.substr(0,1);
        }
        else{
            matrix[8-stoi(bar.substr(2,1))][convert_for_matrix(bar.substr(1,1))] = "D"+bar.substr(0,1);
            dumai[8-stoi(bar.substr(2,1))][convert_for_matrix(bar.substr(1,1))] = "D"+bar.substr(0,1);
        }
        color ++;
    }

    if(numb % 2 == 0) // ОПРЕДЕЛЕНИЕ СТОРОНЫ
    {
        for(int i = 0;i<long(hodi.size());i=i+2)
        {
            if(hodi[i].substr(0,1) == "P")
                figuri[0]--;
            else if(hodi[i].substr(0,1) == "B")
                figuri[1]--;
            else if(hodi[i].substr(0,1) == "N")
                figuri[2]--;
            else if(hodi[i].substr(0,1) == "R")
                figuri[3]--;
            else if(hodi[i].substr(0,1) == "Q")
                figuri[4]--;
            else if(hodi[i].substr(0,1) == "K")
                figuri[5]--;
        }
    }
    if(numb % 2 == 1)
    {
        for(int i = 1;i<long(hodi.size());i=i+2)    // Сколько фигур осталось в запасе
        {
            if(hodi[i].substr(0,1) == "P")
                figuri[0]--;
            else if(hodi[i].substr(0,1) == "B")
                figuri[1]--;
            else if(hodi[i].substr(0,1) == "N")
                figuri[2]--;
            else if(hodi[i].substr(0,1) == "R")
                figuri[3]--;
            else if(hodi[i].substr(0,1) == "Q")
                figuri[4]--;
            else if(hodi[i].substr(0,1) == "K")
                figuri[5]--;
        }                                           // Сколько фигур осталось в запасе

        int maksimal = 0, s_p, most_expensive_fig_R, most_expensive_fig_C;
        for(int r = 0; r < int(dumai.size()); r += 1)       // Нахождение самой дорогой фигуры
        {
            for(int c = 0; c < int(dumai[r].size()); c += 1)
            {
                if(dumai[r][c]!=".." and dumai[r][c].substr(0,1)!="D")
                {
                    s_p = stoimost_figuri(dumai[r][c].substr(1,1));
                    if(s_p > maksimal)
                    {
                        maksimal = s_p;
                        most_expensive_fig_R = r;
                        most_expensive_fig_C = c;
                    }
                }
            }
        }                                                   // Нахождение самой дорогой фигуры

        if(maksimal == 8)
        {
            if(figuri[0]!=0 and (most_expensive_fig_R-1 >= 0 and most_expensive_fig_C+1 < 8) or (most_expensive_fig_R-1 >=0 and most_expensive_fig_C-1>=0))
            {
                figura = "P";
                if(dumai[most_expensive_fig_R-1][most_expensive_fig_C+1]=="..")
                {
                    if(dumai[most_expensive_fig_R-1][most_expensive_fig_C+1]=="..")
                    
                    {
                        posicia_bukva = convert_for_pos(most_expensive_fig_C+1);
                        posicia_4islo = to_string(8-most_expensive_fig_R+1);
                    }
                    else if(dumai[most_expensive_fig_R-1][most_expensive_fig_C-1]=="..")
                    {
                        posicia_bukva = convert_for_pos(most_expensive_fig_C-1);
                        posicia_4islo = to_string(8-most_expensive_fig_R+1);
                    }
                }
            }
            else if (figuri[2]!=0 and (most_expensive_fig_R-2 >= 0 and most_expensive_fig_C-1 >= 0 or most_expensive_fig_R-2 >= 0 and most_expensive_fig_C+1 < 8 or most_expensive_fig_R-1 >= 0 and most_expensive_fig_C-2 ==".." or dumai[most_expensive_fig_R-1][most_expensive_fig_C+2]==".." or dumai[most_expensive_fig_R+1][most_expensive_fig_C-2]==".." or dumai[most_expensive_fig_R+1][most_expensive_fig_C+2]==".."))
            {
                figura = "N";
                if(dumai[most_expensive_fig_R-2][most_expensive_fig_C-1]=="..")
                {
                    posicia_bukva = convert_for_pos(most_expensive_fig_C-1);
                    posicia_4islo = to_string(8-most_expensive_fig_R+2);
                }
                else if(dumai[most_expensive_fig_R-2][most_expensive_fig_C+1]=="..")
                {
                    posicia_bukva = convert_for_pos(most_expensive_fig_C+1);
                    posicia_4islo = to_string(8-most_expensive_fig_R+2);
                }
                else if(dumai[most_expensive_fig_R-1][most_expensive_fig_C-2]=="..")
                {
                    posicia_bukva = convert_for_pos(most_expensive_fig_C-2);
                    posicia_4islo = to_string(8-most_expensive_fig_R+1);
                }
                else if(dumai[most_expensive_fig_R-1][most_expensive_fig_C+2]=="..")
                {
                    posicia_bukva = convert_for_pos(most_expensive_fig_C+2);
                    posicia_4islo = to_string(8-most_expensive_fig_R+1);
                }
                else if(dumai[most_expensive_fig_R+1][most_expensive_fig_C-2]=="..")
                {
                    posicia_bukva = convert_for_pos(most_expensive_fig_C-2);
                    posicia_4islo = to_string(8-most_expensive_fig_R-1);
                }
                else if(dumai[most_expensive_fig_R+1][most_expensive_fig_C+2]=="..")
                {
                    posicia_bukva = convert_for_pos(most_expensive_fig_C+2);
                    posicia_4islo = to_string(8-most_expensive_fig_R-1);
                }
                else if(dumai[most_expensive_fig_R+2][most_expensive_fig_C+1]=="..")
                {
                    posicia_bukva = convert_for_pos(most_expensive_fig_C+1);
                    posicia_4islo = to_string(8-most_expensive_fig_R-2);
                }
                else if(dumai[most_expensive_fig_R+2][most_expensive_fig_C-1]=="..")
                {
                    posicia_bukva = convert_for_pos(most_expensive_fig_C-1);
                    posicia_4islo = to_string(8-most_expensive_fig_R-2);
                }
            }
            else            // рандом
            {
                while (!for_random)
                { 
                    prov = randomize(6);
                    if(figuri[prov-1]>0)
                        figura = convert_for_fig(prov);
                    prov = randomize(8);
                    prov2 = randomize(8);
                    if(matrix[8-prov][prov2-1] == "..")
                    {
                        posicia_bukva = convert_for_pos(prov2-1);
                        posicia_4islo = to_string(prov);
                    }
                    if (posicia_bukva!="" and posicia_4islo!="" and figura!="")
                        for_random = true;
                }
            }
        }
        else            // рандом
        {
            while (!for_random)
            {
                prov = randomize(6);
                if(figuri[prov-1]>0)
                    figura = convert_for_fig(prov);
                prov = randomize(8);
                prov2 = randomize(8);
                if(matrix[8-prov][prov2-1] == "..")
                {
                    posicia_bukva = convert_for_pos(prov2-1);
                    posicia_4islo = to_string(prov);
                }
                if (posicia_bukva!="" and posicia_4islo!="" and figura!="")
                    for_random = true;
            }
        }

        for(int r = 0; r < int(matrix.size()); r += 1){
            for(int c = 0; c < int(matrix[r].size()); c += 1)
                cout<<dumai[r][c]<<" ";
            cout<<endl;
        }
        ofstream f("hod.txt");
        f <<figura<<posicia_bukva<<posicia_4islo;
        f.close();
    }
    return 0;
}
