#include "common.h"

char *strpad(char *str,int total,const char *padding){
	if(strlen(str)>=total) return str;
	for (int i = strlen(str); i < total; ++i){
		strcat(str,padding);
	}
	return str;
}

char *strppad(char *str,int total,const char *padding){
	int str_len=strlen(str);
	if(str_len>=total) return str;
	int diff=total-str_len;
	for (int i = total; i >= 0; --i){
		if(i>=diff) *(str+i)=*(str+i-diff);
		else *(str+i)=*padding;
	}
	return str;
}

int start_with(char *str,char *prefix){
	int len=strlen(str),pre_len=strlen(prefix);
	if(len<pre_len) return 0;
	for( ; ; str++,prefix++){
		if(!*prefix) return 1;
		return *str==*prefix;
	}
}

int end_with(const char *str,const char *suffix){
	int len=strlen(str) ,suff_len=strlen(suffix);
	if(suff_len>len) return 0;
	return !strcmp(str+suff_len,suffix);
}