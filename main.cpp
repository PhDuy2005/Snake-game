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
int Score = 0;
void draw_Wall();
void init_Snake();
void draw_Snake();
void move();
int check_Direction();
void init_fruit();
void draw_fruit();
void run();
void setting();// cai dat cau hinh
void display();

//ham xu li ran an qua to va nho
//ham kiem tra ran an qua to va nho
// ham kiem tra ran cham tuong
// ham kiem tra ran cham than
//ham kiem tra game over

int main()
{
	run();
	_getch();
	
}

int check_Direction()
{
    if (_kbhit())  
    {
        char x = _getch();  
        if (x == 0 || x == -32)
        {
            x = _getch(); 
            switch (x)
            {
                case 72:  
                    return 2;
                case 75:  
                    return 1;
                case 80:  
                    return 0;
                case 77:  
                    return 3;
                default:
                    return -1;  
            }
        }
        else
        {
            switch (x)
            {
                case 'w':
                    return 2;
                case 'a':
                    return 1;
                case 's':
                    return 0;
                case 'd':
                    return 3;
                default:
                    return -1;  
            }
        }
    }
    return -1; 
}

void move() {
    int newDirection = check_Direction();
    if (newDirection != -1 &&newDirection != (Direction^2) ) {
        Direction = newDirection;
    }

    xcu = Snake[Length - 1].x;
    ycu = Snake[Length - 1].y;

    for (int i = Length - 1; i > 0; --i) {
        Snake[i] = Snake[i - 1];
    }

    switch (Direction) {
        case 0:
            Snake[0].y++;
            break;
        case 1:
            Snake[0].x--;
            break;
        case 2:
            Snake[0].y--;
            break;
        case 3:
            Snake[0].x++;
            break;
    }

    gotoXY(xcu, ycu);
    cout << " ";
    draw_Snake();
    Sleep(100);
}
void init_Snake()
{
	Snake[0].x = 50; Snake[0].y = 10;
	Snake[1].x = 49; Snake[1].y = 10;
	Snake[2].x = 48; Snake[2].y = 10;
}
void draw_Snake()
{
	for(int i = 0; i<Length; i++)
	{
		gotoXY(Snake[i].x, Snake[i].y);
		if(i==0) cout<<'0';
		else cout<<'o';
	}
}
void draw_Wall()
{
    SetColor(11);
    int x = 10, y = 1;
    for(x = 10; x < 100; ++x)
    {
        gotoXY(x, y);
        cout << (char)205;
    }
    for(y = 1; y < 28; ++y)
    {
        gotoXY(x, y);
        cout << (char)186;
    }
    for(; x > 10; --x)
    {
        gotoXY(x, y);
        cout << (char)205;
    }
    for(; y > 1; --y)
    {
        gotoXY(x, y);
        cout << (char)186;
    }
    gotoXY(10, 1); cout << (char)201; 
    gotoXY(100, 1); cout << (char)187; 
    gotoXY(100, 28); cout << (char)188; 
    gotoXY(10, 28); cout << (char)200; 
}
void draw_Scoreboard()
{
    SetColor(11); 
    int x = 101, y = 1; 

    // V? khung b?ng di?m
    for(int i = 0; i < 28; ++i)
    {
        gotoXY(x, y + i);
        cout << (char)186; // Ðu?ng d?c
        gotoXY(x+17, y+i);
        cout<<(char)186;
    }
    for(int i = 0; i < 18; ++i)
    {
        gotoXY(x + i, y);
        cout << (char)205;
        gotoXY(x + i, y + 27);
        cout << (char)205; 
    }
    gotoXY(x, y); cout << (char)201; 
    gotoXY(x + 17, y); cout << (char)187; 
    gotoXY(x, y + 27); cout << (char)200; 
    gotoXY(x + 17, y + 27); cout << (char)188; 
    gotoXY(x + 2, y + 2);
    cout << "DIEM SO: 0";
    gotoXY(x + 2, y + 6);
    cout << "Len: W ";
    gotoXY(x + 2, y + 7);
    cout << "Xuong: S ";
    gotoXY(x + 2, y + 8);
    cout << "Trai: A ";
    gotoXY(x + 2, y + 9);
    cout << "Phai: D ";
    gotoXY(x+2, y+13);
    cout<<"Thoat: Enter";
    gotoXY(x+2, y+14);
    cout<<"Tam dung: Space"; 
}

void run()
{
	system("cls");
	//setting();
	ShowCur(0);//an con tro
	draw_Wall();
	init_Snake();
	draw_Snake();
	//init_fruit();
	//draw_fruit();
	draw_Scoreboard();
	while(1)
	{
		move();
	}
	
}
