#include<stdio.h>
#include<stdbool.h>
#include<windows.h>
#include<conio.h>
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	setcolor(2, 4);
	gotoxy(x, y);
	printf(" <-0-> ");
}
void erase_ship(int x, int y) {
	setcolor(2, 0);
	gotoxy(x, y);
	printf("       ");
}
void erase_bullet(int x, int y) {
	setcolor(2, 0);
	gotoxy(x, y);
	printf(" ");
}
void draw_bullet(int x, int y)
{
	setcolor(2, 0);
	gotoxy(x,y);
	printf("0");
}
int main()
{
	setcursor(0);
	char ch = '.';
	int x = 38, y = 20, direction = 0,i=0;
	int Bx[5] = { 38,38,38,38,38 }, By[5] = { 20,20,20,20,20 };
	bool checkBullet[6] = { false,false,false,false,false,false };
	int numBullet = 0;
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') {
				direction = -1;
			}
			if (ch == 'd') {
				direction = 1;
			}
			if (ch == 's') {
				direction = 0;
			}
			if (ch == ' ' && !checkBullet[numBullet]) {
				checkBullet[numBullet] = true;
				Bx[numBullet] = x + 3;
				By[numBullet] = y - 1;
				numBullet++;
				numBullet = (numBullet + 1) % 5;
			}
		}
		Sleep(100);
		if (direction != 0) {
			if (direction == 1 && x < 73) {
				erase_ship(x, y);
				draw_ship(++x, y);
			}
			else if (direction == -1 && x > 0) {
				erase_ship(x, y);
				draw_ship(--x, y);
			}
			else {
				direction = 0;
			}
		}
		for (i = 0; i < 5; i++){
			if (checkBullet[i]){
				erase_bullet(Bx[i], By[i]);
				if (By[i] > 0){
					draw_bullet(Bx[i], --By[i]);
				}
				else{
					checkBullet[i] = false;
				}
			}
		}
	} while (ch != 'x');
	return 0;
}