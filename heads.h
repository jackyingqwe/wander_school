#define _CRT_SECURE_NO_WARNINGS 1
#define MAX 12     // 构造最原始的个数
#define INFINE 100 // 无穷大表示两个点不邻接

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
// 顶点信息
typedef struct VIEW
{
    int num;         // 景点代号
    char name[40];   // 景点名称
    char intro[100]; // 景点介绍
    struct VIEW *next;
} VIEW;
// 输出景点名称及详细介绍
void show_view(VIEW *head);
// 构造最原始的景点信息
VIEW *make();
// 新增景点信息
// 将信息从控制台读取
VIEW *crate_view(int num, char name[40], char intro[100]);
// 添加景点信息
// 将信息添加到链表
VIEW *insert_view(VIEW *head);
// 从文件中读取景点链表
VIEW *read_view(char filepath[50]);
// 修改景点信息的函数入口
VIEW *alter_view(VIEW *head);
// 将景点信息的链表写入文件
int write_view(VIEW *head);
// 根据绝对路径读取相对应的csv文件
int *read_csv(char filepath[], int row, int col);
// 构造最原始的景点之间的路径长度
// 在图论中称之为边
int makeroad();
// 将二维数组写入csv文件
void write_2csv(char filepath[], int **p, int row, int col);
// 运行floyd算法，得到最短路径，并写入csv文件
void Floyd(int **p, int row, int col, char file[80]);
int main();
// 输出菜单
void printMenu();
// 选择功能（路线与景点两部分）
void select_fun(char filepath[]);
// 获取景点个数
int get_row();
// 展示两点之间最短路径函数入口
void find_points_path(int **p, int row);
// 输出最短路径的途径地点
void printGraphPath(int i, int j, int row);
// 输出指定位置的景点的名称
void printfname(int i);
// 展示最短路径的长度
// 在图论中称之为边
void show_min_distance(int i, int j, int row);
// 构造最原始的景点的漂亮程度权重
void make_beauti(char filepath[50]);
// 构造最原始的路径阴影权重
void make_shandow(char filepath[50]);
// 初始化树荫、漂亮程度的最短路径
void init_dowandbeati();
// 检验函数，方便遍历二维数组
void printfroad(int **p);
// 根据序号删除景点信息
VIEW *delete_view_num(VIEW *head, int num);
// 根据名称删除景点信息
VIEW *delete_view_name(VIEW *head, char name[30]);
