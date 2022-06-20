CC=gcc
CFLAGS=-Wall
32BIT=-m32
64BIT=-m64
DISFORMAT=-Wno-format
BUILD=build
SRC=src

# Normal compilation
%: $(SRC)/%.c $(SRC)/config.h
	$(CC) $(CFLAGS) $(32BIT) $^ -o $(BUILD)/$@
	chmod +x $(BUILD)/*
	./$(BUILD)/$@

install:
	mkdir -p $(BUILD) 2>/dev/null
	mkdir -p $(SRC) 2>/dev/null
	touch $(SRC)/config.h 2>/dev/null
	chmod +x $(BUILD)/* 2>/dev/null

clean:
	rm -rf src/hello hello build/* src/*.o *.x test demo *.o 2>/dev/null

check:
	find ./ -type f 2>/dev/null

malicious:
	gcc -ldl $(SRC)/malicious.c -fPIC -shared -D_GNU_SOURCE -o $(BUILD)/malicious.so