BASE_DIR=../..
BUILD_DIR=build
DEBUG_OPTIONS=-DCMAKE_BUILD_TYPE=Debug
DEBUG_DIR=$(BUILD_DIR)/debug/
RELEASE_OPTIONS=-DCMAKE_BUILD_TYPE=Release
RELEASE_DIR=$(BUILD_DIR)/release

all: cmake

$(BUILD_DIR):
	-mkdir $(BUILD_DIR)

$(DEBUG_DIR): $(BUILD_DIR)
	-mkdir $(DEBUG_DIR)

$(RELEASE_DIR): $(BUILD_DIR)
	-mkdir $(RELEASE_DIR)

$(DEBUG_DIR)/Makefile: $(DEBUG_DIR)
	cd $(DEBUG_DIR) && cmake $(DEBUG_OPTIONS) $(BASE_DIR)

$(RELEASE_DIR)/Makefile: $(RELEASE_DIR)
	cd $(RELEASE_DIR) && cmake $(RELEASE_OPTIONS) $(BASE_DIR)

cmake: $(DEBUG_DIR)
	cd $(DEBUG_DIR) && cmake $(DEBUG_OPTIONS) $(BASE_DIR)

debug: $(DEBUG_DIR)/Makefile
	cd $(DEBUG_DIR) && make

release: $(RELEASE_DIR)/Makefile
	cd $(RELEASE_DIR) && make

clean:
	rm -rf build/*