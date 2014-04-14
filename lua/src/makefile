Product = lua
Platform = $(shell uname)
Include = 
LibDir = ../../Library/$(Platform)
Lib = 
Define =
ObjDir = ../../Build/$(Platform)
OutDir = 

CC = gcc
CXX = g++
CFLAGS =
CXXFLAGS = $(CFLAGS) -Wno-invalid-offsetof

Link = ar
LinkFlags =

ProductX86D = $(LibDir)/lib$(Product)D.a
ProductX86  = $(LibDir)/lib$(Product).a

ObjDirX86D = $(ObjDir)/$(Product)/Debug
ObjDirX86  = $(ObjDir)/$(Product)/Release

CompX86DFlags = $(Include:%=-I%) $(Define:%=-D%) -m32 -c -g -D_DEBUG -o
CompX86Flags  = $(Include:%=-I%) $(Define:%=-D%) -m32 -c -O3 -DNDEBUG -o

LinkX86D = $(Link) cr $@ $^ $(LinkFlags)
LinkX86 = $(Link) cr $@ $^ $(LinkFlags)

SrcC = $(shell ls *.c)

Obj = $(SrcC:%.c=%.o)

$(shell mkdir -p $(LibDir))
#$(shell mkdir -p $(OutDir))
$(shell mkdir -p $(ObjDirX86D) $(ObjDirX86))

CompCEcho = @echo gcc $< ... ...
CompCPPEcho = @echo g++ $< ... ...
AfterMake = @echo

.PHONY: all
all: DebugX86 ReleaseX86

.PHONY: clean
clean :
	rm -f $(ObjDirX86D)/* $(ObjDirX86)/*

.PHONY: DebugX86
DebugX86: StartX86D $(ProductX86D)
	$(AfterMake)

.PHONY: ReleaseX86
ReleaseX86: StartX86 $(ProductX86)
	$(AfterMake)

.PHONY: StartX86D
StartX86D:
	@echo "---> "Build $(Product) Debug X86 ... ...
	@echo $(CC) $(CFLAGS) $(CompX86DFlags) ...
	@echo $(CXX) $(CXXFLAGS) $(CompX86DFlags) ...

.PHONY: StartX86
StartX86:
	@echo "---> "Build $(Product) Release X86 ... ...
	@echo $(CC) $(CFLAGS) $(CompX86Flags) ...
	@echo $(CXX) $(CXXFLAGS) $(CompX86Flags) ...

$(ProductX86D): $(Obj:%=$(ObjDirX86D)/%)
	@echo link "-->" $@
	@$(LinkX86D)
	$(AfterLink)

$(ProductX86): $(Obj:%=$(ObjDirX86)/%)
	@echo link "-->" $@
	@$(LinkX86)
	$(AfterLink)

$(ObjDirX86D)/%.o: %.c
	$(CompCEcho)
	@$(CC) $(CFLAGS) $(CompX86DFlags) $@ $<

$(ObjDirX86)/%.o: %.c
	$(CompCEcho)
	@$(CC) $(CFLAGS) $(CompX86Flags) $@ $<

$(ObjDirX86D)/%.o: %.cpp
	$(CompCPPEcho)
	@$(CXX) $(CXXFLAGS) $(CompX86DFlags) $@ $<

$(ObjDirX86)/%.o: %.cpp
	$(CompCPPEcho)
	@$(CXX) $(CXXFLAGS) $(CompX86Flags) $@ $<

