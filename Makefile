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

cholesky:
	$(CXX) -o cholesky.out $(CXXINCLUDE) $(CXXFLAGS) cholesky.cpp -lm

inv_mat:
	$(CXX) -o inv_mat.out $(CXXINCLUDE) $(CXXFLAGS) inv_mat.cpp -lm

clean:
	rm -f $(EXEC)
