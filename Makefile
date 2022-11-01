CC=clang++ -std=c++11
OBJ=src/*.cpp

SDIR=src
IDIR=-Iinclude -I/usr/include/rtaudio
ODIR=obj
LDIR=lib

DEPS=$(SDIR)/%.h $(IDIR)/%.h
LIBS=-lmidifile -lrtaudio

CFLAGS=$(IDIR) -L$(LDIR) -g

$(ODIR)/%.o:$(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

fugueSampler:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm fugueSampler

run:
	./fugueSampler FugueSampler.mid
