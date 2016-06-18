#
# Makefile for lab7
#

##############################################################
# Compiler and flags to use
##############################################################

CXX       = g++
CXXFLAGS  = -g -Wall -Werror $(SPECIAL_FLAGS)
SPECIAL_FLAGS  = -std=c++0x
LIBS = -lpthread

##############################################################
# You shouldn't have to change anything below this line.
##############################################################

LAB7_EXE  = qsort_by_thread_pool
LAB7_OBJS = qsort_by_thread_pool.o

LAB7_TEST_QUEUE_EXE  = test_queue
LAB7_TEST_QUEUE_OBJS = test_queue.o

LAB7_TEST_POOL_EXE  = test_thread_pool
LAB7_TEST_POOL_OBJS = test_thread_pool.o

LAB7_EXE_SIMPLE   = qsort_by_thread_pool_simple
LAB7_OBJS_SIMPLE  = qsort_by_thread_pool_simple.o

LAB7_TEST_QUEUE_EXE_SIMPLE   = test_queue_simple
LAB7_TEST_QUEUE_OBJS_SIMPLE  = test_queue_simple.o

LAB7_TEST_POOL_EXE_SIMPLE   = test_thread_pool_simple
LAB7_TEST_POOL_OBJS_SIMPLE  = test_thread_pool_simple.o

###
$(LAB7_EXE): $(LAB7_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(LAB7_TEST_QUEUE_EXE): $(LAB7_TEST_QUEUE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(LAB7_TEST_POOL_EXE): $(LAB7_TEST_POOL_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(LAB7_EXE_SIMPLE): $(LAB7_OBJS_SIMPLE)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(LAB7_TEST_QUEUE_EXE_SIMPLE): $(LAB7_TEST_QUEUE_OBJS_SIMPLE)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(LAB7_TEST_POOL_EXE_SIMPLE): $(LAB7_TEST_POOL_OBJS_SIMPLE)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

all: $(LAB7_EXE) $(LAB7_TEST_QUEUE_EXE) $(LAB7_TEST_POOL_EXE) \
	 $(LAB7_TEST_QUEUE_EXE_SIMPLE) \
	 $(LAB7_TEST_POOL_EXE_SIMPLE) \
	 #$(LAB7_EXE_SIMPLE) 

###

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<


###
clean:
	rm -f $(LAB7_EXE) $(LAB7_OBJS) \
		  $(LAB7_TEST_QUEUE_EXE) $(LAB7_TEST_QUEUE_OBJS) \
		  $(LAB7_TEST_POOL_EXE) $(LAB7_TEST_POOL_OBJS) \
		  $(LAB7_EXE_SIMPLE) $(LAB7_OBJS_SIMPLE) \
		  $(LAB7_TEST_QUEUE_EXE_SIMPLE) $(LAB7_TEST_QUEUE_OBJS_SIMPLE) \
		  $(LAB7_TEST_POOL_EXE_SIMPLE) $(LAB7_TEST_POOL_OBJS_SIMPLE)
###


qsort_by_thread_pool.o: qsort_by_thread_pool.cpp \
	thread_pool.h thread_safe_queue.h

test_queue.o: test_queue.cpp thread_safe_queue.h

test_thread_pool.o: test_thread_pool.cpp thread_pool.h

qsort_by_thread_pool_simple.o: qsort_by_thread_pool_simple.cpp \
	thread_pool_simple.h thread_safe_queue_simple.h

test_queue_simple.o: test_queue_simple.cpp thread_safe_queue_simple.h

test_thread_pool_simple.o: test_thread_pool_simple.cpp thread_pool_simple.h
