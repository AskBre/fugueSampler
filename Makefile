CC=g++ -std=c++11
OBJ=main.cpp
DEPS=
CONF=-lrtaudio

%.o:%..cpp $(DEPS)
	$(CC) $(CONF) -c -o $@ $<

main:$(OBJ)
	$(CC) $(CONF) -o $@ $^

run:
	./main
