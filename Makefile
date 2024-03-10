#指定编译器
CC = g++

#找出当前目录下，所有的源文件（以.cpp结尾）
SRCS := $(shell find ./* -type f | grep '\.cpp' | grep -v 'main\.cpp' | grep -v '\./server\.cpp' | grep -v '\./client\.cpp' | grep -v 'cmake')
$(warning SRCS is ${SRCS})

#确定cpp源文件对应的目标文件
OBJS := $(patsubst %.cpp, %.o, $(filter %.cpp, $(SRCS)))
$(warning OBJS is ${OBJS})

#编译选项
CFLAGS = -g -O2 -Wall -Werror -Wno-unused -ldl -fPIC -std=c++11
$(warning CFLAGS is ${CFLAGS})

#找出当前目录下所有头文件
INCLUDE = -I.

#主程序
SRC_SERVER = server.cpp
OBJ_SERVER = ${SRC_SERVER:%.cpp=%.o}
EXE_SERVER = server

SRC_CLIENT = client.cpp
OBJ_CLIENT = ${SRC_CLIENT:%.cpp=%.o}
EXE_CLIENT = client

target: ${EXE_SERVER} ${EXE_CLIENT}

$(EXE_SERVER): $(OBJ_SERVER) $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDE)

$(EXE_CLIENT): $(OBJ_CLIENT) $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDE)

%.o: %.cpp
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

clean:
	rm -f ${OBJS} ${EXE_SERVER} ${OBJ_SERVER} ${EXE_CLIENT} ${OBJ_CLIENT}
