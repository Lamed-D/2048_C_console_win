//������ Lamed https://github.com/Lamed-D/2048_C_console_win/upload
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define LEFT    75
#define RIGHT   77
#define UP      72
#define DOWN    80

void init(int board[4][4], int* score, int bestscore, int* Limitless_mode_flag);
void newnum(int board[4][4]);
void gamedraw(int board[4][4], int* score, int bestscore, int Limitless_mode_flag);
int IsGameOver(int board[4][4], int* score, int bestscore, int* Limitless_mode_flag);
int move(int board[4][4], int* score);
inline int get_directionkey(int board[4][4]);
int Is2048(int board[4][4]);
void ConsoleSetting();
void Load(int* bestscore);
void Save(int* bestscore, int score);
void Reset_BestScore();
void Debug_cheat(int board[4][4]); 
void Debug_cheat2(int board[4][4]);



//�ؾ����� ���� �����̴� ���� �����ϱ� move�� switch��
int main()
{
    int score; // ���� ��ġ�� ���� ��
    int bestscore = 0; // �ְ�����
    int board[4][4] = { // ������ 
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0} };

    int Limitless_mode_flag; //���̸������ 

    ConsoleSetting();
    Load(&bestscore);

    //�����ʱ� ����
    init(board, &score, bestscore, &Limitless_mode_flag);

    while (TRUE)
    {
        if (move(board, &score)) newnum(board);
        Save(&bestscore, score);
        Sleep(100);
        gamedraw(board, &score, bestscore, Limitless_mode_flag);
        if (Is2048(board) && Limitless_mode_flag)
        {
            char answer = 0;
            printf("\n\t\tCongratulations");
            printf("\n\t\tYou win the game");
            printf("\n\t\tLimitless Mode is enabled");
            printf("\n\t\tStart? Y or N : ");
            A:
            scanf_s("%c", &answer);
            if (answer == 'Y') goto B;
            goto A;
            B:
            Limitless_mode_flag = 0;
        }
        IsGameOver(board, &score, bestscore, &Limitless_mode_flag);
    }
}

void init(int board[4][4], int* score, int bestscore, int* Limitless_mode_flag)
{
    *score = 0;
    *Limitless_mode_flag = 1;
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++)board[i][j] = 0;
    newnum(board);
    newnum(board);
    gamedraw(board, score, bestscore, Limitless_mode_flag);
}

//�������ڻ�����
void newnum(int board[4][4])
{
    srand((unsigned)time(NULL));
    int count;
again:
    count = 0;

    //�����ǿ� 0�� ���°�?
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (board[i][j] != 0) count++; if (count == 16) return;

    int random_number = rand() % 4;
    int random_number_v2 = rand() % 4;
    int random2 = rand() % 2;
    if (random2 && board[random_number][random_number_v2] == 0)
        board[random_number][random_number_v2] = 2;
    else if (board[random_number][random_number_v2] == 0)
        board[random_number][random_number_v2] = 4;
    else
        goto again;
}

// �����Ǳ׸���
void gamedraw(int board[4][4], int* score, int bestscore, int Limitless_mode_flag)
{
    system("cls");
    printf("\n");
    printf("\t\t ��ǥ : 2048�������\n");
    printf("\t\t      Bestscore : %d\n", bestscore);
    printf("\t\t\t  score : %d", *score);
    printf("\n\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
            if (board[i][j] == 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            if (board[i][j] == 8) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
            if (board[i][j] == 16) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            if (board[i][j] == 32) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
            if (board[i][j] == 64) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
            if (board[i][j] == 128) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
            if (board[i][j] == 256) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            if (board[i][j] == 512) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            if (board[i][j] == 1024) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            if (board[i][j] == 2048) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            if (board[i][j] != 0)
            {
                printf("%10d", board[i][j]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //���� ����� ��ħ
            } 
            else
                printf("         -");
        }
        printf("\n\n\n");
    }
    if (Limitless_mode_flag == 0) printf("\t\tLimitless Mode is enabled\n");
    printf("\t\t\t\t��\n");
    printf("\t\t\t����Ű����");
}

int IsGameOver(int board[4][4], int* score, int bestscore, int* Limitless_mode_flag)
{
    int i, j;
    char answer;
    //�����ǿ� 0�� �ִ°�?
    for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) if (board[i][j] == 0) return 1;
    //�����ǿ� �������ڰ� �ִ°�? (��)
    for (i = 0; i < 3; i++) for (j = 0; j < 3; j++) if (board[i][j] == board[i + 1][j] || board[i][j] == board[i][j + 1]) return 1;
    //�����ǿ� �������ڰ� �ִ°�? (��)
    for (i = 0; i < 3; i++) if (board[i][3] == board[i + 1][3]) return 1;
    //�����ǿ� �������ڰ� �ִ°�? (��)
    for (j = 0; j < 3; j++) if (board[3][j] == board[3][j + 1]) return 1;

    printf("\n\t\t  Game Over..\n");
    printf("\t\t  Continued? Y or N : ");
A2:
    scanf_s("%c", &answer);
    if (answer == 'Y') goto B2;
    goto A2;
B2:
    init(board, score, bestscore, Limitless_mode_flag);
    return 0;
}

