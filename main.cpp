#include<iostream>
#include"mylib.h"
#include"title.h"
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
Point fruit;
bool fruitIsOnField = false;
int fruitsEaten = 0;
int fruitType = 1;// 1: nho, 2: lon
int Length = 3;
int Level = 1;//muc de nhat (co 3 muc:1, 2, 3)
int Mode = 1;//1: classic, 2: morden
int SnakeColor = 2;//Green
int Direction = 3;//1: qua trai, 2: len tren, 3: qua phai, 0: xuong duoi  
bool GameOver = false;
int Score = 0;
//----------------------------------------------------------------
//Khai Bao Ham
void draw_Wall();//ve tuong
void init_Snake();//khoi tao ran
void draw_Snake();//ve ran
void delete_snake();//Xoa cac dot ran sau moi lan restart game
void move();//di chuyen ran 
void action_while_moving(); //Chay cac ham khac trong khi ran dang di chuyen
int check_Direction();//kiem tra huong khi nhap phim
void init_fruit();//khoi tao qua
void draw_fruit();//ve qua
void eat_fruit();//an qua
void collide_wall();// ham kiem tra ran cham tuong
void collide_self();// ham kiem tra ran cham than
void start();//Khoi tao cac gia tri khi bat dau
void run();//chay chuong trinh
void gameover();//Man hinh ket thuc tro choi
void setting();// cai dat cau hinh
void draw_Scoreboard();//ve bang diem va huong dan
void draw_Menu();//ve khung menu
void setting_Level();//chinh do kho
void setting_Mode();//chinh che do
void setting_SnakeColor();//chinh mau ran
void pause(); //tam dung game
void game_control(); //Dieu khien tro choi (Pause, Quit)


//ham kiem tra game over

int main()
{
    start();
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

                case 27:
                    pause();
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
    
    action_while_moving();
    
    gotoXY(xcu, ycu);
    cout << " ";

    

    if(Level ==1) Sleep(400);
    if(Level ==2) Sleep(200);
    if(Level ==3) Sleep(80);
}

