#ifndef SOAP_H
#define SOAP_H
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define UNIT "g"

#define NAOH_TO_WATER(x,y) (x)*(y)

struct oil{
	int code;
	char *name; // 中文名
	double naoh; // 氢氧化钠皂化值
	int ins; //	INS值
};

struct fat{
	struct oil oil;
	double weight;
	double percent;
};

struct soap{
	double total_weight;
	int oils_num;
	struct fat *fats;
	
	double naoh_weight;
	double water_weight;
	char *water_weight_span;
	double ins;
};

struct soap soap;

struct oil *get_oil(int code);

#endif