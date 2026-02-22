.PHONY: default
default:
	cmake --build build -j$(nproc)

.PHONY: setup
setup:
	cmake -B build

.PHONY: debug
debug:
	cmake -B build -DCMAKE_BUILD_TYPE=Debug
	cmake --build build -j$(nproc)

.PHONY: release
release:
	cmake -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build -j$(nproc)

.PHONY: run
run:
	./build/mini_dungeon

.PHONY: gdb
gdb:
	gdb ./build/mini_dungeon

.PHONY: valgrind
valgrind:
	valgrind --leak-check=full ./build/mini_dungeon

.PHONY: clean
clean:
	cmake --build build --target clean

.PHONY: veryclean
veryclean:
	rm -rf build .cache
