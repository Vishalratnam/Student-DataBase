#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
struct marks{
	int dml;
	int ids;
	int ds;
	int ddco;
};
typedef struct marks MARKS;

struct student{
	char srn[13];
	char name[20];
	int sem;
	int year;
	int in_hostel;
	int room_no;
	char block[20];
	MARKS mark;
	int key;
};
typedef struct student STUD;

struct node{
	STUD student;
	struct node* left;
	struct node* right;
};
typedef struct node NODE;

struct head{
	NODE * root;
	int length;
};
typedef struct head HEAD;


int toint(char str[])
{
    int len = strlen(str);
    int i, num = 0;
 
    for (i = 0; i < len; i++)
    {
        num = num + ((str[len - (i + 1)] - '0') * pow(10, i));
    }
 
   return num;
}


void create_entry(HEAD* head, STUD s)
{
	NODE* newnode=malloc(sizeof(NODE));
	newnode->left=NULL;
	newnode->right=NULL;
	char key[4];
	for(int i=0;i<4;i++)
	{
		key[i]=s.srn[9+i];
	}
	
	s.key=toint(key);
	newnode->student.key= toint(key);
	
	newnode->student=s;
	
	if(head->root==NULL)
	{
		head->root=newnode;
	}
	else{
		NODE *temp;
		NODE *prev;
		temp=head->root;
		if(temp->student.key < s.key)
		{
			prev=temp;
			temp=temp->right;
		}
		else if(temp->student.key > s.key)
		{
			prev=temp;
			temp=temp->left;
		}
		else
			return;
		if(prev->student.key > s.key)
		{
			prev->left=newnode;
		}
		else if(prev->student.key < s.key)
		{
			prev->right=newnode;
		}
		else
			return;
	}
}

void display(NODE* t)
{
	while(t!=NULL)
	{
		display(t->left);
		printf("%d\n", t->student.year);
		display(t->right);
		return;
	}
}
	
int main()
{
	int size;
	FILE *fp;
	fp=fopen("StudentData.txt","a+");
	
	HEAD head;

	if (NULL != fp) 
	{
		printf("File Opened Sucessfully\n");
		fseek (fp, 0, SEEK_END);
		size = ftell(fp);
		if (0 == size) {
			printf("File is empty\n");
			head.root=NULL;
			head.length=0;
		}
		else{
			printf("Loading Student Database\n");
			char str[20];
			while(!feof(fp))
			{
				fscanf(fp,"%[^\n]",str);
				while(str[0]!=',')
				{
					STUD s;
					fscanf(fp,"%[^\n]",s.srn);
					fscanf(fp,"%[^\n]",s.name);
					fscanf(fp,"%d",&s.sem);
					fscanf(fp,"%d",&s.year);
					fscanf(fp,"%d",&s.in_hostel);
					fscanf(fp,"[^\n]",s.block);
					fscanf(fp,"%d",&s.room_no);
					fscanf(fp,"%d",&s.mark.dml);
					fscanf(fp,"%d",&s.mark.ids);
					fscanf(fp,"%d",&s.mark.ds);
					fscanf(fp,"%d",&s.mark.ddco);
					create_entry(&head,s);
				}
			}				
		}
	}
	int choice;
	printf("\t\t\t\t1:NEW ENTRY\n\t\t\t\t2:STUDENT QUERY\n\t\t\t\t3:AVERAGE MARKS\n");
	int loop=1;
	while(loop)
	{
		scanf("%d",&choice);
		fflush(stdin);
		switch(choice)
		{
			case 1:{
				STUD s;
				printf("Enter the SRN of the Student:");
				scanf("%[^\n]",&(s.srn));
				fflush(stdin);
				fprintf(fp,"%s\n",s.srn);
				printf("Enter the name of the student:");
				scanf("%[^\n]",&(s.name));
				fflush(stdin);
				fprintf(fp,"%s\n",s.name);
				printf("Enter the Semster:");
				scanf("%d",&(s.sem));
				fflush(stdin);
				fprintf(fp,"%d\n",s.sem);
				if(s.sem ==1 || s.sem ==2)
					s.year=1;
				else if(s.sem ==3 || s.sem ==4)
					s.year=2;
				else if(s.sem ==5 || s.sem ==6)
					s.year=3;
				else if(s.sem =7 || s.sem ==8)
					s.year=4;
				fprintf(fp,"%d\n",s.year);
				printf("Does the student stay in hostel (y/n) :");
				char h;
				scanf("%c",&h);
				fflush(stdin);
				if(h=='y')
				{
					printf("Enter the block name:");
					scanf("%[^\n]",&(s.block));
					fprintf(fp,"%s\n",s.block);
					fflush(stdin);
					printf("Enter the room number:");
					scanf("%d",&s.room_no);
					fflush(stdin);
					fprintf(fp,"%d\n",s.room_no);		
				}
				else{
					s.block[0]='N';
					s.room_no=-1;
					fprintf(fp,"%d\n",-1);
				}
				printf("Enter Marks?(y/n) :");
				scanf("%c",&h);
				fflush(stdin);
				if(h=='y')
				{
					printf("Enter the marks in DML:");
					scanf("%d",&s.mark.dml);
					fprintf(fp,"%d\n",s.mark.dml);
					printf("Enter the marks in IDS:");
					scanf("%d",&s.mark.ids);
					fprintf(fp,"%d\n",s.mark.ids);
					printf("Enter the marks in DS:");
					scanf("%d",&s.mark.ds);
					fprintf(fp,"%d\n",s.mark.ds);
					printf("Enter the marks in DDCO:");
					scanf("%d",&s.mark.ddco);
					fprintf(fp,"%d\n",s.mark.ddco);
				}
				else{
					s.mark.dml=-1;
					s.mark.ids=-1;
					s.mark.ds=-1;
					s.mark.ddco=-1;
					fprintf(fp,"%d\n",-1);
					fprintf(fp,"%d\n",-1);
					fprintf(fp,"%d\n",-1);
					fprintf(fp,"%d\n",-1);
				}
				create_entry(&head,s);
				fprintf(fp,",\n");
			}
			break;		
			case 2: display(head.root);
					break;
			case 4: loop=0;
					break;
		}
	}
	fclose(fp);
}