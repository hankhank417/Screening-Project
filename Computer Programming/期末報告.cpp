#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <time.h>
using namespace std;

int changeCharToInt(char *s){
	int i=0,tmp=0;
	for(i ; *(s+i)!='\0' ; i++){
		tmp=tmp*10+*(s+i)-'0';
	} 
	return tmp;
}

void label(FILE *file,const char *name){
	int i=0,thing;
	char s[64],str[50];
	vector<string> v;
	FILE *fptr;
	fptr = fopen(name,"a+");
	while(fgets(str,50,fptr)){
		int len = strlen(str);
		if(str[len-1]=='\n')
			str[--len]='\0';
		v.push_back(str);
		cout<<i+1<<". "<<v[i]<<endl;
		i++;
	}
	printf("%d. %s\n",i+1,"Other");
	printf("Your project : ");
	scanf("%d",&thing);
	if(thing!=i+1){
		fprintf(file,"%s",v[thing-1].c_str());
	}else{
		printf("Add a project name : ");
		scanf("%s",s);
		fprintf(fptr,"\n%s",s);
		fprintf(file,"%s",s);
	}
	fclose(fptr);
}

void item(FILE *file){
	int choose;
	printf("1. Food\n2. Drink\n3. Transport\n4. Shopping\n5. Entertainment\n6. Housing\n7. Digital\n8. Medical\n9. Income\n10. Misc\n");
	printf("Your subjects : ");
	scanf("%d",&choose);
	system("cls");
	switch(choose){
		case 1: 
			fprintf(file,"\n1");
			label(file,"Food.txt");
			break;
		case 2: 
			fprintf(file,"\n2");
			label(file,"Drink.txt");
			break;
		case 3: 
			fprintf(file,"\n3");
			label(file,"Transport.txt");
			break;
		case 4: 
			fprintf(file,"\n4");
			label(file,"Shopping.txt");
			break;
		case 5: 
			fprintf(file,"\n5");
			label(file,"Entertainment.txt");
			break;
		case 6: 
			fprintf(file,"\n6");
			label(file,"Housing.txt");
			break;
		case 7: 
			fprintf(file,"\n7");
			label(file,"Digital.txt");
			break;
		case 8: 
			fprintf(file,"\n8");
			label(file,"Medical.txt");
			break;
		case 9: 
			fprintf(file,"\n9");
			label(file,"Income.txt");
			break;
		case 10: 
			fprintf(file,"\n0");
			label(file,"Misc.txt");
			break;
	}
	char a[20];
	printf("Your spend amount : ");
	scanf("%s",&a);
	fprintf(file," $%s",a);
}

int getDate(FILE *file){
	int date;
	char s[50];
	fseek(file,0,SEEK_SET);
	while(fgets(s,50,file)){
	    if(s[0]=='-')
	        sscanf(s+5,"%d",&date);
	}
	return date;
}

