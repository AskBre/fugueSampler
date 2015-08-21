CC=clang++ -std=c++11
OBJ=main.cpp
DEPS=
CONF=-lrtaudio -g

%.o:%..cpp $(DEPS)
	$(CC) $(CONF) -c -o $@ $<

main:$(OBJ)
	$(CC) $(CONF) -o $@ $^

run:
	./main
