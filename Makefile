CC = g++
CFLAGS = -Wall -Wno-unused-variable -Wno-sign-compare

SOURCES = SimCity_Project1.cpp Cell.cpp gameBoard.cpp Residential.cpp Commercial.cpp Industrial.cpp firstResponse.cpp Hospital.cpp Season.cpp Tornado.cpp unitTesting.cpp
HEADERS = Cell.h gameBoard.h Residential.h Commercial.h Industrial.h firstResponse.h Hospital.h Season.h Tornado.h unitTesting.h
OBJECTS = $(SOURCES:.cpp=.o)

all: Simcity

Simcity: $(OBJECTS)
	$(CC) $(CFLAGS) -o Simcity $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) Simcity
