lsh:
	make -f makefileLSH

cube:
	make -f makefileCube

all: 
	make -f makefileLSH
	make -f makefileCube

clean:
	rm -f lsh cube *.o
