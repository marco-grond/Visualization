CC		= g++
LIBS 		= -lglfw -lGL -lGLU -lglut -lSOIL -std=c++11 
OBJECTS1	= MultiRes1D.o filters.o
OBJECTS2	= MultiRes2D.o filters.o
EXEFILE1	= Multires1D
EXEFILE2	= Multires2D

all: $(EXEFILE1) $(EXEFILE2) clean

$(EXEFILE1): $(OBJECTS1) Main1D.o
	$(CC) -o $(EXEFILE1) Main1D.o $(OBJECTS1) $(LIBS)

$(EXEFILE2): $(OBJECTS2) Main2D.o
	$(CC) -o $(EXEFILE2) Main2D.o $(OBJECTS2) $(LIBS)

#TestMain.o: $(OBJECTS)
#	$(CC) $(LIBS) -c TestMain.cpp

Main1D.o: $(OBJECTS1)
	$(CC) $(LIBS) -c Main1D.cpp

Main2D.o: $(OBJECTS2)
	$(CC) $(LIBS) -c Main2D.cpp

MultiRes2D.o:
	$(CC) $(LIBS) -c MultiRes2D.cpp

MultiRes1D.o:
	$(CC) $(LIBS) -c MultiRes1D.cpp

filters.o:
	$(CC) $(LIBS) -c filters.cpp

clean:
	rm MultiRes1D.o MultiRes2D.o filters.o Main1D.o Main2D.o

cleanest: clean
	rm $(EXEFILE1) $(EXEFILE2)

