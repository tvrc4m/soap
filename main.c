#include "common.h"
#include "soap.h"
#include "builtin.h"


struct builtin_cmd cmds[]={
	{"list",cmd_list},
	{"calc",cmd_calc}
};

int run_builtin(int argc,const char **argv){
	for(int i=0,c=count(cmds);i<c;i++){
		if(!strcmp(*argv,cmds[i].name)){
			return cmds[i].fn(argc,argv);
		}
	}
	
	return 0;
}

int handle_builtin(int argc,const char **argv){

	return 0;
}



int main(int argc,char **av){
	const char **argv=(const char**)av;

	argv++;

	return run_builtin(argc-1,argv);
}