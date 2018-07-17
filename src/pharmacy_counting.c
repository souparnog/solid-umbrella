#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXLEN 100000000 

typedef struct 
{
	int id[MAXLEN], drug_cost[MAXLEN];
	char last_name[MAXLEN][100], first_name[MAXLEN][100], drug_name[MAXLEN][100]; 
}Pharm;

Pharm P;

typedef struct 
{
	int num_pres[MAXLEN], total_cost[MAXLEN];
	char d_name[MAXLEN][100];
}Drug;

Drug D;

FILE *fpt1, *fpt2;
int pharm_ctr, drug_ctr;
char input_file[100];

void readFile()
{
	char line[5000], temp[500];
	int i,j,comma_ctr;
	pharm_ctr = 0;
	fpt1=fopen(input_file,"r");
	while(fgets(line,5000,fpt1)!=NULL)
	{
	  
	  if((int)line[0] >= 48 &&  (int)line[0] <= 57)  // first entry should be id
	  {
	
        i=0; comma_ctr=0;  
	    while(comma_ctr<4)
	    {
		  j=0; 
		  while(line[i]!=',')
		  {   
		    
		    temp[j]=line[i];
		    j++; i++;
		    
		  }
	      temp[j]='\0'; comma_ctr++;
		  if(comma_ctr == 1)
		  {
		    P.id[pharm_ctr]=atoi(temp);
		    temp[0]='\0';j=0; i++;
		    
          }
		  else if(comma_ctr == 2)
		  {
		    strcpy(P.last_name[pharm_ctr],temp);
		    temp[0]='\0';j=0; i++;
		
		  }
		  else if(comma_ctr == 3)
		  {
		    strcpy(P.first_name[pharm_ctr],temp);
		    temp[0]='\0';j=0; i++;
		  }
		  else 
		  {
		    strcpy(P.drug_name[pharm_ctr],temp);
		    temp[0]='\0';j=0; i++;
	        do
	        {   
      	        temp[j]=line[i]; j++, i++;	
      	        if(line[i] == ' ' || line [i] == '\n')
      	          break;  
            }while(line[i]);
  	        temp[j]='\0';
  	        P.drug_cost[pharm_ctr] = atoi(temp);
  	        pharm_ctr++;
  	      }
  	     }
  	    }   
      }
      fclose(fpt1);


}
void remove_duplicates()
{
	int i,j,unique;
	drug_ctr = 0;
	for(i = 0;i < pharm_ctr;i++)
	{
	   if(P.drug_cost[i] == -1)  // already encountered
	      continue;
	      
	   strcpy(D.d_name[drug_ctr],P.drug_name[i]);
	   D.total_cost[drug_ctr] = P.drug_cost[i];
	   D.num_pres[drug_ctr] = 1; 
	     
	   for(j = i+1; j< 	pharm_ctr;j++)
	   {
	       unique = 1;
	       if(strcmp(P.drug_name[i],P.drug_name[j]) == 0)
	       {
	           unique = 0; D.total_cost[drug_ctr]+=P.drug_cost[j];
	           P.drug_cost[j]=-1; // this flag indicates this entry is taken care of
	           if(strcmp(P.last_name[i],P.last_name[j]) == 0 && strcmp(P.first_name[i],P.first_name[j]) == 0)
	           	  D.num_pres[drug_ctr] = D.num_pres[drug_ctr];
	           else 
	           	  D.num_pres[drug_ctr] += 1;	 
	       } 
	   }
	   drug_ctr = drug_ctr + 1;
	}
}	
void swap(int a, int b)
{
   int temp_cost, temp_pres;
   char temp_name[1000];
   temp_cost = D.total_cost[a]; temp_pres = D.num_pres[a]; strcpy(temp_name,D.d_name[a]);
   D.total_cost[a] = D.total_cost[b]; D.num_pres[a] = D.num_pres[b]; strcpy(D.d_name[a],D.d_name[b]);
   D.total_cost[b] = temp_cost; D.num_pres[b] = temp_pres; strcpy(D.d_name[b],temp_name);
}
void bubble_sort()
{
    int i, j, temp;
    for (i = 0; i< (drug_ctr-1); i++)
    {
        for(j = 0;j < drug_ctr-i-1; j++)
        {
            if(D.total_cost[j]< D.total_cost[j+1])
               swap(j,j+1);
            else if(D.total_cost[j] == D.total_cost[j+1])
            {
                if(strcmp(D.d_name[j],D.d_name[j+1])<0)
                    swap(j,j+1);
            }   
        }
    }
}
void write_file()
{
  int i;
  fpt2=fopen("top_cost_drug.txt","w");
  fprintf(fpt2,"drug_name,num_prescriber,total_cost");
  for(i=0;i<drug_ctr;i++)
    fprintf(fpt2,"\n%s,%d,%d",D.d_name[i],D.num_pres[i],D.total_cost[i]);
  fclose(fpt2);

}
int main()
{
       printf("\nEnter name of input file with extension\n");
       scanf("%s",input_file);
       readFile(); 
       remove_duplicates();
       bubble_sort();
       write_file();
       
       	
}
    
