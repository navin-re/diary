#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
struct note
{
	int fav;
	char k[7][15];
	char title[50];
	char year[9];
	char a[1000];
	struct note *next;
	struct note *next3;
}*n,*prev,*temp,*end,*temp1,*start2,*temp3,*prev3 ;
typedef struct note * notes;
 struct note *n1;
struct note *start=NULL;
struct note *start3=NULL;
void diisplay(notes start);
void searchnote(notes start);
int main();
FILE *fp;
void getkeyword(char *k,int n)
{
    printf("\n%d.",n);
	scanf("%s",k);
}
int datepreference(notes n,notes m)
{
    int l;
    l=strcmp((n->year),(m->year));
    if(l<=1)
    return 0;
    else
    return 1;
}
void display(notes start)
{
     temp=start;
     while(temp!=NULL)
     {
                      printf("\n%s",temp->title);
                      temp=temp->next;
     }
}
void filewrite(notes n)
{
     fp=fopen("notes.dat","a+");
     while(n!=NULL)
     {
                fwrite(n,sizeof(struct note),1,fp);
                n=n->next;
                }
                fclose(fp);
}
notes fileread()
{
     fp=fopen("notes.dat","r+");
     int i=0;
     if(fp==NULL)
     printf("The File cannot be opened");
     while(!feof(fp))
     {
     
         n=(notes)malloc(sizeof(struct note));
        
         if(n==NULL)
         printf("space cannot be allocated");
         if(i==0)
         {
                 fread(n,sizeof(struct note),1,fp);
                 start=n;
                 end=n;
                 end->next=NULL;
                 i++;
                 }
         else
         {
             fread(n,sizeof(struct note),1,fp);
             end->next=n;
             n->next=NULL;
             end=n;        
             }
         }
         
         fclose(fp); 
         fp=fopen("notes.dat","w");
         fclose(fp); 
         return start;         
         
}
notes sort(notes start,notes n)
{
     temp=start;
     while(temp->next!=NULL && datepreference(n,temp)==0)
     {
      prev=temp;
      temp=temp->next;
      
     }
     if(temp==start && datepreference(n,temp)==1)
     {
      n->next=start;
      start=n;
     }
     else if(temp==start && datepreference(n,temp)==0)
     {
          start->next=n;
          n->next=NULL;
     }
     else if(temp->next==NULL && datepreference(n,temp)==0)
     {
      n->next=NULL;
      temp->next=n;
      end=n;
     }
     else if(temp->next==NULL && datepreference(n,temp)==1)
     {
      prev->next=n;
      n->next=temp;
      end=temp;
     }
     else
     {
      prev->next=n;
      n->next=temp;
     }
     return(start);
}
int isempty()
{
    return(start==NULL);
}
char* getstring(char *a, char end)//getting the data//
{
	int i=0;
	while((a[i++]=getchar())!=end);
	a[i-1]='\0';
	return a;
}
void create()
{
	int i;
	char c;
	do
	{
    notes n;
   	n=(notes)malloc(sizeof(struct note));
   	printf("\nEnter the title:\n");
	gets(n->title);
	printf("\nEnter your data:\n");
	getstring(n->a,'~');
	printf("Enter the keywords");
	for(i=0;i<7;i++)
    {                
                    getkeyword(&(n->k[i][0]),i+1);
                    if(n->k[i][0]=='~')
                    break;
    }
	printf("\nEnter date,month and time(YYYYMMDD):\n");
	scanf("%s",n->year);
	if(isempty())
	{
                 n->next=NULL;
                 start=n;
    }
    else
    start=sort(start,n);
	printf("\nEntry created");
	printf("\nDo You want to enter another note:\n");
	c=getch();
    }while(c=='y' ||c=='Y');
    
}

notes deletenote(notes start,notes temp,notes prev)
{
     if(temp==start)
     {
                        start=NULL;
                        printf("\nNote deleted\n");
                        return NULL;
     }
     else
     {
         prev->next=temp->next;
         printf("\nNote deleted\n");
         return(prev);
     }
     
}
void changedate(notes temp)
{
     printf("\n Enter date,month and year:\n");
	 scanf("%s",temp->year);
	 printf("\nDate changed\n");
}

