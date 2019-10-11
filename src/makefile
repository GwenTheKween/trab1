COMP = g++
COMP_FLAGS = -c -g
LINK_FLAGS = -o
LDFLAGS = -lncurses
OUT_NAME = trab1
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEPS = $(SRC:.cpp=.d)

all: $(OBJ) $(DEPS)
	$(COMP) $(LINK_FLAGS) $(OUT_NAME) $(OBJ) $(LDFLAGS)

clean:
	rm $(OBJ) $(OUT_NAME)

include $(DEPS)

%.o:%.cpp
	$(COMP) $< $(COMP_FLAGS) -o $@

%.d:%.cpp
	$(COMP) -MM $< -o $@

run: $(OUT_NAME) $(OBJS)
	./$(OUT_NAME)
