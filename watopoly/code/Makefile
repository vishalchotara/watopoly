CXX=g++
CXXFLAGS=-std=c++14 -g -MMD
SOURCES=$(wildcard *.cc)
OBJECTS=${SOURCES:.cc=.o}
DEPENDS=${OBJECTS:.o=.d}
EXEC=watopoly

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)
%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)
-include ${DEPENDS}
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(DEPENDS) $(EXEC)
