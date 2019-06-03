#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include<cstdlib>



using namespace std;

int rec_flag_contact=0,no_contact=0;
char rec_ind_contact[5];
//For contacts
struct contact
{
 char fname[20];//for contact first name
 char lname[20];//for contact last name
 char id[20];//for Registration No number
 char age[5];//contact phone
 char cel_no[20];//Phone number
 char city[20];//for class info
 char ind[5];//for index

}contactData[20];//Variable of contact type

struct index
{
	char id[20],indcontact[20];
}incontact[20],tempcontact;

void sort_index_contact()
{
	int i,j;

	for(i=0;i<no_contact-1;i++)
	for(j=0;j<no_contact-i-1;j++)
	if(strcmp(incontact[j].id,incontact[j+1].id)>0)
	{
		tempcontact=incontact[j];
		incontact[j]=incontact[j+1];
		incontact[j+1]=tempcontact;
	}
}

void retrive_record_contact(char *ind)
{
	for(int i=0;i<no_contact;i++)
	{
		if(strcmp(contactData[i].ind,ind)==0)
		{
			strcpy(rec_ind_contact,ind);
			rec_flag_contact=1;
			cout<<"Record found:\n";
			cout<<contactData[i].ind<<"\t"<<contactData[i].fname<<"\t"<<contactData[i].lname<<"\t"<<contactData[i].id<<"\t"<<contactData[i].age<<"\t"<<contactData[i].cel_no<<"\t"<<contactData[i].city<<"\n";
            return;
		}
	}

	cout<<"Press any key to continue\n";
    getch();
}

int search_index_contact(char *id)
{
	int flag=0;
	for(int i=0;i<no_contact;i++)
	{
		if(strcmp(incontact[i].id,id)==0)
		{
			retrive_record_contact(incontact[i].indcontact);
			flag=1;
		}
	}
	if(flag)
		return 1;
	else
		return -1;
}

