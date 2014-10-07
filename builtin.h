#ifndef SOAP_BUILTIN_H
#define SOAP_BUILTIN_H
#include <stdio.h>
#include <stdlib.h>

struct builtin_cmd{
	char *name;
	int (*fn)(int argc,const char **argv);
};

extern int cmd_list(int argc,const char **argv);
extern int cmd_calc(int argc,const char **argv);

#endif