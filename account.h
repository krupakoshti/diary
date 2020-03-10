#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>
#include<C:\Users\Dell\Desktop\DA-IICT\C project\time.h>
struct account
{
	char *username,*password,*fname,*lname,*gender,*dob,*email,*ans1,*ans2;
};
struct category
{
	char *catname;
	int catid;
};
struct note
{
	int cid;
	char *notes;
	char *notedate;
};
typedef struct account ac;
typedef struct category cat;
typedef struct note nt;
int date_validation(int dd,int mm,int yy)
{
			if(yy>=1900 && yy<=9999)
    		{
        		//check month
        		if(mm>=1 && mm<=12)
        		{
		            //check days
		            if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
		                return 1;
		            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
		                return 1;
		            else if((dd>=1 && dd<=28) && (mm==2))
		                return 1;
		            else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0)))
		                return 1;
		            else
		                return 0;
		        }
		        else
		        {
		            return 0;
		        }
		    }
		    else
		    {
		        return 0;
		    }
}

void insert_note(char *username)
{
	cat cat1;
	FILE *fp1;
	FILE *fptr;
	time_t now = time(NULL);
   	struct tm *t = localtime(&now);
	cat1.catname=(char *)malloc(sizeof(char)*100);
	fp1=fopen("category.txt","r");
	while(fscanf(fp1,"%d%s",&cat1.catid,cat1.catname)!=EOF)
	{
		printf("\n%d %s",cat1.catid,cat1.catname);
	}
	printf("\n");
	fclose(fp1);
	nt n1;
	int flag=0;
	n1.notes=(char *)malloc(sizeof(char)*1000);
	L:printf("\nEnter category: ");
	scanf("%d",&n1.cid);
	fp1=fopen("category.txt","r");
	while(fscanf(fp1,"%d%s",&cat1.catid,cat1.catname)!=EOF)
	{
		if(cat1.catid==n1.cid)
		{
			flag=1;
		}
	}
	fclose(fp1);
	if(!flag)
	{
		printf("Please enter a valid category :)");
		goto L;
	}
	int c;
	char userdt[15];
	printf("\nEnter using :\n");
	printf("\n1.Current Date");
	printf("\n2.Past Or Future Date");
	printf("\nEnter your choice:");
	scanf("%d",&c);
	switch(c)
	{
		case 1:
			printf("\nEnter your note: \n");
			fflush(stdin);
			gets(n1.notes);
			fptr=fopen(username,"a+");
			fprintf(fptr,"%d/%d/%d	%d	%s\n",t->tm_mday,t->tm_mon+1,t->tm_year+1900,n1.cid,n1.notes);
			fclose(fptr);
			break;
		
		case 2:
			re_date : printf("\nEnter Date(DD/MM/YYYY)");
			scanf("%s",userdt);
			char *p = strtok (userdt, "/");
		    int array[3];
			int i=0;
		    while (p != NULL)
		    {
		        array[i++] = atoi( p );
		        p = strtok (NULL, "/");
		    }
			int is_valid=date_validation(array[0],array[1],array[2]);
			if(is_valid)
			{
				printf("\nEnter your note: \n");
				fflush(stdin);
				gets(n1.notes);
				fptr=fopen(username,"a+");
				fprintf(fptr,"%d/%d/%d	%d	%s\n",array[0],array[1],array[2],n1.cid,n1.notes);
				fclose(fptr);			
			}
			else
			{
				printf("\nPlease, Enter Valid Date");
				goto re_date;
			}
			break;
		}		
}
void search_by_date(char *username)
{
	FILE *fp1,*fp2;
	char *userdt1,*userdt;
	userdt=(char *)malloc(sizeof(char)*15);
	userdt1=(char *)malloc(sizeof(char)*15);
	fp1=fopen(username,"r");
	search_date : printf("\nEnter Date(DD/MM/YYYY)");
			scanf("%s",userdt1);
			strcpy(userdt,userdt1);
			char *p = strtok (userdt1, "/");
		    int array[3];
			int i=0;
		    while (p != NULL)
		    {
		        array[i++] = atoi( p );
		        p = strtok (NULL, "/");
		    }
			int is_valid=date_validation(array[0],array[1],array[2]);
			if(is_valid)
			{
				nt n1;
				cat cat1;
				cat1.catname=(char *)malloc(sizeof(char)*100);
				n1.notes=(char *)malloc(sizeof(char)*1000);
				n1.notedate=(char *)malloc(sizeof(char)*15);

				while(fscanf(fp1,"%s%d",n1.notedate,&n1.cid)!=EOF)
				{
					fgets(n1.notes, 1000, fp1);
					if(strcmp(n1.notedate,userdt)==0)
					{
						fp2=fopen("category.txt","r");
						while(fscanf(fp2,"%d%s",&cat1.catid,cat1.catname)!=EOF)
						{
							if(n1.cid==cat1.catid)
							{
								printf("\n****************************************************************\n");
								printf("\nDATE: %s",n1.notedate);
								printf("\nCATEGORY: %s",cat1.catname);
								printf("\nNOTE: %s",n1.notes);
								printf("\n****************************************************************\n");
								break;
							}
						}
						fclose(fp2);
					}
				}
				fclose(fp1);
				
			}
			else
			{
				printf("\nPlease, Enter Valid Date");
				goto search_date;
			}
}
void search_by_cat(char *username)
{
	FILE *fp1,*fp2;
	nt n1;
	cat cat1;
	char *cat_user;
	fp1=fopen(username,"r");
	cat1.catname=(char *)malloc(sizeof(char)*100);
	n1.notes=(char *)malloc(sizeof(char)*1000);
	n1.notedate=(char *)malloc(sizeof(char)*15);
	cat_user=(char *)malloc(sizeof(char)*100);
	printf("\nEnter Category: ");
	scanf("%s",cat_user);
	while(fscanf(fp1,"%s%d",n1.notedate,&n1.cid)!=EOF)
	{
		fgets(n1.notes, 1000, fp1);
		fp2=fopen("category.txt","r");
		while(fscanf(fp2,"%d%s",&cat1.catid,cat1.catname)!=EOF)
		{
			if(n1.cid==cat1.catid && strcmpi(cat_user,cat1.catname)==0)
			{
				printf("\n****************************************************************\n");
				printf("\nDATE: %s",n1.notedate);
				printf("\nCATEGORY: %s",cat1.catname);
				printf("\nNOTE: %s",n1.notes);
				printf("\n****************************************************************\n");
				break;
			}
		}
		fclose(fp2);
	}
	fclose(fp1);	
}
void search_note(char *username)
{
	int ch;
	do
	{
		printf("\n1.Search By Date: ");
		printf("\n2.Search By Category: ");
		printf("\n3.Exit");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				search_by_date(username);
				break;
			case 2:
				search_by_cat(username);
				break;
		}
	
	}while(ch!=3);
}
void view_note(char *username)
{
	FILE *fp1,*fp2;
	fp1=fopen(username,"r");
	nt n1;
	cat cat1;
	cat1.catname=(char *)malloc(sizeof(char)*100);
	n1.notes=(char *)malloc(sizeof(char)*1000);
	n1.notedate=(char *)malloc(sizeof(char)*15);
	while(fscanf(fp1,"%s%d",n1.notedate,&n1.cid)!=EOF)
	{
		fp2=fopen("category.txt","r");
		while(fscanf(fp2,"%d%s",&cat1.catid,cat1.catname)!=EOF)
		{
			if(n1.cid==cat1.catid)
			{
				fgets(n1.notes, 1000, fp1);
				printf("%s	%s	%s",n1.notedate,cat1.catname,n1.notes);
				break;
			}
		}
		fclose(fp2);
	}
}
void welcome_ac(char *username)
{
	FILE *fp;
	char ch;
	fp=fopen(strcat(username,".txt"),"a+");
	fclose(fp);
	do
	{
		printf("\n\n1.Insert Note: ");
		printf("\n2.View Note: ");
		printf("\n3.Search Note:");
		printf("\n4.Logout\n");
		printf("Enter your choice: ");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
				insert_note(username);
				break;
			case 2:
				view_note(username);
				break;
			case 3:
				search_note(username);
				break;
		} 
	}while(ch!=4);
	printf("\a");
}

