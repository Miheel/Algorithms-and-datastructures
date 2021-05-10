SRC := source/
INCL := includes/
BUILD := build/
DEL := rm -rf

FLAGOBJ := g++ -g -c -std=c++17 -Wall -Wextra -Wpedantic
FLAGEXE := g++ -std=c++17 -Wall -Wextra -Wpedantic

all: $(BUILD)main.exe

$(BUILD)main.exe: $(BUILD)main.o $(BUILD)reader.o
	$(FLAGEXE) $(BUILD)main.o $(BUILD)reader.o -o $(BUILD)main.exe

$(BUILD)main.o: $(SRC)main.cpp $(INCL)reader.hpp $(INCL)graph.hpp
	$(FLAGOBJ) $(SRC)main.cpp -I$(INCL) -o $(BUILD)main.o
	
$(BUILD)reader.o: $(SRC)reader.cpp $(INCL)reader.hpp $(INCL)typedef.hpp
	$(FLAGOBJ) $(SRC)reader.cpp -I$(INCL) -o $(BUILD)reader.o
	
clear: 
	-$(DEL) $(BUILD)*.o $(BUILD)*.exe $(BUILD)*.cvs