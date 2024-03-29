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

long checkPawn(const vector<vector<string>> &matrix, int posV, int posG, string WoD){
    long minas = 0;
    if(WoD == "W"){
        if(posV+1 < 8 and posG + 1 < 8 and matrix[posV+1][posG+1].substr(0,1) == WoD and matrix[posV+1][posG+1].substr(1,1)=="P") minas -= 1;
        if(posV+1 < 8 and posG - 1 >=0 and matrix[posV+1][posG-1].substr(0,1) == WoD and matrix[posV+1][posG-1].substr(1,1)=="P") minas -= 1;
    }
    else{
        if(posV-1 >=0 and posG + 1 < 8 and matrix[posV-1][posG+1].substr(0,1) == WoD and matrix[posV-1][posG+1].substr(1,1)=="P") minas -= 1;
        if(posV-1 >=0 and posG - 1 >=0 and matrix[posV-1][posG-1].substr(0,1) == WoD and matrix[posV-1][posG-1].substr(1,1)=="P") minas -= 1;
    }
    return minas;
}

long checkSlon(vector<vector<string>> matrix, int posV, int posG, string whiteOrDark){
    long lose = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (abs(i - posV) == abs(j - posG) and matrix[i][j].substr(0, 2) == whiteOrDark + "B" and (i != posV or j != posG)) lose -= 1;
        }
    }
    return lose;
}

long checkKnight(vector<vector<string>> matrix, int posV, int posG, string whiteOrDark){
    long lose = 0;
    if(posV + 1 < 8 and posG + 2 < 8 and matrix[posV + 1][posG + 2].substr(0, 2) == whiteOrDark + "N")   lose -= 1;
    if(posV - 1 >= 0 and posG + 2 < 8 and matrix[posV - 1][posG + 2].substr(0, 2) == whiteOrDark + "N")  lose -= 1;
    if(posV + 2 < 8 and posG + 1 < 8 and matrix[posV + 2][posG + 1].substr(0, 2) == whiteOrDark + "N")   lose -= 1;
    if(posV + 2 < 8 and posG - 1 >= 0 and matrix[posV + 2][posG - 1].substr(0, 2) == whiteOrDark + "N")  lose -= 1;
    if(posV - 1 >= 0 and posG - 2 >= 0 and matrix[posV - 1][posG - 2].substr(0, 2) == whiteOrDark + "N") lose -= 1;
    if(posV + 1 < 8 and posG - 2 >= 0 and matrix[posV + 1][posG - 2].substr(0, 2) == whiteOrDark + "N")  lose -= 1;
    if(posV - 2 >= 0 and posG - 1 >= 0 and matrix[posV - 2][posG - 1].substr(0, 2) == whiteOrDark + "N") lose -= 1;
    if(posV - 2 >= 0 and posG + 1 < 8  and matrix[posV - 2][posG + 1].substr(0, 2) == whiteOrDark + "N") lose -= 1;

    return lose;
}

long checkRook(vector<vector<string>> matrix, int posV, int posG, string whiteOrDark){
    long lose = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((posV == j or posG == i) and (posV != i or posG != j) and matrix[i][j].substr(0, 2) == whiteOrDark + "R") lose -= 1;
        }
    }
    return lose;
}

long checkKing(vector<vector<string>> matrix, int posV, int posG, string whiteOrDark){
    long lose = 0;
    if(posV -1 >=0 and posG-1 >=0 and matrix[posV-1][posG-1].substr(0,1) == whiteOrDark and matrix[posV-1][posG-1].substr(1,1) == "K") lose--;
    if(posV -1 >=0 and matrix[posV-1][posG].substr(0,1) == whiteOrDark and matrix[posV-1][posG].substr(1,1) == "K") lose--;
    if(posV -1 >=0 and posG+1 < 8 and matrix[posV-1][posG+1].substr(0,1) == whiteOrDark and matrix[posV-1][posG+1].substr(1,1) == "K") lose--;
    if(posG+1 <8 and matrix[posV][posG+1].substr(0,1) == whiteOrDark and matrix[posV][posG+1].substr(1,1) == "K") lose--;
    if(posV +1 <8 and posG+1 <8 and matrix[posV+1][posG+1].substr(0,1) == whiteOrDark and matrix[posV+1][posG+1].substr(1,1) == "K") lose--;
    if(posV +1 <8 and matrix[posV+1][posG].substr(0,1) == whiteOrDark and matrix[posV+1][posG].substr(1,1) == "K") lose--;
    if(posV +1 <8 and posG-1 >=0 and matrix[posV+1][posG-1].substr(0,1) == whiteOrDark and matrix[posV+1][posG-1].substr(1,1) == "K") lose--;
    if(posG-1>=0 and matrix[posV][posG-1].substr(0,1) == whiteOrDark and matrix[posV][posG-1].substr(1,1) == "K") lose--;
    return lose;
}

