//show_bmp.c
#include "show_bmp.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define WIDTH 800
#define HEIGHT 480

int lcd_fd = -1;
int *mp = NULL;

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
