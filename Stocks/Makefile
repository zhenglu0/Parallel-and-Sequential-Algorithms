CXX=g++
#BITS=-m64
#INCLUDES=-I.
CXXFLAGS= -Wall -Werror -O2 $(INCLUDES) $(BITS)

# If you are using a version of binutils prior to 2.17, 
# uncomment following line to work around a known issue. 
# please reference the Release Notes for more information. 
#LIBS = -lcilkrts
#LIBS= -lcilkrts /opt/cilk/lib64/libcilkrts.so

PROGS=Stocks

all:: $(PROGS)

Stocks: Stocks.o StocksResult.o StocksSupport.o \
		Timer.o StudentSolution.o
	$(CXX) $(BITS) -o $@ $< $(LIBS)

clean::
	-rm -f $(PROGS) *.o

Stocks.o: StocksSupport.cpp StocksResult.cpp StocksResult.h\
	StudentSolution.cpp Timer.cpp Timer.h cilktime.h
StocksResult.o: StocksResult.cpp StocksResult.h
StocksSupport.o: StocksSupport.cpp
Timer.o: Timer.cpp Timer.h cilktime.h
StudentSolution.o: StudentSolution.cpp StocksResult.cpp \
	StocksResult.h