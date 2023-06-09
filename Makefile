loq: main.o loq_add.o loq_list.o printb.o readc.o Itoa/itoa.o print/libprint.a
	$(CC) -s -z norelro -z noseparate-code -o loq $^

print/libprint.a: print/Makefile
	cd print; make

clean:
	rm -rf Itoa/itoa.o *.o loq

install: loq
	install loq /usr/local/bin

.PHONY: clean install
