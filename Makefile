CXX=g++
INCLUDE:=${INCLUDE} -Iinclude
LIBS=-ldl -lglfw
CXXFLAGS:=${CXXFLAGS} -Wall -Wextra -Wpedantic -fno-trapping-math -fno-math-errno -fno-signed-zeros -march=native -falign-functions=16 -lstdc++fs -std=c++20
SRCS=$(shell find . | grep \\.cpp$)
HDRS=$(shell find . | grep \\.hpp$)
OBJS=$(SRCS:.cpp=.cpp.o)
OPTS=-L"/usr/lib" include/audio/libIrrKlang.so -pthread

.PHONY: debug release clean

# will build debug as default because its at the top
debug: CXXFLAGS += -g
debug: a.out

release: CXXFLAGS += -O2
release: a.out
	strip -s a.out

a.out: $(OBJS) include/glad.c
	$(CXX) $(OBJS) include/glad.c $(CXXFLAGS) $(LIBS) $(OPTS)

%.cpp.o: %.cpp $(HDRS) Makefile
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDE)

clean:
	rm -f $(OBJS) a.out