void setDay(FILE *file){
	int today;
	char tmp[64];
	time_t t = time(0);
	strftime( tmp, sizeof(tmp), "%Y%m%d",localtime(&t) );
	today=changeCharToInt(tmp);
	if(getDate(file)!=today){
		fprintf(file,"\n-----%d-----",today);
	}
}
void printPieChart(FILE* file,int total,int s,int e){
	double cost[10]={0};
	int date,money;
	char str[50];
	const char *name[]={"Food","Drink","Transport","Shopping","Entertainment","Housing","Digital","Medical","Misc"};
	fseek(file,0,SEEK_SET);
	while(!feof(file)){
		fscanf(file,"%s",str);
		if(str[0]=='-')
			sscanf(str+5,"%d",&date);
		if( date<=e && date>=s ){
			if(str[0]=='1'){
				while(str[0]!='$')
					fscanf(file,"%s",str);
				sscanf(str+1,"%d",&money);
			    cost[0]+=money;
			}else if(str[0]=='2'){
				while(str[0]!='$')
					fscanf(file,"%s",str);
				sscanf(str+1,"%d",&money);
			    cost[1]+=money;
			}else if(str[0]=='3'){
				while(str[0]!='$')
					fscanf(file,"%s",str);
				sscanf(str+1,"%d",&money);
			    cost[2]+=money;
			}else if(str[0]=='4'){
				while(str[0]!='$')
					fscanf(file,"%s",str);
				sscanf(str+1,"%d",&money);
			    cost[3]+=money;
			}else if(str[0]=='5'){
				while(str[0]!='$')
					fscanf(file,"%s",str);
				sscanf(str+1,"%d",&money);
			    cost[4]+=money;
			}else if(str[0]=='6'){
				while(str[0]!='$')
					fscanf(file,"%s",str);
				sscanf(str+1,"%d",&money);
			    cost[5]+=money;
			}else if(str[0]=='7'){
				while(str[0]!='$')
					fscanf(file,"%s",str);
				sscanf(str+1,"%d",&money);
			    cost[6]+=money;
			}else if(str[0]=='8'){
				while(str[0]!='$')
					fscanf(file,"%s",str);
				sscanf(str+1,"%d",&money);
			    cost[7]+=money;
			}else if(str[0]=='0'){
				while(str[0]!='$')
					fscanf(file,"%s",str);
				sscanf(str+1,"%d",&money);
			    cost[8]+=money;
			}else if(str[0]=='9'){
				while(str[0]!='$')
					fscanf(file,"%s",str);
				sscanf(str+1,"%d",&money);
				cost[9]+=money;
			}
		}
	}
	printf("Total Income : %.0f\n\n",cost[9]);
	for(int i=0 ; i<9 ; i++){
		printf("%-15s%5.2f%\t",*(name+i),cost[i]/total*100);
		for(int j=1 ; j<=cost[i]/total*100 ; j++){
			cout<<"*";										//看你們要不要印星星 
		}
		puts("");
	}
	puts("");
}
void recordFile(FILE *file,int s,int e){
	int total=0,money=0,date;
	char str[50],str1[50];
	fseek(file,0,SEEK_SET);
	printf("--------------record----------------\n");
	while(!feof(file)){
		fscanf(file,"%s",str);
		if(str[0]=='-')
	        sscanf(str+5,"%d",&date);
		if( date<=e && date>=s ){
			if(str[0]=='9'){
				sscanf(str+1,"%s",&str1);
				printf("%s",str1);
				while(str[0]!='$'){
					fscanf(file,"%s",str);
					printf(" %s",str);
				}
				puts("");
				continue;
			}
			if(str[0]=='$'){
				sscanf(str+1,"%d",&money);
			    total+=money;
				printf(" %s",str);
			}
			else if(isdigit(str[0])!=0){
				sscanf(str+1,"%s",&str1);
				printf("%s",str1);
			}else{
				printf(" %s",str);
			}
			if(str[0]=='-' || str[0]=='$')
				puts("");
		}
	}
	printf("------------------------------------");
	puts("");
	printf("Total cost : %d\n",total);
	printPieChart(file,total,s,e);
	printf("------------------------------------\n");
} 
int main(){
	FILE *book;
	book = fopen("Account.txt","a+");
	while(1){
		int select;
		cout<<"What do you want to do ? "<<endl
			<<"1. Added cost"<<endl
			<<"2. Query record"<<endl
			<<"3. Quit"<<endl;
		cin>>select;
		if(select==1){
			system("cls");
			setDay(book);
			item(book);
		}else if(select==2){
			int range,start,end;
			system("cls");
			cout<<"Range of dates : "<<endl
				<<"1. All"<<endl
				<<"2. Customize"<<endl;
			cin>>range;
			system("cls");
			if(range==1){
				recordFile(book,0,99999999);
			}else if(range==2){
				cout<<"Starting time ( ex.20170101 ): ";
				cin>>start;
				cout<<"End Time ( ex.20171231 ): ";
				cin>>end;
				recordFile(book,start,end);
			}
		}else if(select==3){
			break;
		}else{
			cout<<"Input error."<<endl;
		}
	}
	fclose(book);
	system("Pause.");
	return 0;
} 
