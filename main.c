#include "heads.h"
int main()
{
    char filepath[50] = {"G:/college file/out_work/cowander/view.txt"};
    // 输出主菜单
    printMenu();
    // 选择功能（路线与景点两部分）
    // for (int i = 0; i < 100; i++)
    select_fun(filepath);
    // 初始化道路
    // makeroad();
    // 初始化美景
    //  init_dowandbeati();
    return 0;
}