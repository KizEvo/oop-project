CC=g++
CPPFLAGS=-Wall -Wextra -g -O0 -Iinc/ -I.

SRCDIR=src/
BUILDDIR=build/

SRCFILES=${wildcard ${SRCDIR}*.cpp}
OBJFILES=${patsubst ${SRCDIR}%.cpp,${BUILDDIR}%.o, ${SRCFILES}}
BUILDFILES=${BUILDDIR}out.exe

all: ${BUILDFILES}

${BUILDFILES}: ${OBJFILES}
	${CC} ${CPPFLAGS} -o $@ $^

${BUILDDIR}%.o: ${SRCDIR}%.cpp
	${CC} ${CPPFLAGS} -c -o $@ $^

run:
	@./${BUILDFILES}

clean:
	rm -rf ${OBJFILES} ${BUILDFILES}

help:
	@echo	"'make'"\	\	-\> build source files
	@echo "'make run'"\	-\> run the executable file \(build sources files first\)
	@echo "'make clean'"\	-\> delete the executable and object files
