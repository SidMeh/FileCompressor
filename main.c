#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trie.h"
#include "sequence.h"
void encode(FILE *fp,FILE *fi);
void decode(FILE *fp, FILE *fd);

int numlen(int num);
void makestring(FILE *fp, int num);


typedef struct dictElement{

    int prefixCode;
    char currChar;

}dictElement;



void getOutput(FILE *fp,int code, char *t);

void addElementToDictionary(int p, char c,int *l);
dictElement dictionary[4096];

int main() {

	FILE *fd, *fs, *fi;
	
	fs = fopen("source.txt","r+");
	
	if(fs == NULL){
		printf("Problem in opening File !!!\n");
//		return 0;
	}
	
	fd = fopen("destination.txt","w");
	
	if(fd == NULL){
		printf("Problem in compressing File1 !!!\n");
	//	return 0;
	}	
	
	fi = fopen("intermediate.txt","w");
	
	if(fi == NULL){
		printf("Problem in compressing File2 !!!\n");
	//	return 0;
	}	
	// encoding
//	encode(fs,fi);
	fclose(fi);
	fi = fopen("huffman1.txt","r");
	decode(fi,fd);
	
//	makestring(fi,1024);
	return 0;
}


int numlen(int num){
	if(num == 0)
		return 1;
	int i = 0;
	while(num > 0){
		num = num/10;
		i++;
	}
	return i;
}

void makestring(FILE *fp, int num){
	int k = numlen(num);
	char *s = (char*)malloc(sizeof(char)*k);
	int i;
	for(i = k-1;i >= 0;i--){
		s[i] = num%10 + '0';
		num = num/10;
	//	printf("%d %c ",num,s[i]);
	}
	fprintf(fp,"%s ",s);
}


void encode(FILE *fp, FILE *fi) {
	Trie T;
	init(&T);
	int arr[1000];
	int l = 0;
	insert_pattern(&T,"A");
	insert_pattern(&T,"B");
	insert_pattern(&T,"C");
	insert_pattern(&T,"D");
	insert_pattern(&T,"E");
	insert_pattern(&T,"F");
	insert_pattern(&T,"G");
	insert_pattern(&T,"H");
	insert_pattern(&T,"I");
	insert_pattern(&T,"J");
	insert_pattern(&T,"K");
	insert_pattern(&T,"L");
	insert_pattern(&T,"M");
	insert_pattern(&T,"N");
	insert_pattern(&T,"O");
	insert_pattern(&T,"P");
	insert_pattern(&T,"Q");
	insert_pattern(&T,"R");
	insert_pattern(&T,"S");
	insert_pattern(&T,"T");
	insert_pattern(&T,"U");
	insert_pattern(&T,"V");
	insert_pattern(&T,"W");
	insert_pattern(&T,"X");
	insert_pattern(&T,"Y");
	insert_pattern(&T,"Z");
	insert_pattern(&T,"a");
	insert_pattern(&T,"b");
	insert_pattern(&T,"c");
	insert_pattern(&T,"d");
	insert_pattern(&T,"e");
	insert_pattern(&T,"f");
	insert_pattern(&T,"g");
	insert_pattern(&T,"h");
	insert_pattern(&T,"i");
	insert_pattern(&T,"j");
	insert_pattern(&T,"k");
	insert_pattern(&T,"l");
	insert_pattern(&T,"m");
	insert_pattern(&T,"n");
	insert_pattern(&T,"o");
	insert_pattern(&T,"p");
	insert_pattern(&T,"q");
	insert_pattern(&T,"r");
	insert_pattern(&T,"s");
	insert_pattern(&T,"t");
	insert_pattern(&T,"u");
	insert_pattern(&T,"v");
	insert_pattern(&T,"w");
	insert_pattern(&T,"x");
	insert_pattern(&T,"y");
	insert_pattern(&T,"z");
	insert_pattern(&T,"[");
	insert_pattern(&T,"\\");
	insert_pattern(&T,"]");
	insert_pattern(&T,"^");
	insert_pattern(&T,"_");
	insert_pattern(&T,"`");
	insert_pattern(&T,"1");
	insert_pattern(&T,"2");
	insert_pattern(&T,"3");
	insert_pattern(&T,"4");
	insert_pattern(&T,"5");
	insert_pattern(&T,"6");
	insert_pattern(&T,"7");
	insert_pattern(&T,"8");
	insert_pattern(&T,"9");
	insert_pattern(&T,"0");
	insert_pattern(&T,"!");
	insert_pattern(&T,"@");
	insert_pattern(&T,"#");
	insert_pattern(&T,".");
	insert_pattern(&T,"%");
	insert_pattern(&T,"&");
	insert_pattern(&T,"*");
	insert_pattern(&T,"(");
	insert_pattern(&T,")");
	insert_pattern(&T," ");
	insert_pattern(&T,"\t");
	insert_pattern(&T,"\n");
	insert_pattern(&T,",");
//	insert_pattern(&T,".");
	char sample[5000];
	fgets(sample,5000,fp);
	char output[1000],P1[10] = "",temp[100],nil[1] = "\0",P[10] ,C,K[2];
	int i = 0,k,m,f,j = 0;
	P[0] = sample[0];
	P1[0] = sample[0];
//	i++;
	while(sample[i] != '\0'){
		i++;
		C = sample[i];		
		strncat(P1,&C,1);
		m = check_string(&T,P1);
		if(m != -1)
			strncat(P,&C,1);
		else{
			k = insert_pattern(&T,P);
			strncat(P,&C,1);
			insert_pattern(&T,P);
			arr[l++] = k;
			strcpy(P,nil);
			strcpy(P1,nil);
			strncat(P,&C,1);
			strncat(P1,&C,1);		
			printf("%d ",k);
		//	makestring(fi,k);
			fprintf(fi,"%d ",k);			
		}
	}
	arr[l++] = m;
	fprintf(fi,"%d ",-1);
}


