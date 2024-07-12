#include "Snake.h"

// ȫ�ֱ���
int moveDirection; // С���ƶ�λ�ã��������ҷֱ���1��2��3��4��ʾ
int food_x, food_y; // ʳ���λ��
int item_x, item_y; // ���ߵ�λ��
int item_type; // ���ߵ����ͣ�1��ʾ������2��ʾ����
int lives = 3; // ��ҵ�������
int Snake_speed = 100; // ��Ϸ�ٶ�
int Snake_canvas[High][Width] = {0}; // ��ά����洢��Ϸ�����ж�Ӧ��Ԫ��
	// 0Ϊ�ո�0��-1Ϊ�߿�#��-2Ϊʳ��F��1Ϊ��ͷ@������1������Ϊ����*
	// -3Ϊ��������L��-4Ϊ���ٵ���S

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

    if (moveDirection == 1) // �����ƶ�
    {
        newHead_i = oldHead_i - 1;
        newHead_j = oldHead_j;
    }
    if (moveDirection == 2) // �����ƶ�
    {
        newHead_i = oldHead_i + 1;
        newHead_j = oldHead_j;
    }
    if (moveDirection == 3) // �����ƶ�
    {
        newHead_i = oldHead_i;
        newHead_j = oldHead_j - 1;
    }
    if (moveDirection == 4) // �����ƶ�
    {
        newHead_i = oldHead_i;
        newHead_j = oldHead_j + 1;
    }

    // ����ͷ����Ե�ʳ��
    if (Snake_canvas[newHead_i][newHead_j] == -2)
    {
        Snake_canvas[food_x][food_y] = 0;
        // ����һ���µ�ʳ��
        food_x = rand() % (High - 5) + 2;
        food_y = rand() % (Width - 5) + 2;
        Snake_canvas[food_x][food_y] = -2;

        // ԭ���ľ���β���ţ������Զ�+1
    }
    else if (Snake_canvas[newHead_i][newHead_j] == -3) // �Ե���������
    {
        Snake_canvas[item_x][item_y] = 0;
        lives++;
        // ����һ���µĵ���
        item_x = rand() % (High - 5) + 2;
        item_y = rand() % (Width - 5) + 2;
        item_type = rand() % 2 + 1;
        Snake_canvas[item_x][item_y] = -3 - (item_type - 1);
    }
    else if (Snake_canvas[newHead_i][newHead_j] == -4) // �Ե����ٵ���
    {
        Snake_canvas[item_x][item_y] = 0;
        Snake_speed += 50;
        // ����һ���µĵ���
        item_x = rand() % (High - 5) + 2;
        item_y = rand() % (Width - 5) + 2;
        item_type = rand() % 2 + 1;
        Snake_canvas[item_x][item_y] = -3 - (item_type - 1);
    }
    else // ����ԭ���ľ���β���������ֳ��Ȳ���
        Snake_canvas[oldTail_i][oldTail_j] = 0;

    // �Ƿ�С�ߺ�����ײ�����ߺͱ߿�ײ����Ϸʧ��
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
void Snake_startup() // ���ݳ�ʼ��
{
    int i, j;

    // ��ʼ���߿�
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

    // ��ʼ����ͷλ��
    Snake_canvas[High / 2][Width / 2] = 1;
    // ��ʼ������������Ԫ��ֵ�ֱ�Ϊ2,3,4,5....
    for (i = 1; i <= 4; i++)
        Snake_canvas[High / 2][Width / 2 - i] = i + 1;

    // ��ʼС�������ƶ�
    moveDirection = 4;

    food_x = rand() % (High - 5) + 2;
    food_y = rand() % (Width - 5) + 2;
    Snake_canvas[food_x][food_y] = -2;

    // ��ʼ������
    item_x = rand() % (High - 5) + 2;
    item_y = rand() % (Width - 5) + 2;
    item_type = rand() % 2 + 1;
    Snake_canvas[item_x][item_y] = -3 - (item_type - 1);
}

void Snake_show()  // ��ʾ����
{
    hidecursor();
    gotoxy(0, 0);  // ����ƶ���ԭ��λ�ã������ػ�����
    int i, j;
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (Snake_canvas[i][j] == 0)
                printf(" ");   //   ����ո�
            else if (Snake_canvas[i][j] == -1)
                printf("#");   //   ����߿�#
            else if (Snake_canvas[i][j] == 1)
                printf("@");   //   �����ͷ@
            else if (Snake_canvas[i][j] > 1)
                printf("*");   //   �������*
            else if (Snake_canvas[i][j] == -2)
                printf("F");   //   ���ʳ��F
            else if (Snake_canvas[i][j] == -3)
                printf("L");   //   �����������L
            else if (Snake_canvas[i][j] == -4)
                printf("S");   //   ������ٵ���S
        }
        printf("\n");
    }
    printf("Lives: %d\n", lives);
    Sleep(Snake_speed);
}

void Snake_updateWithoutInput()  // ���û������޹صĸ���
{
    moveSnakeByDirection();
}


void Snake_updateWithInput()  // ���û������йصĸ���
{
    char input;
    if (kbhit())  // �ж��Ƿ�������
    {
        input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
        if (input == 'a')
        {
            moveDirection = 3;   // λ������
            moveSnakeByDirection();
        }
        else if (input == 'd')
        {
            moveDirection = 4;  // λ������
            moveSnakeByDirection();
        }
        else if (input == 'w')
        {
            moveDirection = 1;  // λ������
            moveSnakeByDirection();
        }
        else if (input == 's')
        {
            moveDirection = 2;   // λ������
            moveSnakeByDirection();
        }
    }
}

int Snake_main()
{
    Snake_startup();  // ���ݳ�ʼ��
    while (1) //  ��Ϸѭ��ִ��
    {
        Snake_show();  // ��ʾ����
        Snake_updateWithoutInput();  // ���û������޹صĸ���
        Snake_updateWithInput();  // ���û������йصĸ���
    }
    return 0;
}

