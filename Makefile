SOURCES  = $(wildcard *.cc)
HEADERS  = $(wildcard *.h)
OBJECTS  = $(SOURCES:.cc=.o)
LDFLAGS  = -lboost_system -lpthread
CPPFLAGS =
CXXFLAGS = $(CPPFLAGS) -W -Wall -g -O3 -I. --std=c++11
CXX = clang++
MAIN = mcinfo

all: $(MAIN) tags

.PHONY: clean tags

depend: $(DEPENDS)

clean:
	rm -f *.o *.d $(MAIN)

$(MAIN): $(OBJECTS)
	@echo Creating $@...
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cc $(HEADERS)
	@echo Compiling $<...
	$(CXX) -o $@ -c $(CXXFLAGS) $<

tags:
	ctags -R
