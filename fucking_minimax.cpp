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

long checkSlon(vector<vector<string>> matrix, int posV, int posG, string whiteOrDark){
    long lose = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (abs(i - posV) == abs(j - posG) and matrix[i][j].substr(1, 1) == whiteOrDark + 'B' and (i != posV or j != posG)) lose -= 1;
        } 
    }
    return lose;
}

long checkKnight(vector<vector<string>> matrix, int posV, int posG, string whiteOrDark){
    long lose = 0;
    if(posV + 1 < 8 and posG + 2 < 8 and matrix[posV + 1][posG + 2].substr(1, 1) == whiteOrDark + 'N')   lose -= 1;
    if(posV - 1 >= 0 and posG + 2 < 8 and matrix[posV - 1][posG + 2].substr(1, 1) == whiteOrDark + 'N')  lose -= 1;
    if(posV + 2 < 8 and posG + 1 < 8 and matrix[posV + 2][posG + 1].substr(1, 1) == whiteOrDark + 'N')   lose -= 1;
    if(posV + 2 < 8 and posG - 1 >= 0 and matrix[posV + 2][posG - 1].substr(1, 1) == whiteOrDark + 'N')  lose -= 1;
    if(posV - 1 >= 0 and posG - 2 >= 0 and matrix[posV - 1][posG - 2].substr(1, 1) == whiteOrDark + 'N') lose -= 1;
    if(posV + 1 < 8 and posG - 2 >= 0 and matrix[posV + 1][posG - 2].substr(1, 1) == whiteOrDark + 'N')  lose -= 1;
    if(posV - 2 >= 0 and posG - 1 >= 0 and matrix[posV - 2][posG - 1].substr(1, 1) == whiteOrDark + 'N') lose -= 1;
    if(posV - 2 >= 0 and posG + 1 < 8  and matrix[posV - 2][posG + 1].substr(1, 1) == whiteOrDark + 'N') lose -= 1;
    
    return lose;
}

long checkRook(vector<vector<string>> matrix, int posV, int posG, string whiteOrDark){
    long lose = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((posV == j or posG == i) and (posV != i or posG != j) and matrix[i][j].substr(1, 1) == whiteOrDark + 'R') lose -= 1;
        }
    }
    return lose;
}

long checkKing(vector<vector<string>> matrix, int posV, int posG, string whiteOrDark){
    long lose = 0;
    if(posV + 1 < 8 and posG - 1 >= 0 and matrix[posV + 1][posG - 1].substr(1, 1) == whiteOrDark + 'K') lose -= 1;
    if(posV + 1 < 8 and matrix[posV + 1][posG].substr(1, 1) == 'K') lose -= 1;
    if(posV + 1 < 8 and posG + 1 < 8 and matrix[posV + 1][posG + 1].substr(1, 1) == whiteOrDark + 'K') lose -= 1;
    if(posG - 1 < 8 and matrix[posV][posG - 1].substr(1, 1) == whiteOrDark + 'K') lose -= 1;
    if(posG + 1 < 8 and matrix[posV][posG + 1].substr(1, 1) == whiteOrDark + 'K') lose -= 1;
    if(posV - 1 >= 0 and posG - 1 >= 0 and matrix[posV - 1][posG - 1].substr(1, 1) == whiteOrDark + 'K') lose -= 1;
    if(posV - 1 >= 0 and matrix[posV - 1][posG].substr(1, 1) == whiteOrDark + 'K') lose -= 1;
    if(posV - 1 >= 0 and posG + 1 < 8 and matrix[posV - 1][posG + 1].substr(1, 1) == whiteOrDark + 'K') lose -= 1;

    return lose;
}

long checkFerz(vector<vector<string>> matrix, int posV, int posG, string whiteOrDark){
    long lose = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if((j==posG||i==posV||j-posG==i-posV||posG-j==posV-i||-(j-posG)==i-posV||-(posG-j)==posV-i) and (posV != i or posG != j) and matrix[i][j].substr(1, 1) == whiteOrDark + 'Q') lose -= 1;
        }
    }
    return lose;
}

long potery(vector<vector<string>> matrix, int posV, int posG, long numb){
    string whiteOrDark;
    if(num % 2 == 1) whiteOrDark = "W";
    else whiteOrDark = "D";
    long lose = 0;
    if(posV + 1 < 8 and posG - 1 >= 0 and matrix[posV + 1][posG - 1].substr(1, 1) == whiteOrDark + 'P') lose -= 1; //пешка
    if(posV + 1 < 8 and posG + 1 < 8 and matrix[posV + 1][posG + 1].substr(1, 1) == whiteOrDark + 'P') lose -= 1; //пешка
    lose -= checkSlon(matrix, posV, posG);
    lose -= checkKnight(matrix, posV, posG);
    lose -= checkRock(matrix, posV, posG);
    lose -= checkKing(matrix, posV, posG);
    lose -= checkFerz(matrix, posV, posG);
}

long poluch(vector<vector<string>> matrix, int posV, int posG){
    
}


int main()
{
    srand(time(nullptr));
    bool for_random = false;
    string str,figura="",posicia_bukva="",posicia_4islo="",bar;
    int numb,pos,prov,prov2,color=0;
    vector<string> hodi;
    vector<int> figuri {8,2,2,2,1,1}; // 0 - пешка, 1 - конь, 2 - слон, 3 - ладья, 4 - ферзь, 5 - король
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
        }     

    long figuraWithMinPrice = -1;
    for(int i = 0; i < long(figuri.size()); i++){
        if(figuri[i] != 0) {
            figuraWithMinPrice = i;
            break;
        }
    } 

    int maximumPoluch = 0, maximumPoter = 0;

    for(int i = 0; i < 8; i++){         //сравнение потерь (potery) (т.е. получение очков противником) и получения очков нами (poluch)
        for(int j = 0; j < 8; j++){
            cout << potery(matrix, i, j) << endl;
        }
    }
}