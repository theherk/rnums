rnums:
	g++ *.cpp -o rnums

clean:
	rm -f rnums

run: rnums
	./rnums
