SRC := source/
INCL := includes/
BUILD := build/
DEL := rm -rf

FLAGOBJ := g++ -g -c -std=c++17 -Wall -Wextra -Wpedantic
FLAGEXE := g++ -std=c++17 -Wall -Wextra -Wpedantic

all: $(BUILD)main.exe

$(BUILD)main.exe: $(BUILD)main.o $(BUILD)parser.o
	$(FLAGEXE) $(BUILD)main.o $(BUILD)parser.o -o $(BUILD)main.exe

$(BUILD)main.o: $(SRC)main.cpp $(INCL)parser.hpp $(INCL)u_graph.hpp
	$(FLAGOBJ) $(SRC)main.cpp -I$(INCL) -o $(BUILD)main.o
	
$(BUILD)parser.o: $(SRC)parser.cpp $(INCL)parser.hpp $(INCL)typedef.hpp
	$(FLAGOBJ) $(SRC)parser.cpp -I$(INCL) -o $(BUILD)parser.o
	
clear: 
	-$(DEL) $(BUILD)*.o $(BUILD)*.exe $(BUILD)*.cvs