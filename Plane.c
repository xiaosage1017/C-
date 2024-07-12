#include "Plane.h"

// ȫ�ֱ���
int Plane_position_x, Plane_position_y; // �ɻ�λ��
int enemy_x[EnemyNum], enemy_y[EnemyNum];  // �л�λ��
int enemy_bullet_x[EnemyNum], enemy_bullet_y[EnemyNum];  // �л��ӵ�λ��
int Plane_canvas[High][Width] = {0}; // ��ά����洢��Ϸ�����ж�Ӧ��Ԫ��
                        // 0Ϊ�ո�1Ϊ�ɻ�*��2Ϊ�ӵ�|��3Ϊ�л�@��4Ϊboss�л�#
int Plane_score; // �÷�
int BulletWidth; // �ӵ�����
int EnemyMoveSpeed; // �л��ƶ��ٶ�

void Plane_startup() // ���ݳ�ʼ��
{
    Plane_position_x = High - 1;
    Plane_position_y = Width / 2;
    Plane_canvas[Plane_position_x][Plane_position_y] = 1;
    int k;
    for (k = 0; k < EnemyNum; k++)
    {
        enemy_x[k] = rand() % 2;
        enemy_y[k] = rand() % Width;
        Plane_canvas[enemy_x[k]][enemy_y[k]] = 3;
        enemy_bullet_x[k] = -1; // ��ʼ���л��ӵ�λ��
        enemy_bullet_y[k] = -1;
    }
    Plane_score = 0;
    BulletWidth = 0;
    EnemyMoveSpeed = 20;
}

void Plane_show()  // ��ʾ����
{
    gotoxy(0, 0);  // ����ƶ���ԭ��λ�ã������ػ�����
	hidecursor();
    int i, j;
    // ���ƶ����߿�
    for (j = 0; j < Width + 2; j++)
        printf("-");
    printf("\n");
    for (i = 0; i < High; i++)
    {
        // �������߿�
        printf("|");
        for (j = 0; j < Width; j++)
        {
            if (Plane_canvas[i][j] == 0)
                printf(" ");   //   ����ո�
            else if (Plane_canvas[i][j] == 1)
                printf("*");   //   ����ɻ�*
            else if (Plane_canvas[i][j] == 2)
                printf("|");   //   ����ӵ�|
            else if (Plane_canvas[i][j] == 3)
                printf("@");   //  ����л�@
            else if (Plane_canvas[i][j] == 4)
                printf("#");   //  ���boss�л�#
            else if (Plane_canvas[i][j] == 5)
                printf("!");   //  ����л��ӵ�!
        }
        // �����Ҳ�߿�
        printf("|");
        printf("\n");
    }
    // ���Ƶײ��߿�
    for (j = 0; j < Width + 2; j++)
        printf("-");
    printf("\n");
    printf("score:%d\n", Plane_score);
    Sleep(20);
}

