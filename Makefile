CC=gcc
#CFLAGS += -Iinclude -I/usr/include/SDL2 -I../include
RELEASE= bin/release
DEBUG= bin/debug
INC_DIR= include
SRC_DIR= src
OBJ_DIR= build
LIB_DIR= lib
P_HEADERS := $(wildcard *.h include/*.h include/*/*.h include/*/*/*.h)
HEADERS := $(wildcard *.hpp include/*.hpp include/*/*.hpp include/*/*/*.hpp)
CFLAGS += $(addprefix -I,$(dir $(HEADERS))) $(addprefix -I,$(dir $(P_HEADERS)))
CXXFLAGS += -g -Wall
LINK_FLAGS := $(shell echo `pkg-config --cflags gtk4` `pkg-config --cflags libadwaita-1`)
LIBS := $(shell echo `pkg-config --libs gtk4` `pkg-config --libs libadwaita-1`)
SRCS := $(wildcard *.c src/*.c src/*/*.c src/*/*/*.c)
OBJS := $(patsubst %.c,%.o,$(addprefix $(OBJ_DIR)/,$(notdir $(SRCS))))
# match strings with % ex: %.c: %.o
.PHONY: all clean stream 
vpath %.c $(dir $(SRCS))
all: debug

release: CXXFLAGS += -O2 -m64- Wall
#release: LINK_FLAGS = -s
release: $(OBJS)
	$(CC) -o $(RELEASE)/$@ $^ $(LIBS)

debug: $(OBJS)
	$(CC) $^ $(LIBS) -o $(DEBUG)/$@ 

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $^ $(CFLAGS) $(LINK_FLAGS) $(CXXFLAGS) -o $@ 

clean:
	echo "$(SRCS)"
	echo "$(OBJS)"
	echo "$(dir $(SRCS))"
	echo "$(CFLAGS)"
	rm -r $(OBJS)
	rm $(RELEASE)/release
	rm $(DEBUG)/debug

# $@: $<
