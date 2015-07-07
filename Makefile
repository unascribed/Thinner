thinner:
	gcc -std=c99 thinner.c -o thinner -lIL -lm

clean:
	rm thinner

all: clean thinner

