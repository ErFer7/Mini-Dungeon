.PHONY: default
default:
	cmake --build build

.PHONY: setup
setup:
	cmake -B build

.PHONY: debug
debug:
	cmake --build build --config Debug

.PHONY: release
release:
	cmake --build build --config Release

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
	rm -rf build
