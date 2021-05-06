CXX = g++
CXXFLAGS = \
  $(shell pkg-config --libs lapacke) \
  $(shell pkg-config --libs blas)

CXXINCLUDE = \
  $(shell pkg-config --cflags lapacke) \
  $(shell pkg-config --cflags blas)



CXX_SRC = main.cpp
CXX_OBJ = $(CXX_SRC:.cpp=)

EXEC = $(CXX_OBJ)


all: $(EXEC)

$(CXX_OBJ): $(CXX_SRC)
	$(CXX) -o $@.out $(CXXINCLUDE) $(CXXFLAGS) $(CXX_SRC) -lm



clean:
	rm -f $(EXEC)
