BUILD_DIR_11 = build/11
BUILD_DIR_20 = build/20
BIN_DIR_11 = $(BUILD_DIR_11)/bin
BIN_DIR_20 = $(BUILD_DIR_20)/bin
CXX_FLAGS = -G Ninja

all: $(BUILD_DIR_11) $(BUILD_DIR_20)
	cmake --build $(BUILD_DIR_11)
	cmake --build $(BUILD_DIR_20)

$(BUILD_DIR_11):
	mkdir -p $(BUILD_DIR_11)
	cmake -S . -B $(BUILD_DIR_11) $(CXX_FLAGS) -DCMAKE_CXX_STANDARD=11

$(BUILD_DIR_20):
	mkdir -p $(BUILD_DIR_20)
	cmake -S . -B $(BUILD_DIR_20) $(CXX_FLAGS) -DCMAKE_CXX_STANDARD=20

clean:
	rm -rf build

rebuild: clean all

run:
	@echo "Running C++11 binaries:"
	@for binary in $(BIN_DIR_11)/*; do \
		echo "Running $$binary"; \
		$$binary; \
	done
	@echo "Running C++20 binaries:"
	@for binary in $(BIN_DIR_20)/*; do \
		echo "Running $$binary"; \
		$$binary; \
	done