#include "heads.h"
// 建立校园的游行景点
void create_view_points()
{
    printf("请依次输入要建立的景点名称、景点介绍");
    char name[10], intro[100];
    scanf("%s", &name);
    scanf("%s", &intro);
}
VIEW *crate_view(int num, char name[40], char intro[100])
{
    VIEW *temp_inner = (VIEW *)malloc(sizeof(VIEW));
    temp_inner->num = num;
    strcpy(temp_inner->name, name);
    strcpy(temp_inner->intro, intro);
    temp_inner->next = NULL;
    return temp_inner;
}
void show_view(VIEW *head)
{
    head = head->next;
    for (VIEW *temp = head; temp; temp = temp->next)
    {
        // 根据名称的长度，美化输出格式
        if (strlen(temp->name) > 10)
            printf("%d\t%s\t\t%s\n", temp->num, temp->name, temp->intro);
        else
            printf("%d\t%s\t\t\t%s\n", temp->num, temp->name, temp->intro);
    }
}
int write_view(VIEW *head)
{
    // 输出文件绝对路径
    char filepath[50] = {"G:/college file/out_work/cowander/view.txt"};
    FILE *fp = fopen(filepath, "w");
    head = head->next;
    for (VIEW *temp = head; temp; temp = temp->next)
    {
        fprintf(fp, "%d\t%s\t%s\n", temp->num, temp->intro, temp->name);
    }
    fclose(fp);
    return 0;
}
VIEW *read_view(char filepath[50])
{
    VIEW *head = (VIEW *)malloc(sizeof(VIEW));
    head->next = NULL;
    VIEW *temp = head;
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL)
        perror("Error opening file"); // 打开失败
    char name[40] = {}, intro[100] = {};
    int num;
    while (!feof(fp))
    {
        int am = fscanf(fp, "%d", &num);
        int am1 = fscanf(fp, "%s %s\n", intro, name);
        // printf("为v%d %d\n",am,am1);
        // printf("%d %s %s", num, name, intro);
        temp->next = crate_view(num, name, intro);
        temp = temp->next;
    }
    temp->next = NULL;
    fclose(fp);
    return head;
}
VIEW *alter_view(VIEW *head)
{
    // 显示
    printf("景点名称不能超过十个汉字，介绍不超过50\n");
    printf("更改请按1\t新增按2\t删除按3\t退出按\n");
    int case_index = 5;
    scanf("%d", &case_index);
    while (case_index > 3)
    {
        printf("请正确输入\n");
        scanf("%d", &case_index);
    }
    switch (case_index)
    {
    case 2:
        head = insert_view(head);
        if (write_view(head))
            printf("修改后保存文件时出现错误");
        break;
    case 3:
    {
        int method = 5;
        do
        {
            printf("请选择删除方式\t输入序号1\t输入名称2\t退出大于2\n");
            scanf("%d", &method);
            if (method == 2)
            {
                printf("请输入名称\n");
                char name[30];
                scanf("%s", name);
                head = delete_view_name(head, name);
            }
            else if (method == 1)
            {
                printf("请输入序号\n");
                int max_num = get_row();
                int num;
                scanf("%d", &num);
                if (num >= max_num)
                    printf("error,index exceed");
                else
                    head = delete_view_num(head, num);
            }
        } while (method < 3);
    }
    default:
        break;
    }
    return head;
}
VIEW *insert_view(VIEW *head)
{
    char name[40], intro[100];
    printf("请依次输入景点名称及简介\t退出按0 0\n");
    scanf("%s %s", name, intro);
    printf("%s %s", name, intro);
    int num = 0;
    // 获取当前序号
    VIEW *end = head->next;
    while (end->next)
    {
        num = num + 1;
        end = end->next;
    }
    while ((strcmp(name, "0") & strcmp(intro, "0")))
    {
        VIEW *temp = crate_view(num, name, intro);
        end->next = temp;
        end = end->next;
        printf("继续添加\n");
        scanf("%s %s", name, intro);
        printf("%s %s\n", name, intro);
    }
    return head;
}
VIEW *delete_view_name(VIEW *head, char name[30])
{
    for (VIEW *temp = head; temp->next; temp = temp->next)
    {
        VIEW *temp_next = temp->next;
        if (strcmp(temp_next->name, name))
        {
            VIEW *temp_next = temp->next;
            temp_next = temp_next->next;
            temp->next = temp_next;
            printf("删除成功\n");
            write_view(head);
            return head;
        }
    }
    printf("找不到该名称\n");
    return head;
}
VIEW *delete_view_num(VIEW *head, int num)
{
    VIEW *temp = head;
    while (temp->next)
    {
        temp = temp->next;
        num--;
        if (num == 0)
        {
            VIEW *temp_next = temp->next;
            temp_next = temp_next->next;
            temp->next = temp_next;
            write_view(head);
            printf("删除成功\n");
            return head;
        }
    }
    printf("序号超出\n");
    return head;
}