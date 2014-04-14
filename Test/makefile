Product = Test
Platform = $(shell uname)
Include = ../Include ../lua/src
LibDir 	= ../Library/$(Platform)
Lib 	= lua LuaPort
Define 	=
ObjDir	= ../Build/$(Platform)
OutDir	= ../Product/$(Platform)

CC = gcc
CXX = g++
CFLAGS =
CXXFLAGS = $(CFLAGS) -Wno-invalid-offsetof

Link = g++
LinkFlags = -fPIC -Wl,-rpath ./

ProductX86D = $(OutDir)/$(Product)D
ProductX86  = $(OutDir)/$(Product)

ObjDirX86D = $(ObjDir)/$(Product)/DebugX86
ObjDirX86  = $(ObjDir)/$(Product)/ReleaseX86

CompX86DFlags = $(Include:%=-I%) $(Define:%=-D%) -m32 -c -g -D_DEBUG -o
CompX86Flags  = $(Include:%=-I%) $(Define:%=-D%) -m32 -c -O3 -DNDEBUG -o

LinkX86D = $(Link) -o $@ $^ $(LinkFlags) -m32 $(LibDir:%=-L%) $(Lib:%=-l%D)
LinkX86 = $(Link) -o $@ $^ $(LinkFlags) -m32 $(LibDir:%=-L%) $(Lib:%=-l%)

#SrcC = $(shell ls *.c)
SrcCPP = $(shell ls *.cpp) 

Obj = $(SrcC:%.c=%.o) $(SrcCPP:%.cpp=%.o)

$(shell mkdir -p $(LibDir))
$(shell mkdir -p $(OutDir))
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

