PRJ=$(shell basename $(CURDIR))

$(PRJ):
		gcc includes/*.h src/*.c -o bin/$(PRJ) -lm -lrt -lpthread

clean:
		rm bin/* output/*.txt
