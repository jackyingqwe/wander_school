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
    char filepath[50] = {"G:/college file/out_work/cowander/view.txt"};
    VIEW *head = read_view(filepath);
    // 主菜单
    printf("欢迎来到西安邮电大学导游咨询系统!\n");
    show_view(head);
    printf("\n查询景点请按1\t");
    printf("修改景点请按2\t");
    printf("查询路线请按3\t");
    printf("修改路线请按4\n");
    printf("输入5退出程序\n\n");
}
int **init_road(char filepath_road_origin[80], char file[50])
{
    int row = get_row();
    int col = row;
    int **road = read_csv(filepath_road_origin, row);
    Floyd(road, row, file);
    return road;
}
int select_fun(char filepath[])
{
    int index = 6;
    scanf("%d", &index);
    while (index > 5)
    {
        printf("请重新输入");
        scanf("%d", &index);
    }
    VIEW *head = read_view(filepath);
    switch (index)
    {
    case 1:
    {
        printf("请输入要查询的序号,退出按-1\n");
        int index = 2;
        scanf("%d", &index);
        while (index + 1)
        {
            if (index > get_row() | index < -1)
            {
                printf("序号超出当前景点最大序号\n重新输入\n");
            }
            else
            {
                int i = 0;
                for (VIEW *temp = head->next; temp; temp = temp->next)
                {
                    if (i == index)
                        printf("%s\t%s\n", temp->name, temp->intro);
                    i++;
                }
                printf("请继续输入查询,退出按-1\n");
            }
            scanf("%d", &index);
        }
        main();
        free(head);
        break;
    }
    case 2:
    {
        alter_view(head);
        free(head);
        main();
        break;
    }
    case 3:
    {
        int index = chose_way();
        int **p = (int **)init_road(show_filepath(index, 0), show_filepath(0, index));
        find_points_path(p, get_row(), show_filepath(0, index));
        free(head);
        free(p);
        main();
        break;
    }
    case 4:
    {
        Ater_roads();
        free(head);
        main();
        break;
    }
    case 5:
        free(head);
        return 0;
    default:
        free(head);
        main();
        break;
    }
}

int chose_way()
{
    int index = 5;
    while (index > 3)
    {
        printf("查询最短路径按1\t最漂亮的路按2\t树荫最多的路按3\n");
        scanf("%d", &index);
    }
    return index;
}
// 前面一个返回origin——road，后面是子目录
char *show_filepath(int index, int order)
{
    // 用户输入的路径
    char *filepath_road_origin, *file;
    filepath_road_origin = (char *)malloc(sizeof(char) * 80);
    strcpy(filepath_road_origin, "G:/college file/out_work/cowander/road_origin.csv");
    file = (char *)malloc(sizeof(char) * 50);
    strcpy(file, "G:/college file/out_work/cowander");
    if (index)
    {
        switch (index)
        {
        case 2:
            strcpy(filepath_road_origin, "G:/college file/out_work/cowander/beati/beati_origin.csv");
            return filepath_road_origin;
            break;
        case 3:
            strcpy(filepath_road_origin, "G:/college file/out_work/cowander/shandow/shandow_origin.csv");
            return filepath_road_origin;
            break;
        case 4:
            strcpy(filepath_road_origin, "G:/college file/out_work/cowander/view.txt");
            return filepath_road_origin;
            break;
        default:
            return filepath_road_origin;
            break;
        }
    }
    else
    {
        switch (order)
        {
        case 2:
            strcpy(file, "G:/college file/out_work/cowander/beati");
            return file;
            break;
        case 3:
            strcpy(file, "G:/college file/out_work/cowander/shandow");
            return file;
            break;
        default:
            return file;
            break;
        }
    }
}