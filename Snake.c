#include "Snake.h"

// 全局变量
int moveDirection; // 小蛇移动位置，上下左右分别用1，2，3，4表示
int food_x, food_y; // 食物的位置
int item_x, item_y; // 道具的位置
int item_type; // 道具的类型，1表示加命，2表示减速
int lives = 3; // 玩家的生命数
int Snake_speed = 100; // 游戏速度
int Snake_canvas[High][Width] = {0}; // 二维数组存储游戏画布中对应的元素
	// 0为空格0，-1为边框#，-2为食物F，1为蛇头@，大于1的正数为蛇身*
	// -3为加命道具L，-4为减速道具S

void moveSnakeByDirection()
{
    int i, j;
    for (i = 1; i < High - 1; i++)
        for (j = 1; j < Width - 1; j++)
            if (Snake_canvas[i][j] > 0)
                Snake_canvas[i][j]++;

    int oldTail_i, oldTail_j, oldHead_i, oldHead_j;
    int max = 0;

    for (i = 1; i < High - 1; i++)
        for (j = 1; j < Width - 1; j++)
            if (Snake_canvas[i][j] > 0)
            {
                if (max < Snake_canvas[i][j])
                {
                    max = Snake_canvas[i][j];
                    oldTail_i = i;
                    oldTail_j = j;
                }
                if (Snake_canvas[i][j] == 2)
                {
                    oldHead_i = i;
                    oldHead_j = j;
                }
            }

    int newHead_i, newHead_j;

    if (moveDirection == 1) // 向上移动
    {
        newHead_i = oldHead_i - 1;
        newHead_j = oldHead_j;
    }
    if (moveDirection == 2) // 向下移动
    {
        newHead_i = oldHead_i + 1;
        newHead_j = oldHead_j;
    }
    if (moveDirection == 3) // 向左移动
    {
        newHead_i = oldHead_i;
        newHead_j = oldHead_j - 1;
    }
    if (moveDirection == 4) // 向右移动
    {
        newHead_i = oldHead_i;
        newHead_j = oldHead_j + 1;
    }

    // 新蛇头如果吃到食物
    if (Snake_canvas[newHead_i][newHead_j] == -2)
    {
        Snake_canvas[food_x][food_y] = 0;
        // 产生一个新的食物
        food_x = rand() % (High - 5) + 2;
        food_y = rand() % (Width - 5) + 2;
        Snake_canvas[food_x][food_y] = -2;

        // 原来的旧蛇尾留着，长度自动+1
    }
    else if (Snake_canvas[newHead_i][newHead_j] == -3) // 吃到加命道具
    {
        Snake_canvas[item_x][item_y] = 0;
        lives++;
        // 产生一个新的道具
        item_x = rand() % (High - 5) + 2;
        item_y = rand() % (Width - 5) + 2;
        item_type = rand() % 2 + 1;
        Snake_canvas[item_x][item_y] = -3 - (item_type - 1);
    }
    else if (Snake_canvas[newHead_i][newHead_j] == -4) // 吃到减速道具
    {
        Snake_canvas[item_x][item_y] = 0;
        Snake_speed += 50;
        // 产生一个新的道具
        item_x = rand() % (High - 5) + 2;
        item_y = rand() % (Width - 5) + 2;
        item_type = rand() % 2 + 1;
        Snake_canvas[item_x][item_y] = -3 - (item_type - 1);
    }
    else // 否则，原来的旧蛇尾减掉，保持长度不变
        Snake_canvas[oldTail_i][oldTail_j] = 0;

    // 是否小蛇和自身撞，或者和边框撞，游戏失败
    if (Snake_canvas[newHead_i][newHead_j] > 0 || Snake_canvas[newHead_i][newHead_j] == -1)
    {
        printf("Game over!\n");
        Sleep(2000);
        system("pause");
        exit(0);
    }
    else
        Snake_canvas[newHead_i][newHead_j] = 1;
}
void Snake_startup() // 数据初始化
{
    int i, j;

    // 初始化边框
    for (i = 0; i < High; i++)
    {
        Snake_canvas[i][0] = -1;
        Snake_canvas[i][Width - 1] = -1;
    }
    for (j = 0; j < Width; j++)
    {
        Snake_canvas[0][j] = -1;
        Snake_canvas[High - 1][j] = -1;
    }

    // 初始化蛇头位置
    Snake_canvas[High / 2][Width / 2] = 1;
    // 初始化蛇身，画布中元素值分别为2,3,4,5....
    for (i = 1; i <= 4; i++)
        Snake_canvas[High / 2][Width / 2 - i] = i + 1;

    // 初始小蛇向右移动
    moveDirection = 4;

    food_x = rand() % (High - 5) + 2;
    food_y = rand() % (Width - 5) + 2;
    Snake_canvas[food_x][food_y] = -2;

    // 初始化道具
    item_x = rand() % (High - 5) + 2;
    item_y = rand() % (Width - 5) + 2;
    item_type = rand() % 2 + 1;
    Snake_canvas[item_x][item_y] = -3 - (item_type - 1);
}

void Snake_show()  // 显示画面
{
    hidecursor();
    gotoxy(0, 0);  // 光标移动到原点位置，以下重画清屏
    int i, j;
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (Snake_canvas[i][j] == 0)
                printf(" ");   //   输出空格
            else if (Snake_canvas[i][j] == -1)
                printf("#");   //   输出边框#
            else if (Snake_canvas[i][j] == 1)
                printf("@");   //   输出蛇头@
            else if (Snake_canvas[i][j] > 1)
                printf("*");   //   输出蛇身*
            else if (Snake_canvas[i][j] == -2)
                printf("F");   //   输出食物F
            else if (Snake_canvas[i][j] == -3)
                printf("L");   //   输出加命道具L
            else if (Snake_canvas[i][j] == -4)
                printf("S");   //   输出减速道具S
        }
        printf("\n");
    }
    printf("Lives: %d\n", lives);
    Sleep(Snake_speed);
}

void Snake_updateWithoutInput()  // 与用户输入无关的更新
{
    moveSnakeByDirection();
}


void Snake_updateWithInput()  // 与用户输入有关的更新
{
    char input;
    if (kbhit())  // 判断是否有输入
    {
        input = getch();  // 根据用户的不同输入来移动，不必输入回车
        if (input == 'a')
        {
            moveDirection = 3;   // 位置左移
            moveSnakeByDirection();
        }
        else if (input == 'd')
        {
            moveDirection = 4;  // 位置右移
            moveSnakeByDirection();
        }
        else if (input == 'w')
        {
            moveDirection = 1;  // 位置上移
            moveSnakeByDirection();
        }
        else if (input == 's')
        {
            moveDirection = 2;   // 位置下移
            moveSnakeByDirection();
        }
    }
}

int Snake_main()
{
    Snake_startup();  // 数据初始化
    while (1) //  游戏循环执行
    {
        Snake_show();  // 显示画面
        Snake_updateWithoutInput();  // 与用户输入无关的更新
        Snake_updateWithInput();  // 与用户输入有关的更新
    }
    return 0;
}

