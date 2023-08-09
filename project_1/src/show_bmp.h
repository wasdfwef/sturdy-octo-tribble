#ifndef SHOW_BMP_H //如果没有定义SHOW_BMP_H宏
#define SHOW_BMP_H //就定义SHOW_BMP_H宏

//定义一个变量，用于存储LCD的文件描述符
int lcd_fd;

//定义一个指针，用于指向内存映射的地址
int *mp;

//定义一个函数，用于显示指定的bmp图片
void show_bmp(char *bmp_name);
void change_bmp(void); // declare the function change_bmp


#endif //结束条件编译指令
