

CC = g++
CFLAGS = -g

INCLUDES = -I. -I/opt/local/include
LDLIBS = -L/opt/local/lib -lhdf5_cpp -lhdf5 -lstdc++

CFLAGS += $(INCLUDES)

all: raw2hdf5

raw2hdf5.o: raw2hdf5.cc
	$(CC) $(CFLAGS) -c $^ -o $@

raw2hdf5: raw2hdf5.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)