void action_while_moving(){
    eat_fruit();
    collide_wall();
    collide_self();
    draw_Snake();
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

void delete_snake(){
    for (int i = 3; i < MAX; i++)
    Snake[i].x = Snake[i].y = -1;
    return;
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


void init_fruit()
{
    if (!fruitIsOnField){
        bool validPosition;
        do {
            validPosition = true;
            fruit.x = rand() % (100 - 11) + 11; //11<=x<=99
            fruit.y = rand() % (28 - 2) + 2; //2<=x<=27  

            if (fruitsEaten % 4 == 0 && fruitsEaten != 0){
                fruitType = 2;
            } else {
                fruitType = 1;
            }

            for (int i = 0; i < Length; ++i)//kiem tra thuc an co trung voi than ran khong
			{
                if (Snake[i].x == fruit.x && Snake[i].y == fruit.y){
                    validPosition = false;
                    break;
                }
            }
        } while (!validPosition);

        draw_fruit();
        fruitIsOnField = true;
    }
}

void draw_fruit()
{
    SetColor(4);
    gotoXY(fruit.x, fruit.y);
    if (fruitType == 2){
        cout << "0";
    } else {
        cout << "o";
    }
    SetColor(11);
}

void eat_fruit()
{
    if (Snake[0].x == fruit.x && Snake[0].y == fruit.y)
    {
        Length++;
        fruitsEaten++;
        
        fruitIsOnField = false;

        //Update scoreboard
        if (fruitType == 2){
            Score += 25;
        } else {
            Score += 5;
        }
        draw_Scoreboard();

        // Generate new fruit
        init_fruit();
    }
}

void collide_wall()
{
    if (Mode == 2){
        if (Snake[0].x < 11 || Snake[0].x > 99 || Snake[0].y < 2 || Snake[0].y > 27){
            GameOver = true;
        }
    }
    else if (Mode == 1){
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
}

void collide_self()
{
    for (int i = 1; i < Length; ++i){
        if (Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y){
            GameOver = true;
        }
    }
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
    cout << "DIEM SO: " << Score;
    gotoXY(x + 2, y + 6);
    cout << "Len: W ";
    gotoXY(x + 2, y + 7);
    cout << "Xuong: S ";
    gotoXY(x + 2, y + 8);
    cout << "Trai: A ";
    gotoXY(x + 2, y + 9);
    cout << "Phai: D ";
    gotoXY(x+2, y+13);
    cout<<"Tam dung: Esc";
}
void draw_Menu()
{
    draw_title(); //Duoc khai bao trong file title.h 
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
		char temp = _getch(); //change data type from int to char
        while (temp != '1' && temp != '2' && temp != '3')
            temp = _getch();

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
		char temp = _getch(); //change data type from int to char
        while (temp != '1' && temp != '2' && temp != '3')
            temp = _getch();

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
		char temp = _getch(); //change data type from int to char
        while (temp != '1' && temp != '2' && temp != '3')
            temp = _getch();

		if(temp == '1') SnakeColor = 2;
		if(temp == '2') SnakeColor = 4;
		if(temp == '3') SnakeColor = 6;
		system("cls");

		setting();	
}
void setting()
{
        system("cls");
	    SetColor(7);
	    gotoXY(57, 12);
	    cout<<"MENU";
	    gotoXY(50, 14);
	    cout<<"1: Play New Game";
	    gotoXY(50, 16);
	    cout<<"2: Setting";
        gotoXY(50, 18);
	    cout<<"3: Quit";
        draw_Menu();	
		char temp = _getch();
        while (temp != '1' && temp != '2' && temp != '3')
            temp = _getch();

		system("cls");
		if(temp == '1') run();
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
			
            //code de fix tam cho issue #2 ////////////////////
            while (temp != '1' && temp != '2' && temp != '3'){
                temp = _getch();
            }
            ///////////////////////////////////////////////////

            system("cls");
            if(temp == '1') setting_Level();
			if(temp == '2') setting_Mode();
			if(temp == '3') setting_SnakeColor();
		
		}
        if(temp == '3') exit(0);
		
        //setting(); //Dong nay de fix tam thoi cho issue #2
}

void start()
{
    
    GameOver = false;
    fruitsEaten = 0;
    Score = 0;
    fruitIsOnField = false;
    Length = 3;
    Direction = 3;
    delete_snake();
    init_Snake();
    init_fruit();
    setting();
}

void run()
{
    GameOver = false;
	system("cls");
	ShowCur(0);//an con tro
    //Do cac ham init da call trong start() roi nen ko can call nua
	draw_Wall();
	draw_Snake();
    draw_fruit();
	draw_Scoreboard();
	while(1&&!GameOver)
	{
		move();
	}
    gameover();
}

void pause() {
    while (true) {
        system("cls");
        SetColor(7);
        gotoXY(57, 12);
        cout << "PAUSED";
        gotoXY(50, 14);
        cout << "1: Resume";
        gotoXY(50, 16);
        cout << "2: Return to menu";
        draw_Menu();
        
        char temp = _getch();
        if (temp == '1') {
            system("cls");

            //Dua game ve trang thai bang dau
            draw_Snake();
            draw_fruit();
            draw_Scoreboard();
            draw_Wall();

            return;
        }
        if (temp == '2') {
            // GameOver = true;
            system("cls");
            start();
            return;
        }
    }
}

void gameover() {
    system("cls");
    draw_Menu();
    SetColor(7);
    gotoXY(50, 12);
    cout << "GAME OVER";
    gotoXY(48, 14);
    cout << "1: Return to menu";
    gotoXY(48, 16);
    cout << "2: Quit";


    while (true) {
        char temp = _getch();
        switch (temp) {
            case '1':
                system("cls");
                start();
            case '2':
                exit(0);
        }
    }
}
