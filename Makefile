all: main.c
	 gcc -O0 -g -o i2t main.c -I.

clean:
	rm i2t

test:
	./i2t 1
	./i2t 10
	./i2t 11
	./i2t 78
	./i2t 100
	./i2t 111
	./i2t 134
	./i2t 1000
	./i2t 1111
	./i2t 1245
	./i2t 1001
	./i2t 1345234535
	./i2t 134523452345
	./i2t 16784353546578
