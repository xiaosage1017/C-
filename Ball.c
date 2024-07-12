#include "Ball.h"

// ȫ�ֱ���
typedef struct {
    int x, y; // С�������
    int vx, vy; // С����ٶ�
} Ball;

typedef struct {
    int x, y; // ��ҵ�����
} Coin;

Ball balls[MAX_BALLS];
int ball_count = 0;

Coin coins[MAX_COINS];
int coin_count = 0;

int Ball_position_x, Ball_position_y; // ������������
int radius;  // ����뾶��С
int left, right; // ��������λ��
int Ball_canvas[High][Width] = {0}; // ��ά����洢��Ϸ�����ж�Ӧ��Ԫ��
int score = 0; // ��ҵ÷�

// 0Ϊ�ո�1ΪС��O��2Ϊ����*��3Ϊ����#��4Ϊ���$

void Ball_startup()  // ���ݳ�ʼ��
{
    radius = 5;
    Ball_position_x = High - 1;
    Ball_position_y = Width / 2;
    left = Ball_position_y - radius;
    right = Ball_position_y + radius;

    // ��ʼ��һ��С��
    balls[0].x = Ball_position_x - 1;
    balls[0].y = Ball_position_y;
    balls[0].vx = -1;
    balls[0].vy = 1;
    ball_count = 1;
    Ball_canvas[balls[0].x][balls[0].y] = 1;

    // ��ʼ�����
    srand(time(NULL));
    for (int i = 0; i < MAX_COINS; i++) {
        coins[i].x = rand() % (High / 2);
        coins[i].y = rand() % Width;
        Ball_canvas[coins[i].x][coins[i].y] = 4;
        coin_count++;
    }

    int k, i;
    for (k = left; k <= right; k++)  // ����
        Ball_canvas[Ball_position_x][k] = 2;

    for (k = 0; k < Width; k++)  // �Ӽ���ש��
        for (i = 0; i < High / 4; i++)
            Ball_canvas[i][k] = 3;
}

void Ball_show()  // ��ʾ����
{
    gotoxy(0, 0);    // ����ƶ���ԭ��λ�ã������ػ�����
    hidecursor();
    int i, j;
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (Ball_canvas[i][j] == 0)
                printf(" ");   //   ����ո�
            else if (Ball_canvas[i][j] == 1)
                printf("0");   //   ���С��0
            else if (Ball_canvas[i][j] == 2)
                printf("*");   //   �������*
            else if (Ball_canvas[i][j] == 3)
                printf("#");   //   ���ש��#
            else if (Ball_canvas[i][j] == 4)
                printf("$");   //   ������$
        }
        printf("|\n"); // ��ʾ�ұ߽�
    }
    for (j = 0; j < Width; j++)
        printf("-"); // ��ʾ�±߽�
    printf("\n");
    printf("Score: %d\n", score);
}

void Ball_updateWithoutInput()  // ���û������޹صĸ���
{
    for (int i = 0; i < ball_count; i++) {
        if (balls[i].x == High - 2) {
            if ((balls[i].y >= left) && (balls[i].y <= right)) {
                // �����嵲ס
            } else {
                // û�б����嵲ס
                printf("Game Over!\n");
                system("pause");
                exit(0);
            }
        }

        static int speed = 0;
        if (speed < 7)
            speed++;
        if (speed == 7) {
            speed = 0;

            Ball_canvas[balls[i].x][balls[i].y] = 0;
            // ����С������
            balls[i].x = balls[i].x + balls[i].vx;
            balls[i].y = balls[i].y + balls[i].vy;
            Ball_canvas[balls[i].x][balls[i].y] = 1;

            // �����߽�󷴵�
            if ((balls[i].x == 0) || (balls[i].x == High - 2))
                balls[i].vx = -balls[i].vx;
            if ((balls[i].y == 0) || (balls[i].y == Width - 1))
                balls[i].vy = -balls[i].vy;

            // ����ש��󷴵�
            if (Ball_canvas[balls[i].x - 1][balls[i].y] == 3) {
                balls[i].vx = -balls[i].vx;
                Ball_canvas[balls[i].x - 1][balls[i].y] = 0;
                printf("\a");
            }

            // ���С���Ƿ��ס�˽��
            for (int j = 0; j < coin_count; j++) {
                if (balls[i].x == coins[j].x && balls[i].y == coins[j].y) {
                    score++;
                    Ball_canvas[coins[j].x][coins[j].y] = 0;
                    coins[j].x = rand() % (High / 2);
                    coins[j].y = rand() % Width;
                    Ball_canvas[coins[j].x][coins[j].y] = 4;
                }
            }
        }
    }
}

void Ball_updateWithInput()  // ���û������йصĸ���
{
    char input;
    if (kbhit())  // �ж��Ƿ�������
    {
        input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
        if (input == 'a' && left > 0) {
            Ball_canvas[Ball_position_x][right] = 0;
            Ball_position_y--;  // λ������
            left = Ball_position_y - radius;
            right = Ball_position_y + radius;
            Ball_canvas[Ball_position_x][left] = 2;
        }
        if (input == 'd' && right < Width - 1) {
            Ball_canvas[Ball_position_x][left] = 0;
            Ball_position_y++;  // λ������
            left = Ball_position_y - radius;
            right = Ball_position_y + radius;
            Ball_canvas[Ball_position_x][right] = 2;
        }
        if (input == ' ' && ball_count < MAX_BALLS)  // ���¿ո�������µ�С��
        {
            if (Ball_canvas[Ball_position_x - 1][Ball_position_y] == 0)  // ȷ�������λ���ǿյ�
            {
                balls[ball_count].x = Ball_position_x - 1;
                balls[ball_count].y = Ball_position_y;
                balls[ball_count].vx = -1;
                balls[ball_count].vy = 1;
                Ball_canvas[balls[ball_count].x][balls[ball_count].y] = 1;
                ball_count++;
            }
        }
    }
}

int Ball_main()
{
    Ball_startup();  // ���ݳ�ʼ��
    while (1)  //  ��Ϸѭ��ִ��
    {
        Ball_show();  // ��ʾ����
        Ball_updateWithoutInput();  // ���û������޹صĸ���
        Ball_updateWithInput();     // ���û������йصĸ���
    }
    return 0;
}
