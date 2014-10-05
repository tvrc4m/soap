#ifndef SOAP_H
#define SOAP_H
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define UNIT "g"

struct oil{
	int code;
	char *name; // 中文名
	// char *english; // 英文名
	double naoh; // 氢氧化钠皂化值
	int ins; //	INS值
};

struct fat{
	struct oil oil;
	double weight;
	double percent;
};

struct fats{
	struct fats *next;
	struct fat fat;
	unsigned int length;
};


struct soap{
	double total_weight;
	// struct fats *fats_cursor;
	struct fat *fats;
	int oils_num;
	double naoh_weight;
	double water_weight;
	double ins;
};

struct soap soap;

double get_soap_ins();

struct oil *get_oil(int code);

#endif