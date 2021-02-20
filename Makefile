#############################################
##              CONFIGURATION              ##
#############################################

# Include directory with the .h files
INC_DIR = include

# Source directory with the .cpp files
SRC_DIR = src

# Output directory
BUILD_DIR = build

# Report directory
REPORT_DIR = reports/$(CXX)

# Compiler options
FLAGS = -Wall -Wextra -pedantic -O3 -fomit-frame-pointer -std=c++17 -lbenchmark


#############################################
##          CORE (do not touch)            ##
#############################################

.PHONY: build run_all build_dir report_dir clean

CXX_LIST := $(shell find $(SRC_DIR) -name "*.cpp")
HEADER_LIST := $(shell find $(INC_DIR) -name "*.h")

OUT_FILES := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%, $(CXX_LIST:.cpp=))

START_TIME := $(shell date +%s%3N)

build : build_dir $(OUT_FILES) report_dir
	@diff=$$(($(shell date +%s%3N) - $(START_TIME))); echo 'Build process completed in '$$(($$diff / 1000))'.'$$(($$diff % 1000))'s'
	@echo

build_dir:
	@echo  '__________Building__________'
	@mkdir -p $(BUILD_DIR)

report_dir: $(OUT_FILES)
	@mkdir -p $(REPORT_DIR)

clean:
	@echo  Removing build artifacts...
	@rm -rf $(BUILD_DIR)

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp Makefile $(HEADER_LIST)
	$(CXX) $< $(FLAGS) -I $(INC_DIR) -o $@