long checkFerz(vector<vector<string>> matrix, int posV, int posG, string whiteOrDark){
    long lose = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if((j==posG||i==posV||j-posG==i-posV||posG-j==posV-i||-(j-posG)==i-posV||-(posG-j)==posV-i) and (posV != i or posG != j) and matrix[i][j].substr(0, 2) == whiteOrDark + "Q") lose -= 1;
        }
    }
    return lose;
}

long potery(vector<vector<string>> matrix, int posV, int posG, long numb){
    string whiteOrDark;
    if(numb % 2 == 1) whiteOrDark = "W";
    else whiteOrDark = "D";
    long lose = 0;
    lose += checkPawn(matrix, posV, posG, whiteOrDark);
    lose += checkSlon(matrix, posV, posG, whiteOrDark);
    lose += checkKnight(matrix, posV, posG, whiteOrDark);
    lose += checkRook(matrix, posV, posG, whiteOrDark);
    lose += checkKing(matrix, posV, posG, whiteOrDark);
    lose += checkFerz(matrix, posV, posG, whiteOrDark);
    return lose;
}

long poluchPawn (const vector<vector<string>> &matrix, int posV, int posG, long numb){
    string WoD;
    if(numb%2 == 1) WoD = "W";
    else WoD = "D";
    long plas = 0;
    if(WoD == "W"){
        if(posV+1 < 8 and posG + 1 < 8 and matrix[posV+1][posG+1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV+1][posG+1].substr(1,1));
        if(posV+1 < 8 and posG - 1 >=0 and matrix[posV+1][posG-1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV+1][posG-1].substr(1,1));
    }
    else{
        if(posV-1 >=0 and posG + 1 < 8 and matrix[posV-1][posG+1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV-1][posG+1].substr(1,1));
        if(posV-1 >=0 and posG - 1 >=0 and matrix[posV-1][posG-1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV-1][posG-1].substr(1,1));
    }
    return plas;
}

long poluchBishop(const vector<vector<string>> &matrix, int posV, int posG, long numb){
    string WoD;
    int pr=posV,pc=posG;
    if(numb%2 == 1) WoD = "W";
    else WoD = "D";
    long plas = 0;
    while(pr<7 and pc<7)
    {
        pr++;
        pc++;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    pr=posV,pc=posG;
    while(pr<7 and pc>0)
    {
        pr++;
        pc--;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    pr=posV,pc=posG;
    while(pr>0 and pc>0)
    {
        pr--;
        pc--;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    pr=posV,pc=posG;
    while(pr>0 and pc<7)
    {
        pr--;
        pc++;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    return plas;
}

long poluchKnight (const vector<vector<string>> &matrix, int posV, int posG, long numb){
    string WoD;
    if(numb%2 == 1) WoD = "W";
    else WoD = "D";
    long plas = 0;
    if(posV-2 >=0 and posG -1 >=0 and matrix[posV-2][posG-1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV-2][posG-1].substr(1,1));
    if(posV-2 >=0 and posG +1 < 8 and matrix[posV-2][posG+1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV-2][posG+1].substr(1,1));
    if(posV-1 >=0 and posG -2 >=0 and matrix[posV-1][posG-2].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV-1][posG-2].substr(1,1));
    if(posV-1 >=0 and posG +2 < 8 and matrix[posV-1][posG+2].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV-1][posG+2].substr(1,1));
    if(posV+1 < 8 and posG -2 >=0 and matrix[posV+1][posG-2].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV+1][posG-2].substr(1,1));
    if(posV+1 < 8 and posG +2 < 8 and matrix[posV+1][posG+2].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV+1][posG+2].substr(1,1));
    if(posV+2 < 8 and posG -1 >=0 and matrix[posV+2][posG-1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV+2][posG-1].substr(1,1));
    if(posV+2 < 8 and posG +1 < 8 and matrix[posV+2][posG+1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV+2][posG+1].substr(1,1));
    return plas;
}

