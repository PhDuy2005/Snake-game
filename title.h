 #pragma once
#include "Mylib.h"
#include <iostream>
using namespace std;

class TitleDraw{
    void draw(int, int a[], int);
    friend void draw_title();
};

void TitleDraw::draw(int n, int a[], int color = 10){
    SetColor(color);
    int i = 0;
    while (n > 0) {
        if (i % 2 == 0){
            for (int j = 0; j < a[i]; j++){
                cout << " ";
            }
            i++;
        } else {
            for (int j = 0; j < a[i]; j++){
                cout << (char)176;
            }
            i++;
            n--;
        }
    }
}

void draw_title(){
    TitleDraw t;
    
    int x = 11, y = 0;

    gotoXY(x,y+2);
    int line2[6] = {3,6,35,1,2,3};
    t.draw(3, line2);

    gotoXY(x,y+3);
    int line3[112] = {2,2,4,2,15,3,16,1,2,1,1,1};
    t.draw(6, line3);

    gotoXY(x, y+4);
    int line4[31] = {2,2,22,2,2,2,2,4,6,1,2,1,1,1,4,5,1,5,1,3,1,1,1,5,1,5,1,1,5,5};
    t.draw(15, line4);

    gotoXY(x, y+5);
    int line5[34] = {3,6,2,2,1,3,3,5,1,2,1,2,2,2,2,2,15,1,5,5,1,1,1,1,1,1,1,1,5,5,1,1,5,1};
    t.draw(17, line5);

    gotoXY(x, y+6);
    int line6[40] = {8,2,1,3,2,2,1,2,3,1,2,2,4,5,4,5,1,1,1,1,3,1,5,5,1,1,1,1,1,1,1,5,1,5,1,1,5,5};
    t.draw(19, line6);

    gotoXY(x, y+7);
    int line7[44] = {2,2,4,2,1,2,3,2,1,2,2,1,2,2,1,2,2,2,7,1,1,1,1,1,1,3,3,1,5,5,1,1,1,1,1,1,5,1,1,5,1,1,5,1};
    t.draw(22, line7);

    gotoXY(x, y+8);
    int line8[40] = {3,6,2,2,3,2,2,3,1,1,1,2,2,2,2,5,3,1,1,1,1,1,2,1,4,5,1,5,1,1,1,3,1,5,1,5,1,5,1,5};
    t.draw(20, line8);
}

