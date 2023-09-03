exec = interpreter.out

sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./interpreter.out /usr/local/bin/myLang

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o

rebuild:
	make clean
	make

run:
	make rebuild
	clear
	./$(exec)
