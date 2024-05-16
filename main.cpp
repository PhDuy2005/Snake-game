#include<iostream>
#include"mylib.h"
#define MAX 100
using namespace std;
struct Point
{
	int x;
	int y;
};
//----------------------------------------------------------------
//Bien Toan Cuc
int xcu, ycu;
Point Snake[MAX];
int Length = 3;
int Level = 1;//muc de nhat (co 3 muc:1, 2, 3)
int Mode = 1;//1: classic, 2: morden
int SnakeColor = 2;//Green
int Direction = 3;//1: qua trai, 2: len tren, 3: qua phai, 0: xuong duoi  
int Score = 0;
//----------------------------------------------------------------
//Khai Bao Ham
void draw_Wall();//ve tuong
void init_Snake();//khoi tao ran
void draw_Snake();//ve ran
void move();//di chuyen ran 
int check_Direction();//kiem tra huong khi nhap phim
void init_fruit();//khoi tao qua
void draw_fruit();//ve qua
void run();//chay chuong trinh
void setting();// cai dat cau hinh
void draw_Scoreboard();//ve bang diem va huong dan
void draw_Menu();//ve khung menu
void setting_Level();//chinh do kho
void setting_Mode();//chinh che do
void setting_SnakeColor();//chinh mau ran

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
    if (_kbhit())//kiem tra nguoi dung co nhap phim khong nhung khong dung chuong trinh  
    {
        char x = _getch();//lay ki tu ra  
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
    SetColor(SnakeColor);
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
    for(int i = 0; i < 28; ++i)
    {
        gotoXY(x, y + i);
        cout << (char)186; 
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
void draw_Menu()
{
	SetColor(11);
		int x = 45, y = 10;
		for(x=45;x<70;++x)
		{
			gotoXY(x, y);
			cout<<(char)205;
		}
		for(y=10;y<21;++y)
		{
			gotoXY(x, y);
			cout<<(char)186;
		}
		for(x=70;x>45;--x)
		{
			gotoXY(x, y);
			cout<<(char)205;
		}
		for(y = 21;y>10;--y)
		{
			gotoXY(x, y);
			cout<<(char)186;
		}
		gotoXY(45, 10); cout<<(char)201;
		gotoXY(70, 10); cout<<(char)187;
		gotoXY(70, 21); cout<<(char)188;
		gotoXY(45, 21); cout<<(char)200;

}
void setting_Level()
{
	    SetColor(7);
	    gotoXY(57, 12);
	    cout<<"LEVEL";
	    gotoXY(50, 14);
	    cout<<"1: Easy";
	    gotoXY(50, 16);
	    cout<<"2: Normal";
	    gotoXY(50, 18);
	    cout<<"3: Difficult";
        draw_Menu();
		int temp = _getch();
		if(temp == '1') Level = 1;
		if(temp == '2') Level = 2;
		if(temp == '3') Level = 3;
		system("cls");
		setting();	
}
void setting_Mode()
{
	    SetColor(7);
	    gotoXY(57, 12);
	    cout<<"MODE";
	    gotoXY(50, 14);
	    cout<<"1: Classic";
	    gotoXY(50, 16);
	    cout<<"2: Modern";
        draw_Menu();
		int temp = _getch();
		if(temp == '1') Mode = 1;
		if(temp == '2') Mode = 2;
		system("cls");
		setting();	
}
void setting_SnakeColor()
{
	    SetColor(7);
	    gotoXY(57, 12);
	    cout<<"SNAKE COLOR";
	    gotoXY(50, 14);
	    cout<<"1: Green";//ma mau: 2
	    gotoXY(50, 16);
	    cout<<"2: Red";//ma mau: 4
	    gotoXY(50, 18);
	    cout<<"3: Yellow";//mau mau: 6
        draw_Menu();
		int temp = _getch();
		if(temp == '1') SnakeColor = 2;
		if(temp == '2') SnakeColor = 4;
		if(temp == '3') SnakeColor = 6;
		system("cls");
		setting();	
}
void setting()
{
	    SetColor(7);
	    gotoXY(57, 12);
	    cout<<"MENU";
	    gotoXY(50, 14);
	    cout<<"1: Play New Game";
	    gotoXY(50, 16);
	    cout<<"2: Setting";
        draw_Menu();	
		char temp = _getch();
		system("cls");
		if(temp == '1') return;
		if(temp == '2')
		{
			SetColor(7);
			gotoXY(57, 12);
	        cout<<"SETTING";
			gotoXY(50, 14);
	        cout<<"1: Choose level";
	        gotoXY(50, 16);
	        cout<<"2: Choose mode";
	        gotoXY(50, 18);
	        cout<<"3: Choose color";
			draw_Menu();
			temp = _getch();
			system("cls");
			if(temp == '1') setting_Level();
			if(temp == '2') setting_Mode();
			if(temp == '3') setting_SnakeColor();
		
		} 
		
}
void run()
{
	system("cls");
	setting();
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
