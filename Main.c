#include "Ball.h"
#include "Bird.h"
#include "Plane.h"
#include "Snake.h"

#define Height 25
void SetconsoleTexAttritbute(HANDLE hConsole, WORD attributes) 
{
    SetConsoleTextAttribute(hConsole, attributes);
}

void ShowSelectItem()
{
	SetConsoleTitle("姓名：谢祥志\n学号:2023214929\n");
	system("cls");

	gotoxy(Width / 3, Height / 3 - 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
	printf(" 姓名：谢祥志\t学号:2023214929\n*请选择你想玩耍的游戏* ");
	gotoxy(Width / 4, Height / 3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0B);
	printf("------------------------------");
	gotoxy(Width / 3, Height / 3 + 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
	printf("[1] Ball");
	gotoxy(Width / 3, Height / 3 + 3);
	printf("[2] Plane");
	gotoxy(Width / 3, Height / 3 + 4);
	printf("[3] Snake");
	gotoxy(Width / 3, Height / 3 + 5);
	printf("[4] Flappy bird");
	gotoxy(Width / 3, Height / 3 + 6);
	printf("[5] Exit");
	gotoxy(Width / 3, Height / 3 + 8);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0B);
	printf("------------------------------\n");
	gotoxy(Width / 3 - 1, Height / 3 + 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
	printf("Please select:");
	system("color 72");
}

int GetUserSelect()
{
	int n = 0;
	scanf("%d",&n);
	return n;
}

int UserSelectGame()
{
    int choice = 0;

    do {
        ShowSelectItem();
        choice = GetUserSelect();

        switch (choice) {
            case 1:
				Ball_main();
				break;
			case 2:
				Plane_main();
				break;
			case 3:
				Snake_main();
				break;
			case 4:
				Bird_main();
				break;
			case 5:
				return 0;
			default:
                break;
        }

        // ?????????????????????????????????
        if (choice != 5) {
            printf("\nPress any key to continue...");
            _getch(); // ??????????
        }
        
    } while (choice != 5);

    return 0;
}

int main()
{
    // ??????????????????????

    UserSelectGame();

    return 0;
}