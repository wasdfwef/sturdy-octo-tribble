//change_bmp.c
#include "change_bmp.h"
#include "show_bmp.h"
#include <fcntl.h> //包含open函数的定义
#include <unistd.h> //包含read, close函数的定义
#include <string.h> //包含strcmp函数的定义
#include <linux/input.h> //包含input_event结构体和EV_ABS、ABS_X、ABS_Y、EV_KEY、BTN_TOUCH等宏的定义
#include <linux/uinput.h> //包含uinput_user_dev结构体的定义

//定义一个结构体，用于存储触摸坐标
struct touch_pos {
	int x;
	int y;
};

//定义一个函数，用于获取用户的触摸坐标
struct touch_pos get_touch_pos(void)
{
	struct touch_pos pos;
	
	//打开触摸屏的设备文件
	int ts_fd = open("/dev/input/event0", O_RDWR);
	
	//读取触摸屏数据
	struct input_event ts;
	
	while(1)
	{
		read(ts_fd, &ts, sizeof(ts));	
	
		//分析触摸屏数据
		if(ts.type == EV_ABS &&  ts.code == ABS_X)  //事件为触摸屏的x坐标
			pos.x = ts.value;
		
		if(ts.type == EV_ABS &&  ts.code == ABS_Y)  //事件为触摸屏的y坐标
			pos.y = ts.value;
		
		if(ts.type == EV_KEY &&  ts.code == BTN_TOUCH) //事件为触摸屏按下和松开的事件
		{
			if(ts.value == 0) //如果用户松开了触摸屏
			{
				break; //跳出循环
			}
		} 
	}
	
	//关闭触摸屏
	close(ts_fd);
	
	return pos; //返回用户的触摸坐标
}

//定义一个函数，用于判断用户是否点击了"杂食"对应的区域
int is_food_clicked(void)
{
	struct touch_pos pos = get_touch_pos(); //获取用户的触摸坐标
	
	//判断用户的触摸坐标是否在"杂食"区域内
	if (pos.x >= 0 && pos.x <= 100 && pos.y >= 0 && pos.y <= 100)
	{
		return 1; //返回1表示点击了"杂食"
	}
	else
	{
		return 0; //返回0表示没有点击"杂食"
	}
}

//定义一个函数，用于根据用户的触摸坐标切换不同的bmp图片
void change_bmp(void)
{
    //定义一个变量，用于存储当前显示的图片名称
    char *current_bmp = "./1.bmp";

    while (1) //无限循环
    {
        if (is_food_clicked()) //如果用户点击了"杂食"
        {
            if (strcmp(current_bmp, "./1.bmp") == 0) //如果当前显示的是菜单.bmp
            {
                show_bmp("./2.bmp"); //显示杂食.bmp
                current_bmp = "./2.bmp"; //更新当前显示的图片名称
            }
            else if (strcmp(current_bmp, "./2.bmp") == 0) //如果当前显示的是杂食.bmp
            {
                show_bmp("./1.bmp"); //显示菜单.bmp
                current_bmp = "./1.bmp"; //更新当前显示的图片名称
            }
        }
        //TODO: 添加其他判断条件和操作，例如点击其他区域或商品时的处理逻辑
    }
}
