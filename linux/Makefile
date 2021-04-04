CC := g++
FLAGS := -std=c++17 -O2 -Wall
EXTRA_FLAGS := -Wsuggest-override

TARJET := bin/TheGoonies
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
LIBS_DIR := libs

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

LIBS_DIRS := $(wildcard $(LIBS_DIR)/*)
LIBS := $(foreach dir,$(LIBS_DIRS),-L$(dir) $(foreach file,$(patsubst lib%,%,$(basename $(notdir $(wildcard $(dir)/lib*.a)))),-l$(file)))
EXTERNAL_LIBS := -lGL -lGLEW -lglut -lfreetype -lIrrKlang

$(TARJET): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LIBS) $(EXTERNAL_LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(EXTRA_FLAGS) -I$(INCLUDE_DIR) -I$(SRC_DIR) -I/usr/include/freetype2 -c -o $@ $<

clean:
	rm -f $(OBJ_FILES)
	rm -f $(TARJET)

.PHONY: clean

