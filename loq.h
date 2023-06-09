#ifndef LOQ_H
#define LOQ_H

#ifdef __cplusplus
extern "C" {
#endif

#define bool int
#define true 1
#define false 0

void loq_add(char *);
void loq_list();
void printb(int, char, bool);
char readc(int);

extern char **environ;

#ifdef __cplusplus
}
#endif

#endif
