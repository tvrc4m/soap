#ifndef SOAP_COMMON_H
#define SOAP_COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define count(x) (sizeof(x))/(sizeof(x[0]))

char *strpad(char *str,int total,const char *padding);

char *strppad(char *str,int total,const char *padding);

int start_with(char *str,char *prefix);

int end_with(const char *str,const char *suffix);

#endif