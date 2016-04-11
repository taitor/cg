buildtype:=release
APP:=./app/
SRC:=./src/
SRCS:=${wildcard $(SRC)*.cpp}
CXX:=g++

CXXFLAGS+=-Wall
LDFLAGS+=
LIBS+=
GL:=-framework OpenGL
GLFW:=`pkg-config --libs --cflags glfw3`

ifeq ($(buildtype), release)
	CXXFLAGS+=-O3
else ifeq ($(buildtype), debug)
	CXXFLAGS+=-O0 -g
else
	$(error buildtype must be release, debug, profile or coverage)
endif

OUTDIR:=./build/$(buildtype)

OBJS:=$(SRCS:%.cpp=$(OUTDIR)/%.o)
DEPS:=$(SRCS:%.cpp=$(OUTDIR)/%.d)

.PHONY: clean distclean run

all: sample

-include $(DEPS)

sample: $(OBJS) ./app/sample.cpp
	@if [ ! -e $(OUTDIR) ]; then mkdir -p $(OUTDIR); fi
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(GL) $(GLFW) -o $(OUTDIR)/sample $^ $(LIBS)

$(OUTDIR)/%.o: %.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) -o $@ -c -MMD -MP -MF $(@:%.o=%.d) $<

clean:
	rm -rf $(OUTDIR)

distclean:
	rm -rf ./build/
