APP_NAME := CapyScreen
VERSION := 0.0.2
PLATFORM ?= linux

BUILD_DIR = build/$(PLATFORM)
SRC_DIR := src
LIB_DIR := lib
RES_DIR := res

WIN64_SFML_URL := https://www.sfml-dev.org/files/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit.zip
WIN64_SFML_VER := 2.6.1
WIN64_SFML_DIR := $(LIB_DIR)/SFML-$(WIN64_SFML_VER)

ifeq ($(PLATFORM), linux)
	TARGET := $(BUILD_DIR)/$(APP_NAME)
	CXX := g++
	CXXFLAGS := $(shell pkg-config --cflags sfml-all)
	LDFLAGS := $(shell pkg-config --libs sfml-all)

else ifeq ($(PLATFORM), win64)
	TARGET := $(BUILD_DIR)/$(APP_NAME).exe
	CXX := x86_64-w64-mingw32-g++
	CXXFLAGS := -I $(WIN64_SFML_DIR)/include -DSFML_STATIC
	LDFLAGS := -L $(WIN64_SFML_DIR)/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -mwindows --static
	BUILD_DEP := $(WIN64_SFML_DIR)

else
	$(error Unsupported platform: $(PLATFORM))

endif

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
DEPENDS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.d,$(SOURCES))

.PHONY: all run release clean

all: $(TARGET)

-include $(DEPENDS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(BUILD_DEP)
	@mkdir -p $(dir $@)
	$(CXX) -MMD -MP -c $< -o $@ $(CXXFLAGS)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(WIN64_SFML_DIR):
	@echo "Downloading SFML..."
	@wget -O sfml.zip $(WIN64_SFML_URL)
	@echo "Extracting SFML..."
	@unzip -q sfml.zip -d $(LIB_DIR)
	@rm sfml.zip

run: $(TARGET)
ifeq ($(PLATFORM), linux)
	./$(TARGET)
endif

release: $(TARGET)
	@mkdir -p release
	@cp $(TARGET) release/
	@cp -r $(RES_DIR) release/
ifeq ($(PLATFORM), linux)
	@tar -czvf release/$(APP_NAME)-$(VERSION).tar.gz -C release $(notdir $(TARGET)) $(RES_DIR)
else ifeq ($(PLATFORM), win64)
	@cd release && zip -r $(APP_NAME)-$(VERSION).zip $(notdir $(TARGET)) $(RES_DIR)
endif
	@rm release/$(notdir $(TARGET))
	@rm -rf release/$(RES_DIR)

clean:
	@rm -rf build/*
	@rm -rf lib/*
	@rm -rf release/*
