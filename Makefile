.PHONY: all
all: Build/Binaries/X86-64/Debug/BTool

CXXFLAGS += -std=c++14
CPPFLAGS += -IInclude
LDFLAGS += -LLibrary -lyaml-cpp -lstdc++fs

OBJECTS := $(shell find -L Source -type f -name '*.cpp' | sed 's/Source/Build\/Objects/g' | sed 's/\.cpp/\.o/g')
DEPENDENCIES := $(patsubst %.o,%.d,$(OBJECTS))

-include $(DEPENDENCIES)

Build/Binaries/X86-64/Debug/BTool: $(OBJECTS)
	@mkdir -p $(@D)
	@g++ -g -o $@ $^ $(LDFLAGS)

Build/Objects/%.o: Source/%.cpp Makefile
	@mkdir -p $(@D)
	@g++ $(CPPFLAGS) -g -Wall -MMD -Wextra -c -o $@ $<

clean:
	@rm -rf Build/

run: all
	@./Build/Binaries/X86-64/Debug/BTool

rebuild: clean all