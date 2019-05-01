BASE_DIR=../..
BUILD_DIR=build
DEBUG_DIR=$(BUILD_DIR)/debug/
RELEASE_DIR=$(BUILD_DIR)/release

all: debug

$(BUILD_DIR):
	-mkdir $(BUILD_DIR)

$(DEBUG_DIR): $(BUILD_DIR)
	-mkdir $(DEBUG_DIR)

$(RELEASE_DIR): $(BUILD_DIR)
	-mkdir $(RELEASE_DIR)

debug: $(DEBUG_DIR) CMakeLists.txt
	cd $(DEBUG_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug $(BASE_DIR)

release: $(RELEASE_DIR) CMakeLists.txt
	cd $(RELEASE_DIR) && cmake -DCMAKE_BUILD_TYPE=Release $(BASE_DIR)

build_debug:

build_release:

clean:
	rm -rf build/*