void login_account()
{
	ac ac1,ac2;
	FILE *fp,*fp2;
	int flag=0;

	ac1.username=(char *)malloc(sizeof(char)*100);
	ac1.password=(char *)malloc(sizeof(char)*100);
	ac1.ans1=(char *)malloc(sizeof(char)*100);
	ac1.ans2=(char *)malloc(sizeof(char)*100);

	ac2.username=(char *)malloc(sizeof(char)*100);
	ac2.password=(char *)malloc(sizeof(char)*100);
	ac2.fname=(char *)malloc(sizeof(char)*100);
	ac2.lname=(char *)malloc(sizeof(char)*100);
	ac2.gender=(char *)malloc(sizeof(char)*100);
	ac2.dob=(char *)malloc(sizeof(char)*100);
	ac2.email=(char *)malloc(sizeof(char)*100);
	ac2.ans1=(char *)malloc(sizeof(char)*100);
	ac2.ans2=(char *)malloc(sizeof(char)*100);
	
	int count=0;
	A:printf("\nEnter username: ");
	scanf("%s",ac1.username);
	
	printf("\nEnter password: ");
	scanf("%s",ac1.password);
		
	fp=fopen("account.txt","r");
	if(fp==NULL)
	{
		printf("cant open");
	}
	flag=0;
	while(fscanf(fp,"%s%s%s%s%s%s%s%s%s", ac2.username, ac2.password,ac2.fname,ac2.lname,ac2.gender,ac2.dob,ac2.email,ac2.ans1,ac2.ans2)!=EOF)
	{
		if(strcmp(ac1.username,ac2.username)==0 && strcmp(ac1.password,ac2.password)==0)
		{
			flag=1;
		}
		if(strcmp(ac1.username,ac2.username)==0 && strcmp(ac1.password,ac2.password)!=0)
		{
			count++;
			strcpy(ac1.ans1,ac2.ans1);
			strcpy(ac1.ans2,ac2.ans2);
		}
	}
	fclose(fp);
	if(flag==1)
	{
		printf("Login successful!!");
		printf("\a");
		printf("\a");
		welcome_ac(ac1.username);
	}
	else
	{
		if(count>=3)
		{
			int q,c,cc,status;
			char city[10],sch[100],pwd[20];
			printf("\nForgot Password???");
			printf("\n1.Do you want to retry??");
			printf("\n2.Proceed for Security Questions\n");
			printf("\nEnter your Choice: ");
			scanf("%d",&q);	
			switch(q)
			{
				case 1:
					goto A;
					break;
				case 2:
					f:
					printf("\nIn Which City You Were Born??  ");
					scanf("%s",city);
					printf("\nWhat Was The Name of Your Primary School??  ");
					scanf("%s",sch);
					
					if(strcmp(sch,ac1.ans2)==0 && strcmp(city,ac1.ans1)==0)
					{
						
						printf("\nEnter new Password: ");
						scanf("%s",pwd);
						fp=fopen("account.txt","r+");
						fp2=fopen("accounttemp.txt","w");
						while(fscanf(fp,"%s%s%s%s%s%s%s%s%s", ac2.username, ac2.password,ac2.fname,ac2.lname,ac2.gender,ac2.dob,ac2.email,ac2.ans1,ac2.ans2)!=EOF)
						{
							if(strcmp(ac2.username,ac1.username)==0)
							{
								strcpy(ac2.password,pwd);
							}
							fprintf(fp2,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",ac2.username,ac2.password,ac2.fname,ac2.lname,ac2.gender,ac2.dob,ac2.email,ac2.ans1,ac2.ans2);	
						}
						fclose(fp);
						fclose(fp2);	
						remove("account.txt");
						status = rename("accounttemp.txt","account.txt");
						
						if(status==0)
							printf("\n Password reset successfully!");
						else
							printf("\n Something went wrong!");
						
						
						
					}
					else
					{
							printf("\nYour Answers of Security Questions are not matiching..Try again.");
							printf("\nPress 0 to Quit from Security Question-answers");
							printf("\nPress 1 to Continue\n");
							printf("\nPress 1|0: ");
							scanf("%d",&c);
							if(c==0)
							{
								goto A;
							}
							else
							{
								goto f;	
							}
					}
					break;
			}
		}
		else
		{
			printf("Invalid username or password! please try again...");
			goto A;
		}
	}
}
void create_account()
{
	ac ac1,ac2;
	FILE *fp;
	int flag=0;
	
	ac1.username=(char *)malloc(sizeof(char)*100);
	ac1.password=(char *)malloc(sizeof(char)*100);
	ac1.fname=(char *)malloc(sizeof(char)*100);
	ac1.lname=(char *)malloc(sizeof(char)*100);
	ac1.gender=(char *)malloc(sizeof(char)*100);
	ac1.dob=(char *)malloc(sizeof(char)*100);
	ac1.email=(char *)malloc(sizeof(char)*100);
	ac1.ans1=(char *)malloc(sizeof(char)*100);
	ac1.ans2=(char *)malloc(sizeof(char)*100);
	
	ac2.username=(char *)malloc(sizeof(char)*100);
	ac2.password=(char *)malloc(sizeof(char)*100);
	ac2.fname=(char *)malloc(sizeof(char)*100);
	ac2.lname=(char *)malloc(sizeof(char)*100);
	ac2.gender=(char *)malloc(sizeof(char)*100);
	ac2.dob=(char *)malloc(sizeof(char)*100);
	ac2.email=(char *)malloc(sizeof(char)*100);
	ac2.ans1=(char *)malloc(sizeof(char)*100);
	ac2.ans2=(char *)malloc(sizeof(char)*100);
	
	A:printf("\nEnter username: ");
	scanf("%s",ac1.username);
	
	printf("\nEnter password: ");
	scanf(" %s",ac1.password);
	
	fp=fopen("account.txt","r");
	if(fp==NULL)
	{
		printf("cant open");
	}
	flag=0;
	while(fscanf(fp,"%s%s%s%s%s%s%s%s%s", ac2.username, ac2.password,ac2.fname,ac2.lname,ac2.gender,ac2.dob,ac2.email,ac2.ans1,ac2.ans2)!=EOF)
	{
		if(strcmp(ac1.username,ac2.username)==0)
		{
			printf("\nusername already exist\n");
			flag=1;
			fclose(fp);
			goto A;
		}
	}
	
	if(flag!=1)
	{
		fp=fopen("account.txt","a+");
		printf("\nEnter First Name: ");
		scanf(" %s",ac1.fname);
	
		printf("\nEnter Last Name: ");
		scanf(" %s",ac1.lname);
		
		printf("\nEnter Gender: ");
		scanf(" %s",ac1.gender);
		
		chck_date:printf("\nEnter Date of Birth: ");
		scanf(" %s",ac1.dob);
		
		char *p = strtok (ac1.dob, "/");
		    int array[3];
			int i=0;
		    while (p != NULL)
		    {
		        array[i++] = atoi( p );
		        p = strtok (NULL, "/");
		    }
			int is_valid=date_validation(array[0],array[1],array[2]);
			if(!is_valid)
				goto chck_date;
		
		printf("\nEnter Email: ");
		scanf(" %s",ac1.email);
		
		printf("\n Answer to Security Questions:\n");
		printf("\nIn Which City You Were Born??  ");
		scanf("%s",ac1.ans1);
		
		printf("\nWhat Was The Name of Your Primary School??  ");
		scanf("%s",ac1.ans2);
				
		fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",ac1.username,ac1.password,ac1.fname,ac1.lname,ac1.gender,ac1.dob,ac1.email,ac1.ans1,ac1.ans2);
		printf("\n\nAccount created successfully!!");
		fclose(fp);
		welcome_ac(ac1.username);
	}
}
