#ifndef SHOW_BMP_H
#define SHOW_BMP_H

//声明一个变量，用于存储LCD的文件描述符
extern int lcd_fd;

//声明一个指针，用于指向内存映射的地址
extern int *mp;

//声明一个函数，用于显示指定的bmp图片

void change_bmp();


#endif
