CC = /usr/local/cs/bin/g32

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)

.PHONY: default all clean

PRODUCT = p4sanity

all: $(PRODUCT)

%.o: %.cpp $(HEADERS)
	$(CC) -c -Wno-unused-parameter -Wno-unused-variable -Wno-reorder -Wno-misleading-indentation -Wno-switch $< -o $@

$(PRODUCT): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

clean:
	rm -f *.o
	rm -f $(PRODUCT)
