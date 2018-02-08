#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M   4
#define N   4

void game_show();
void game_num();
void game_num_handle();

int num[4][4] = {0};
char key;
int score = 0;
int flags = 1;
int getnum_flags = 1;
int over_flags = 0;
int handle_flags = 1;

int main()
{
    while(flags)
    {
        system("clear");
        game_num();
        if(over_flags == 1)
        {
            printf("game over!!!\n");
            getchar();
            getchar();
            break;
        }
        game_show();
        game_num_handle();
    }
    return 0;
}

void game_show()
{
    static int i,j;
    printf("\n********************\n\n");
    printf("score:%d",score);
    printf("\n********************\n\n");
    printf("┌────┬────┬────┬────┐\n");
    for(i = 0;i < M;i++)
    {
        printf("│");
        for(j = 0;j < N;j++)
        {
            if(num[i][j] != 0)
                printf("%4d│",num[i][j]);
            else
                printf("    │");
        }
        printf("\n");
        if(i < 3)
            printf("├────┼────┼────┼────┤\n");
        else
            printf("└────┴────┴────┴────┘");
    }
    printf("\n\n********************\n");
}

void game_num()
{
    srand((unsigned)time(NULL));
    static int i,j;
    getnum_flags = 0;
    handle_flags = 0;
    score = 0;

    for(i = 0;i < 4;i++)
    {
        for(j = 0;j < 4;j++)
        {
            if(num[i][j] == 0)
                getnum_flags++;
            if(j < 3 && num[i][j] == num[i][j+1])
                handle_flags = 1;
        }
    }
    for(j = 0;j < 4;j++)
    {
        for(i = 0;i < 4;i++)
        {
            score += num[i][j];
            if(i < 3 && num[i][j] == num[i+1][j])
                handle_flags = 1;
        }
    }
    while(getnum_flags > 0)
    {
        i = rand() % 4;
        j = rand() % 4;
        if(num[i][j] == 0)
        {
            num[i][j] = ( rand() % 2 ? 2:4 );
            break;
        }
    }
    if(getnum_flags == 0 && handle_flags == 0)
    {
        over_flags = 1;
    }
}

void game_num_handle()
{
    handle_flags = 1;
    int temp = 0;
    int len = 0;
    while(handle_flags)
    {
        scanf("%c",&key);
        getchar();
        switch (key) {
        case 'w':
            for(int j = 0;j < 4;j++)
            {
                for(int i = 0;i < 4;i++)
                {
                    if(num[i][j] != 0)
                    {
                        for(int k = i-1;k >= 0;k--)
                        {
                            if(num[k][j] == 0)
                                len++;
                            else
                                break;
                        }
                        temp = num[i][j];
                        num[i][j] = 0;
                        num[i-len][j] = temp;
                        if(i != len && num[i-len][j] == num[i-len-1][j])//
                        {
                            num[i-len][j] = 0;
                            num[i-len-1][j] *= 2;
                        }
                        len = 0;
                    }
                }
            }
            handle_flags = 0;
            break;
        case 's':
            for(int j = 0;j < 4;j++)
            {
                for(int i = 3;i >= 0;i--)
                {
                    if(num[i][j] != 0)
                    {
                        for(int k = i+1;k <= 3;k++)
                        {
                            if(num[k][j] == 0)
                                len++;
                            else
                                break;
                        }
                        temp = num[i][j];
                        num[i][j] = 0;
                        num[i+len][j] = temp;
                        if(i != (3-len) && num[i+len][j] == num[i+len+1][j])
                        {
                            num[i+len][j] = 0;
                            num[i+len+1][j] *= 2;
                        }
                        len = 0;
                    }
                }
            }
            handle_flags = 0;
            break;
        case 'a':
            for(int i = 0;i < 4;i++)
            {
                for(int j = 0;j < 4;j++)
                {
                    if(num[i][j] != 0)
                    {
                        for(int k = j-1;k >= 0;k--)
                        {
                            if(num[i][k] == 0)
                                len++;
                            else
                                break;
                        }
                        temp = num[i][j];
                        num[i][j] = 0;
                        num[i][j-len] = temp;
                        if(j != len && num[i][j-len] == num[i][j-len-1])//
                        {
                            num[i][j-len] = 0;
                            num[i][j-len-1] *= 2;
                        }
                        len = 0;
                    }
                }
            }
            handle_flags = 0;
            break;
        case 'd':
            for(int i = 0;i < 4;i++)
            {
                for(int j = 3;j >= 0;j--)
                {
                    if(num[i][j] != 0)
                    {
                        for(int k = j+1;k <= 3;k++)
                        {
                            if(num[i][k] == 0)
                                len++;
                            else
                                break;
                        }
                        temp = num[i][j];
                        num[i][j] = 0;
                        num[i][j+len] = temp;
                        if(j != (3-len) && num[i][j+len] == num[i][j+len+1])
                        {
                            num[i][j+len] = 0;
                            num[i][j+len+1] *= 2;
                        }
                        len = 0;
                    }
                }
            }
            handle_flags = 0;
            break;
        case 'q':
            if(key == 'q')
                flags = 0;
            handle_flags = 0;
            break;
        default:
            printf("err!!\n");
            key = 0;
            break;
        }
    }
}
