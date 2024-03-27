CC=gcc
FLAGS=-Wall -Werror
OBJS=mtll.o main.o
TARGET=mtll
CFILE=main.c mtll.c
TESTDIR=tests

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

build: ${TARGET}

tests: $(TARGET)

.PHONY:
run_tests: tests
	bash run_tests.sh ${TESTDIR}

.PHONY:
clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

build_debug:
	$(CC) -fsanitize=address -g -o ${TARGET} ${CFILE}