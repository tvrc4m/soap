#include <regex.h>
#include "soap.h"
#include "common.h"

struct oil oils[]={
	{01,"椰子油",0.1900,258},
	{02,"油菜花籽",0.1240,56},
	{03,"米糠油",0.1280,70},	
	{04,"玫瑰籽油",0.1378,0},
	{05,"红花油",0.1360,47},
	{06,"苧麻油",0.1240,56},
	{07,"油菜花",0.1240,56},
	{ 8,"芝麻油",0.1330,81},
	{ 9,"乳油木果脂",0.1280,116},
	{10,"白油",0.1360,115},
	{11,"葵花籽油",0.1340,63},
	{12,"核桃",0.1353,45},
	{13,"小麦胚芽",0.1310,58},
	{14,"玉米油",0.1360,69},
	{15,"南瓜籽",0.1331,67},
	{16,"开心果",0.1328,92},
	{17,"花生",0.1360,99},
	{18,"水蜜桃核仁油",0.1370,96},
	{19,"羚羊油",0.1672,204},
	{20,"葵花籽油",0.1340,63},
	{21,"核桃",0.1353,45},
	{22,"小麥胚芽",0.1310,58},
	{23,"玉米油",0.1360,69},
	{24,"南瓜籽",0.1331,67},
	{25,"开心果",0.1328,92},
	{26,"芒果脂",0.1371,146},
	{27,"芥子油",0.1241,56},
	{28,"橄榄油",0.1340,109},
	{29,"棕榈油",0.1410,145},
	{30,"棕榈脂",0.1560,183},
	{31,"棕榈核油",0.1560,227},
	{32,"棉籽油",0.1386,89},
	{33,"芒果油",0.1280,120},
	{34,"澳洲胡桃油",0.1390,119},
	{35,"亚麻仁油",0.1357,-6},
	{36,"夏威夷核果",0.1350,24},
	{37,"榛果油",0.1356,94},
	{38,"荷荷芭",0.0690,11},
	{39,"麻籽油",0.1345,39},
	{40,"葡萄籽油",0.1265,66},
	{41,"亚麻籽",0.1357,-6},
	{42,"月见草油",0.1357,30},
	{43,"甜杏仁油",0.1360,97},
	{44,"山茶花",0.1362,108},
	{45,"杏桃仁油",0.1350,91},
	{46,"酪梨油",0.1339,0},
	{47,"巴西核果",0.1750,230},
	{48,"蜂蠟",0.0690,84},
	{49,"琉璃苣",0.1357,50},
	{50,"芥花油",0.1324,56},
	{51,"蓖麻油",0.1286,95},
	{52,"大豆油",0.1350,61},
	{53,"可可脂",0.1370,157},
	{54,"山茶花油",0.1362,108},
	{55,"葡萄籽油",0.1265,66},
	{56,"菜籽油",0.124,56},
	{57,"向日葵籽油",0.134,63},
	{58,"南瓜籽油",0.1331,67},
	{59,"大麻籽油",0.1345,39},
	{60,"杏桃核油",0.135,91},
	{61,"玫瑰果油",0.1378,0},
	{62,"雞油",0.1389,130},
	{63,"駝鸟油",0.139,128},
	{64,"羊毛脂",0.0741,83},
	{65,"牛蹄油",0.141,124},
	{66,"牛足油",0.1359,124},
	{67,"猪油",0.138,139},
	{68,"牛脂/牛油",0.1619,191},
	{69,"羚羊油",0.1672,204}
};

const int OIL_TOTAL=count(oils);

int calc_soap_weight_ins(){
	double naoh,water,ins;
	for(int i=0,num=soap.oils_num;i<num;i++){
		naoh+=soap.fats[i].weight*soap.fats[i].oil.naoh;
		ins+=soap.fats[i].percent*soap.fats[i].oil.ins/100;
	}
	soap.naoh_weight=naoh;
	soap.water_weight=naoh*3;
	char *span=(char*)malloc(sizeof(char)*12);
	sprintf(span,"%.1f~%.1f",naoh*2.6,naoh*3.2);
	soap.water_weight_span=span;
	soap.ins=ins;
	return 0;
}

struct oil *get_oil(int code){
	for (int i = 0; i < OIL_TOTAL; ++i){
		if(oils[i].code==code){
			return &oils[i];
		}
	}
	return NULL;
}

static int set_soap_params(int argc,const char **argv){
	int num=0;
	while(*argv){
		if(!strcmp("-o",*argv)){
			argv++;
			if(atoi(*argv))
				argv++;
			soap.oils_num++;		
		}else if(!strcmp("-w",*argv)){
			argv++;
			soap.total_weight=atof(*argv);
		}
		argv++;
	}
	return 0;
}

int check_cmd(const char **argv){
	while(*argv){
		argv++;
	}
	return 1;
}

