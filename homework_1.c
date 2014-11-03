#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct nod {
	char *val;
	struct nod *next;
	struct nod *prev;
}nod;
nod *Lista;
nod *initList(nod *cap)
{
	
	cap=NULL;
	return cap;	
}

nod *insertList(nod *cap, char *line)
{
	nod *nou, *aux;
	
	if (cap==NULL)
	{
		cap=(nod*)malloc(sizeof(nod));
		cap->val=line;
		cap->next=NULL;
		cap->prev=NULL;
		return cap;
	}	
	else
	{
		nou=(nod*)malloc(sizeof(nod));
		nou->val=line;
		aux=cap;
		
		while(aux->next!=NULL)
			aux=aux->next;
		nou->prev=aux;
		aux->next=nou;
		nou->next=NULL;	
	}
return cap;
}

nod *insertText(nod *cap, char *line, int *contorLine, int *contorChar)
{
	nod *aux1, *aux2;
	aux1=cap;
	aux2=cap;
	char *cmd, *cuv[3];
	char *sep=" .,\n";
	int i,q=0,l,c;
	for (i=1;i<*contorLine;i++)
		aux1=aux1->next;

	cmd=strstr(aux1->val,"::");
        cuv[q++]=strtok(cmd,sep);
      	if (strcmp(cuv[q-1],"::gl")==0)
        {
                cuv[q++]=strtok(0,sep);
                l=atoi(cuv[q-1]);
		c=1;
                strcpy(cmd,cmd+strlen(cmd)); 
		for (i=1;i<l;i++)
			aux2=aux2->next;			
	aux1=aux1->next;
	char *temp;
	temp=aux2->val;
	int ld=strlen(temp), ls=strlen(line);
	strcpy(temp+ld+ls,temp);
	strcpy(temp,line);
	strcpy(temp+ls,temp+ld+ls);
/*	if (comd[0]!=NULL)
	{
		if (strcmp(comd[0],"::gl")==0)
			
			
	}*/
//	else 
//	{
		if (strstr(aux->val,"\n")!=NULL)
		{
			nod *nou=(nod*)malloc(sizeof(nod));
			nou->val=strstr(aux->val,"\n")+1;
			nou->next=aux->next;
			aux->next->prev=nou;
			aux->next=nou;
			nou->prev=aux;
			(*contorLine)++;
			*contorChar=1;
		}
//	}
return cap;	
}

char * gotoLine(nod *cap, int l, int *contorLine, int *contorChar)
{
	nod *aux;
	aux=cap;
	int i;
	for (i=1;i<*contorLine;i++)
		aux=aux->next;
	while (*contorLine<l)
	{
		aux=aux->next;
		(*contorLine)++;
	}
	while (*contorLine>l)
	{
		aux=aux->prev;
		(*contorLine)--;
	}
	*contorChar=1;
return aux->val;
}

char *gotoChar(nod *cap, int c, int l, int *contorLine, int *contorChar)
{
	nod *aux;
	char *temp;
	int i;
	aux=cap;
	for (i=1;i<*contorLine;i++)
		aux=aux->next;
//	puts(aux->val);
//	printf("contorline=%d\n",*contorLine);
	while  (*contorLine<l)
        {
                  aux=aux->next;
//		  puts(aux->val);
                  *contorLine=(*contorLine)++;
//		  printf("contorLine=%d\n",*contorLine);
        }
        while (*contorLine>l)
        {
                  aux=aux->prev;
                  (*contorLine)--;
        }
//	printf("contorLine=%d\n",*contorLine);
//	puts(aux->val);
//	printf("\n");
	temp=aux->val;
	*contorChar=1;
	while (*contorChar<c)
	{
		temp=temp+1;
	        *contorChar=(*contorChar)++;	
	}

return temp;
} 

void backspace(nod *cap, char *poz, int *contorLine, int *contorChar)
{
	nod *aux;
	aux=cap;
	int i;
	for (i=1;i<*contorLine;i++)
		aux=aux->next;
	if (poz==NULL)
	{
		poz=aux->val + strlen(aux->val);
		strcpy(poz-1,poz);
		poz=poz-1;
		*contorChar=strlen(aux->val);
	}
	else
	{
		if (*contorChar==1)
		{
			
			poz=aux->prev->val+strlen(aux->prev->val);
			*contorChar=strlen(aux->prev->val);
			strcat(aux->prev->val,aux->val);
			strcpy(poz-1,poz);
			poz=poz-1;
			aux->prev->next=aux->next;
			aux->next->prev=aux->prev;
			(*contorLine)--;
			nod *temp;
			temp=aux;
			aux=aux->prev;
			free(temp);			
		}
		else
		{
			poz=aux->val+*contorChar-1;
			strcpy(poz-1,poz);
			poz=poz-1;
			(*contorChar)--;
		}

	}
}
void callFunct(nod *cap,char *poz, int *contorLine, int *contorChar,int *tempL, int *tempC )
{
     nod *aux;
     aux=cap;
     int l, c, q=0;
     char *cuv[3], *sep="., \n", *cmd;
   	   while (aux!=NULL)
                if (strstr(aux->val,"::")==NULL)
		{                      
			aux=aux->next;		
			(*contorLine)++;
			*contorChar=strlen(aux->val);
                }
		else
                {
			if (aux->val[0]!=':' && aux->val[1]!=':')
			{
				(*contorLine)++;
				*contorChar=strlen(aux->val);
	/*			cmd=strstr(aux->val,"::");
				cuv[q++]=strtok(cmd,sep);
				if (strcmp(cuv,"::gl")==0)
				{
					cuv[q++]=strtok(0,sep);
					l=atoi(cuv);
					strcpy(cmd,cuv);
					strcpy(cmd,cmd+strlen(cuv));
					strcat(aux->val,"\n");				*/
					printf("%d %d",*tempL,*tempC);
			
				}
			}
       			else
			{
	                 	cuv=strtok(aux->val,sep);
				if (strcmp(cuv,"::b")==0)
                                	backspace(cap,poz,&contorLine, &contorChar); 

				if (strcmp(cuv,"::gl")==0)
				{
					cuv=strtok(0,sep);
					l=atoi(cuv);
					poz=gotoLine(cap,l, &contorLine, &contorChar);
					//	printf("::gl %d =%c\n",l, *poz);
					//puts(poz);
				}
				if (strcmp(cuv,"::gc")==0)
				{
					cuv=strtok(0,sep);
					c=atoi(cuv);	
					cuv=strtok(0,sep);
					if (cuv!=NULL)
						l=atoi(cuv);					
					else
						l=contorLine;
					poz=gotoChar(cap,c,l, &contorLine, &contorChar);
					//	printf("::gc %d [%d]=%c\n",c,l,*poz);
//					puts(poz);
				} 			
				aux=aux->next;   
			}
		}
}
void printList(nod *cap)
{
	nod *aux;
	aux=cap;
	while(aux!=NULL)
	{
		puts(aux->val);
		aux=aux->next;
	}
}

void printFile(nod *cap, FILE  *fisier)
{
	nod *aux;
	aux=cap;
	while (aux!=NULL)
	{
		if (strstr(aux->val,"::")==NULL)
			fputs(aux->val,fisier);
				
		aux=aux->next;
	}
}

int main (int argc, char *argv[])

{
	FILE *fisier;
	char *line,*poz=NULL;
	int i, contorLine=1, contorChar,tempL=1,tempC;   
	Lista=initList(Lista);
	fisier=fopen(argv[1],"w");
	do
	{
		line=(char*)malloc(100*sizeof(char));
		gets(line);
		strcat(line,"\n");
		Lista=insertList(Lista,line);
	}
	while (strcmp(line,"::q\n")!=0);
	printf("\n");	
	callFunct(Lista,poz,&contorLine,&contorChar);
	
	printList(Lista);
//	printf("cL %d , cC %d", contorLine, contorChar);
	printFile(Lista,fisier);
	fclose(fisier);		
return 0;
}