int search_id_contact(char *id,int j)
{
	int flag=0;
	for(int i=0;i<j;i++)
	{
		if(strcmp(contactData[i].id,id)==0)
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


void delet_contact(char *st_id)
{
	rec_flag_contact=0;
	int fr=0;
	search_index_contact(st_id);
	if(!rec_flag_contact)
	{
		cout<<"Deletion failed.Record not found\n";
		cout<<"Press any key to continue\n";
		getch();
		return;

	}
	for(int i=0;i<no_contact;i++)
	{
		if(strcmp(contactData[i].ind,rec_ind_contact)==0)
		{
			fr=i;
			break;
		}
	}
	for(int i=fr;i<no_contact-1;i++)
	{
		contactData[i]=contactData[i+1];
		char str[3];
		sprintf(str,"%d",i);
		strcpy(contactData[i].ind,str);
	}
	no_contact--;
	fstream f1,f2;
	f1.open("contact.txt",ios::out);
	f2.open("index_contact.txt",ios::out);
	for(int i=0;i<no_contact;i++)
	{
		strcpy(incontact[i].id,contactData[i].id);
		strcpy(incontact[i].indcontact,contactData[i].ind);
	}
	sort_index_contact();
	for(int i=0;i<no_contact;i++)
	{
	    f1<<contactData[i].ind<<"|"<<contactData[i].fname<<"|"<<contactData[i].lname<<"|"<<contactData[i].id<<"|"<<contactData[i].age<<"|"<<contactData[i].cel_no<<"|"<<contactData[i].city<<"\n";
		f2<<incontact[i].id<<"|"<<incontact[i].indcontact<<"\n";
	}
	f1.close();
	f2.close();
	cout<<"Deletion successful\n";
	cout<<"Press any key to continue\n";
	getch();
}


///////////////////////////////////////////////////
//Main function

int main()
{

    char fname[20];//for contact first name
    char lname[20];//for contact last name
    char id[20];//for Registration No number
    char st_id[20];
    char age[5];//contact phone
    char cel_no_contact[20];//Phone number
    char city_contact[20];//for class info
    char ind_contact[5];//for index


    fstream file1;
    int i=0,j;//for processing usage
    char choice;//for getting choice
    int n;
while(1)//inner loop-1
{
system("cls");//Clear screen
//Level-2 display
cout<<"\n\n\t\t\t\t\tCONTACT INFORMATION AND BIO DATA SECTION\n\n\n";
cout<<"Enter your choice: "<<endl;
cout<<"1.ADD New Contact\n";
cout<<"2.Find Contact\n";
cout<<"3.Remove Contact\n";
cout<<"4.Display contacts City-wise\n";
cout<<"5.Display all Contacts\n";
cout<<"6.Exit\n";
cin>>choice;

switch (choice)//Second switch

{
    case '1'://Insert data
    {
        file1.open("contact.txt",ios::out);

        while(choice!='n')
        {

            if((choice=='y')||(choice=='Y')||(choice=='1'))
            {

                cout<<"enter the no of contacts:\t";
                cin>>n;
                cout<<"enter the details\n";
                for(i = no_contact;i<no_contact+n;i++)
				{
					label: cout<<"enter "<<i+1<<" contact details:\n";
					cout<<"First name : ";
					cin>>contactData[i].fname;
					cout<<"Last name : ";
					cin>>contactData[i].lname;
					cout<<" Id : ";
					cin>>contactData[i].id;
					cout<<"Age : ";
					cin>>contactData[i].age;
					cout<<"City Name : ";
					cin>>contactData[i].city;
					cout<<"Contact Number : ";
					cin>>contactData[i].cel_no;
					int q = search_id_contact(contactData[i].id,i);
					if(q==1)
					{
						cout<<"Duplicate value\n";
						cout<<"enter again:\n";
						goto label;
					}
					file1<<i<<"|"<<contactData[i].fname<<"|"<<contactData[i].lname<<"|"<<contactData[i].id<<"|"<<contactData[i].age<<"|"<<contactData[i].cel_no<<"|"<<contactData[i].city<<"\n";

				}
				no_contact=no_contact+n;
				cout<<"Do you want to enter more data?\n ";
                cout<<"Press Y for Continue and N to Finish:  ";
                cin>>choice;

            }
        }
                file1.close();

					fstream file1,file2;
					file1.open("contact.txt",ios::in);
					file2.open("index_contact.txt",ios::out);
					for(int i=0;i<no_contact;i++)
					{
						file1.getline(ind_contact,5,'|');
						file1.getline(fname,20,'|');
						file1.getline(lname,20,'|');
						file1.getline(id,20,'|');
						file1.getline(age,5,'|');
						file1.getline(cel_no_contact,20,'|');
						file1.getline(city_contact,20,'\n');
						strcpy(contactData[i].ind,ind_contact);
						strcpy(incontact[i].id,id);
						strcpy(incontact[i].indcontact,ind_contact);
					}
					sort_index_contact();
					for(int i=0;i<no_contact;i++)
					{
						file2<<incontact[i].id<<"|"<<incontact[i].indcontact<<"\n";
					}
					file1.close();
					file2.close();
    }
continue;//control back to inner loop -1

case '2'://search data
{
                cout<<"Enter the Id of the contact whose record is to be searched:\t";
				cin>>st_id;
				int q=search_index_contact(st_id);
				if(q==1){
					cout<<"Search successful\n";
					cout<<"Press any key to continue\n";
                    getch();
				}
				else{
					cout<<"Search unsuccessful\n";
					cout<<"Press any key to continue\n";
                    getch();
				}

}
continue;//control back to inner loop -1



case '3'://delete data

    {
                cout<<"Enter the Id of the contact whose record is to be deleted:\t";
				cin>>st_id;
				delet_contact(st_id);
    }
    continue;//control back to inner loop -1

case '4'://display contacts city-wise
    {
        char bat[10];
        cout<<"Enter the city whose record you want to display\n";
        cin>>bat;
        for(int k = 0;k<no_contact;k++)
        {
            if(strcmp(contactData[k].city,bat)==0)
            {
                cout<<contactData[k].fname<<"\t"<<contactData[k].lname<<"\t"<<contactData[k].id<<"\t"<<contactData[k].age<<"\t"<<contactData[k].cel_no<<"\t"<<contactData[k].city<<endl;

            }
        }

        cout<<"Press any key to continue\n";
        getch();
    }
    continue;



case '5'://display all data
			{
				fstream f1;
				f1.open("contact.txt",ios::in);
				if(!f1)
				{
					cout<<"Error!!!";
					exit(0);
				}
				int i=0;
				while(i!=no_contact)
				{
				    cout<<contactData[i].ind<<"\t"<<contactData[i].fname<<"\t"<<contactData[i].lname<<"\t"<<contactData[i].id<<"\t"<<contactData[i].age<<"\t"<<contactData[i].cel_no<<"\t"<<contactData[i].city<<"\n";
				    i++;
				}
				f1.close();
				cout<<"Press any key to continue\n";
				getch();
			}
			continue;



case '6':
{
	cout<<"thankyou for using software\n";
	exit(0);
}
}
}
}
