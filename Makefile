loq: main.o loq_add.o loq_list.o Itoa/itoa.o
	$(CC) -s -z norelro -z noseparate-code -o loq main.o loq_list.o loq_add.o Itoa/itoa.o

clean:
	rm -rf Itoa/itoa.o *.o loq

.PHONY: clean
