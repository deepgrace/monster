# Makefile

CXX = g++
BIN = monster
SOURCE = main.cpp
CXXFLAGS = -I . -m64 -std=c++2a -s -Wall -Os -fconcepts

${BIN}: ${SOURCE}
	${CXX} ${CXXFLAGS} ${LDLIBS} -o $@ $^

clean:
	rm -f ${BIN}
