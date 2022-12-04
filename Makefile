CXX=g++
CXXFLAGS=-std=c++14 -MMD -Werror=vla
OBJECTS=main.o Board.o Piece.o King.o Pawn.o Knight.o SlidingPieces.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=a4q2

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
