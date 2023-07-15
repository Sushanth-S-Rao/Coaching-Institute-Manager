//COACHING INSTITUTE MANAGEMENT SYSTEM

//Header Files
#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <cstdlib>

using namespace std;

//Global Variables
int rec_flag_student=0, no_student=0;
char rec_ind_student[5];

int rec_flag_teacher=0,no_teacher=0;
char rec_ind_teacher[5];


//Structure Definition
//For Students
struct student
{
 char fname[20];                    //Student First Name
 char lname[20];                    //Student Last name
 char registrationid[20];           //Registration Number
 char age[5];                       //Age
 char feestatus[10];                //Fee Status
 char cel_no[20];                   //Phone Number
 char batch[20];                    //Class Information
 char ind[5];                       //Index

}studentData[20];                   //Variable of student type

//For Teachers
struct teacher
{
 char fst_name[20];                 //Teacher First Name
 char lst_name[20];                 //Teacher Last Name
 char teacherid[20];                //Teacher ID
 char qualification[20];            //Qualification
 char pay[10];                      //Salary
 char batch[20];                    //Subjects taught
 char cel_no[20];                   //Phone Number
 char ind[5];                       //Index

}teacherData[20];                   //Variable of teacher type


// Primary Index Definition (for Student)
struct index
{
	char registrationid[20];		//Registration ID 
	char indstudent[20];			//Corresponding Student Index
}instudent[20], tempstudent;


// Primary Index Definition (for Teacher)
struct index1
{
	char teacherid[20];				//Teacher ID
	char indteacher[20];		    //Corresponding Teacher Index
}inteacher[20],tempteacher;


void sort_index_student()
{
	int i,j;

	for(i=0;i<no_student-1;i++)
	for(j=0;j<no_student-i-1;j++)
	if(strcmp(instudent[j].registrationid,instudent[j+1].registrationid)>0)
	{
		tempstudent=instudent[j];
		instudent[j]=instudent[j+1];
		instudent[j+1]=tempstudent;
	}
}

void sort_index_teacher()
{

	int i,j;

	for(i=0;i<no_teacher-1;i++)
	for(j=0;j<no_teacher-i-1;j++)
	if(strcmp(inteacher[j].teacherid,inteacher[j+1].teacherid)>0)
	{
		tempteacher=inteacher[j];
		inteacher[j]=inteacher[j+1];
		inteacher[j+1]=tempteacher;
	}
}


void retrive_record_student(char *ind)
{
	for(int i=0;i<no_student;i++)
	{
		if(strcmp(studentData[i].ind,ind)==0)
		{
			strcpy(rec_ind_student,ind);
			rec_flag_student=1;
			cout<<"Record Found:\n";
			cout<<"Index\tFname\tLname\tID\tAge\tPhone\tBatch\n"; 
			cout<<studentData[i].ind<< "\t" <<studentData[i].fname \
			<<"\t"<<studentData[i].lname<<"\t"<<studentData[i].registrationid \
			<<"\t"<<studentData[i].age<<"\t"<<studentData[i].cel_no \
			<<"\t"<<studentData[i].batch<<"\n";
            return;
		}
	}
	cout<<"Press any key to continue: \n";
    getch();
}

void retrive_record_teacher(char *ind)
{
	for(int i=0;i<no_teacher;i++)
	{
		if(strcmp(teacherData[i].ind,ind)==0)
		{
			strcpy(rec_ind_teacher,ind);
			rec_flag_teacher=1;
			cout<<"Record Found:\n";
			cout<<"Index\tFname\tLname\tID\tQualification\tPay\tBatch\tPhone\n";
			cout<<teacherData[i].ind<<"\t"<<teacherData[i].fst_name<<"\t"<<teacherData[i].lst_name<<"\t"<<teacherData[i].teacherid<<"\t"<<teacherData[i].qualification<<"\t"<<teacherData[i].pay<<"\t"<<teacherData[i].batch<<"\t"<<teacherData[i].cel_no<<"\n";
			return;
		}
	}
	cout<<"Press any key to continue: \n";
    getch();
}

int search_index_student(char *registrationid)
{
	int flag=0;
	for(int i=0;i<no_student;i++)
	{
		if(strcmp(instudent[i].registrationid,registrationid)==0)
		{
			retrive_record_student(instudent[i].indstudent);
			flag=1;
		}
	}
	if(flag)
		return 1;
	else
		return -1;
}


int search_index_teacher(char *teacherid)
{
	int flag=0;
	for(int i=0;i<no_teacher+1;i++)
	{
		if(strcmp(inteacher[i].teacherid,teacherid)==0)
		{
			retrive_record_teacher(inteacher[i].indteacher);
			flag=1;
		}
	}
	if(flag)
		return 1;
	else
		return -1;
}


int search_id_student(char *registrationid,int j)
{
	int flag=0;
	for(int i=0;i<j;i++)
	{
		if(strcmp(studentData[i].registrationid,registrationid)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag)
		return 1;
	else
		return -1;
}

int search_id_teacher(char *teacherid,int j)
{
	int flag=0;
	for(int i=0;i<j;i++)
	{
		if(strcmp(teacherData[i].teacherid,teacherid)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag)
		return 1;
	else
		return -1;
}


void delet_student(char *st_registrationid)
{
	rec_flag_student=0;
	int fr=0;
	search_index_student(st_registrationid);
	if(!rec_flag_student)
	{
		cout<<"Deletion failed. Record not found\n";
		cout<<"Press any key to continue: \n";
		getch();
		return;

	}
	for(int i=0;i<no_student;i++)
	{
		if(strcmp(studentData[i].ind,rec_ind_student)==0)
		{
			fr=i;
			break;
		}
	}
	for(int i=fr;i<no_student-1;i++)
	{
		studentData[i]=studentData[i+1];
		char str[3];
		sprintf(str,"%d",i);
		strcpy(studentData[i].ind,str);
	}
	no_student--;
	fstream f1,f2;
	f1.open("record_student.txt",ios::out);
	f2.open("index_student.txt",ios::out);
	for(int i=0;i<no_student;i++)
	{
		strcpy(instudent[i].registrationid,studentData[i].registrationid);
		strcpy(instudent[i].indstudent,studentData[i].ind);
	}
	sort_index_student();
	for(int i=0;i<no_student;i++)
	{
	    f1<<studentData[i].ind<<"|"<<studentData[i].fname<<"|" <<studentData[i].lname<<"|"<<studentData[i].registrationid<<"|"<< studentData[i].feestatus<<"|"<<studentData[i].age<<"|"<< studentData[i].cel_no<<"|"<<studentData[i].batch<<"\n";
		f2<<instudent[i].registrationid<<"|"<<instudent[i].indstudent<<"\n";
	}
	f1.close();
	f2.close();
	cout<<"Deletion Successful\n";
	cout<<"Press any key to continue:\n";
	getch();
}


void delet_teacher(char *st_teacherid)
{
	rec_flag_teacher=0;
	int fr=0;
	search_index_teacher(st_teacherid);
	if(!rec_flag_teacher)
	{
		cout<<"Deletion failed. Record not found\n";
		cout<<"Press any key to continue:\n";
		getch();
		return;
	}
	for(int i=0;i<no_teacher;i++)
	{
		if(strcmp(teacherData[i].ind,rec_ind_teacher)==0)
		{
			fr=i;
			break;
		}
	}
	for(int i=fr;i<no_teacher-1;i++)
	{
		teacherData[i]=teacherData[i+1];
		char str[3];
		sprintf(str,"%d",i);
		strcpy(teacherData[i].ind,str);
	}
	no_teacher--;
	fstream f1,f2;
	f1.open("record_teacher.txt",ios::out);
	f2.open("index_teacher.txt",ios::out);
	for(int i=0;i<no_teacher;i++)
	{
		strcpy(inteacher[i].teacherid,teacherData[i].teacherid);
		strcpy(inteacher[i].indteacher,teacherData[i].ind);
	}
	sort_index_teacher();
	for(int i=0;i<no_teacher;i++)
	{
	    f1<<teacherData[i].ind<<"|"<<teacherData[i].fst_name<<"|"<<teacherData[i].lst_name<<"|"<<teacherData[i].teacherid<<"|"<<teacherData[i].qualification<<"|"<<teacherData[i].pay<<"|"<<teacherData[i].batch<<"|"<<teacherData[i].cel_no<<"\n";
		f2<<inteacher[i].teacherid<<"|"<<inteacher[i].indteacher<<"\n";
	}
	f1.close();
	f2.close();
	cout<<"Deletion successful\n";
	cout<<"Press any key to continue\n";
	getch();
}


void update_status(char *id)
{

    for (int k = 0;k<no_student;k++)
    {
        if(strcmp(studentData[k].registrationid,id)==0)
        {
            if (strcmp(studentData[k].feestatus,"Unpaid")==0)
            {
                strcpy(studentData[k].feestatus,"Paid");
            }
        }
    }
    fstream f1;
	f1.open("record_student.txt",ios::out);
    for(int k = 0;k<no_student;k++ )
    {

        f1<<studentData[k].ind<<"|"<<studentData[k].fname<<"|" \
		<<studentData[k].lname<<"|"<<studentData[k].registrationid<<"|" \
		<<studentData[k].feestatus<<"|"<<studentData[k].age<<"|"<< \
		studentData[k].cel_no<<"|"<<studentData[k].batch<<"\n";
    }
    f1.close();
    cout<<"Updation Successful\n";
    cout<<"Press any key to continue: ";
    getch();
}







///////////////////////////////////////////////////
//Main function

int main()
{

    char fname[20];					
    char lname[20];
    char registrationid[20]; 
    char st_registrationid[20];
    char age[5]; 
    char feestatus[10]; 
    char cel_no_student[20]; 
    char batch_student[20]; 
    char ind_student[5]; 

    char fst_name[20]; 
    char lst_name[20]; 
    char teacherid[20]; 
    char st_teacherid[20];
    char qualification[20];
    char pay[10];
    char batch_teacher[20];  
    char cel_no_teacher[20];
    char ind_teacher[5];

    fstream file1;
    int i=0,j; 		//for processing usage
    char choice; 	//for getting choice

	fstream file2;
    file1.open("record_student.txt",ios::in);
	file2.open("index_student.txt",ios::out);
	for(int i=0;i<100;i++)
	{
		file1.getline(studentData[i].ind,5,'|');
		file1.getline(studentData[i].fname,20,'|');
		file1.getline(studentData[i].lname,20,'|');
		file1.getline(studentData[i].registrationid,20,'|');
		file1.getline(studentData[i].feestatus,10,'|');
		file1.getline(studentData[i].age,5,'|');
		file1.getline(studentData[i].cel_no,20,'|');
		file1.getline(studentData[i].batch,20,'\n');
		strcpy(instudent[i].registrationid,studentData[i].registrationid);
		strcpy(instudent[i].indstudent,studentData[i].ind);
		int m=atoi(studentData[i].ind);
		if(i==m)
			no_student++;
		else	
			break;					
	}
					
	sort_index_student();
	for(int i=0;i<no_student;i++)
	{
		file2<<instudent[i].registrationid<<"|"<<instudent[i].indstudent<<"\n";
	}

	file1.close();
	file2.close();
    fstream f11,f21;
	f11.open("record_teacher.txt",ios::in);
	f21.open("index_teacher.txt",ios::out);
	for(int i=0;i<100;i++)
	{
		f11.getline(teacherData[i].ind,5,'|');
		f11.getline(teacherData[i].fst_name,20,'|');
		f11.getline(teacherData[i].lst_name,20,'|');
		f11.getline(teacherData[i].teacherid,20,'|');
		f11.getline(teacherData[i].qualification,20,'|');
		f11.getline(teacherData[i].pay,10,'|');
		f11.getline(teacherData[i].batch,20,'|');
		f11.getline(teacherData[i].cel_no,10,'\n');
		strcpy(inteacher[i].teacherid,teacherData[i].teacherid);
		strcpy(inteacher[i].indteacher,teacherData[i].ind);
		int m=atoi(teacherData[i].ind);
		if(i==m)
			no_teacher++;
		else
			break;
	}
					
	sort_index_teacher();
	for(int i=0;i<no_teacher;i++)
	{
		f21<<inteacher[i].teacherid<<"|"<<inteacher[i].indteacher<<"\n";
	}
	f11.close();
	f21.close();



while(1) //Outer Loop
{
system("cls");	//Clear Screen

//Level 1 - Display Process
 cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\";
 cout<<"\n\n\t\tCOACHING INSTITUTE MANAGEMENT SYSTEM\n\n";
 cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\";
 cout<<"\n\n\t\tHOME PAGE\n\n";
 cout<<"This is a Coaching System, used to maintain the records of\nstudents and teachers in the coaching institute\n";
 cout<<"\tThe two basic sections are: \n";
 cout<<"\t1.Student Section\n";
 cout<<"\t2.Teacher Section\n\n";
 cout<<"Which section do you want to avail? Choose an option below\n";
 cout<<"1) Student Information"<<endl;
 cout<<"2) Teacher Information"<<endl;
 cout<<"3) Exit Program"<<endl;
 cin>>choice;
system("cls");


switch(choice)	//First Switch
{
	case '1': 	//STUDENT
	{
    int n;
	while(1)	//Inner Loop 1
	{
		system("cls");
		//Level 2 - Display Process
		cout<<"\nSTUDENTS INFORMATION AND BIODATA SECTION\n\n\n";
		cout<<"Enter your Choice: "<<endl;
		cout<<"1) New Admission\n";
		cout<<"2) Find Student\n";
		cout<<"3) Check Fee Status\n";
		cout<<"4) Remove Student\n";
		cout<<"5) Display Students Batchwise\n";
		cout<<"6) Display all Students\n";
		cout<<"7) Update Fee status\n";
		cout<<"8) Jump to Main Menu\n";
		cin>>choice;

		switch (choice)		//Second switch
		{
    	case '1':			//Insert data
    	{
        	file1.open("record_student.txt",ios::app|ios::out);
        	while(choice!='N')
        	{
            	if((choice=='y')||(choice=='Y')||(choice=='1'))
            	{
					cout<<"Enter the number of students: ";
					cin>>n;
					cout<<"Enter the Details below\n";
					for(i = no_student;i<no_student+n;i++)
					{
						label: cout<<"Enter Student Details:\n";
						cout<<"First Name: ";
						cin>>studentData[i].fname;
						cout<<"Last Name: ";
						cin>>studentData[i].lname;
						cout<<"Registration ID: ";
						cin>>studentData[i].registrationid;
						cout<<"Fee Status: ";
						cin>>studentData[i].feestatus;
						cout<<"Age: ";
						cin>>studentData[i].age;
						cout<<"Batch Allotted: ";
						cin>>studentData[i].batch;
						cout<<"Contact Number: ";
						cin>>studentData[i].cel_no;
						int q = search_id_student(studentData[i].registrationid,i);
						if(q==1)
						{
							cout<<"Duplicate Value\n";
							cout<<"Enter Again:\n";
							goto label;
						}
						file1<<i<<"|"<<studentData[i].fname<<"|"<<studentData[i].lname<<"|"<<studentData[i].registrationid<<"|"<<studentData[i].feestatus<<"|"<<studentData[i].age<<"|"<<studentData[i].cel_no<<"|"<<studentData[i].batch<<"\n";
					}
					no_student=no_student+n;
					cout<<"\nDo You Want to Enter More Data?\n";
					cout<<"Press Y for Continue and N to Finish: ";
					cin>>choice;

           		}
        	}
        
			file1.close();
			fstream file1,file2;
			file1.open("record_student.txt",ios::in);
			file2.open("index_student.txt",ios::out);
			for(int i=0;i<no_student;i++)
			{
				file1.getline(ind_student,5,'|');
				file1.getline(fname,20,'|');
				file1.getline(lname,20,'|');
				file1.getline(registrationid,20,'|');
				file1.getline(feestatus,10,'|');
				file1.getline(age,5,'|');
				file1.getline(cel_no_student,20,'|');
				file1.getline(batch_student,20,'\n');
				strcpy(studentData[i].ind,ind_student);
				strcpy(instudent[i].registrationid,registrationid);
				strcpy(instudent[i].indstudent,ind_student);
			}
			sort_index_student();
			for(int i=0;i<no_student;i++)
			{
				file2<<instudent[i].registrationid<<"|"<<instudent[i].indstudent<<"\n";
			}
			file1.close();
			file2.close();
    	}
		continue;	//Control Back to Inner Loop 1

		case '2':	//Search Data
		{
			cout<<"Enter the ID of the student whose record is to be searched: ";
			cin>>st_registrationid;
			int q=search_index_student(st_registrationid);
			if(q==1)
			{
				cout<<"\nSearch Successful!\n";
				cout<<"Press any key to continue: \n";
				getch();
			}
			else
			{
				cout<<"\nSearch Unsuccesful!\n";
				cout<<"Press any key to continue: \n";
				getch();
			}

		}
		continue; 	//Control Back to Inner Loop 1

		case '3':	//Print Fee Status
		{
			char ch;
			cout<<"Choose the kind of status: \n";
			cout<<"1) Paid\n";
			cout<<"2) Unpaid\n";
			cin>>ch;
			if(ch== '1')
			{
				cout<<"Students Who Have Paid Their Fees: \n";
				for (int k=0;k<no_student;k++)
				{
					if (strcmp(studentData[k].feestatus,"Paid")==0)
					{
						cout<<studentData[k].fname<<"\t"<<studentData[k].lname<<"\t"<<studentData[k].registrationid<<"\t"<<studentData[k].feestatus<<"\t"<<studentData[k].age<<"\t"<<studentData[k].cel_no<<"\t"<<studentData[k].batch<<endl;
					}
				}
			}

			else if(ch == '2')
			{
				cout<<"Students Who Have Not Paid Their Fees: \n";
				for (int k=0;k<no_student;k++)
				{
					if (strcmp(studentData[k].feestatus,"Unpaid")==0)
					{
						cout<<studentData[k].fname<<"\t"<<studentData[k].lname<<"\t"<<studentData[k].registrationid<<"\t"<<studentData[k].feestatus<<"\t"<<studentData[k].age<<"\t"<<studentData[k].cel_no<<"\t"<<studentData[k].batch<<endl;
					}
				}
			}
			cout<<"Press any key to continue: ";
			getch();
		}

		continue;

		case '4':	//Delete Data
		{
			cout<<"Enter the ID of the Student whose Record is to be Deleted: ";
			cin>>st_registrationid;
			delet_student(st_registrationid);
		}
		continue;

		case '5':	//Display Students Batch-wise
		{
			char bat[10];
			cout<<"Enter the Batch whose Record you want to Display: ";
			cin>>bat;
			for(int k = 0;k<no_student;k++)
			{
				if(strcmp(studentData[k].batch,bat)==0)
				{
					cout<<studentData[k].fname<<"\t"<<studentData[k].lname<<"\t"<<studentData[k].registrationid<<"\t"<<studentData[k].age<<"\t"<<studentData[k].cel_no<<"\t"<<studentData[k].batch<<endl;
				}
			}
			cout<<"Press any key to continue: \n";
			getch();
		}
		continue;

		case '6':	//Display All Data
		{
			fstream f1;
			f1.open("record_student.txt",ios::in);
			if(!f1)
			{
				cout<<"Error!!!";
				exit(0);
			}
			int i=0;
			while(i!=no_student)
			{
				cout<<studentData[i].ind<<"\t"<<studentData[i].fname<<"\t"<<studentData[i].lname<<"\t"<<studentData[i].registrationid<<"\t"<<studentData[i].age<<"\t"<<studentData[i].cel_no<<"\t"<<studentData[i].batch<<"\n";
				i++;
			}
			f1.close();
			cout<<"Press any key to continue: \n";
			getch();
		}
		continue;

		case '7': 
		{
			char id[20];
			cout<<"Students who have not paid the fees: \n";
			for (int k=0;k<no_student;k++)
			{
				if (strcmp(studentData[k].feestatus,"Unpaid")==0)
				{
					cout<<studentData[k].fname<<"\t"<<studentData[k].lname<<"\t"<<studentData[k].registrationid<<"\t"<<studentData[k].feestatus<<"\t"<<studentData[k].age<<"\t"<<studentData[k].cel_no<<"\t"<<studentData[k].batch<<endl;
				}
			}
			cout<<"Enter the ID of the student whose status you want to update: ";
			cin>>id;
			update_status(id);
		}
		continue;

		case '8':	//Jump to Main
		{
			break;	//Inner Switch Breaking
		}

	}
	break; 			//Inner Loop 1 Breaking
	}
	continue;		//Control Pass to Loop 1
	}

	case '2':		//TEACHERS
	{
		int n;
		while(1)	//Inner Loop 2
		{
			system("cls");
			//Level 2 - Display Process
			cout<<"\nTEACHERS INFORMATION AND BIODATA SECTION\n\n\n";
			cout<<"Enter your Choice: "<<endl;
			cout<<"1) Create New Entry\n";
			cout<<"2) Find Teacher\n";
			cout<<"3) Remove Teacher\n";
			cout<<"4) Batcheswise Display\n";
			cout<<"5) Students Assigned\n";
			cout<<"6) Display All Teachers\n";
			cout<<"7) Jump to Main Menu\n";
			cin>>choice;

			switch (choice)	//Second Switch
			{
				case '1':	//Insert Data
				{
					file1.open("record_teacher.txt",ios::app|ios::out);
					for( i=0;choice!='N';i++)
					{
						if((choice=='y')||(choice=='Y')||(choice=='1'))
						{
							cout<<"Enter the number of Teachers: ";
							cin>>n;
							cout<<"Enter the Details Below\n";
							for( i=no_teacher;i<no_teacher+n;i++)
							{
								label1: cout<<"Enter Teacher Details: \n";
								cout<<"First Name: ";
								cin>>teacherData[i].fst_name;
								cout<<"Last Name: ";
								cin>>teacherData[i].lst_name;
								cout<<"Qualification: ";
								cin>>teacherData[i].qualification;
								cout<<"Teacher ID: ";
								cin>>teacherData[i].teacherid;
								cout<<"Pay: ";
								cin>>teacherData[i].pay;
								cout<<"Batch Allotted: ";
								cin>>teacherData[i].batch;
								cout<<"Contact Number: ";
								cin>>teacherData[i].cel_no;
								int q=search_id_teacher(teacherData[i].teacherid,i);
								if(q==1)
								{
									cout<<"Duplicate Value\n";
									cout<<"Enter Again: \n";
									goto label1;
								}
								file1<<i<<"|"<<teacherData[i].fst_name<<"|"<<teacherData[i].lst_name<<"|"<<teacherData[i].teacherid<<"|"<<teacherData[i].qualification<<"|"<<teacherData[i].pay<<"|"<<teacherData[i].batch<<"|"<<teacherData[i].cel_no<<"\n";


							}
							no_teacher=no_teacher+n;
							cout<<"\nDo you want to Enter further Data?\n";
							cout<<"Press Y for Continue and N to Finish: ";
							cin>>choice;
						}
					}

					file1.close();
					fstream file1,file2;
					file1.open("record_teacher.txt",ios::in);
					file2.open("index_teacher.txt",ios::out);
					for(int i=0;i<no_teacher;i++)
					{
						file1.getline(ind_teacher,5,'|');
						file1.getline(fst_name,20,'|');
						file1.getline(lst_name,20,'|');
						file1.getline(teacherid,20,'|');
						file1.getline(qualification,20,'|');
						file1.getline(pay,10,'|');
						file1.getline(batch_teacher,20,'|');
						file1.getline(cel_no_teacher,10,'\n');
						strcpy(teacherData[i].ind,ind_teacher);
						strcpy(inteacher[i].teacherid,teacherid);
						strcpy(inteacher[i].indteacher,ind_teacher);
					}

					sort_index_teacher();
					for(int i=0;i<no_teacher;i++)
					{
						file2<<inteacher[i].teacherid<<"|"<<inteacher[i].indteacher<<"\n";
					}
					file1.close();
					file2.close();
				}
				continue;

				case '2':		//Display data
				{
					cout<<"Enter the ID of the Teacher whose record is to be Searched: ";
					cin>>st_teacherid;
					int q=search_index_teacher(st_teacherid);
					if(q==1)
					{
						cout<<"\nSearch Succesful!\n";
						cout<<"Press any key to continue: ";
						getch();
					}
					else
					{
						cout<<"\nSearch Unsuccesful!\n";
						cout<<"Press any key to continue: ";
						getch();
					}

				}
				continue;

	case '3':
	{
		cout<<"Enter the ID of the Teacher whose record is to be Deleted: ";
		cin>>st_teacherid;
		delet_teacher(st_teacherid);
	}
	continue;

	case '4':
	{
		char bat[20];
		cout<<"See the Teachers assigned to the Batch \nEnter the Batch Name: ";
		cin>>bat;
		for(int k = 0;k<no_teacher;k++)
		{
			if(strcmp(studentData[k].batch,bat)==0)
			{
				cout<<teacherData[k].fst_name<<"\t"<<teacherData[k].lst_name<<"\t"<<teacherData[k].teacherid<<"\t"<<teacherData[k].batch<<endl;
			}
		}
		cout<<"Press any key to continue: ";
		getch();
	}
	continue;

	case '5':
	{
		char id[20];
		cout<<"Enter ID of the Teacher to see the Students Assigned: ";
		cin>>id;
		char bat[20];

		for(int i = 0;i<no_teacher;i++)
		{
			if(strcmp(teacherData[i].teacherid,id)==0)
			{
				strcpy(bat,teacherData[i].batch);

			}
		}

		for(int k=0;k<no_teacher;k++)
		{
			if(strcmp(studentData[k].batch,bat)==0)
			{
				cout<<studentData[k].fname<<"\t"<<studentData[k].lname<<"\t"<<studentData[k].registrationid<<"\t"<<studentData[k].age<<"\t"<<studentData[k].cel_no<<endl;
			}
		}
		cout<<"Press any key to continue: ";
		getch();

	}
	continue;

	case '6':
	{
		fstream f1;
		f1.open("record_teacher.txt",ios::in);
		if(!f1)
		{
			cout<<"Error!!!";
			exit(0);
		}
		int i=0;
		while(i!=no_teacher)
		{
			cout<<teacherData[i].ind<<"\t"<<teacherData[i].fst_name<<"\t"<<teacherData[i].lst_name<<"\t"<<teacherData[i].teacherid<<"\t"<<teacherData[i].qualification<<"\t"<<teacherData[i].pay<<"\t"<<teacherData[i].batch<<"\t"<<teacherData[i].cel_no<<"\n";
			i++;
		}
		f1.close();
		cout<<"Press any key to continue: ";
		getch();
	}
	continue;


	case '7':	//Jump to Main
	{
		break;	//Inner Switch Breaking
	}
}
break;			//Inner Loop 2 Breaking
}

continue;		//Control Pass to 2nd Loop
}


case '3':
{
	break;	//Outer Case 3
}			
}
break;		//Outer Loop
}

}
