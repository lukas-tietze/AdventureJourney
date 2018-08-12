BASE_DIR=../..
BUILD_DIR=build
DEBUG_OPTIONS=-DCMAKE_BUILD_TYPE=Debug
DEBUG_DIR=$(BUILD_DIR)/debug/
RELEASE_OPTIONS=-DCMAKE_BUILD_TYPE=Release
RELEASE_DIR=$(BUILD_DIR)/release



all: debug

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(DEBUG_DIR): $(BUILD_DIR)
	mkdir $(DEBUG_DIR)

$(RELEASE_DIR): $(BUILD_DIR)
	mkdir $(RELEASE_DIR)

debug: $(DEBUG_DIR)
	cd $(DEBUG_DIR) && \
	cmake $(DEBUG_OPTIONS) $(BASE_DIR) && \
	make

release: releasedir
	cd $(RELEASE_DIR) && \
	cmake $(RELEASE_OPTIONS) $(BASE_DIR) && \
	make