void decode(FILE *fp, FILE *fd) {

	 for(int i=0;i<=25;i++)
    {	dictElement tmp;
        
        tmp.prefixCode = -1;
        tmp.currChar = i+65;
        dictionary[i] = tmp;
    }
	 for(int i=0;i<=25;i++)
    {   dictElement tmp;
        tmp.prefixCode = -1;
        tmp.currChar = i+97;
        dictionary[i+26] = tmp;
    }
    dictElement tmp;
        tmp.prefixCode = -1;
	 tmp.currChar = '[';
      dictionary[52] = tmp;
	 tmp.currChar = '\\';
      dictionary[53] = tmp;
	 tmp.currChar = ']';
      dictionary[54] = tmp;      
	 tmp.currChar = '^';
      dictionary[55] = tmp;      
	 tmp.currChar = '_';
      dictionary[56] = tmp;
	 tmp.currChar = '`';
      dictionary[57] = tmp;      
	 tmp.currChar = '1';
      dictionary[58] = tmp;
	 tmp.currChar = '2';
      dictionary[59] = tmp;
	 tmp.currChar = '3';
      dictionary[60] = tmp;    
	 tmp.currChar = '4';
      dictionary[61] = tmp;      
      tmp.currChar = '5';
      dictionary[62] = tmp;
      tmp.currChar = '6';
      dictionary[63] = tmp;
      tmp.currChar = '7';
      dictionary[64] = tmp;
      tmp.currChar = '8';
      dictionary[65] = tmp;
      tmp.currChar = '9';
      dictionary[66] = tmp;
      tmp.currChar = '0';
      dictionary[67] = tmp;
      tmp.currChar = '!';
      dictionary[68] = tmp;
      tmp.currChar = '@';
      dictionary[69] = tmp;
      tmp.currChar = '#';
      dictionary[70] = tmp;
      tmp.currChar = '.';
      dictionary[71] = tmp;
      tmp.currChar = '%';
      dictionary[72] = tmp;
      tmp.currChar = '&';
      dictionary[73] = tmp;
      tmp.currChar = '*';
      dictionary[74] = tmp;
      tmp.currChar = '(';
      dictionary[75] = tmp;
      tmp.currChar = ')';
      dictionary[76] = tmp;
      tmp.currChar = ' ';
      dictionary[77] = tmp;
   //   tmp.currChar = '.';
  //    dictionary[78] = tmp;
     tmp.currChar = '\t';
     dictionary[78] = tmp;
      tmp.currChar = '\n';
      dictionary[79] = tmp;
     tmp.currChar = ',';
     dictionary[80] = tmp; 
        
    int prevCode;
    int currCode;
    char ch = 'b';
    int limitingCode = 80;

	int num;
	fscanf(fp,"%d",&num);
//	fscanf(fd,"%d",&num);
    prevCode = num;
//	printf("dec%d",num);
    getOutput(fd,prevCode , &ch);
   
    int index = 1;
    while(1)
    {	fscanf(fp,"%d",&num);
        currCode = num;
        if(num < 0)
        	return;
        char tmpCh;
        if(currCode > limitingCode)
        {	
            getOutput(fd,prevCode , &tmpCh);
            printf("%c",ch);
		  fprintf(fd,"%c",ch);
        }
        else
        {		
            getOutput(fd,currCode,&tmpCh);

        }

        ch = tmpCh;

        addElementToDictionary(prevCode,ch,&limitingCode);
        index++;

        prevCode =  currCode;

}


}



void getOutput(FILE *fp,int code, char *t)
{//	printf("%d %c",code,dictionary[code].currChar);
    if(dictionary[code].prefixCode == -1)
    { //   printf("UYT");
        *t  = dictionary[code].currChar;
        char tmpt = *t;
        printf("%c",tmpt);
      fprintf(fp,"%c",tmpt);
        return ;

    }
   else
    {// printf("UYT");
        int pre = dictionary[code].prefixCode;
        getOutput(fp,pre, t);
        char curr = dictionary[code].currChar;
        printf("%c",curr);
        fprintf(fp,"%c",curr);

    }




}

void addElementToDictionary(int p, char c,int *l)
{
    *l = *l+1;
    dictionary[(*l)].currChar = c;
    dictionary[(*l)].prefixCode = p;
    return;

}




