#include "heads.h"
// 获取景点个数
int get_row()
{
    char filepath[50] = "G:/college file/out_work/cowander/view.txt";
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL)
        perror("Error opening file"); // 打开失败
    int num = 0;
    char intro[500];
    while (fgets(intro, 500, fp))
        num = num + 1;
    return num;
}
void printMenu()
{
    // 主菜单
    printf("1欢迎来到西安邮电大学导游咨询系统!\n");
    printf("查询景点请按1\n");
    printf("修改景点请按2\n");
    printf("查询路线请按3\n");
    printf("修改路线请按4\n");
    printf("输入exit退出程序\n\n");
}
int *init_road()
{
    char filepath[50] = "G:/college file/out_work/cowander/view.txt";
    // 景点简介
    char filepath_path[50] = "G:/college file/out_work/cowander/path.csv";
    // 用户输入的路径
    char filepath_road_origin[50] = "G:/college file/out_work/cowander/road_origin.csv";
    // 最短路径
    char filepath_road[50] = "G:/college file/out_work/cowander/road.csv";
    char file[] = "G:/college file/out_work/cowander";
    int row = get_row();
    int col = row;
    int(*road)[row] = read_csv(filepath_road_origin, row, col);
    // for (int i = 0; i < 12; i++)
    // {
    //     for (int j = 0; j < 10; j++)
    //         printf("%d", road[i][j]);
    // }
    int **p = (int **)road;
    Floyd(p, row, col, file);
    return (*road)[row];
}
void select_fun(char filepath[])
{
    int index = 5;
    scanf("%d", &index);
    while (index > 4)
    {
        printf("请重新输入");
        scanf("%d", &index);
    }
    VIEW *head = read_view(filepath);
    show_view(head);

    switch (index)
    {
    case 1:
    {
        break;
    }
    case 2:
    {
        show_view(head);
        alter_view(head);
        break;
    }
    case 3:
    {
        int **p = (int **)init_road();
        find_points_path(p, get_row());
        break;
    }
    case 4:
    {
        init_road();
        break;
    }
    default:
        break;
    }
}