void finddate(notes start)
{
     int i=1,ch;
     char date[9];
     printf("\nPlease enter the date(YYYYMMDD):\n");
     scanf("%s",date);
     temp=start;
     while(temp!=NULL && strcmp(date,temp->year)!=0)
           {
            prev=temp;
            temp=temp->next;
            }
     if(temp->next==NULL && strcmp(temp->year,date)!=0)
           {
           printf("\nNo entries were found on this date..Sorry!\n");
           }
     else
         {
           printf("\n%d.%s\n",i,temp->title);
           printf("\n\n%s",temp->a);
         
     printf("\n1.Delete note\n2.change date\n");
     printf("\nEnter your choice:");
     scanf("%d",&ch);
     switch(ch)
     {
               case 1:
                    temp=deletenote(start,temp,prev);
                    break;
               case 2:
                    changedate(temp);
                    sort(start,temp);
     }           
}
}
void findkeyword(notes start)
{
     int h=0,k=0,e=0,i;
     char keyword[15];
     printf("\nEnter the keyword to be found:\n");
     scanf("%s",keyword); 
     temp=start;
     for(temp=start;temp!=NULL;h=0,e=0)
     {
      for(i=0;i<7 && h==0;i++)
      {
        
        if(strcmp((temp->k)[i],keyword)==0)
            {            
                   h++;   
            }
        else if((temp->k)[i+1][0]=='~')
        break;
      }
     if(h!=0)//checks whether the word is found for the given temp//
     {
                int ch;
                printf("\nTITLE:%s",temp->title);
                printf("\nDATA:%s",temp->a);
                printf("\nDATE:%s",strrev((temp->year)));
                k++;
                printf("\n1.Delete\t2.Edit date\nEnter your choice:\n");
                scanf("%d",&ch);
                switch(ch)
                {
                          case 1:
                               temp=deletenote(start,temp,prev);
                               e++;
                               break;
                          case 2:
                               changedate(temp);
                               sort(start,temp);
                               
                }
     }     
     if(e==0)//checks whetheter the node has been deleted//
             {
                 temp=prev;
                 temp=temp->next;
             }
     else
     temp=temp->next;        
     }
     if(k==0)//checks whether the word is found atleast once//
     printf("\nKeyword not found!\n");
}                                        
void titlesearch(notes start)
{
     int l=1,n,i,ch,j,g;
     char title[50];
     printf("\nEnter the title:\n");
     scanf("%s",title);
     n=strlen(title);
     temp=start;
     while(temp!=NULL)
     {
           for(i=0;i<n;i++)//checks each keyword of a given temp//
           {
               if((temp->title)[i]==title[i])
               continue;
               else 
               break;
           }
           if(i==n)//checks whether the stored keyword is exact as the input//
           {
                                 
                     n1=(struct note *)malloc(sizeof(struct note));
                     strcpy(n1->title,temp->title);
                     strcpy(n1->a,temp->a);
                     strcpy(n1->year,temp->year);
                     if(start3==NULL)
                     { 
                         start3=n1;
                         start3->next3=NULL;
                     }
                     else
                     {
                         temp3=start3;
                         while(temp3->next3!=NULL)
                         temp3=temp3->next3;
                         temp3->next3=n1;
                         n1->next3=NULL;
                     }         
                     printf("\n%d.%s",l,temp->title);
                     l++;
           }
           temp=temp->next;
     }
     if(l==1)
     printf("\nNo entries were found on this date..Sorry!\n");
     else
     {
     printf("\nEnter choice:\n");
     scanf("%d",&g);
     temp3=start3;
     for(i=1;i<g;i++)
     {                                       
                         prev3=temp3;
                         temp3=temp3->next3;
     }
     printf("\nTITLE %s",temp3->title);
     printf("\nDATA %s",temp3->a);
     printf("\nDATE %s",temp3->year);
}
}
void searchnote(notes start)
{
     int ch2;
     printf("\n                 Search notes:\n");
     printf("\n\n1.Search by date");
     printf("\n2.Search by Title");
     printf("\n3.Search by Keyword\n4.Previous menu");
     printf("\nEnter choice:\n");
     scanf("%d",&ch2);
     switch(ch2)
     {
      case 1:
           finddate(start);
           break;
      case 2:
           titlesearch(start);
           break;
      case 3:
           findkeyword(start);
           break;
      case 4:
           main();
           break;
      }
}      
int main()
{
   int i;
   //create();
  
   start=fileread();
   //display(start);
   searchnote(start);
    //filewrite(start);
   
   getch();
   return 1;
} 
