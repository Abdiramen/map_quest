CPP=clang++
CFLAGS=
LDFLAGS=-lncurses
HEADERS=$(wildcard:*.h)

map_quest: map.o wall.o
	${CPP} ${CFLAGS} ${LDFLAGS} $^ -o $@

%.o: %.cpp ${HEADERS}
	${CPP} ${CFLAGS} -c $<

.PHONY:clean
clean:
	-@ rm *.o
	-@ rm map_quest
