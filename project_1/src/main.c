//main.c
#include "show_bmp.h" //包含show_bmp函数的声明

#include "change_bmp.h"


int main(void)
{
    show_bmp("./0.bmp"); //调用show_bmp函数，显示菜单.bmp
    while(1) //添加一个循环，以实现动态地切换图片
    {
        change_bmp(); //调用change_bmp函数，根据用户的触摸坐标切换不同的bmp图片
    }
    
    return 0;
}
