COMP = g++
COMP_FLAGS = -c -g -O3
LINK_FLAGS = -o
OUT_NAME = trab1
SRC = $(wildcard *.cpp)
OBJ = $(SRC.cpp=.o)
DEPS = $(SRC.cpp=.d)

all: $(OBJ) $(DEPS)
	$(COMP) $(LINK_FLAGS) $(OUT_NAME) $(OBJ)

clean:
	rm $(OBJ) $(OUT_NAME)

include $(DEPS)

%.o:%.cpp
	$(COMP) $< -o $@

%.d:%.cpp
	$(COMP) -MM $< -o $@

run: $(OUT_NAME)
	./$(OUT_NAME)