int cmd_list(int argc,const char **argv){
	char *fields[]={"编码","植物油","皂化价","NIS值"};
	int cols=count(fields);
	int max_len[4],rows[OIL_TOTAL+3][cols];
	for (int i = 0; i < cols; ++i){
		max_len[i]=strlen(fields[i]);
	}
	for (int i = 0; i < OIL_TOTAL; ++i){
		if(strlen(oils[i].name)>max_len[1]) max_len[1]=strlen(oils[i].name);
	}
	for (int i = 0,r=0; i < OIL_TOTAL+3; ++i){
		for (int j = 0; j < cols; ++j){
			char *text=(char*)calloc(sizeof(char),max_len[j]);
			if(i==0 || i==2 || i==OIL_TOTAL+2){
				strpad(text,max_len[j],"-");
				printf("+%s", text);
			}else if(i==1){
				strcat(text,fields[j]);
				strpad(text,max_len[j]/3*2," ");
				printf("| %s\t", text);
			}else{
				switch(j){
					case 0:sprintf(text,"%d",oils[r].code);break;
					case 1:sprintf(text,"%s",oils[r].name);break;
					case 2:sprintf(text,"%.4f",oils[r].naoh);break;
					case 3:sprintf(text,"%d",oils[r].ins);break;
				}
				strpad(text,max_len[j]/3*2," ");
				printf("| %s\t", text);
			}
			free(text);
		}
		if(i==0 || i==2 || i==OIL_TOTAL+2){
			printf("%s\n", "+");
		}else{
			if(i!=1){
				r++;
			}
			printf("%s\n", "|");
		}
	}
	return 0;
}

static int print_soap(){
	char *fields[]={"成分","用量(g)"};
	int cols=count(fields);
	int oils_num=soap.oils_num;
	int row_count=oils_num+3+2+1;
	int max_len[4];
	char *rows[row_count][cols];

	rows[0][0]="+";
	rows[0][1]="+";
	rows[2][0]="+";
	rows[2][1]="+";

	for (int i = 0; i < cols; ++i){
		rows[1][i]=fields[i];
	}

	for (int i = 0; i < oils_num; ++i){
		rows[i+3][0]=(char*)malloc(sizeof(char)*50);
		sprintf(rows[i+3][0],"%s(%.0f%c)",soap.fats[i].oil.name,soap.fats[i].percent,'%');
		rows[i+3][1]=(char*)malloc(sizeof(char)*20);
		sprintf(rows[i+3][1],"%.1f",soap.fats[i].weight);
	}

	
	rows[oils_num+3][0]="碱(NAOH)";
	rows[oils_num+3][1]=(char*)malloc(sizeof(char)*20);
	sprintf(rows[oils_num+3][1],"%.1f",soap.naoh_weight);

	rows[oils_num+4][0]="水(H2O)";
	rows[oils_num+4][1]=(char*)malloc(sizeof(char)*20);
	sprintf(rows[oils_num+4][1],"%s",soap.water_weight_span);
	
	for (int i = 0; i < cols; ++i){
		max_len[i]=strlen(fields[i]);
	}

	for (int i = 3; i < oils_num+2; ++i){
		if(strlen(rows[i][0])>max_len[0]) max_len[0]=strlen(rows[i][0]);
		if(strlen(rows[i][1])>max_len[1]) max_len[1]=strlen(rows[i][1]);
	}

	for (int i = 0,r=0; i < row_count; ++i){
		for (int j = 0; j < cols; ++j){
			char *text=(char*)calloc(sizeof(char),max_len[j]);
			if(i==0 || i==2 || i==row_count-1){
				strpad(text,max_len[j],"-");
				printf("+%s", text);
			}else if(i==1){
				strcat(text,fields[j]);
				strpad(text,max_len[j]/3*2," ");
				printf("| %s\t", text);
			}else{
				strcat(text,rows[i][j]);
				strpad(text,max_len[j]/3*2," ");
				printf("| %s\t", text);
			}
			free(text);
		}
		if(i==0 || i==2 || i==row_count-1){
			printf("%s\n", "+");
		}else{
			r++;
			printf("%s\n", "|");
		}
	}

	int cols_2=max_len[0]+max_len[1];
	char soap_ins[cols_2];
	sprintf(soap_ins,"肥皂的软硬度值(NIS):%.1f",soap.ins);
	strppad(soap_ins,cols_2," ");
	printf("| %s\n",soap_ins);

	char *bot=(char*)calloc(sizeof(char),cols_2);
	strpad(bot,cols_2,"-");
	printf("+ %s+\n", bot);

	printf("| 肥皂的总重量:%.1fg\n", soap.total_weight);
	
	printf("+ %s+\n", bot);

	return 0;
}


int cmd_calc(int argc,const char **argv){
	if(check_cmd(argv)){

	}

	set_soap_params(argc,argv);
	double total_weight=0;
	struct fat *fats=(struct fat*)calloc(sizeof(struct fat),soap.oils_num);
	while(*argv){
		if(!strcmp(*argv,"-o")){
			
			argv++;
			if(atoi(*argv)){
				static int i = 0;
				int code=atoi(*argv);
				argv++;
				struct fat fat;
				struct oil *oil=get_oil(code);
				fat.oil=*oil;
				if(end_with(*argv,"%")){
					double percent=atof(strchl(*argv,'%'));
					fat.percent=percent;
					fat.weight=soap.total_weight*percent/100;
					total_weight+=fat.weight;
				}else if(end_with(*argv,"g")){
					double weight=atof(strchl(*argv,'g'));
					total_weight+=weight;
					fat.weight=weight;
					fat.percent=weight/soap.total_weight*100;
				}else{
					double percent=atof(*argv);
					fat.percent=percent;
					fat.weight=soap.total_weight*percent/100;
					total_weight+=fat.weight;
				}
				fats[i]=fat;
				i++;
			}
		}
		argv++;
	}

	if(abs(soap.total_weight-total_weight)>1){
		printf("皂的质量为%.1fg,但是油的总质量为:%.1fg\n", soap.total_weight, total_weight);
		exit(0);
	}

	soap.fats=fats;

	calc_soap_weight_ins();
	
	print_soap();

	return 0;
}
