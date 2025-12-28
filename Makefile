all: clean build .PHONY

build:
	cmake -S . -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug

.PHONY: 
	cmake --build build 

clean:
	rm -rf build