void Plane_updateWithoutInput()  // ���û������޹صĸ���
{
    int i, j, k;
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (Plane_canvas[i][j] == 2)
            {
                for (k = 0; k < EnemyNum; k++)
                {
                    if ((i == enemy_x[k]) && (j == enemy_y[k]))  // �ӵ����ел�
                    {
                        Plane_score++;                // ������1
                        if (Plane_score % 5 == 0 && EnemyMoveSpeed > 3)   // �ﵽһ�����ֺ󣬵л����
                            EnemyMoveSpeed--;
                        if (Plane_score % 5 == 0)   // �ﵽһ�����ֺ��ӵ�������
                            BulletWidth++;
                        Plane_canvas[enemy_x[k]][enemy_y[k]] = 0;
                        if (rand() % 100 < 10)  // �ٷ�֮ʮ�ĸ�������boss�л�
                        {
							enemy_x[k] = rand() % 2;
                            enemy_y[k] = rand() % Width;
                            Plane_canvas[enemy_x[k]][enemy_y[k]] = 4;
                        }
                        else
                        {
                            enemy_x[k] = rand() % 2;           // �����µĵл�
                            enemy_y[k] = rand() % Width;
                            Plane_canvas[enemy_x[k]][enemy_y[k]] = 3;
                        }
                        Plane_canvas[i][j] = 0;      // �ӵ���ʧ
                    }
                }
                // �ӵ������ƶ�
                Plane_canvas[i][j] = 0;
                if (i > 0)
                    Plane_canvas[i - 1][j] = 2;
            }
        }
    }

    static int speed = 0;
    if (speed < EnemyMoveSpeed)
        speed++;

    for (k = 0; k < EnemyNum; k++)
    {
        if ((Plane_position_x == enemy_x[k]) && (Plane_position_y == enemy_y[k]))  // �л�ײ���һ�
        {
            printf("Game Over!\n");
            Sleep(3000);
            system("pause");
            exit(0);
        }

        if (enemy_x[k] > High)   // �л��ܳ���ʾ��Ļ
        {
            Plane_canvas[enemy_x[k]][enemy_y[k]] = 0;
            enemy_x[k] = rand() % 2;           // �����µĵл�
            enemy_y[k] = rand() % Width;
            Plane_canvas[enemy_x[k]][enemy_y[k]] = 3;
            Plane_score--;  // ����
        }

        if (speed == EnemyMoveSpeed)
        {
            // �л�����
            for (k = 0; k < EnemyNum; k++)
            {
                Plane_canvas[enemy_x[k]][enemy_y[k]] = 0;
                enemy_x[k]++;
                speed = 0;
                Plane_canvas[enemy_x[k]][enemy_y[k]] = 3;
            }
        }

        // �л������ӵ�
        if (enemy_bullet_x[k] == -1 && rand() % 100 < 5) // 5% �ĸ��ʷ����ӵ�
        {
            enemy_bullet_x[k] = enemy_x[k] + 1;
            enemy_bullet_y[k] = enemy_y[k];
            Plane_canvas[enemy_bullet_x[k]][enemy_bullet_y[k]] = 5;
        }

        // �л��ӵ��ƶ�
        if (enemy_bullet_x[k] != -1)
        {
            Plane_canvas[enemy_bullet_x[k]][enemy_bullet_y[k]] = 0;
            enemy_bullet_x[k]++;
            if (enemy_bullet_x[k] < High)
                Plane_canvas[enemy_bullet_x[k]][enemy_bullet_y[k]] = 5;
            else
                enemy_bullet_x[k] = -1; // �ӵ���ʧ
        }

        // �л��ӵ����зɻ�
        if (enemy_bullet_x[k] == Plane_position_x && enemy_bullet_y[k] == Plane_position_y)
        {
            printf("Game Over!\n");
            Sleep(3000);
            system("pause");
            exit(0);
        }
    }
}

void Plane_updateWithInput()  // ���û������йصĸ���
{
    char input;
    if (kbhit())  // �ж��Ƿ�������
    {
        input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
        if (input == 'a' && Plane_position_y > 0)
        {
            Plane_canvas[Plane_position_x][Plane_position_y] = 0;
            Plane_position_y--;  // λ������
            Plane_canvas[Plane_position_x][Plane_position_y] = 1;
        }
        else if (input == 'd' && Plane_position_y < Width - 1)
        {
            Plane_canvas[Plane_position_x][Plane_position_y] = 0;
            Plane_position_y++;  // λ������
            Plane_canvas[Plane_position_x][Plane_position_y] = 1;
        }
        else if (input == 'w')
        {
            Plane_canvas[Plane_position_x][Plane_position_y] = 0;
            Plane_position_x--;  // λ������
            Plane_canvas[Plane_position_x][Plane_position_y] = 1;
        }
        else if (input == 's')
        {
            Plane_canvas[Plane_position_x][Plane_position_y] = 0;
            Plane_position_x++;  // λ������
            Plane_canvas[Plane_position_x][Plane_position_y] = 1;
        }
        else if (input == ' ')  // �����ӵ�
        {
            int left = Plane_position_y - BulletWidth;
            int right = Plane_position_y + BulletWidth;
            if (left < 0)
                left = 0;
            if (right > Width - 1)
                right = Width - 1;
            int k;
            for (k = left; k <= right; k++) // ��������
                Plane_canvas[Plane_position_x - 1][k] = 2; // �����ӵ��ĳ�ʼλ���ڷɻ������Ϸ�
        }
    }
}
int Plane_main()
{
	Plane_startup();
	while(1)
	{
		Plane_show();
		Plane_updateWithoutInput();
		Plane_updateWithInput();
	}
	return 0;
}
