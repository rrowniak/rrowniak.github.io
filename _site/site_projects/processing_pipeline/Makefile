IDIR =include
CXX=g++
CXXFLAGS=-I$(IDIR) -std=c++17 -Wall -Wextra -Wshadow -Wstrict-aliasing -pedantic -Werror -g

ODIR=./obj
LDIR =../lib

LIBS=-lpthread 

_OBJ = ReqResp.o main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/ReqResp.o: ReqResp.cpp ReqResp.h
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/main.o: main.cpp ReqResp.cpp ReqResp.h ThreadPool.hpp counter.hpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

processing_pipeline: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.DEFAULT_GOAL := processing_pipeline

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core processing_pipeline