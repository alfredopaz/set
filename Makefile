
CXX      = g++
CXXFLAGS = -Wall -std=c++11
TARGET   = set
SRC      = main.cc
OBJ      = main.o

# regla general
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# dependencias
main.o: main.cc ISet.h ArraySet.h
	$(CXX) $(CXXFLAGS) -c main.cc

run: $(TARGET)
	./$(TARGET)

release:
	$(CXX) $(CXXFLAGS) -DNDEBUG -o $(TARGET) $(SRC)

clean:
	rm -f $(OBJ) $(TARGET)

help:
	@echo "make         -> compila con assert"
	@echo "make run     -> ejecuta"
	@echo "make release -> compila sin assert (-DNDEBUG)"
	@echo "make clean   -> limpia"
