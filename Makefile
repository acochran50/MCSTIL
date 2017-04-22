# MCSTIL makefile
# Written by Alex Cochran, 2016.
# v0.1 ~ 10/31/2016

#
#	TO DO: find out why an extra src dir gets created (check line 41)
#

# compiler & options
CXX		:= g++
CFLAGS	:= -c -Wall -std=c++11
LDFLAGS	:=
EXEC	:= MCSTIL

# folders
SRCDIR	:= src
OBJDIR	:= build
BIN		:= bin
INC		:= include

# files
SRC_FILES	:= $(wildcard $(SRCDIR)/*.cpp)
EXEC_FILES	:= $(EXEC:%=$(BIN)/%)
OBJ_FILES	:= $(SRC_FILES:%.cpp=$(OBJDIR)/%.o)

build: $(EXEC_FILES)

clean:
	rm -r -f $(BIN)

.PHONY: build clean

# build
$(EXEC_FILES): $(OBJ_FILES)
	@$(CXX) $(LDFLAGS) -o $@ $^
	@echo "Build successful."

# compile
$(OBJ_FILES): $(OBJDIR)/%.o: %.cpp
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) -o $@ $<