int move(int board[4][4], int* score)
{
    int flag = 0; //���������� üũ��
    int key = get_directionkey(board);
    switch (key)
    {
    case LEFT:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                //��ġ��
                for (int k = 0; k < 3; k++)
                {
                    if (board[i][k] == board[i][k + 1] && board[i][k] != 0)
                    {
                        if (flag == 0) flag = 1;
                        board[i][k] = board[i][k] * 2;
                        board[i][k + 1] = 0;
                        *score += board[i][k];
                        break;
                    }
                }
                //�����ʿ� ���ڰ� 0�ϰ�� �����̵�
                if (board[i][j] == 0)
                {
                    for (int A = 1; A < 4 - j; A++)
                    {
                        if (board[i][j + A] != 0)
                        {
                            if (flag == 0) flag = 1;
                            board[i][j] = board[i][j + A];
                            board[i][j + A] = 0;
                            //��ġ��
                            for (int k = 0; k < 3; k++)
                            {
                                if (board[i][k] == board[i][k + 1] && board[i][k] != 0)
                                {
                                    if (flag == 0) flag = 1;
                                    board[i][k] = board[i][k] * 2;
                                    board[i][k + 1] = 0;
                                    *score += board[i][k];
                                    break;
                                }
                            }
                            break;
                        }

                    }
                }
            }
        }
        break;
    case RIGHT:
        for (int i = 0; i < 4; i++)
        {
            //��ġ��
            for (int k = 3; k > 0; k--)
            {
                if (board[i][k] == board[i][k - 1] && board[i][k] != 0)
                {
                    if (flag == 0) flag = 1;
                    board[i][k] = board[i][k] * 2;
                    board[i][k - 1] = 0;
                    *score += board[i][k];
                    break;
                }
            }
            for (int j = 3, count = 0; j >= 0; j--, count++)
            {
                //���ʿ� ���ڰ� 0�ϰ�� �������̵�
                if (board[i][j] == 0)
                {
                    for (int A = 1; A < 4 - count; A++)
                    {
                        if (board[i][j - A] != 0)
                        {
                            if (flag == 0) flag = 1;
                            board[i][j] = board[i][j - A];
                            board[i][j - A] = 0;
                            //��ġ��
                            for (int k = 3; k > 0; k--)
                            {
                                if (board[i][k] == board[i][k - 1] && board[i][k] != 0)
                                {
                                    if (flag == 0) flag = 1;
                                    board[i][k] = board[i][k] * 2;
                                    board[i][k - 1] = 0;
                                    *score += board[i][k];
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
        break;
    case UP:
        for (int j = 0; j < 4; j++)
        {
            //��ġ��
            for (int k = 0; k < 3; k++)
            {
                if (board[k][j] == board[k + 1][j] && board[k][j] != 0)
                {
                    if (flag == 0) flag = 1;
                    board[k][j] = board[k][j] * 2;
                    board[k + 1][j] = 0;
                    *score += board[k][j];
                }
            }
            for (int i = 0; i < 4; i++)
            {
                //���� ���ڰ� 0�ϰ�� �����̵�
                if (board[i][j] == 0)
                {
                    for (int A = 1; A < 4 - i; A++)
                    {
                        if (board[i + A][j] != 0)
                        {
                            if (flag == 0) flag = 1;
                            board[i][j] = board[i + A][j];
                            board[i + A][j] = 0;
                            //��ġ��
                            for (int k = 0; k < 3; k++)
                            {
                                if (board[k][j] == board[k + 1][j] && board[k][j] != 0)
                                {
                                    if (flag == 0) flag = 1;
                                    board[k][j] = board[k][j] * 2;
                                    board[k + 1][j] = 0;
                                    *score += board[k][j];
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
        break;
    case DOWN:
        for (int j = 0; j < 4; j++)
        {
            //��ġ��
            for (int k = 3; k > 0; k--)
            {
                if (board[k][j] == board[k - 1][j] && board[k][j] != 0)
                {
                    if (flag == 0) flag = 1;
                    board[k][j] = board[k][j] * 2;
                    board[k - 1][j] = 0;
                    *score += board[k][j];
                }
            }
            for (int i = 3, count = 0; i >= 0; i--, count++)
            {
                //���� ���ڰ� 0�ϰ�� �Ʒ����̵�
                if (board[i][j] == 0)
                {
                    for (int A = 1; A < 4 - count; A++)
                    {
                        if (board[i - A][j] != 0)
                        {
                            if (flag == 0) flag = 1;
                            board[i][j] = board[i - A][j];
                            board[i - A][j] = 0;
                            //��ġ��
                            for (int k = 3; k > 0; k--)
                            {
                                if (board[k][j] == board[k - 1][j] && board[k][j] != 0)
                                {
                                    if (flag == 0) flag = 1;
                                    board[k][j] = board[k][j] * 2;
                                    board[k - 1][j] = 0;
                                    *score += board[k][j];
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
        break;
    }
    return flag;
}

inline int get_directionkey(int board[4][4]) //����Ű�� �Է¹޴� �Լ�
{
    int key;
    key = _getch();
    if (key == 0)//����Ű
    {
        key = _getch();
        if(key == 59) Debug_cheat(board); //F1�ϰ�� ġƮ�ߵ�
        if (key == 60) Reset_BestScore(); //F2�ϰ�� �ְ����� �ʱ�ȭ
        if (key == 62) Debug_cheat2(board); //F4�ϰ�� 4�κ��� �ʱ�ȭ
    }
    if (key == 224)//����Ű
    {
        return _getch(); //� ���� Ű���� ��ȯ
    }
    return 0;    //����Ű�� �ƴ�
}

int Is2048(int board[4][4]) //2048�� �ϼ��Ǿ����� Ȯ���ϴ��Լ�
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 2048) return 1;
        }
    }
    return 0;
}

void ConsoleSetting()
{
    system("title 2048����");
    //system("mode con cols=25 lines=25 | title 2048����");
}

void Load(int* bestscore)
{
    FILE* fp;

    fopen_s(&fp, "value_setting.txt", "r+");

    //���Ͽ��� ����
    if (fp == NULL) {
        return;
    }
    //���Ͽ��� ����
    else {
        fscanf_s(fp, "bestscore : %d", bestscore);
        fclose(fp);
    }
    return;
}

void Save(int* bestscore, int score)
{
    if (score > *bestscore)  *bestscore = score;
    FILE* fp;

    fopen_s(&fp, "value_setting.txt", "w+");

    if (fp == NULL) {
        return;
    }
    else {
        fprintf(fp, "bestscore : %d", *bestscore);
        fclose(fp);
    }
    return;
}

void Reset_BestScore()
{
    FILE* fp;

    fopen_s(&fp, "value_setting.txt", "w+");

    //���Ͽ��� ����
    if (fp == NULL) {
        return;
    }
    //���Ͽ��� ����
    else {
        fprintf(fp, "bestscore : %d", 0);
        fclose(fp);
        exit(1);
    }
    return;
}

void Debug_cheat(int board[4][4])
{
    int Test = 2048;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if(Test != 1) board[i][j] = Test;
            Test /= 2;
        }
    }
}

void Debug_cheat2(int board[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = 2;
        }
    }
}
