DIR=./

TARGET=main
CXX=g++
FLAGS=-std=c++11 -lcurses -o
main: ./src/*.hpp
	${CXX} ${FLAGS} ${TARGET} src/main.cpp -I ${DIR}
