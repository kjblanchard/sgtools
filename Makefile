all: rebuild
BINARY_NAME := sgtools_exe
BUILD_TYPE := Debug
# BUILD_TYPE := Release

rebuild: clean
	@mkdir build
	@cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -B build .
	@cmake --build build

install:
	@cmake --install build

run:
	@./build/$(BINARY_NAME)

clean:
	@rm -rf build
