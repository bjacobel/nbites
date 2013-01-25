# The makefile!

# How to find the build dir from here
BUILD_DIR = ../../build/tool
# How to find the src dir from build
SRC_DIR = ../../src/tool

EXECUTABLE = $(BUILD_DIR)/tool
TOOLCHAIN = ../man/cmake/generic.cmake

CMAKE_FLAGS = -DTOOL_EXECUTABLE=$(EXECUTABLE) -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)

.PHONY: build
build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR); \
	cmake $(CMAKE_FLAGS) $(SRC_DIR); \
	$(MAKE) --no-print-directory

.PHONY: run
run: build
	$(EXECUTABLE)

.PHONY: config
config:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR); \
	cmake $(CMAKE_FLAGS) $(SRC_DIR); \
	ccmake $(SRC_DIR)

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)/*