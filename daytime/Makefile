CC = gcc
#定义编译选项，I引入头部文件
#CFLAGS = -I../lib -g -O2 -D_REENTRANT -Wall
#定义链接库变量
LIBS = -lpthread
PROGS = tcpcli tcpserv
      
#会自动检查每个依赖的，然后找到其对应的。c文件，生成。o文件
all:    ${PROGS}
tcpcli: tcpcli.o str_cli.o
	${CC} ${CFLAGS} -o $@ $? ${LIBS}
tcpserv: tcpserv.o str_echo.o sigchldwaitpid.o
	${CC} ${CFLAGS} -o $@ $? ${LIBS}
