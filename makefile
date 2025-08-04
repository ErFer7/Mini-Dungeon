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
	./build/runtime_test

.PHONY: gdb
gdb:
	gdb ./build/runtime_test

.PHONY: valgrind
valgrind:
	valgrind --leak-check=full ./build/runtime_test

.PHONY: engine
engine:
	cmake --build build --target engine

.PHONY: engine_debug
engine_debug:
	cmake --build build --config Debug --target engine

.PHONY: engine_release
engine_release:
	cmake --build build --config Release --target engine

.PHONY: test
test:
	cmake --build build --target test

.PHONY: test_run
test_run: test
	./build/test

.PHONY: test_debug
test_debug: test
	cmake --build build --config Debug --target test

.PHONY: gdb_test
gdb_test: test
	gdb ./build/test

.PHONY: clean
clean:
	cmake --build build --target clean

.PHONY: veryclean
veryclean:
	rm -rf build
