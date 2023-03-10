SRCS := $(wildcard *.cpp *.hpp)
OBJS := $(SRCS:.cpp=.o)

all: $(OBJS)
	g++ -g -w -o interpreter $(OBJS) -std=c++17

clean:
	rm *.o