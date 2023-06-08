loq: main.c loq_add.c loq_list.c
	cc -s -z norelro -z noseparate-code -o loq main.c loq_list.c loq_add.c
