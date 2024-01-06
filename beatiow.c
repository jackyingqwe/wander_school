// 设置树荫与好看
#include "heads.h"
void make_beauti(char filepath[50])
{
    // 越好看越小
    //  边初始化
    int road[MAX][MAX] = {[0 ...(MAX - 1)][0 ...(MAX - 1)] = 100};
    road[0][1] = 2;
    road[0][3] = 10;
    road[1][2] = 8;
    road[1][7] = 2;
    road[2][3] = 4;
    road[2][8] = 1;
    road[2][7] = 3;
    road[2][5] = 10;
    road[2][6] = 14;
    road[3][4] = 18;
    road[3][7] = 4;
    road[3][10] = 4;
    road[3][11] = 3;
    road[4][5] = 1;
    road[4][7] = 12;
    road[4][9] = 2;
    road[5][6] = 1;
    road[6][9] = 2;
    road[7][8] = 1;
    road[8][10] = 3;
    road[10][11] = 4;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = i; j < MAX; j++)
        {
            if (i == j)
                road[i][j] = road[j][i] = 0;
            else
                road[j][i] = road[i][j];
        }
    }
    FILE *fp = fopen(filepath, "w");
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
            fprintf(fp, "%d,", road[i][j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

// 树荫
void make_shandow(char filepath[50])
{
    // 没有树荫为500
    //  边初始化
    int road[MAX][MAX] = {[0 ...(MAX - 1)][0 ...(MAX - 1)] = 500};
    road[0][1] = 2;
    road[0][3] = 10;
    road[1][2] = 8;
    road[1][7] = 2;
    road[2][3] = 4;
    road[2][8] = 1;
    road[2][7] = 3;
    road[2][5] = 10;
    road[2][6] = 14;
    road[3][4] = 18;
    road[3][7] = 4;
    road[3][10] = 4;
    road[3][11] = 3;
    road[4][5] = 1;
    road[4][7] = 12;
    road[4][9] = 2;
    road[5][6] = 1;
    road[6][9] = 2;
    road[7][8] = 1;
    road[8][10] = 3;
    road[10][11] = 4;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = i; j < MAX; j++)
        {
            if (i == j)
                road[i][j] = road[j][i] = 0;
            else if (road[i][j] < 20)
                road[j][i] = road[i][j] = 20 - road[i][j];
        }
    }
    FILE *fp = fopen(filepath, "w");
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
            fprintf(fp, "%d,", road[i][j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void init_dowandbeati()
{
    make_beauti(show_filepath(2, 0));
    make_shandow(show_filepath(3, 0));
    int **road_beati = read_csv(show_filepath(2, 0), MAX);
    int **road_shandow = read_csv(show_filepath(3, 0), MAX);
    int row = get_row();
    Floyd(road_shandow, row, show_filepath(0, 3));
    Floyd(road_beati, row, show_filepath(0, 2));
}
