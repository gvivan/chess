CXX=g++
CXXFLAGS=-std=c++14 -MMD -Werror=vla
OBJECTS=Bishop.o Board.o King.o Knight.o Pawn.o Piece.o Queen.o Rook.o Sliding.o
DEPENDS={OBJECTS:.o=.d}
EXEC=chess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}
.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
