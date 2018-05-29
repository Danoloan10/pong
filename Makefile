CC=g++

SDIR=src
SRC=$(wildcard $(SDIR)/*.cpp)

ODIR=obj
OBJ=$(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRC))
DODIR=obj-d
DOBJ=$(patsubst $(SDIR)/%.cpp,$(DODIR)/%-d.o,$(SRC))

BDIR=bin
BIN=main
DEBUG=main-d

LIBS=-lsfml-window -lsfml-graphics -lsfml-system 

DEPS=$(wildcard $(SDIR)/*.hpp) #includes all the header files. improve

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $<

$(DODIR)/%-d.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o -g $@ $<

$(BDIR)/$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

$(BDIR)/$(DEBUG): $(DOBJ)
	$(CC) -o $@ $^ $(LIBS) 

all: bin/main
debug: bin/main-d
