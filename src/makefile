COMP = g++
COMP_FLAGS = -c -g -O0
LINK_FLAGS = -o
OUT_NAME = trab1
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEPS = $(SRC:.cpp=.d)

all: $(OBJ) $(DEPS)
	$(COMP) $(LINK_FLAGS) $(OUT_NAME) $(OBJ)

clean:
	rm $(OBJ) $(OUT_NAME)

include $(DEPS)

%.o:%.cpp
	$(COMP) $< $(COMP_FLAGS) -o $@

%.d:%.cpp
	$(COMP) -MM $< -o $@

run: $(OUT_NAME) $(OBJS)
	./$(OUT_NAME)

debug: clean all
	gdb ./$(OUT_NAME)
