all:
	gcc src/*.c -o a.out -lm

clean:
	rm -f a.out
