//change_bmp.c
#include "show_bmp.h"
#include "font.h" //包含字库头文件

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <unistd.h> 
#define WIDTH 800
#define HEIGHT 480

//定义一个全局变量num，初始值为0
int num= 0 ;
int num1= 0;
int num2= 0;
int num3= 0;
int num4= 0;
int num5= 0;


int z1=0, flag1=0;
int z2=0, flag2=0;
int z3=0, flag3=0;
unsigned char z1_str[3]={0}; 
unsigned char z2_str[3]={0}; 
unsigned char z3_str[3]={0}; 

int nums=0;


//定义一个字符数组，用于存储num变量的值
unsigned char num_str[3]={0}; 
unsigned char num_str1[3]={0}; 
unsigned char num_str2[3]={0}; 
unsigned char num_str3[3]={0}; 
unsigned char num_str4[3]={0}; 
unsigned char num_str5[3]={0}; 


unsigned char num_strs[4]={0}; 


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

//显示总价
void all(){
	Init_Font();
	   nums=num+num1*3+num2*5+num3*7+num4*10+num5*4+z1*7+z2*5+z3*3;
           
    
	
       //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
      sprintf((char *)num_strs, "%d", nums); 
       Clean_Area(340,  
               400,  
			   110, 
			   80,
			   0xFFFFFFFF); 

    //显示num的值在数量的位置上
    Display_characterX(340, 400, num_strs, 0xFF, 4);
	UnInit_Font(); 

}

