#all:
#	g++ -O3 -DNDEBUG -I../smile_linux_x64_gcc_4_4_5/ -L../smile_linux_x64_gcc_4_4_5/  -ffast-math  test.cpp -o bn_test -lsmile

# important that -lsmile is at the end 0o

LDFLAGS = -O3 -DNDEBUG -I../smile_linux_x64_gcc_4_4_5/ -L../smile_linux_x64_gcc_4_4_5/  -ffast-math -lsmile -lsmilearn -fpermissive -g

OBJ  = 


all: $(OBJ)
	g++ test.cpp $(LDFLAGS) $(OBJ) -o bn_test

%.o: %.cpp
	g++ -Wall -g -c $< $(LDFLAGS) -o $@


clean:
	rm -f *.o
	rm -f *~
	rm -f bn_test
