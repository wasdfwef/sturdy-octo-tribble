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

int lcd_fd = -1;
int *mp = NULL;

//定义一个结构体，用于存储触摸坐标
struct touch_pos {
    int x;
    int y;
};

//定义一个函数，用于显示指定的bmp图片
void show_bmp(char *bmp_name)
{
    //打开LCD，路径：/dev/fb0
    lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd < 0)
    {
        perror("open lcd failed");
        return;
    }
    //内存映射
    mp = mmap(NULL, WIDTH * HEIGHT * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    if (mp == NULL)
    {
        perror("mmap failed");
        return;
    }

    //打开bmp图片
    int bmp_fd = open(bmp_name, O_RDWR);
    if (bmp_fd < 0)
    {
        perror("open bmp failed");
        return;
    }
    //偏移54字节（因为前54不是图片数据）
    lseek(bmp_fd, 54, SEEK_SET);

    //读取bmp数据
    char bmp_buf[WIDTH * HEIGHT * 3];
    //char color_buf[WIDTH * HEIGHT * 4]; //删除这个未使用的变量

    read(bmp_fd, bmp_buf, sizeof(bmp_buf));

    int x, y;
    int color;
    int i = 0;
    unsigned char r, g, b;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            b = bmp_buf[i++];
            g = bmp_buf[i++];
            r = bmp_buf[i++];
            color = b | g << 8 | r << 16;
            *(mp + 800 * (479 - y) + x) = color;
        }
    }
    //关闭bmp
    close(bmp_fd);

	//关闭lcd
	close(lcd_fd);
	//解除映射
	munmap(mp,WIDTH*HEIGHT*4);
}

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
