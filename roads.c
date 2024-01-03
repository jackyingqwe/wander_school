#include "heads.h"
int **read_csv(char filepath[], int row)
{
    FILE *fp;
    // 原始数组
    // 开辟连续二维数组空间
    // *road这个指针为一级指针，但road(road[0])其实是二级指针的地址
    int(*road)[row] = (int(*)[row])malloc(sizeof(int) * row * row);
    //  一级指针
    int **p = (int **)malloc(sizeof(int *) * row);
    fp = fopen(filepath, "r");
    char line[300];
    int i = 0;
    while (fgets(line, 300, fp))
    {
        char *token = strtok(line, ",");
        int j = 0;
        while (token != NULL)
        {
            road[i][j] = atoi(token);
            token = strtok(NULL, ",");
            j++;
        }
        i++;
    }
    for (int i = 0; i < row; i++)
    {
        p[i] = road[i];
    }
    fclose(fp);
    return p;
}
int makeroad()
{
    // 边初始化
    int road[MAX][MAX] = {[0 ...(MAX - 1)][0 ...(MAX - 1)] = INFINE};
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
            road[j][i] = road[i][j];
        }
    }
    // for (int i = 0; i < MAX; i++)
    // {
    //     for (int j = 0; j < MAX; j++)
    //         printf("%d ", road[i][j]);
    //     printf("\n");
    // }
    char filepath[50] = "G:/college file/out_work/cowander/road_origin.csv";
    FILE *fp = fopen(filepath, "w");
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
            fprintf(fp, "%d,", road[i][j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}
void printfname(int i)
{
    char file_view[50] = "G:/college file/out_work/cowander/view.txt";
    char name[20];
    FILE *fp;
    fp = fopen(file_view, "r");
    int ii = -1;
    while (ii != i)
    {
        ii++;
        fscanf(fp, "%*d %*s %s", name);
    }
    printf("%s", name);
    fclose(fp);
}
void write_2csv(char filepath[], int **road, int row)
{
    FILE *fp = fopen(filepath, "w");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < row; j++)
            fprintf(fp, "%d,", road[i][j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}
void Floyd(int **road, int row, char file[80])
{
    int(*path)[row] = (int(*)[row])malloc(sizeof(int) * row * row);
    // 初始化path
    for (int i = 0; i < row; i++)
    {
        for (int j = i; j < row; j++)
        {
            path[i][j] = path[j][i] = -1;
        }
    }
    for (int k = 0; k < row; k++)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = i; j < row; j++)
            {
                if (road[i][j] > road[i][k] + road[k][j])
                {
                    road[i][j] = road[j][i] = road[i][k] + road[k][j];
                    path[i][j] = path[j][i] = k;
                }
            }
        }
    }
    int **p_path = (int **)malloc(sizeof(int *) * row);
    for (int i = 0; i < row; i++)
    {
        p_path[i] = path[i];
    }
    char file_inner[80];
    strcpy(file_inner, file);
    strcat(file, "/path.csv");
    strcat(file_inner, "/road.csv");
    write_2csv(file, p_path, row);
    write_2csv(file_inner, road, row);
}
void printGraphPath(int i, int j, int row)
{
    char file_path[50] = "G:/college file/out_work/cowander/path.csv";
    int **path = read_csv(file_path, row);
    int flag = path[i][j];
    if (path[i][j] != -1)
    {
        printGraphPath(i, path[i][j], row);
        printGraphPath(path[i][j], j, row);
    }
    else
    {
        printfname(i);
        printf("->");
    }
    return;
}
void find_points_path(int **road, int row)
{
    printf("请输入要查询的序号\n输入0 0退出");
    int start = 5, end = 4;
    scanf("%d %d", &start, &end);
    while (start | end)
    {
        printf("\n最短路径为：\n");
        printGraphPath(start, end, row);
        printfname(end);
        show_min_distance(start, end, row);
        printf("\n再次输入查询\n");
        scanf("%d %d", &start, &end);
    }
}
void show_min_distance(int i, int j, int row)
{
    char filepath_road[50] = "G:/college file/out_work/cowander/road.csv";
    int **road = read_csv(filepath_road, row);
    printf("最短路径长度为%d\n", road[i][j]);
}
void printfroad(int **road)
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
            printf("%d", road[i][j]);
        printf("\n");
    }
}
int Ater_roads()
{
    int row = get_row();
    char filepath_road_origin[50] = "G:/college file/out_work/cowander/road_origin.csv";
    int **p = read_csv(filepath_road_origin, row);
    printf("数值不超过100\t1确认进行修改，任意键返回\n");
    int method, start, end, lenth;
    scanf("%d", &method);
    int max_num = get_row();
    if (method == 1)
    {
        printf("退出按-1,-1,-1。");
        printf("请依次输入起点、终点序号,以及长度\n");
        scanf("%d %d %d", &start, &end, &lenth);

        while ((start + 1) | (end + 1) | (lenth + 1))
        {
            if ((start - max_num > 0) | (end - max_num > 0))
            {
                printf("禁止输入超出景点序号的序号\n");
            }
            else if (start - end)
            {
                write_2csv(filepath_road_origin, insert_roads(p, start, end, lenth), row);
            }

            else
            {
                printf("禁止修改景点到景点的距离\n");
            }
            printf("退出按-1,-1,-1。");
            printf("请依次输入起点、终点序号,以及长度\n");
            scanf("%d %d %d", &start, &end, &lenth);
        }
        return 0;
    }
    else
    {
        return 0;
    }
}
int **insert_roads(int **road, int start, int end, int lenth)
{
    if (lenth > 100)
        lenth = 100;
    else if (lenth <= 0)
        printf("长度不能为非正数");
    road[start][end] = road[end][start] = lenth;
    return road;
}