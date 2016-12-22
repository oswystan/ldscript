#######################################################################
## 
## 1. only a.out is useful for you.
## 2. default.lds is the default ldscript used by ld. so when the main.lds
##    can not work. please use this file by inserting the sections(._local_init)
##    before bss section
## 
#######################################################################
.PHONY: all clean

all: a.out default.lds

a.out: main.c main.lds
	@gcc main.c -T main.lds -o $@
	@echo DONE

default.lds:
	@ld --verbose | sed -e '1,/^====/d' | sed -e '/^====/d' > $@

clean:
	@rm -f a.out default.lds

#######################################################################

