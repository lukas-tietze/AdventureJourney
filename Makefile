SRC := src
BIN := bin
OBJ := obj
DEP := dep

FIND := /bin/find.exe 

V := cppcheck
VFLAGS := --enable=all --error-exitcode=0 -q $(SRC) 2> code_check.txt

INCLUDES := -I$(SRC) -I.
C := g++
CFLAGS = -Wall $(INCLUDES) -std=c++17 #-MMD -MF $(patsubst $(OBJ)/%.o,$(DEP)/%.d,$@)

L := g++
LIBDIRS := 
LIBS := -lncurses -lm
LFLAGS := -Wall -std=c++17 $(LIBDIRS) $(LIBS)

# object from cpp
$(OBJ)/%.o : $(SRC)/%.cpp
	#$(info compiling $< to $@)
	$(C) $(CFLAGS) -c $< -o $@

.PHONY: debug, release, debug_p, release_p, clean

all : debug

debug_p: LFLAGS += -pg
debug_p: debug

debug: CFLAGS += -ggdb -DDEBUG
debug: app
	$(V) -DDEBUG $(VFLAGS)

release_p: LFLAGS += -pg
release_p: release

release: CFLAGS += -o2
release: app
	$(V) $(VFLAGS)

APPLICATION := $(BIN)/adventureJourney
CFILES := $(shell $(FIND) $(SRC) -name \*.cpp -print)
DFILES := $(shell $(FIND) $(DEP) -name \*.d -print)
OFILES := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(CFILES))
ODIRS := $(dir $(OFILES))
DDIRS := $(dir $(DFILES))

app : $(ODIRS) $(DDIRS) $(OFILES)
	$(info changes to $? triggered main)
# 	$(info $$CFILES is [$(CFILES)])
# 	$(info $$DFILES is [$(DFILES)])
# 	$(info $$OFILES is [$(OFILES)])
# 	$(info $$ODIRS is [$(ODIRS)])
	$(L) $(LFLAGS) $(OFILES) -o $(APPLICATION) $(LIBDIRS) $(LIBS)

clean:
	-rm -rf $(BIN)/* 2> /dev/null
	-rm -rf $(OBJ)/* 2> /dev/null
	-rm -rf $(DEP)/* 2> /dev/null

$(OBJ)/%:
	mkdir -p $@

$(DEP)/%:
	mkdir -p $@