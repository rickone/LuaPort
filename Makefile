# make LuaPort's all projects(Libs, Tests)

MAKE = cd $@ && make

all: lua/src Source Test
.PHONY: all

clean:
	rm -rf Build
.PHONY: clean

lua/src:
	$(MAKE)
.PHONY: lua/src

Source:
	$(MAKE)
.PHONY: Source

Test: lua/src Source
	$(MAKE)
.PHONY: Test

