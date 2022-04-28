CC=g++
LIBS=-lm --std=c++11

pca: valueIteration.o 
	$(CC) valueIteration.o -o valueIteration $(LIBS)

PCA.o: valueIteration.cpp
	$(CC) valueIteration.cpp -c $(LIBS)




clean:
	@rm -f *.o

install:
	@mv valueIteration ~/bin

run:
	./valueIteration