//定义一个函数，用于根据触摸坐标显示不同的图片
void change_bmp(void)
{
    //获取用户的触摸坐标
    struct touch_pos pos = get_touch_pos();

    //判断用户点击了哪个区域
    if (pos.x >= 0 && pos.x <= 100 && pos.y >= 350 && pos.y <= 480) //如果用户点击了广告页面左边的"点击购买商品"字样
    {
		Init_Font();
        flag1=0;
          flag2=0;
            flag3=0;
        //显示首页界面的图片
        show_bmp("1.bmp");
		
		 Display_characterX(200, 160, num_str, 0xFF, 2);
		 Display_characterX(420, 160, num_str1, 0xFF, 2);
		 Display_characterX(640, 160, num_str2, 0xFF, 2);
	   Display_characterX(200, 360, num_str3, 0xFF, 2);
	   Display_characterX(640, 360, num_str5, 0xFF, 2);
	   Display_characterX(420, 360, num_str4, 0xFF, 2);
	   all();
       UnInit_Font();
    }




     //如果用户点击了导航栏的"杂食"
   if (pos.x >= 50 && pos.x <= 100 && pos.y >= 0 && pos.y <= 100)
    {
        //显示杂食的图片
		 Init_Font();
      show_bmp("1.bmp");
       Display_characterX(200, 160, num_str, 0xFF, 2);
		  Display_characterX(420, 160, num_str1, 0xFF, 2);
		  Display_characterX(640, 160, num_str2, 0xFF, 2);
	    Display_characterX(200, 360, num_str3, 0xFF, 2);
	    Display_characterX(640, 360, num_str5, 0xFF, 2);
	    Display_characterX(420, 360, num_str4, 0xFF, 2);
	    all();
		UnInit_Font();
    }




    //如果用户点击了导航栏的"餐具"
     if (pos.x >= 50 && pos.x <= 100 && pos.y >= 120 && pos.y <= 220) 
    { 
		Init_Font();
    //显示餐具的图片
    show_bmp("2.bmp");        

    flag1=1;
           flag2=1;
            flag3=1;                  
     
      Display_characterX(200, 160, z1_str, 0xFF, 2);
		   Display_characterX(420, 160, z2_str, 0xFF, 2);
		   Display_characterX(640, 160, z3_str, 0xFF, 2);
	 
     all();
		UnInit_Font();
    }


    //如果用户点击了导航栏的"用具"
    if (pos.x >= 50 && pos.x <= 100 && pos.y >= 240 && pos.y <= 340) //如果用户点击了导航栏的"用具"
    {
		Init_Font();
   
        //显示用具的图片
        show_bmp("3.bmp");
		   
	 all();
	UnInit_Font();
    }
    if (pos.x >= 560 && pos.x <= 760 && pos.y >= 400 && pos.y <= 480) //如果用户点击了结算
    {
        //显示结算的图片
		   Init_Font();
        show_bmp("m.bmp");
		
	    all();
			UnInit_Font();
      
       sleep(2); //延时2秒
      show_bmp("w.bmp");
      sleep(2); //延时2秒
      show_bmp("c.bmp");
      sleep(1); //延时1秒
      show_bmp("1.bmp");
     num= 0 ;
     num1= 0;
     num2= 0;
     num3= 0;
     num4= 0;
     num5= 0;
     z1=0;
     z2=0;
     z3=0;
    nums=0;
    sprintf((char *)num_str, "%d", 0);
    sprintf((char *)num_str1, "%d", 0);
    sprintf((char *)num_str2, "%d", 0);
    sprintf((char *)num_str3, "%d", 0);
    sprintf((char *)num_str4, "%d", 0);
    sprintf((char *)num_str5, "%d", 0);
    sprintf((char *)z1_str, "%d", 0);
    sprintf((char *)z2_str, "%d", 0);
    sprintf((char *)z3_str, "%d", 0);

    }



//位置一
if(flag1==0){
    if (pos.x >= 120 && pos.x <= 200 && pos.y >= 160 && pos.y <= 200) //如果用户点击了减号
       {
       Init_Font();
        //判断num是否大于0，如果是，就减1
          if (num > 0)
         {
        num--;
           }
	
     //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
       sprintf((char *)num_str, "%d", num);

         //清空显示位置的背景颜色
	      Clean_Area(200,  
               160,  
			   40, 
			   30,
			   0xFFFFFFFF); 
         //显示num的值在数量的位置上
         Display_characterX(200, 160, num_str, 0xFF, 2);
		   
		  all();
	    UnInit_Font();
     }

    if (pos.x >= 240 && pos.x <= 320 && pos.y >= 160 && pos.y <= 200) //如果用户点击了加号
      {
            Init_Font();
         //判断num是否小于99，如果是，就加1
           if (num < 99)
          {
        num++;
         }
	
          //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
        sprintf((char *)num_str, "%d", num); 
         Clean_Area(200,  
               160,  
			   40, 
			   30,
			   0xFFFFFFFF); 

         //显示num的值在数量的位置上
        Display_characterX(200, 160, num_str, 0xFF, 2);

	         all();
	         UnInit_Font(); 
       }

}

if(flag1==1){
            if (pos.x >= 120 && pos.x <= 200 && pos.y >= 160 && pos.y <= 200) //如果用户点击了减号
                               {
                              
                        //判断num是否大于0，如果是，就减1
                          if (z1 > 0)
                          {
                             z1--;
                        }
	
               //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
                  sprintf((char *)z1_str, "%d", z1); 

               //清空显示位置的背景颜色
	             Clean_Area(200,  
                  160,  
			            40, 
			            30,
			            0xFFFFFFFF); 
                   //显示num的值在数量的位置上
                    Display_characterX(200, 160, z1_str, 0xFF, 2);
		       
		              all();
	                   
                       }
		                               


        if (pos.x >= 240 && pos.x <= 320 && pos.y >= 160 && pos.y <= 200) //如果用户点击了加号
                       {
            
                    //判断num是否小于99，如果是，就加1
                      if (z1 < 99)
                     {
                     z1++;
                    }
	
               //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
                sprintf((char *)z1_str, "%d", z1); 
                Clean_Area(200,  
               160,  
			          40, 
			           30,
			              0xFFFFFFFF); 
 
               //显示num的值在数量的位置上
              Display_characterX(200, 160, z1_str, 0xFF, 2);

	              all();

               }

    
  }


//位置二



if(flag2==0){
if (pos.x >= 340 && pos.x <= 420 && pos.y >= 160 && pos.y <= 200)//如果用户点击了减号
    {
       Init_Font();
        //判断num是否大于0，如果是，就减1
          if (num1 > 0)
         {
        num1--;
           }
	
     //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
       sprintf((char *)num_str1, "%d", num1);

         //清空显示位置的背景颜色
	      Clean_Area(420,  
               160,  
			   40, 
			   30,
			   0xFFFFFFFF); 
         //显示num的值在数量的位置上
         Display_characterX(420, 160, num_str1, 0xFF, 2);
	
		  all();
	    UnInit_Font();
    }

    if (pos.x >= 460 && pos.x <= 540 && pos.y >= 160 && pos.y <= 200)//如果用户点击了加号
    {
            Init_Font();
       //判断num是否小于99，如果是，就加1
           if (num1 < 99)
          {
        num1++;
         }
	
       //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
      sprintf((char *)num_str1, "%d", num1); 
       Clean_Area(420,  
               160,  
			   40, 
			   30,
			   0xFFFFFFFF); 

    //显示num的值在数量的位置上
    Display_characterX(420, 160, num_str1, 0xFF, 2);
 
	 all();
	UnInit_Font(); 
    }
}


if(flag2==1){
if (pos.x >= 340 && pos.x <= 420 && pos.y >= 160 && pos.y <= 200)//如果用户点击了减号
    {
       Init_Font();
        //判断num是否大于0，如果是，就减1
          if (z2 > 0)
         {
        z2--;
           }
	
     //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
       sprintf((char *)z2_str, "%d", z2);

         //清空显示位置的背景颜色
	      Clean_Area(420,  
               160,  
			   40, 
			   30,
			   0xFFFFFFFF); 
         //显示num的值在数量的位置上
         Display_characterX(420, 160, z2_str, 0xFF, 2);
	
		  all();
	    UnInit_Font();
    }

    if (pos.x >= 460 && pos.x <= 540 && pos.y >= 160 && pos.y <= 200)//如果用户点击了加号
    {
            Init_Font();
       //判断num是否小于99，如果是，就加1
           if (z2 < 99)
          {
        z2++;
         }
	
       //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
      sprintf((char *)z2_str, "%d", z2); 
       Clean_Area(420,  
               160,  
			   40, 
			   30,
			   0xFFFFFFFF); 

    //显示num的值在数量的位置上
    Display_characterX(420, 160, z2_str, 0xFF, 2);
 
	 all();
	UnInit_Font(); 
    }
}

//位置三



if(flag3==0){
 if (pos.x >= 560 && pos.x <= 640   && pos.y >= 160 && pos.y <= 200)//如果用户点击了减号
    {
       Init_Font();
        //判断num是否大于0，如果是，就减1
          if (num2 > 0)
         {
        num2--;
           }
	
     //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
       sprintf((char *)num_str2, "%d", num2);

         //清空显示位置的背景颜色
	      Clean_Area(640,  
               160,  
			   40, 
			   30,
			   0xFFFFFFFF); 
         //显示num的值在数量的位置上
         Display_characterX(640, 160, num_str2, 0xFF, 2);
		
		  all();
	    UnInit_Font();
    }

    if (pos.x >= 680 && pos.x <= 760 && pos.y >= 160 && pos.y <= 200)//如果用户点击了加号
    {
            Init_Font();
       //判断num是否小于99，如果是，就加1
           if (num2 < 99)
          {
        num2++;
         }
	
       //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
      sprintf((char *)num_str2, "%d", num2); 
       Clean_Area(640,  
               160,  
			   40, 
			   30,
			   0xFFFFFFFF); 

    //显示num的值在数量的位置上
    Display_characterX(640, 160, num_str2, 0xFF, 2);
	
	 all();
	UnInit_Font(); 
    }

}

if(flag3==1){
 if (pos.x >= 560 && pos.x <= 640   && pos.y >= 160 && pos.y <= 200)//如果用户点击了减号
    {
       Init_Font();
        //判断num是否大于0，如果是，就减1
          if (z3 > 0)
         {
        z3--;
           }
	
     //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
       sprintf((char *)z3_str, "%d", z3);

         //清空显示位置的背景颜色
	      Clean_Area(640,  
               160,  
			   40, 
			   30,
			   0xFFFFFFFF); 
         //显示num的值在数量的位置上
         Display_characterX(640, 160, z3_str, 0xFF, 2);
		
		  all();
	    UnInit_Font();
    }

    if (pos.x >= 680 && pos.x <= 760 && pos.y >= 160 && pos.y <= 200)//如果用户点击了加号
    {
            Init_Font();
       //判断num是否小于99，如果是，就加1
           if (z3 < 99)
          {
        z3++;
         }
	
       //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
      sprintf((char *)z3_str, "%d", z3); 
       Clean_Area(640,  
               160,  
			   40, 
			   30,
			   0xFFFFFFFF); 

    //显示num的值在数量的位置上
    Display_characterX(640, 160, z3_str, 0xFF, 2);
	
	 all();
	UnInit_Font(); 
    }

}



//位置四




 if  (pos.x >= 120 && pos.x <= 200 && pos.y >= 360 && pos.y <= 400)//如果用户点击了减号
    {
       Init_Font();
        //判断num是否大于0，如果是，就减1
          if (num3 > 0)
         {
        num3--;
           }
	
     //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
       sprintf((char *)num_str3, "%d", num3);

         //清空显示位置的背景颜色
	      Clean_Area(200,  
               360,  
			   40, 
			   30,
			   0xFFFFFFFF); 
         //显示num的值在数量的位置上
         Display_characterX(200, 360, num_str3, 0xFF, 2);
		
		  all();
	    UnInit_Font();
    }

    if (pos.x >= 240 && pos.x <= 320 && pos.y >= 360 && pos.y <= 400)//如果用户点击了加号
    {
            Init_Font();
       //判断num是否小于99，如果是，就加1
           if (num3 < 99)
          {
        num3++;
         }
	
       //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
      sprintf((char *)num_str3, "%d", num3); 
       Clean_Area(200,  
               360,  
			   40, 
			   30,
			   0xFFFFFFFF); 

    //显示num的值在数量的位置上
    Display_characterX(200, 360, num_str3, 0xFF, 2);
	
	 all();
	UnInit_Font(); 
    }

//位置五

 if  (pos.x >= 340 && pos.x <= 420 && pos.y >= 360 && pos.y <= 400)//如果用户点击了减号
    {
       Init_Font();
        //判断num是否大于0，如果是，就减1
          if (num4 > 0)
         {
        num4--;
           }
	
     //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
       sprintf((char *)num_str4, "%d", num4);

         //清空显示位置的背景颜色
	      Clean_Area(420,  
               360,  
			   40, 
			   30,
			   0xFFFFFFFF); 
         //显示num的值在数量的位置上
         Display_characterX(420, 360, num_str4, 0xFF, 2);
		  
		  all();
	    UnInit_Font();
    }

    if (pos.x >= 460 && pos.x <= 540 && pos.y >= 360 && pos.y <= 400)//如果用户点击了加号
    {
            Init_Font();
       //判断num是否小于99，如果是，就加1
           if (num4 < 99)
          {
        num4++;
         }
	
       //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
      sprintf((char *)num_str4, "%d", num4); 
       Clean_Area(420,  
               360,  
			   40, 
			   30,
			   0xFFFFFFFF); 

    //显示num的值在数量的位置上
    Display_characterX(420, 360, num_str4, 0xFF, 2);

	 all();
	UnInit_Font(); 
    }

//位置六




 if  (pos.x >= 560 && pos.x <= 640 && pos.y >= 360 && pos.y <= 400)//如果用户点击了减号
    {
       Init_Font();
        //判断num是否大于0，如果是，就减1
          if (num5 > 0)
         {
        num5--;
           }
	
     //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
       sprintf((char *)num_str5, "%d", num5);

         //清空显示位置的背景颜色
	      Clean_Area(640,  
               360,  
			   40, 
			   30,
			   0xFFFFFFFF); 
         //显示num的值在数量的位置上
         Display_characterX(640, 360, num_str5, 0xFF, 2);
		
		  all();
	    UnInit_Font();
    }

    if (pos.x >= 680 && pos.x <= 760 && pos.y >= 360 && pos.y <= 400)//如果用户点击了加号
    {
            Init_Font();
       //判断num是否小于99，如果是，就加1
           if (num5< 99)
          {
        num5++;
         }
	
       //使用sprintf函数，将num变量的值转换为一个字符串，并且存储在num_str数组中
      sprintf((char *)num_str5, "%d", num5); 
       Clean_Area(640,  
               360,  
			   40, 
			   30,
			   0xFFFFFFFF); 

    //显示num的值在数量的位置上
    Display_characterX(640, 360, num_str5, 0xFF, 2);
	 
	
	 all();
	 
	UnInit_Font(); 
    }


    else //如果用户点击了其他区域
    {
        //显示提示信息
        show_bmp("tip.bmp");
        //或者重新获取触摸坐标
        change_bmp();
    }
}
