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

int start_with(const char *str,char *prefix){
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
	return !strcmp(str+len-suff_len,suffix);
}

char *strchl(const char *str,const char ch){
	int len=strlen(str);
	char *dest=(char*)malloc(sizeof(char)*len);
	char *p=dest;
	while(*str){
		if(*str==ch) return p;
		*dest=*str;
		dest++;
		str++;
	}
	return p;
}

int soap_strlen(const char *str){
	int len=0;
	while(*str){
		char tmp[3]={""};
		strncpy(tmp,str,3);
		printf("%s\t%lu\t %lu\n",tmp,sizeof(tmp), strlen(tmp));
		if(strlen(tmp)==1 && strcmp("?",tmp)) len++;
		else len+=strlen(tmp)/strlen(tmp)*2;
		str++;
		str++;
		str++;
	}
	return len;
}