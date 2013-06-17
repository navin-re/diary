#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
struct treenode
{
   char username[11];
   char password[11];
   struct treenode *left;
   struct treenode *right;
};
FILE *ft;
typedef struct treenode *tree;
typedef tree position;
void makeempty(tree T)
{
	if(T!=NULL)
	{
		makeempty(T->left);
		makeempty(T->right);
		free(T);
	}
}
position find(char tmp[],tree T)
{
	if(T==NULL)
	{
		return NULL;
	}
	else if(strcmp(tmp,T->username)<0)
		return find(tmp,T->left);
	else if(strcmp(tmp,T->username)>0)
		return find(tmp,T->right);
	else
		return T;
}
position findmin(tree T)
{
	if(T!=NULL)
	{
		while(T->left!=NULL)
			T=T->left;
	}
	return T;
}
/*position findmax(tree T)
{
	if(T!=NULL)
	{
		while(T->right!=NULL)
			T=T->right;
	} printf(" MAXIMUM : %d",T->element);
	return T;
}*/
tree insert(char tmpu[],char tmpp[],tree T)
{
	if(T==NULL)
	{
		T=(struct treenode*)malloc(sizeof(struct treenode));
		if(T==NULL)
			printf("Fatal Error");
		strcpy(T->username,tmpu);
		strcpy(T->password,tmpp);
		T->left=NULL;
        T->right=NULL;
	}
	else if(strcmp(tmpu,T->username)<0)
		T->left=insert(tmpu,tmpp,T->left);
	else if(strcmp(tmpu,T->username)>0)
		T->right=insert(tmpu,tmpp,T->right);
	return T;
}
tree delte(char key[],tree T)
{
	position temp;
	if(T==NULL)
		return NULL;
	else if(strcmp(key,T->username)<0)
		T->left=delte(key,T->left);
	else if(strcmp(key,T->username)>0)
		T->right=delte(key,T->right);
	else if(T->left&&T->right)
	{
		temp=findmin(T->right);
		strcpy(T->username,temp->username);
		
		T->right=delte(T->username,T->right);
	}
	else
	{
		temp=T;
		if(T->left!=NULL)
			T=T->left;
		else
			T=T->right;
		free(temp);
	}return T;
}
void display(tree T)
{
	if(T!=NULL)
	{
	display(T->left);
	display(T->right);
	printf(" %s\n ",T->username);
	}
}
int n=0,i=0;
void searchkey(char key[],tree T,int l)
{  
    if(T!=NULL)
    {
    n=strncmp(T->username,key,l);
    if(n==0)
    {i++;
    printf("%d.%s\n",i,T->username);
}
    searchkey(key,T->left,l);
    searchkey(key,T->right,l);
}
}
void displaypreorder(tree T)
{
	if(T!=NULL)
	{
               
    printf("%s\n",T->username);
	displaypreorder(T->left);
	displaypreorder(T->right);
	
	}
}
void fileopen()
{
         ft=fopen("login.txt","a+");
         if(ft==NULL)
         printf("The file cannot be opened");
}
void treewrite(tree T)
{
     fileopen();
     fwrite(T,sizeof(struct treenode),1,ft);
     if(T!=NULL)
     {
               treewrite(T->left);
               printf("Left entered");
               treewrite(T->right);
               printf("Right entered");
               }
               fclose(ft);
}
tree treeread(tree T)
{
     ft=fopen("login.txt","r");
     tree n;
     while(!feof(ft))
     {
      n=(tree)malloc(sizeof(struct treenode));
      fread(n,sizeof(struct treenode),1,ft);
      T=insert(n->username,n->password,T);
      }
      fclose(ft);
      return T;
}
int main()
{
	tree start,T=NULL;
	tree T2=NULL;
	int ch1,l,count=0,ch;
	char tmpu[11],tmpp[11],key[11];
                    
	T=treeread(T);
	do
	{
		printf("\n 1.INSERT\n 2.DELETE\n 3.SEARCH\n 4.PREORDER DISPLAY\n 5.Keyword search\n 6.DISPLAY\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: printf("\n Enter username:");
				scanf("%s",tmpu);
				printf("Enter Password");
				scanf("%s",tmpp);
				T=insert(tmpu,tmpp,T);count++;
				if(count==1)
				start=T;
				break;
			case 2:	printf("\n Enter username");
				scanf("%s",key);
				T2=delte(key,T);
				printf("DELETED");
				break;
			case 3: printf( "\n ENter key");
				scanf("%s",key);
				T=find(key,T);
				if(T!=NULL)
				printf("%s",T->username);
				else 
				printf("The element not found");
				break;
			case 4:displaypreorder(T);break;
			case 5:
                 printf("ENTER key");
                 scanf("%s",key);
                 l=strlen(key);
                 searchkey(key,start,l);break;
			case 6: display(T);
		}
	}while(ch<=6);
	treewrite(T);
	getch();
 return 0;
}

