CC=g++

SDIR=src
SRC=$(wildcard $(SDIR)/*.cpp)

ODIR=obj
OBJ=$(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRC))

BDIR=bin
BIN=main

LIBS=-lsfml-window -lsfml-graphics -lsfml-system 

DEPS=$(wildcard $(SDIR)/*.hpp) #includes all the header files. improve

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $<

$(BDIR)/$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)
	
