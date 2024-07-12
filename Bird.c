#include "Bird.h"

// ȫ�ֱ���
int bird_x, bird_y; // С�������
int score; // �÷֣������ϰ���ĸ���
int bird_velocity = 0; // С��Ĵ�ֱ�ٶ�


typedef struct {
    int y; // �ϰ����y����
    int xDown; // �ϰ�����±߽�
    int xTop; // �ϰ�����ϱ߽�
} Barrier;

Barrier barriers[MAX_BARRIERS];


void Bird_startup() // ���ݳ�ʼ��
{
    bird_x = High / 2;
    bird_y = 3;
    score = 0;
    bird_velocity = 0;

    for (int i = 0; i < MAX_BARRIERS; i++) {
        barriers[i].y = Width + i * (Width / MAX_BARRIERS);
        int temp = rand() % (int)(High * 0.8);
        barriers[i].xDown = temp - High / 10;
        barriers[i].xTop = temp + High / 10;
    }
}

void Bird_show() // ��ʾ����
{
    hidecursor();
    gotoxy(0, 0); // ����
    int i, j;

    // �����ϱ߿�
    for (j = 0; j < Width + 2; j++) {
        printf("-");
    }
    printf("\n");

    for (i = 0; i < High; i++) {
        printf("#"); // ������߿�
        for (j = 0; j < Width; j++) {
            if ((i == bird_x) && (j == bird_y))
                printf("@"); // ���С��
            else {
                int isBarrier = 0;
                for (int k = 0; k < MAX_BARRIERS; k++) {
                    if ((j == barriers[k].y) && ((i < barriers[k].xDown) || (i > barriers[k].xTop))) {
                        printf("*"); // ���ǽ��
                        isBarrier = 1;
                        break;
                    }
                }
                if (!isBarrier)
                    printf(" "); // ����ո�
            }
        }
        printf("#\n"); // �����ұ߿�
    }

    // �����±߿�
    for (j = 0; j < Width + 2; j++) {
        printf("-");
    }
    printf("\n");

    printf("score:%d\n", score);
}

void Bird_updateWithoutInput() // ���û������޹صĸ���
{
    bird_x += bird_velocity;
    bird_velocity++; // �������ٶ�

    if (bird_x >= High - 1) {
        bird_x = High - 1;
    }
    if (bird_x <= 1) {
        bird_x = 1;
    }

    for (int i = 0; i < MAX_BARRIERS; i++) {
        barriers[i].y--;
        if (bird_y == barriers[i].y) {
            if ((bird_x >= barriers[i].xDown) && (bird_x <= barriers[i].xTop)){
                score++;
                printf("\a");
            }      
            else {
                printf("��Ϸʧ��\n");
                system("pause");
                exit(0);
            }
        }
        if (barriers[i].y <= 0) { // ��������һ���ϰ���
            barriers[i].y = Width;
            int temp = rand() % (int)(High * 0.8);
            barriers[i].xDown = temp - High / 8;
            barriers[i].xTop = temp + High / 8;
        }
    }

    Sleep(50);
}

void Bird_updateWithInput() // ���û������йصĸ���
{
    char input;
    if (kbhit()) { // �ж��Ƿ�������
        input = getch(); // �����û��Ĳ�ͬ�������ƶ�����������س�
        if (input == ' ') {     
            bird_velocity = -2; // ������Ծ
        }
    }
}

int Bird_main() 
{
    Bird_startup(); // ���ݳ�ʼ��
    while (1) { // ��Ϸѭ��ִ��
        Bird_show(); // ��ʾ����
        Bird_updateWithoutInput(); // ���û������޹صĸ���
        Bird_updateWithInput(); // ���û������йصĸ���
    }
    return 0;
}
