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
	char srn[14];
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


int toint(char *str); //Convert character to integer
void create_entry(HEAD*, STUD); //Builds the BST
void display_node(NODE* ); //Displays details of a single student
int sum_marks(NODE *); //Finds the sum of all the marks
int count_nodes(NODE *); //Counts the number of students
void avg_marks(NODE *); //Calculates total average marks
void srn_search(NODE *, char*); //Finds student using SRN
NODE* name_search(NODE*, char*);
void display_database(NODE*);

int main()
{
	int size;
	FILE *fp;
	fp = fopen("StudentData.txt","a+");
	
	HEAD head;
	head.root=NULL;
	head.length=0;
	if (NULL != fp) 
	{
		printf("File Opened Sucessfully\n");
		printf("Loading Student Database\n");
		char str[1];
		str[0] = '#';
		while(!feof(fp))
		{
			//fscanf(fp,"%c",str);
			//if(str[0] != ',')
			//{
				STUD s;
				fscanf(fp,"%s\n",s.srn);
				printf("srn: %s\n",s.srn);
				fscanf(fp,"%s\n",s.name);
				fscanf(fp,"%d\n",&s.sem);
				printf("roll no: %d\n",s.sem);
				fscanf(fp,"%d",&s.year);
				printf("year: %d\n",s.year);
				fscanf(fp,"%d\n",&s.in_hostel);
				fscanf(fp,"%s\n",s.block);
				printf("%s\n", s.block);
				fscanf(fp,"%d\n",&s.room_no);
				fscanf(fp,"%d\n",&s.mark.dml);
				printf("%d\n",s.mark.dml);
				fscanf(fp,"%d\n",&s.mark.ids);
				fscanf(fp,"%d\n",&s.mark.ds);
				fscanf(fp,"%d\n",&s.mark.ddco);
				printf("%d\n",s.mark.ddco);
				fscanf(fp,"%s\n",str);
				printf("%s\n", str);
				create_entry(&head,s);
				//str=',';
			//}
		}				
	}
	int choice;
	printf("1:NEW ENTRY\n2:STUDENT QUERY\n3:AVERAGE MARKS OF ALL STUDENTS\n4.DISPLAY ALL STUDENTS\n");
	int loop=1;
	while(loop)
	{
		printf("Enter choice:");
		scanf("%d",&choice);
		//fflush(stdin);
		switch(choice)
		{
			case 1:{
				STUD s;
				printf("Enter the SRN of the Student:");
				scanf("%s",&(s.srn));
				//fflush(stdin);
				fprintf(fp,"%s\n",s.srn);
				printf("Enter the name of the student:");
				scanf("%s",&(s.name));
				//fflush(stdin);
				fprintf(fp,"%s\n",s.name);
				printf("Enter the Semster:");
				scanf("%d",&(s.sem));
				//fflush(stdin);
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
				scanf(" %c",&h);
				//fflush(stdin);
				if(h=='y')
				{
					fprintf(fp,"%d\n",1);
					printf("Enter the block name:");
					scanf("%s",&(s.block));
					fprintf(fp,"%s\n",s.block);
					//fflush(stdin);
					printf("Enter the room number:");
					scanf("%d",&s.room_no);
					//fflush(stdin);
					fprintf(fp,"%d\n",s.room_no);		
				}
				else{
					s.block[0]='N';
					s.room_no=-1;
					fprintf(fp,"%d\n",-1);
					fprintf(fp,"N\n");
					fprintf(fp,"%d\n",-1);
				}
				printf("Enter Marks?(y/n) :");
				scanf(" %c",&h);
				//fflush(stdin);
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
			case 2: 
				printf("1. Enter SRN\n");
				printf("2. Enter Name\n");
				int t_choice;
				printf("Enter choice:");
				scanf("%d", &t_choice);
				if (t_choice == 1)
				{
					char t_srn[14];
					printf("Enter SRN: ");
					scanf("%s", t_srn);
					srn_search(head.root, t_srn);
				}
				else
				{
					char t_name[20];
					printf("Enter Name: ");
					scanf("%s", t_name);
					NODE *temp_root = name_search(head.root, t_name);
				}
				break;
			case 3:
				avg_marks(head.root);
				break;
			case 4: 
				display_database(head.root);
				break;
			case 5: 
				loop = 0;
				break;
		}
	}
	fclose(fp);
}

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
	//Fix key
	s.key = toint(key);
	newnode->student = s;
	//newnode->student.key= toint(key);

	if(head->root==NULL)
	{
		head->root=newnode;
	}
	else
	{
		NODE *temp;
		NODE *prev;
		temp=head->root;
		while (temp != NULL)
		{
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
		}
	
		if(prev->student.key > s.key)
		{
			prev->left=newnode;
		}
		else if(prev->student.key < s.key)
		{
			prev->right=newnode;
		}
	}
}

void display_node(NODE* t)
{
	printf("Key: %d\n", t->student.key);
	printf("SRN: %s\n", (t->student).srn);
	printf("Name: %s\n", t->student.name);
	printf("Semester: %d\n", (t->student).sem);
	printf("Year: %d\n", (t->student).year);
	if (t->student.in_hostel)
	{
		printf("Room Number: %d\n", t->student.room_no);
		printf("Hostel Block: %s\n", t->student.block);
	}
	printf("Marks -");
	printf("DS: %d\n", t->student.mark.ds);
	printf("DML: %d\n", t->student.mark.dml);
	printf("IDS: %d\n", t->student.mark.ids);
	printf("DDCO: %d\n", t->student.mark.ddco);
	printf("\n");
}

int sum_marks(NODE *t)
{
	if (t == NULL) return 0;
	else return (t->student).mark.dml + (t->student).mark.ids + (t->student).mark.ddco + (t->student).mark.ds + sum_marks(t->left) + sum_marks(t->right); 
}

int count_nodes(NODE *t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + count_nodes(t->left) + count_nodes(t->right); 
}

void avg_marks(NODE *t)
{
	int s, n;
	s = sum_marks(t);
	n = count_nodes(t);
	printf("Total Average Marks = %.2f\n", ((double)s)/n);
}

void srn_search(NODE *t, char *t_srn)
{
	char key[4];
	int k;
	for(int i=0;i<4;i++)
	{
		key[i] = t_srn[9+i];
	}
	k = toint(key);
	printf("%d\n", k);
	NODE *temp = t;
	while (temp != NULL)
	{
		if (temp->student.key < k)
		{	
			temp=temp->right;
		}
		else if (temp->student.key > k)
		{
			temp=temp->left;
		}
		else if (temp->student.key == k)
		{
			printf("Query Found!\n");
			display_node(temp);
			return;
		}
	}
	printf("Query Not Found\n");
}

NODE* name_search(NODE* t, char* name)
{

}

void display_database(NODE* t)
{
	if (t == NULL) return;
	display_database(t->left);
	display_node(t);
	display_database(t->right);
}