BINFOLDER := bin/
INCFOLDER := inc/
SRCFOLDER := src/
OBJFOLDER := obj/
DOCFOLDER := doc/

CC := g++
CFLAGS := -Wall -Wno-reorder
FLAGS := -std=c++11 -lSDL2 -lSDL2_image -lz

SRCFILES := $(wildcard $(SRCFOLDER)*.cpp)

all: createDirectories $(SRCFILES:$(SRCFOLDER)%.cpp=$(OBJFOLDER)%.o)
	$(CC) $(CFLAGS) $(OBJFOLDER)*.o -o $(BINFOLDER)main $(FLAGS)

createDirectories:
	mkdir -p $(OBJFOLDER)
	mkdir -p $(BINFOLDER)
	mkdir -p $(SRCFOLDER)
	mkdir -p $(INCFOLDER)
	mkdir -p $(DOCFOLDER)

$(OBJFOLDER)%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I./$(INCFOLDER) $(FLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJFOLDER)*
	rm -rf $(BINFOLDER)*

run:
		$(BINFOLDER)main
