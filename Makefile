
CXX := g++

SRC := verlet.cpp

TARGET := verlet

SFML_INCLUDE := /opt/homebrew/Cellar/sfml/2.6.1/include
SFML_LIB := /opt/homebrew/Cellar/sfml/2.6.1/lib

CXXFLAGS := -std=c++17 -Wall -I$(SFML_INCLUDE)

LDFLAGS := -L$(SFML_LIB)
LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean

