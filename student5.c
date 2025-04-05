#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>


typedef struct student		
{
	char srn[10];		 
	char name[20];
		
		int day;
		int month;
		int year;
	
	char sec[2];
	char gpa[4];
	char phone[10];	
}student;

void create()
{
	FILE *fp;
	student *s;
	int n, i, j;
	printf("Enter no. of students");
	scanf("%d",&n);
	fp = fopen("students.txt","w");

	s=(student *)calloc(n, sizeof(student));

	for(i=0;i<n;i++){
		printf("Enter SRN: ");
		scanf("%s",s[i].srn);
		fflush(stdin);
		printf("Enter name: ");
		scanf("%[^\n]s",s[i].name);
		printf("Date of Birth (dd/mm/yyyy): ");
		scanf("%d/%d/%d", &s[i].day,&s[i].month,&s[i].year);
		printf("Enter Section: ");
		scanf("%s",s[i].sec);
		printf("Enter GPA: ");
		scanf("%s",s[i].gpa);
		printf("Enter Phone no.: ");
		scanf("%s",s[i].phone);

		fwrite(&s[i],sizeof(student),1,fp);
	}
	fclose(fp);
}

void view()
{	
	student s1;
	FILE *fp;
	printf("SRN\t    NAME\t      DATE OF BIRTH\t    SECTION\t GPA\t    PHONE NO.\n");

	fp = fopen("students.txt","r");
	while(fread(&s1,sizeof(student),1,fp))
	{
			
			printf("\n%-10s %-20s %-2d/%-2d/%-15d %-10s %-10.2f %-15s\n", s1.srn, s1.name, s1.day,s1.month,s1.year, s1.sec, atof(s1.gpa), s1.phone);

			/*printf("\n SRN: %s",s1.srn);
			printf("\n Name: %s",s1.name); 
			printf("\n Date of Birth: %d/%d/%d",s1.day,s1.month,s1.year);
			printf("\n Section: %s",s1.sec);
			printf("\n GPA: %s",s1.gpa);
			printf("\n Phone no.: %s",s1.phone);
			printf("\n------------------------");*/		
		
	}
	fclose(fp);
	printf("\n------------------------");
}

void add()
{
	FILE *fp;
	student *s;
	int n, i, j;
	int temp=0, isvalid2=0;
	printf("Enter no. of students: ");
	scanf("%d",&n);
	fp = fopen("students.txt","a");

	s=(student *)calloc(n, sizeof(student));

	for(i=0;i<n;i++){
		
		//printf("Enter SRN : ");
		//scanf("%d",&s[i].srn);
		do{
			temp=0;
			printf("Enter SRN: ");
			scanf("%s",s[i].srn);

			for (int i=0 ; i<(strlen(s[i].srn)); i++)
			{
				if (!(isdigit(s->srn[i])))
						{
							printf("Entry Invalid \n");
							temp++;	
						}
			}
		} while(temp!=0);

		
		fflush(stdin);
		printf("Enter Name : ");
		scanf("%[^\n]s",s[i].name);
		
		printf("Date of Birth(dd/mm/yyyy) : ");
		scanf("%d/%d/%d", &s[i].day,&s[i].month,&s[i].year);
		
		//printf("Enter Section : ");
		//scanf("%s",s[i].sec);
		do{
			printf("Enter Section : ");
			scanf("%s",s[i].sec);
			for (int i=0 ; i<1; i++)
			{
				if (isalpha(s->sec[i]))
					{
						temp=2;
						
					}
				else
				{
					printf("Entry Invalid\n");
					temp=0;
				}
			}
		}while(temp==0);
		
		//printf("Enter GPA : ");
		//scanf("%s",s[i].gpa);
		
		
		int invalid=0;
		int isfloat=0; 
		int ischar=0;
			//float intnum=0;
			float floatnum=0;
			int isvalid1=0, isvalid2=0;
		do{
			
			printf("Enter GPA : ");
			scanf("%s",s[i].gpa);

			isfloat=0; 
			ischar=0;
			isvalid1=0; 
			isvalid2=0;
			invalid=0;
			
			for (int j=0; j < (strlen(s[i].gpa)); j++){
				
				if(!((s->gpa[j]>'/') && (s->gpa[j]<':'))){
					if(s->gpa[j]=='.')
					{
						isfloat++;
					}
					else
					{
						ischar++;
					}
				}
			}

			
			if (ischar>0 || isfloat>1)
			{
				printf("Invalid entry\n");
				invalid++;
				isvalid2=0;
				isvalid1=0;
			}
			
			else
			{
				isvalid1++;
			}

			if (isvalid1==1)
			{
				floatnum=atof(s->gpa);
				if((floatnum>=0 && floatnum<=10))
				{
					isvalid2++;

				}
				else
				{
					isvalid2=0;
					invalid++;
					printf("Entry invalid\n");
				}
			}
			
		}while(invalid!=0);

		
		fflush(stdin);
		// phone no.
	    int temp=0;
		
		do{
			printf("Enter phone no.: ");
			scanf("%s",s[i].phone);
			temp=0;

			for (int j=0 ; j<(strlen(s[i].phone)); j++)
			{
				if(!((s->phone[j]>'/') && (s->phone[j]<':')))
				//if (isdigit(s->phone[i]))
					{
						temp ++;
					}
			}

			if (temp==0)
			{
				long int m = atol(s->phone);
				if (!(m>1000000000 && m<9999999999))
				{
					temp ++;
					printf("Entry invalid \n");
				}	
			}
			else
			{
				printf("Entry Invalid \n");	
			}
			//printf("\nend");
			
		} while(temp!=0);



		printf("------------------------");

		fwrite(&s[i],sizeof(student),1,fp);
	}
	fclose(fp);
}	

void delete()
{
	student s1;
	FILE *fp, *fp1;
	int n,m,i,found=0 ;

	fp = fopen("students.txt","r");
	fp1 = fopen("temp.txt","w");
	printf("Enter SRN to delete : "); 
	scanf("%d", &n);
	while(fread(&s1,sizeof(student),1,fp))
	{
		m=atoi(s1.srn);
		if (m==n)
		{
			found=1;
		}
		else
			fwrite(&s1,sizeof(student),1,fp1);
	}
		
	fclose(fp1);
	fclose(fp);

	if (found)
	{
		fp1 = fopen("temp.txt","r");
		fp = fopen("students.txt","w");

		while(fread(&s1,sizeof(student),1,fp1))
		{
			fwrite(&s1,sizeof(student),1,fp);
		}

		fclose(fp);
		fclose(fp1);
		printf("\nRecord Deleted\n");
	}
	else
		printf("\nRecord not found\n");
}

void search()
{
	student s1;
	FILE *fp;
	int n,m,found=0 ;
	
	fp = fopen("students.txt","r");
	printf("Enter srn to search: ");
	scanf("%d", &n);
	while(fread(&s1,sizeof(student),1,fp))
	{
		m=atoi(s1.srn);
		//printf("%d",m);
		if (m==n)
		{
			found=1;
			printf("\n SRN: %s",s1.srn);
			printf("\n Name: %s",s1.name); 
			printf("\n Date of Birth: %d/%d/%d",s1.day,s1.month,s1.year);
			printf("\n Section: %s",s1.sec);
			printf("\n GPA: %.2f",atof(s1.gpa));
			printf("\n Phone no.: %s",s1.phone);
			printf("\n------------------------");		
		}
	}
	if(!found)
		printf("\nRecord not found\n");
	fclose(fp);
}

