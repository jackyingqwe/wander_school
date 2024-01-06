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
    // for (VIEW *temp = head; temp; temp = temp->next)
    // {
    //     i++;
    //     printf("%d", i);
    //     printf("%s", temp->name);
    // }
    for (VIEW *temp = head; temp; temp = temp->next)
    {
        // 根据名称的长度，美化输出格式
        if (strlen(temp->name) > 10)
            printf("%d\t%s\t", temp->num, temp->name);
        else
            printf("%d\t%s\t\t", temp->num, temp->name);
        if ((temp->num % 3) == 0)
            printf("\n");
    }
}
int write_view(VIEW *head)
{
    FILE *fp = fopen(show_filepath(4, 0), "w");
    head = head->next;
    int i = 0;
    for (VIEW *temp = head; temp; temp = temp->next)
    {
        fprintf(fp, "%d\t%s\t%s\n", i, temp->intro, temp->name);
        i++;
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
    case 1:
        write_view(modefy_view(head));
        break;
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
                {
                    head = delete_view_num(head, num);
                }
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
    scanf("%s[^\n]", name);
    scanf("%s[^\n]", intro);
    int num = 0;
    // 获取当前序号
    VIEW *end = head;
    while (end->next)
    {
        num = num + 1;
        end = end->next;
    }
    while ((strcmp(name, "0") & strcmp(intro, "0")))
    {
        printf("%s %s", name, intro);
        VIEW *temp = crate_view(num, name, intro);
        end->next = temp;
        end = end->next;
        printf("继续添加\n");
        scanf("%s[^\n]", name);
        scanf("%s[^\n]", intro);
    }
    return head;
}
VIEW *delete_view_name(VIEW *head, char name[30])
{
    for (VIEW *temp = head; temp->next; temp = temp->next)
    {
        VIEW *temp_next = temp->next;
        if (!strcmp(temp_next->name, name))
        {
            temp_next = temp_next->next;
            temp->next = temp_next;
            write_view(head);
            printf("删除成功\n");
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
        if (num == 0)
        {
            VIEW *temp_next = temp->next;
            if (temp_next->next)
            {
                temp_next = temp_next->next;
                temp->next = temp_next;
                write_view(head);
                printf("删除成功\n");
                return head;
            }
            else
            {
                temp->next = NULL;
                write_view(head);
                printf("删除成功\n");
                return head;
            }
        }
        temp = temp->next;
        num--;
    }
    return head;
}
VIEW *modefy_view(VIEW *head)
{
    printf("请输入要修改的景点的序号\n");
    int index;
    scanf("%d", &index);
    if (index > get_row())
    {
        printf("序号不能大于景点最大序号\n");
        return head;
    }
    printf("修改名称按1,修改介绍按2,任意键退出\n");
    int method = 3;
    scanf("%d", &method);
    if (method == 1)
    {
        char name[40];
        printf("请输入新的名称");
        scanf("%s", name);
        int i = 0;
        for (VIEW *temp = head->next; temp; temp = temp->next)
        {
            if (i == index)
                strcpy(temp->name, name);
            i++;
        }
        return head;
    }
    else if (method == 2)
    {
        char intro[100];
        printf("请输入新的介绍");
        scanf("%s", intro);
        int i = 0;
        for (VIEW *temp = head->next; temp; temp = temp->next)
        {
            if (i == index)
                strcpy(temp->intro, intro);
            i++;
        }
        return head;
    }
    else
        return head;
}
