
objs = a.o b.o c.o
dep_files := $(patsubst %,.%.d, $(objs))
dep_files := $(wildcard $(dep_files))

CFLAGS = -Werror -I.

test : a.o b.o c.o
	gcc -o test $^
	echo $(dep_files)

ifneq ($(dep_files),)
include $(dep_files)
endif

%.o : %.c
	gcc -c -o $@ $< -MD -MF .$@.d

clean:
	rm *.o test

.PHONY: clean

distclean:
	rm $(dep_files)

.PHONY: distclean