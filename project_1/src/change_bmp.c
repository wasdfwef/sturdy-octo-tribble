//change_bmp.c
#include "show_bmp.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <linux/input.h>

#define WIDTH 800
#define HEIGHT 480



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

//定义一个函数，用于根据触摸坐标显示不同的图片
void change_bmp(void)
{
    //获取用户的触摸坐标
    struct touch_pos pos = get_touch_pos();

    //判断用户点击了哪个区域
    if (pos.x >= 0 && pos.x <= 100 && pos.y >= 0 && pos.y <= 480) //如果用户点击了广告页面左边的"点击购买商品"字样
    {
        //显示首页界面的图片
        show_bmp("1.bmp");
    }
    else if (pos.x >= 0 && pos.x <= 100 && pos.y >= 0 && pos.y <= 100) //如果用户点击了导航栏的"杂食"
    {
        //显示杂食的图片
        show_bmp("0.bmp");
    }
    else if (pos.x >= 0 && pos.x <= 100 && pos.y >= 120 && pos.y <= 220) //如果用户点击了导航栏的"餐具"
    {
        //显示餐具的图片
        show_bmp("2.bmp");
    }
    else if (pos.x >= 0 && pos.x <= 100 && pos.y >= 240 && pos.y <= 340) //如果用户点击了导航栏的"用具"
    {
        //显示用具的图片
        show_bmp("3.bmp");
    }
    else if (pos.x >= 560 && pos.x <= 760 && pos.y >= 400 && pos.y <= 480) //如果用户点击了结算
    {
        //显示结算的图片
        show_bmp("m.bmp");
    }
}
