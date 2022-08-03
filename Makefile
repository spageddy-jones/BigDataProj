.POSIX:

BIN      = BigDataProj
SRC      = $(wildcard *.cpp)

CXX      = g++
CXXFLAGS = -MMD -Wall -Wextra -Wshadow -Wno-unused-parameter

ifeq ($(OS),Windows_NT)
	LDFLAGS = -lws2_32
endif

OBJ      = $(SRC:.cpp=.o)
DEPS     = $(SRC:.cpp=.d)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

-include $(DEPS)

.PHONY: run clean

run: $(BIN)
	./$<

clean:
	rm -f $(BIN) $(OBJ) $(DEPS)
