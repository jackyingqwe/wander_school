#include "heads.h"

int main()
{
    char filepath[50] = {"G:/college file/out_work/cowander/view.txt"};
    // 输出主菜单
    printMenu();
    // 选择功能（路线与景点两部分）
    select_fun(filepath);
    //makeroad();
    // init_dowandbeati();
    return 0;
}