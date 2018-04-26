#MakeFile
CXX = g++
LFLAGS        = -m64
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES) -Wno-sign-compare -Wno-unused-result -Wno-unused-variable -Wno-unused-parameter -Wuninitialized -L /lib64 	
LIBS          = -L/usr/lib/x86_64-linux-gnu/ -lpthread -lGL -lGLU -lglut -lm 
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB


main: main.o Boid.o Flock.o 
	$(CXX) $(LFLAGS) -o main main.o Boid.o Flock.o $(LIBS)

main.o: src/main.cpp src/Boid.cpp include/Boid.h src/Flock.cpp include/Flock.h 
	$(CXX) $(CXXFLAGS)  -c src/main.cpp -o $@

Boid.o: src/Boid.cpp include/Boid.h src/Flock.cpp include/Flock.h 
	$(CXX) $(CXXFLAGS)  -c src/Boid.cpp -o $@

Flock.o: src/Flock.cpp include/Flock.h src/Boid.cpp include/Boid.h
	$(CXX) $(CXXFLAGS)  -c src/Flock.cpp -o $@

clean: 
	$(RM) main *.o *~
