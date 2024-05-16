#include<iostream>
#include"mylib.h"
#define MAX 100
using namespace std;
struct Point
{
	int x;
	int y;
};
int xcu, ycu;
Point Snake[MAX];
int Length = 3;
int Direction = 3;//1: qua trai, 2: len tren, 3: qua phai, 0: xuong duoi  
void draw_Wall();
void init_Snake();
void draw_Snake();
void move();
int check_Direction();
void init_fruit();
void draw_fruit();
void run();
void setting();// cai dat cau hinh

//ham xu li ran an qua to va nho
//ham kiem tra ran an qua to va nho
// ham kiem tra ran cham tuong
// ham kiem tra ran cham than
//ham kiem tra game over
