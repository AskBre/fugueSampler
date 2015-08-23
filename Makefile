CC=clang++ -std=c++11
OBJ=src/main.cpp

SDIR=src
IDIR=include
ODIR=obj
LDIR=lib

DEPS=$(SDIR)/%.h $(IDIR)/%.h
LIBS=-lmidifile

CFLAGS=-I$(IDIR) -L$(LDIR)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

main:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run:
	./main ricercar_6_full.mid
