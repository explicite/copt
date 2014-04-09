CC		= clang
SRC 	= "./src"
BUILD 	= "./build"
CFLAGS 	= -O3

all: mk fun gwo test lib

lib: 
	$(CC) $(CFLAGS) \
	$(BUILD)/fun.o \
	$(BUILD)/gwo.o \
	$(BUILD)/test.o -lm -openmp -o test.out

test:
	$(CC) -c $(CFLAGS) $(SRC)/test.c -o $(BUILD)/test.o

gwo:
	$(CC) -c $(CFLAGS) $(SRC)/gwo.c -o $(BUILD)/gwo.o

fun:
	$(CC) -c $(CFLAGS) $(SRC)/fun.c -o $(BUILD)/fun.o

clean:
	rm -rf $(BUILD)
	rm ./test.out

mk:
	mkdir -p $(BUILD)