long poluchRook (const vector<vector<string>> &matrix, int posV, int posG, long numb){
    string WoD;
    if(numb%2 == 1) WoD = "W";
    else WoD = "D";
    long plas = 0;
    int pr=posV,pc=posG;
    while(pr>0)
    {
        pr--;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    pr=posV,pc=posG;
    while(pr<7)
    {
        pr++;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    pr=posV,pc=posG;
    while(pc>0)
    {
        pc--;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    pr=posV,pc=posG;
    while(pc<7)
    {
        pc++;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    return plas;
}

long poluchQueen (const vector<vector<string>> &matrix, int posV, int posG, long numb){
    string WoD;
    if(numb%2 == 1) WoD = "W";
    else WoD = "D";
    long plas = 0;
    int pr=posV,pc=posG;
    while(pr>0)
    {
        pr--;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    pr=posV,pc=posG;
    while(pr<7)
    {
        pr++;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    pr=posV,pc=posG;
    while(pc>0)
    {
        pc--;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    pr=posV,pc=posG;
    while(pc<7)
    {
        pc++;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }

    pr=posV, pc=posG;
    while(pr<7 and pc<7)
    {
        pr++;
        pc++;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    pr=posV,pc=posG;
    while(pr<7 and pc>0)
    {
        pr++;
        pc--;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    pr=posV,pc=posG;
    while(pr>0 and pc>0)
    {
        pr--;
        pc--;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    pr=posV,pc=posG;
    while(pr>0 and pc<7)
    {
        pr--;
        pc++;
        if(matrix[pr][pc].substr(0,1)==WoD){
            plas += stoimost_figuri(matrix[pr][pc].substr(1,1));
            break;
        }
        else break;
    }
    return plas;
}

long poluchKing (const vector<vector<string>> &matrix, int posV, int posG, long numb){
    string WoD;
    if(numb%2 == 1) WoD = "W";
    else WoD = "D";
    long plas = 0;
    if(posV+1 < 8 and posG + 1 < 8 and matrix[posV+1][posG+1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV+1][posG+1].substr(1,1));
    if(posV+1 < 8 and posG - 1 >=0 and matrix[posV+1][posG-1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV+1][posG-1].substr(1,1));
    if(posV-1 >=0 and posG + 1 < 8 and matrix[posV-1][posG+1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV-1][posG+1].substr(1,1));
    if(posV-1 >=0 and posG - 1 >=0 and matrix[posV-1][posG-1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV-1][posG-1].substr(1,1));

    if(posV+1 < 8 and matrix[posV+1][posG].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV+1][posG].substr(1,1));
    if(posV-1 >=0 and matrix[posV-1][posG].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV-1][posG].substr(1,1));

    if(posG + 1 < 8 and matrix[posV][posG+1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV][posG+1].substr(1,1));
    if(posG - 1 >=0 and matrix[posV][posG-1].substr(0,1) == WoD) plas += stoimost_figuri(matrix[posV][posG-1].substr(1,1));
    return plas;
}

long poluch(vector<vector<string>> matrix, int posV, int posG, long numb, long figg){
    long plas = 0;
    if(figg == 0) plas += poluchPawn(matrix, posV, posG, numb);
    if(figg == 1) plas += poluchBishop(matrix, posV, posG, numb);
    if(figg == 2) plas += poluchKnight(matrix, posV, posG, numb);
    if(figg == 3) plas += poluchRook(matrix, posV, posG, numb);
    if(figg == 4) plas += poluchQueen(matrix, posV, posG, numb);
    else plas += poluchKing(matrix, posV, posG, numb);

    return plas;
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
    }

    long m_vigoda = -11111111,vigoda,Row,Collumn,Figure;
    for(int r = 0;r<8;r++){
        for(int c = 0;c<8;c++){
            for(int i = 0; i<6;i++){
                if(figuri[i]!=0 and dumai[r][c]==".."){
                    vigoda = potery(dumai,r,c,numb)*stoimost_figuri(convert_for_fig(i+1));
                    vigoda += poluch(dumai,r,c,numb,i);
                    if(vigoda>m_vigoda){
                        m_vigoda = vigoda;
                        Row = r;
                        Collumn = c;
                        Figure = i;
                    }
                }
            }
        }
    }

    posicia_bukva = convert_for_pos(Collumn);
    posicia_4islo = to_string(8 - Row);
    figura = convert_for_fig(Figure + 1);


    ofstream file ("hod.txt");
    file << figura << posicia_bukva << posicia_4islo;
    file.close();
}
