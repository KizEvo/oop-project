INCDIR=inc/
SRCDIR=src/
BUILDDIR=build/

CC=g++
CPPFLAGS=-Wall -Wextra -std=c++14 -g -O0 -I${INCDIR} -I.

SRCFILES=${wildcard ${SRCDIR}*.cpp}
OBJFILES=${patsubst ${SRCDIR}%.cpp,${BUILDDIR}%.o, ${SRCFILES}}
BUILDFILES=${BUILDDIR}out.exe

all: ${BUILDFILES}

${BUILDFILES}: ${OBJFILES}
	${CC} ${CPPFLAGS} -o $@ $^

${BUILDDIR}%.o: ${SRCDIR}%.cpp | ${BUILDDIR}
	${CC} ${CPPFLAGS} -c -o $@ $^

${BUILDDIR}: | ${INCDIR}
	@mkdir $@

${INCDIR}: 
	@mkdir $@

run:
	@./${BUILDFILES}

clean:
	rm -rf ${OBJFILES} ${BUILDFILES}

help:
	@echo	"'make'"\	\	-\> build source files
	@echo "'make run'"\	-\> run the executable file \(build sources files first\)
	@echo "'make clean'"\	-\> delete the executable and object files
