#Makefile

#定义编译器和编译选项
CC = gcc
CFLAGS = -Wall -g

#定义目标文件和依赖文件
TARGET = ../bin/main #可执行文件名，放在bin文件夹中
OBJS = src/main.o src/show_bmp.o src/change_bmp.o #目标文件名，放在src文件夹中


#定义默认规则，生成可执行文件
all: $(TARGET)

#定义链接规则，将目标文件链接成可执行文件，并复制到bin文件夹中
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

#定义编译规则，将源代码文件编译成目标文件，并放在src文件夹中
src/%.o: src/%.c src/%.h #匹配有对应头文件的源代码文件
	$(CC) $(CFLAGS) -c -o $@ $<

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/main.o: src/main.c #main.c不需要头文件
	$(CC) $(CFLAGS) -c -o $@ $<

src/show_bmp.o: src/show_bmp.c src/show_bmp.h #show_bmp.c需要show_bmp.h
	$(CC) $(CFLAGS) -c -o $@ $<

src/change_bmp.o: src/change_bmp.c src/change_bmp.h #change_bmp.c需要change_bmp.h
	$(CC) $(CFLAGS) -c -o $@ $<


#定义清理规则，删除生成的可执行文件和目标文件
clean:
	-rm -f $(TARGET) #删除可执行文件
	-rm -f $(OBJS) #删除目标文件
