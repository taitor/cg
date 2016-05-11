buildtype:=release
APP:=app/
SRC:=src/
SRCS:=${wildcard $(SRC)*.cpp}
CXX:=g++

CXXFLAGS+=-std=c++1y -Wall -I./src/
LDFLAGS+=
LIBS+=
GL:=-framework OpenGL
GLFW:=`pkg-config --libs --cflags glfw3`
GLFWI:=`pkg-config --cflags glfw3`

ifeq ($(buildtype), release)
	CXXFLAGS+=-O3
else ifeq ($(buildtype), debug)
	CXXFLAGS+=-O0 -g
else
	$(error buildtype must be release, debug, profile or coverage)
endif

OUTDIR:=./build/$(buildtype)/

OBJS:=$(SRCS:%.cpp=$(OUTDIR)%.o)
DEPS:=$(SRCS:%.cpp=$(OUTDIR)%.d)

.PHONY: clean distclean run

all: sample

-include $(DEPS)

sample: $(APP)sample.cpp
	@if [ ! -e $(OUTDIR) ]; then mkdir -p $(OUTDIR); fi
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(GL) $(GLFW) -o $(OUTDIR)sample $^ $(LIBS)

test: $(OBJS) $(APP)test.cpp
	@if [ ! -e $(OUTDIR) ]; then mkdir -p $(OUTDIR); fi
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(GL) $(GLFW) -o $(OUTDIR)test $^ $(LIBS)

assign1_1: $(OBJS) $(APP)assign1_1.cpp
	@if [ ! -e $(OUTDIR) ]; then mkdir -p $(OUTDIR); fi
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(GL) $(GLFW) -o $(OUTDIR)assign1_1 $^ $(LIBS)

$(OUTDIR)%.o: %.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) -o $@ -c -MMD -MP -MF $(@:%.o=%.d) $<

$(OUTDIR)$(SRC)Window.o: $(SRC)Window.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) $(GLFWI) -o $@ -c -MMD -MP -MF $(@:%.o=%.d) $<

clean:
	rm -rf $(OUTDIR)

distclean:
	rm -rf ./build/
