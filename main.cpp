#include<iostream>
#include"mylib.h"
#define MAX 100
using namespace std;

enum FruitType { BIG, SMALL };
enum GameMode { CLASSIC, MODERN };

struct Point
{
	int x;
	int y;
};

struct Fruit
{
    Point pos;

    FruitType type = SMALL;
    bool isOnField = false;
    int numberEaten = 0;
};

int xcu, ycu;
Point Snake[MAX];
int Length = 3;
int Direction = 3;//1: qua trai, 2: len tren, 3: qua phai, 0: xuong duoi  
Fruit fruit;
int Score = 0;
bool isGameRunning = true;
GameMode gameMode = MODERN;
void draw_Wall();
void init_Snake();
void draw_Snake();
void move();
int check_Direction();
void init_fruit();
void draw_fruit();
void start();// Man hinh khi bat dau game
void start_menu_behavior(int, bool);
void run();
void setting();// cai dat cau hinh
void display();

//ham xu li ran an qua to va nho
void eat_fruit();
//ham kiem tra ran an qua to va nho
// ham kiem tra ran cham tuong
bool collide_wall();
// ham kiem tra ran cham than
bool collide_self();
//ham kiem tra game over

int main()
{
    start();
	//run();
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
    //Sleep(100); // Ham Sleep() da duoc dem vao run()
}
void init_Snake()
{
	Snake[0].x = 50; Snake[0].y = 10;
	Snake[1].x = 49; Snake[1].y = 10;
	Snake[2].x = 48; Snake[2].y = 10;
}
void draw_Snake()
{
    if (Snake[0].x > 10 && Snake[0].x < 100 && Snake[0].y > 1 && Snake[0].y < 28)
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
        cout << (char)186; // �u?ng d?c
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

void init_fruit()
{
    if (!fruit.isOnField){
        bool validPosition;
        do {
            validPosition = true;
            fruit.pos.x = rand() % (100 - 11) + 11; 
            fruit.pos.y = rand() % (28 - 2) + 2;   

            if (fruit.numberEaten % 4 == 0 && fruit.numberEaten != 0){
                fruit.type = BIG;
            } else {
                fruit.type = SMALL;
            }

            for (int i = 0; i < Length; ++i){
                if (Snake[i].x == fruit.pos.x && Snake[i].y == fruit.pos.y){
                    validPosition = false;
                    break;
                }
            }
        } while (!validPosition);

        draw_fruit();
        fruit.isOnField = true;
    }
}

void draw_fruit()
{
    SetColor(4);
    gotoXY(fruit.pos.x, fruit.pos.y);
    if (fruit.type == BIG){
        cout << "O";
    } else {
        cout << "o";
    }
    SetColor(11);
}

void eat_fruit()
{
    if (Snake[0].x == fruit.pos.x && Snake[0].y == fruit.pos.y)
    {
        Length++;
        fruit.numberEaten++;
        fruit.isOnField = false;  // Mark the fruit as eaten

        //Update scoreboard

        // Generate new fruit
        init_fruit();
    }
}

bool collide_wall()
{
    if (gameMode == CLASSIC){
        if (Snake[0].x < 11 || Snake[0].x > 99 || Snake[0].y < 2 || Snake[0].y > 27){
            return true;
        }
    }
    else if (gameMode == MODERN){
        if (Snake[0].x < 11){
            Snake[0].x = 99;
        }
        else if (Snake[0].x > 99){
            Snake[0].x = 11;}

        if (Snake[0].y < 2){
            Snake[0].y = 27;
        }
        else if (Snake[0].y > 27){
            Snake[0].y = 2;
        }
    }
    return false;
}

bool collide_self()
{
    for (int i = 1; i < Length; ++i){
        if (Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y){
            return true;
        }
    }
    return false;
}

void run()
{
	system("cls");
	//setting();
	ShowCur(0);//an con tro
	draw_Wall();
	init_Snake();
	draw_Snake();
	init_fruit();
	//draw_fruit(); Da su dung trong init_fruit()
	draw_Scoreboard();

    //Game Loop
	while(isGameRunning)
	{
        //Kiem tra an moi
        if (Snake[0].x == fruit.pos.x && Snake[0].y == fruit.pos.y){
            eat_fruit();
        }

        //Kiem tra va cham
        if (collide_wall() || collide_self()){
            isGameRunning = false;
        }
        
        move();

        Sleep(100);
	}
}

void start(){
    system("cls");
    ShowCur(0);
    draw_Wall();
    SetColor(4);
    int x = 37, y = 5;
    int cursor = 0;
    gotoXY(x, y);
    cout << "WHY IS THERE A SNAKE IN MY CONSOLE!?";
    start_menu_behavior(cursor, false);
    
    
    while(true){
        if(kbhit()){
            char x = getch();
            switch(x){
                case 'W':
                case 'w':
                case 72 : //Up arrow
                    cursor--;
                    break;
                case 'S':
                case 's':
                case 80 : //Down arrow
                    cursor++;
                    break;
                case 32 : //Spacebar
                case 'x':
                case 'X':
                    start_menu_behavior(cursor, true);
                    return;
                }
            if (cursor > 3) {cursor = 3;}
            if (cursor < 0) {cursor = 0;}
            start_menu_behavior(cursor, false);
        }
    }

    getch();
    run();
}
void start_menu_behavior(int _cursor, bool isSelected){
    int cursor = _cursor; //Con tro de nguoi dung chon cac muc trong menu
    SetColor(11);
    int x = 43, y = 12; 
    gotoXY(x, y);

    if (cursor == 0)
        SetColor(4);
    cout << "CLASSIC";
    SetColor(11);
    y += 4; gotoXY(x, y);
    if (cursor == 1)
        SetColor(4);
    cout << "MODERN";
    SetColor(11);
    y += 4; gotoXY(x, y);
    if (cursor == 2)
        SetColor(4);
    cout << "SETTING";
    SetColor(11);
    y += 4; gotoXY(x, y);
    if (cursor == 3)
        SetColor(4);
    cout << "QUIT";
    SetColor(11);

    if (isSelected){
        switch (cursor){
            case 0:
                gameMode = CLASSIC;
                run();
                break;
            case 1:
                gameMode = MODERN;
                run();
                break;
            case 3:
                exit(0);
        }
    }
}