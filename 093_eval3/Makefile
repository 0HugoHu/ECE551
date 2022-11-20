OBJS	= cyoa-step1.o Tool.o Page.o
SOURCE	= cyoa-step1.cpp Page.cpp Tool.cpp
HEADER	= Page.hpp Tool.hpp
OUT	= cyoa-step1
CC	 = g++
FLAGS	 = -g -c -pedantic -Wall -Werror -ggdb3
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

cyoa-step1.o: cyoa-step1.cpp
	$(CC) $(FLAGS) cyoa-step1.cpp -std=gnu++98

Tool.o: Tool.cpp
	$(CC) $(FLAGS) Tool.cpp -std=gnu++98

Page.o: Page.cpp
	$(CC) $(FLAGS) Page.cpp -std=gnu++98

clean:
	rm -f $(OBJS) $(OUT)
