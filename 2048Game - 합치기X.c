//제작자 Lamed https://github.com/Lamed-D/2048_C_console_win/upload
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



//해야할일 숫자 움직이는 로직 구현하기 move에 switch문
int main()
{
    int score; // 점수 합치면 점수 업
    int bestscore = 0; // 최고점수
    int board[4][4] = { // 게임판 
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0} };

    int Limitless_mode_flag; //리미리스모드 

    ConsoleSetting();
    Load(&bestscore);

    //게임초기 설정
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

//랜덤숫자생성용
void newnum(int board[4][4])
{
    srand((unsigned)time(NULL));
    int count;
again:
    count = 0;

    //보드판에 0이 없는가?
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

// 게임판그리기
void gamedraw(int board[4][4], int* score, int bestscore, int Limitless_mode_flag)
{
    system("cls");
    printf("\n");
    printf("\t\t 목표 : 2048블럭만들기\n");
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
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //원래 색깔로 고침
            } 
            else
                printf("         -");
        }
        printf("\n\n\n");
    }
    if (Limitless_mode_flag == 0) printf("\t\tLimitless Mode is enabled\n");
    printf("\t\t\t\t↑\n");
    printf("\t\t\t조작키←↓→");
}

int IsGameOver(int board[4][4], int* score, int bestscore, int* Limitless_mode_flag)
{
    int i, j;
    char answer;
    //보드판에 0이 있는가?
    for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) if (board[i][j] == 0) return 1;
    //보드판에 같은숫자가 있는가? (행)
    for (i = 0; i < 3; i++) for (j = 0; j < 3; j++) if (board[i][j] == board[i + 1][j] || board[i][j] == board[i][j + 1]) return 1;
    //보드판에 같은숫자가 있는가? (열)
    for (i = 0; i < 3; i++) if (board[i][3] == board[i + 1][3]) return 1;
    //보드판에 같은숫자가 있는가? (열)
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
    int flag = 0; //움직였는지 체크용
    int key = get_directionkey(board);
    switch (key)
    {
    case LEFT:
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                //합치기
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
                //오른쪽에 숫자가 0일경우 왼쪽이동
                if (board[i][j] == 0)
                {
                    for (int A = 1; A < 4 - j; A++)
                    {
                        if (board[i][j + A] != 0)
                        {
                            if (flag == 0) flag = 1;
                            board[i][j] = board[i][j + A];
                            board[i][j + A] = 0;
                            //합치기
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
            //합치기
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
                //왼쪽에 숫자가 0일경우 오른쪽이동
                if (board[i][j] == 0)
                {
                    for (int A = 1; A < 4 - count; A++)
                    {
                        if (board[i][j - A] != 0)
                        {
                            if (flag == 0) flag = 1;
                            board[i][j] = board[i][j - A];
                            board[i][j - A] = 0;
                            //합치기
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
            //합치기
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
                //위에 숫자가 0일경우 위로이동
                if (board[i][j] == 0)
                {
                    for (int A = 1; A < 4 - i; A++)
                    {
                        if (board[i + A][j] != 0)
                        {
                            if (flag == 0) flag = 1;
                            board[i][j] = board[i + A][j];
                            board[i + A][j] = 0;
                            //합치기
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
            //합치기
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
                //위에 숫자가 0일경우 아래로이동
                if (board[i][j] == 0)
                {
                    for (int A = 1; A < 4 - count; A++)
                    {
                        if (board[i - A][j] != 0)
                        {
                            if (flag == 0) flag = 1;
                            board[i][j] = board[i - A][j];
                            board[i - A][j] = 0;
                            //합치기
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

inline int get_directionkey(int board[4][4]) //방향키를 입력받는 함수
{
    int key;
    key = _getch();
    if (key == 0)//방향키
    {
        key = _getch();
        if(key == 59) Debug_cheat(board); //F1일경우 치트발동
        if (key == 60) Reset_BestScore(); //F2일경우 최고점수 초기화
        if (key == 62) Debug_cheat2(board); //F4일경우 4로보드 초기화
    }
    if (key == 224)//방향키
    {
        return _getch(); //어떤 방향 키인지 반환
    }
    return 0;    //방향키가 아님
}

int Is2048(int board[4][4]) //2048이 완성되었는지 확인하는함수
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
    system("title 2048게임");
    //system("mode con cols=25 lines=25 | title 2048게임");
}

void Load(int* bestscore)
{
    FILE* fp;

    fopen_s(&fp, "value_setting.txt", "r+");

    //파일열기 실패
    if (fp == NULL) {
        return;
    }
    //파일열기 성공
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

    //파일열기 실패
    if (fp == NULL) {
        return;
    }
    //파일열기 성공
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