void edit()
{
	student s1;
	FILE *fp, *fp1;
	int m,n,i,temp,found=0 ;

	fp = fopen("students.txt","r");
	fp1 = fopen("temp.txt","w");
	printf("Enter srn to edit: ");
	scanf("%d", &n);
	while(fread(&s1,sizeof(student),1,fp))
	{
		m=atoi(s1.srn);
		if (m==n)
		{
			found=1;
			
			fflush(stdin);
			
			//printf("Enter SRN : ");
			//scanf("%d",&s[i].srn);
			/*do
			{
				printf("Enter SRN: ");
				scanf("%s",s1.srn);
				for (int i=0 ; i<1; i++)
				{
					if (!(isdigit(s1.srn[i])))
							{
								temp++;	
							}
				}
				if (temp!=0)
					printf("Entry Invalid\n");
			} while(temp!=0);*/
			
			//printf("Enter new SRN: ");
			//scanf("%s",s1.srn);
			printf("Enter new name: ");
			scanf("%[^\n]s",s1.name);
			
			printf("Enter new Date of Birth(dd/mm/yyyy): ");
			scanf("%d/%d/%d", &s1.day,&s1.month,&s1.year);
			

			do{
				temp=0;
				printf("Enter Section : ");
				scanf("%s",s1.sec);
				for (int i=0 ; i<1; i++)
				{
					if (isdigit(s1.sec[i]))
			                {
								temp++;	
							}
				}
				if (temp!=0)
					printf("Entry Invalid\n");
			} while(temp!=0);

			
			

			int invalid=0;
			int isfloat=0; 
			int ischar=0;
			//float intnum=0;
			float floatnum=0;
			int isvalid1=0, isvalid2=0;
			do{
			
				printf("Enter new GPA : ");
				scanf("%s",s1.gpa);

				isfloat=0; 
				ischar=0;
				isvalid1=0; 
				isvalid2=0;
				invalid=0;
				
				
				for (int j=0; j < (strlen(s1.gpa)); j++){
					//if(!(isdigit(s->gpa[i]))){
					
					if(!((s1.gpa[j]>'/') && (s1.gpa[j]<':'))){
						if(s1.gpa[j]=='.')
						{
							isfloat++;
						}
						else
						{
							ischar++;
						}
					}
				}

				if (ischar>0 || isfloat>1)
				{
					printf("Invalid entry\n");
					invalid++;
					isvalid2=0;
					isvalid1=0;
				}
				
				else
				{
					isvalid1++;
				}
			

				if (isvalid1==1)
				{
					floatnum=atof(s1.gpa);
					if((floatnum>=0 && floatnum<=10))
					{
						isvalid2++;

					}
					else
					{
						isvalid2=0;
						invalid++;
						printf("Entry invalid\n");
					}
				}
				
			}while(invalid!=0);
			
			
			do{
				printf("Enter phone no.: ");
				scanf("%s",s1.phone);
				temp=0;

				for (int j=0 ; j<(strlen(s1.phone)); j++)
				{
					if(!((s1.phone[j]>'/') && (s1.phone[j]<':')))
						{
							temp ++;
						}
				}

				if (temp==0)
				{
					long int m = atol(s1.phone);
					if (!(m>1000000000 && m<9999999999))
					{
						temp ++;
						printf("Entry invalid \n");
					}	
				}
				else
				{
					printf("Entry Invalid \n");	
				}
		
		} while(temp!=0);

		
		}
		fwrite(&s1,sizeof(student),1,fp1);
	
	}
		
	fclose(fp1);
	fclose(fp);

	if (found)
	{
		fp1 = fopen("temp.txt","r");
		fp = fopen("students.txt","w");

		while(fread(&s1,sizeof(student),1,fp1))
		{
			fwrite(&s1,sizeof(student),1,fp);
		}

		fclose(fp);
		fclose(fp1);
	}
	else
	{
		printf("\nRecord not found\n");
	}
}


int main()
{
	FILE *fp;
	int choice;
	do
	{
		printf("\n------STUDENT RECORD------\n");
		printf("0. Create \n");
		printf("1. View all Student Details \n");
		printf("2. Add Student Record \n");
		printf("3. Delete Student Record \n");
		printf("4. Search Student \n");
		printf("5. Edit Record \n");
		printf("6. Exit\n----------------------\n");
		printf("Enter your choice: ");
		
		scanf("%d",&choice);
		switch(choice){
			case 0:
				create();
				break;
			case 1:
				view();
				break;
			case 2:
				add();
				break;
			case 3:
				delete();
				break;
			
			case 4:
				search();
				break;

			case 5:
				edit();
				break;

			default:
				break;
		}
	}while(choice!=6);
	return 0;
}


