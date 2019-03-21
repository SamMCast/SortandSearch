proj = mysort

CC = g++ -std=c++14 -g
rm = $(proj) *.o

CFLGS = -Werror -g -fmax-errors=5

.PHONY: all

all: $(proj)

$(proj): $(proj).o
	$(CC) $(proj).o -o $(proj)


$(proj).o : $(proj).cpp
	$(CC) $(CFLGS) -c $(proj).cpp


.PHONY: clean

clean: 
	rm -rf $(rm)
