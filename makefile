all:
	g++ chew.cpp -o chew

.PHONY : clean
clean:
	rm -f chew
