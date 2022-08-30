#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#define MAXPATIENTS 100

using namespace std;

void patientQueue();
struct patients
{
   char FirstName[50];
   char LastName[50];
   char ID[20];
};
class Queue
{
   public:
   Queue (void);
   int AddPatientAtEnd (patients p);
   int AddPatientAtBeginning (patients p);
   patients GetNextPatient (void);
   int RemoveDeadPatient (patients * p);
   void OutputList (void);
   char DepartmentName[50];
   private:
   int NumberOfPatients;
   patients List[MAXPATIENTS];
};

Queue::Queue ()
{
   NumberOfPatients = 0;
}

int Queue::AddPatientAtEnd (patients p)
{
   // adds a normal patient to the end of the queue.
   // returns 1 if successful, 0 if queue is full.
    if (NumberOfPatients >= MAXPATIENTS)
     {
      // queue is full
      return 0;
     }

      else
      List[NumberOfPatients] = p;  NumberOfPatients++;
      return 1;
}

int Queue::AddPatientAtBeginning (patients p)
{
   // adds a critically ill patient to the beginning of the queue.
   // returns 1 if successful, 0 if queue is full.
   int i;
   if (NumberOfPatients >= MAXPATIENTS)
   {
      // queue is full
      return 0;
   }
   // move all patients one position back in queue
   for (i = NumberOfPatients-1; i >= 0; i--)
   {
      List[i+1] = List[i];
   }
   // put in new patient
   List[0] = p;  NumberOfPatients++;
   return 1;
}
patients Queue::GetNextPatient (void)
{
   // gets the patient that is first in the queue.
   // returns patient with no ID if queue is empty

   int i;  patients p;
   if (NumberOfPatients == 0) {
   // queue is empty
   strcpy(p.ID,"");
   return p;}
   // get first patient
   p = List[0];
   // move all remaining patients one position forward in queue
   NumberOfPatients--;
   for (i=0; i<NumberOfPatients; i++)
   {
      List[i] = List[i+1];
   }
   // return patient
   return p;
}
int Queue::RemoveDeadPatient (patients * p)
{
   // removes a patient from queue.
   // returns 1 if successful, 0 if patient not found
   int i, j, found = 0;
   // search for patient
   for (i=0; i<NumberOfPatients; i++)
	{
      		if (strcmp(List[i].ID, p->ID) == 0)
		{
	 	// patient found in queue
	 	*p = List[i];  found = 1;
	 	// move all following patients one position forward in queue
	 	NumberOfPatients--;
	 		for (j=i; j<NumberOfPatients; j++)
				{
	    				List[j] = List[j+1];
				}
		}
	}
   return found;
}
void Queue::OutputList (void)
{
   // lists entire queue on screen
   int i;
   if (NumberOfPatients == 0)
	{
        cout << "Queue is empty";
	}
   else
	{
		for (i=0; i<NumberOfPatients; i++)
		{
			cout << " " << List[i].FirstName;
	 		cout << " " << List[i].LastName;
	 		cout << " " << List[i].ID;
		}
	}
}

// declare functions used by main:

patients InputPatient (void)
{
   // this function asks user for patient data.
   patients p;
   cout << " Please enter data for new patient First name: \t";
   cin.getline(p.FirstName, sizeof(p.FirstName));
   cout << " \nLast name: ";
   cin.getline(p.LastName, sizeof(p.LastName));
   cout << " \nSocial security number: ";
   cin.getline(p.ID, sizeof(p.ID));
   // check if data valid
   if (p.FirstName[0]==0 || p.LastName[0]==0 || p.ID[0]==0)
	{
      		// rejected
      		strcpy(p.ID,"");
      		cout << "\n Error: Data not valid. Operation cancelled.";
      		getch;
	}
   return p;
}
void OutputPatient (patients * p)
{
   // this function outputs patient data to the screen
   if (p == NULL || p->ID[0]==0)
	{
      		cout << " No patient";
      		return;
	}
   else
   cout << " \nPatient data:";
cout << " \nFirst name: " << p->FirstName;
   cout << "\n Last name: " << p->LastName;
   cout << " \nSocial security number: " << p->ID;
}
int ReadNumber()
{
   // this function reads an integer number from the keyboard.
   // it is used because input with cin >> doesn't work properly!
   char buffer[20];
   cin.getline(buffer, sizeof(buffer));
   return atoi(buffer);
}
void DepartmentMenu (Queue * q)
{
   // this function defines the user interface with menu for one department
   int choice = 0, success;  patients p;
   while (choice != 6)
	{
      	   // clear screen
      	   system ("CLS");
      	   // print menu
      	   cout << "\nWelcome to department: " << q->DepartmentName;
      	   cout << "\nPlease enter your choice:";
      	   cout << "\n1:  Add normal patient";
      	   cout << "\n2:  Add critically ill patient";
      	   cout << "\n3:  Take out patient for operation";
      	   cout << "\n4:  Remove dead patient from queue";
      	   cout << "\n5:  List queue";
      	   cout << "\n6:  Change department or exit\n";
      	   // get user choice
      	   choice = ReadNumber();
      		// do indicated action
      	switch (choice)
	  {
      		case 1:   // Add normal patient
	 	p = InputPatient();
	 	if (p.ID[0])
		   {
	    		success = q->AddPatientAtEnd(p);
	    		system ("CLS");
	    		  if (success)
			    {
	       			cout << "\nPatient added: \n";

			    }
	        else
		   {
	       		// error
	       		cout << "\nError: The queue is full. Cannot add patient:\n";
		   }
	    		OutputPatient(&p);
	    		cout << "\nPress any key\n";
	    		getch();
	  }
	 break;

      case 2:   // Add critically ill patient
	 p = InputPatient();
	 if (p.ID[0])
	     {
	    	success = q->AddPatientAtBeginning(p);
	    	system ("CLS");
	    	  if (success)
			{
	       		  cout << "\nPatient added:\n";
	     		}
	 	  else
	     		{
	       		  // error
	       		  cout << "\nError: The queue is full. Cannot add patient:\n";
			}

			  OutputPatient(&p);
	    		  cout << "\nPress any key\n";
	    		  getch();
	     }
	 break;

      case 3:   // Take out patient for operation
	 p = q->GetNextPatient();
system ("CLS");
	 if (p.ID[0])
	    {
	       cout << "\nPatient to operate:\n";
	       OutputPatient(&p);}
	 else
	    {
	       cout << "\nThere is no patient to operate.\n";
	    }
	       cout << "\nPress any key\n";
	       getch();
	       break;

      case 4:   // Remove dead patient from queue
	 p = InputPatient();
	 if (p.ID[0])
	   {
	        success = q->RemoveDeadPatient(&p);
	    system ("CLS");
	          if (success)
		      {
	       		cout << "\nPatient removed:\n";
		      }
	    	  else
		      {
	       		// error
	       		cout << "\nError: Cannot find patient:";
		      }
	   	OutputPatient(&p);
	    	cout << "Press any key\n";
	    	getch();
	   }
	 break;

      case 5:   // List queue
	 system ("CLS");
	 q->OutputList();
	 cout << " Press any key ";
	 getch();
	 break;
	 }
      }
}
 // few other function declarations
int  chooseMain();
void getDoctorDatabase();
void getPatientDatabase();
void getPatientReport();

//the password class
class password{

	public:
	string pass;
	void getPassword(){
    cout<<"\nChoose a password for your system:"<<endl;
    cin>>pass;
    }

	int verifyPassword()
	{
	string x;
	cout<<"\nEnter the password:"<<endl;
	cin>>x;
	if (x==pass)
	return 1;
	else
	return 0;
   }

    void passwordProtect(){
    	int veri=verifyPassword();

		 if(veri==1){
		 	cout<<"\nAccess Granted!"<<endl;
		 }
		 else
		 {
		cout<<right<<setw(40)<<setfill(' ')<<"\nAccess Denied!\n\nSystem will shut down\n\nPlease come back again."<<endl;
		 exit(0);
		 }
	}
};

//the doctor class
class doctor{
	public:
	string d_fname,d_lname;
	int d_ID, d_age,experience,d_totalno;
	string qual,d_city;
	string getSpec();
   	friend void addDoc();
   	friend void displayDoc();
   	friend void dispDatabase();
   	friend void numberofDocs();
   	friend void getDoctorDatabase();
};
 string doctor::getSpec(){
 	string sp;
	cout<<"1.GENERAL_MEDICINE"<<endl;
	cout<<"2.NEUROLOGY"<<endl;
	cout<<"3.ONCOLOGY"<<endl;
	cout<<"4.HAEMATOLOGY"<<endl;
	cout<<"5.GASTROENTEROLOGY"<<endl;
	cout<<"6.GYNAECOLOGY "<<endl;
	int s;
	cin>>s;
	switch(s){

		case 1:{
			sp= "GENERAL_MEDICINE";
			break;
		}
		case 2:{
			sp="NEUROLOGY";
			break;
		}
		case 3:{
		    sp="ONCOLOGY";
			break;
		}
		case 4:{
			sp= "HAEMATOLOGY";
			break;
		}
		case 5:{
			sp= "GASTROENTEROLOGY";
			break;
		}
		case 6:{
			sp= "GYNAECOLOGY ";
			break;
		}
		default:{
			cout<<"\nPlease Enter a valid option."<<endl;

		}

	}
		return sp;

}
//the addDoc function
void addDoc(){
	    doctor d;
	    cout<<"Fill up the following details"<<endl;
	    cout<<"ID:"<<endl;
	    cin>>d.d_ID;
   		cout<<"First Name:"<<endl;
   		cin>>d.d_fname;
   		cout<<"Last Name:"<<endl;
   		cin>>d.d_lname;
   		cout<<"Age:"<<endl;
   		cin>>d.d_age;
   		cout<<"Choose Qualification among the following:\n1.MBBS\n2.MD"<<endl;
   		int q;
   		cin>>q;
   		if(q==1)
   			d.qual="MBBS";
		else d.qual="MD";
		cout<<"Choose Specialization among the following:"<<endl;
		string spec=d.getSpec();
		cout<<"Experience (in Years):"<<endl;
		cin>>d.experience;
		cout<<"City:"<<endl;
		cin>>d.d_city;
		system("cls");


		fstream fileObj;
		fileObj.open("doctor.txt",ios::app );
      //ID,firstname,lastname,age,qualification,specialization,experience,city

        fileObj.seekp (0, ios::end);
		fileObj<<d.d_ID<<endl<<d.d_fname<<endl<<d.d_lname<<endl<<d.d_age<<endl<<d.qual<<endl<<spec<<endl<<d.experience<<endl<<d.d_city<<endl;
		fileObj.close();

	//after completion
	cout<<"\n\t\tNew Doctor profile created successfully!"<<endl<<endl<<endl;
	cout<<"\n\n\n\nEnter 1 to return to Doctor Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getDoctorDatabase();
	}

	else
	  exit(0);
 //backtoDoctorMenu

	}
//the displayDoc function
void displayDoc()
{
int x;
cout<<"\n\nEnter the ID of the Doctor whose profile you want to display:"<<endl;
cin>>x;									 //ID,firstname,lastname,age,qualification,specialization,experience,city
	ifstream file;file.open("doctor.txt",ios::out|ios::in);
	file.seekg(0);

	int ID,age,exp,count=0;
	string fname,lname,ci,qua,spe;
	while(file >> ID >> fname >> lname >>age >>qua >> spe >>exp >> ci)   //!fileObj.eof()
	{

		if(ID==x)
		{
		cout<<"\n\n1.ID:"<<ID<<endl<<"2.First Name:"<<fname<<endl<<"3.Last Name:"<<lname<<endl<<"4.Age:"<<age<<endl<<"5.Qualification:"<<qua<<endl<<"6.Specialization:"<<spe<<endl<<"7.Experience:"<<exp<<endl<<"8.City:"<<ci<<endl<<endl;
		count++;
		}
	}
	file.close();
	if (count==0)
			cout<<"\nNo matching records found!"<<endl;

	cout<<"\n\nEnter 1 to return to Doctor Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getDoctorDatabase();
	}

	else
	  exit(0);

}

//the dispDatabase function
void dispDatabase(){
	fstream fileObj("doctor.txt");
	fileObj.seekg(0);
	cout<<right<<setw(70)<<setfill(' ')<<"DOCTOR DATABASE"<<endl<<endl;
	int age,exp,count=0;
	string ID,fname,lname,ci,qua,spe;
	while(fileObj>>ID>>fname>>lname>>age>>qua>>spe>>exp>>ci)
	{	count++;
		cout<<right<<setw(50)<<setfill(' ')<<"Doctor Profile:"<<count<<endl;
		cout<<"\n\n1.ID:"<<ID<<endl<<"2.First Name:"<<fname<<endl<<"3.Last Name:"<<lname<<endl<<"4.Age:"<<age<<endl<<"5.Qualification:"<<qua<<endl<<"6.Specialization:"<<spe<<endl<<"7.Experience:"<<exp<<endl<<"8.City:"<<ci<<endl<<endl;
	}

	if(count==0)
	{cout<<"\nNo matching records found!"<<endl;
 	 exit(0);
	}

	cout<<"\n\nEnter 1 to return to Doctor Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1)
	{
	  system("cls");
	  getDoctorDatabase();
	}
	else
	  exit(0);
}

//the numberofDocs function
void numberofDocs(){
	fstream fileObj("doctor.txt");
	fileObj.seekg(0);
	int age,exp,count=0;
	string ID,fname,lname,ci,qua,spe;
	while(fileObj>>ID>>fname>>lname>>age>>qua>>spe>>exp>>ci)
	{	count++;
	}
	cout<<"\n\n\tThe no. of doctors in the hospital="<<count<<endl<<endl;

	cout<<"\n\nEnter 1 to return to Doctor Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1)
	{
	  system("cls");
	  getDoctorDatabase();
	}
	else
	  exit(0);
}

//the patient class
class patient{
	public:
	string fname,lname,occupation,p_city,dis,addDate,relDate;
	int p_age,p_ID;
	long double phnumber,bill;
	string getDept();
	friend void getDoctor();
	friend void addPat();
	friend void editPat(patient &pat);
	friend void displayPat();
	friend void dispPatDatabase();
	friend void numberofPats();
};
string patient::getDept(){
	string sp;
	cout<<"1.GENERAL_MEDICINE"<<endl;
	cout<<"2.NEUROLOGY"<<endl;
	cout<<"3.ONCOLOGY"<<endl;
	cout<<"4.HAEMATOLOGY"<<endl;
	cout<<"5.GASTROENTEROLOGY"<<endl;
	cout<<"6.GYNAECOLOGY "<<endl<<endl;
	int s;
	cin>>s;
	switch(s){

		case 1:{
			sp= "GENERAL_MEDICINE";
			break;
		}
		case 2:{
			sp="NEUROLOGY";
			break;
		}
		case 3:{
		    sp="ONCOLOGY";
			break;
		}
		case 4:{
			sp= "HAEMATOLOGY";
			break;
		}
		case 5:{
			sp= "GASTROENTEROLOGY";
			break;
		}
		case 6:{
			sp= "GYNAECOLOGY ";
			break;
		}
		default:{
			cout<<"\nCome on!Enter a valid option."<<endl;

		}

	}
		return sp;
}

void getDoctor(){
	patient p;
	string dept;
	cout<<"\nEnter the kind of specialization you are looking for:"<<endl<<endl;
	dept=p.getDept();
	fstream fileObj("doctor.txt");
	fileObj.seekg(0);
	cout<<"The doctors available with  "<<dept<<" specialization are:"<<endl<<endl;
	int age,exp,count=0;
	string ID,fname,lname,ci,qua,spe;
	while(fileObj>>ID>>fname>>lname>>age>>qua>>spe>>exp>>ci)
	{
		if(spe==dept){
		cout<<"\n\n1.ID:"<<ID<<endl<<"2.First Name:"<<fname<<endl<<"3.Last Name:"<<lname<<endl<<"4.Age:"<<age<<endl<<"5.Qualification:"<<qua<<endl<<"6.Specialization:"<<spe<<endl<<"7.Experience:"<<exp<<endl<<"8.City:"<<ci<<endl<<endl;
		count++;
		}
	}

	fileObj.close();
	if(count==0){
		cout<<"\nNo doctors with this specialization found!"<<endl;
		exit(0);
	}
	else
		cout<<"No of doctors with "<<dept<<" specialization:"<<count<<endl;

	cout<<"\n\n\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();	 //backtoPatientMenu
	}

	else
	  exit(0);
}
void addPat(){
	patient p;										//ID,firstname,lastname,age,phnumber,occupation,city,disease,Adate,Rdate,bill,spec
	    cout<<"Fill up the following details"<<endl;
	    cout<<"ID:"<<endl;
	    cin>>p.p_ID;
   		cout<<"First Name:"<<endl;
   		cin>>p.fname;
   		cout<<"Last Name:"<<endl;
   		cin>>p.lname;
   		cout<<"Age:"<<endl;
   		cin>>p.p_age;
		cout<<"Phone No.:"<<endl;
   		cin>>p.phnumber;
   		cout<<"Occupation:"<<endl;
		cin>>p.occupation;
		cout<<"City:"<<endl;
		cin>>p.p_city;
   		cout<<"Disease/Symptoms:"<<endl;
   		cin>>p.dis;
   		cout<<"Admission date  (DD/MM/YYYY):"<<endl;
   		cin>>p.addDate;
   		cout<<"Release date  (DD/MM/YYYY):"<<endl;
   		cin>>p.relDate;
   		cout<<"Total Bill generated:"<<endl;
   		cin>>p.bill;
		cout<<"Kind of Specialization required:"<<endl;
		string dept=p.getDept();
		system("cls");
		fstream patObj;
		patObj.open("patient.txt",ios::app );
      //ID,firstname,lastname,age,phnumber,occupation,city,disease,Adate,Rdate,bill,dept

        patObj.seekp (0, ios::end);
		patObj<<p.p_ID<<endl<<p.fname<<endl<<p.lname<<endl<<p.p_age<<endl<<p.phnumber<<endl<<p.occupation<<endl<<p.p_city<<endl<<p.dis<<endl<<p.addDate<<endl<<p.relDate<<endl<<p.bill<<endl<<dept<<endl;
		patObj.close();

	cout<<"\n\t\tNew Patient profile created successfully!"<<endl<<endl<<endl;
	cout<<"\n\n\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();	 //backtoPatientMenu
	}

	else
	  exit(0);
}
void editPat(patient &pat){
	int x;
	cout<<"\nEnter the ID of the Patient whose profile you want to Edit:"<<endl;
	cin>>x;
	fstream patObj("patient.txt");
	patObj.seekg(0);
													//ID,firstname,lastname,age,phnumber,occupation,city,disease,Adate,Rdate,bill,dept
	string fname,lname,occupation,p_city,dis,addDate,relDate,dept;
	int p_age,p_ID,count=0;
	long double phnumber,bill;
	while(patObj>>p_ID>>fname>>lname>>p_age>>phnumber>>occupation>>p_city>>dis>>addDate>>relDate>>bill>>dept)
	{
		if(p_ID==x){
		cout<<"1.ID:"<<p_ID<<endl<<"2.First Name:"<<fname<<endl<<"3.Last Name:"<<lname<<endl<<"4.Age"<<p_age<<endl<<"5.Phone No.:"<<phnumber<<endl<<"6.Occupation:"<<occupation<<endl<<"7.City:"<<p_city<<endl<<"8.Disease/Symptoms:"<<dis<<endl<<"9.Admission date(DD/MM/YYYY):"<<addDate<<endl<<"10.Release date(DD/MM/YYYY):"<<relDate<<endl<<"11.Total Bill generated:"<<bill<<endl<<"12.Kind of Specialization required:"<<dept<<endl;
		count++;
		break;
		}
	}
	patObj.close();
	if(count==0){
		cout<<"\nNo matching records found!"<<endl;
		exit(0);
	}

							//datatransfer begins
	fstream file("patient.txt");
	file.seekg (0, ios::beg);
	file.seekg(0);
	int line;
    ofstream tempObj;
	tempObj.open("copy2.txt");
    tempObj.seekp(0);
  	int skip = 0;
  	string fname1,lname1,occupation1,p_city1,dis1,addDate1,relDate1,dept1;
	int p_age1;
	long double phnumber1,bill1;
	file.seekg(0);file.seekg(0,ios::cur); //setting the pointer to beginning of file

	while(file>>line>>fname1>>lname1>>p_age1>>phnumber1>>occupation1>>p_city1>>dis1>>addDate1>>relDate1>>bill1>>dept1)
	{
		if(line!=x){
			tempObj<<line<<endl<<fname1<<endl<<lname1<<endl<<p_age1<<endl<<phnumber1<<endl<<occupation1<<endl<<p_city1<<endl<<dis1<<endl<<addDate1<<endl<<relDate1<<endl<<bill1<<endl<<dept1<<endl;
		}
	}
  file.close();
  tempObj.close();
  remove("patient.txt");
  int result;
  char oldname[] ="copy2.txt";
  char newname[] ="patient.txt";
  result= rename( oldname , newname );
								//datatransfer ends
	int edit;
	cout<<"\nEnter number corresponding to the Field you want to Edit:"<<endl<<endl;
	cin>>edit;										//ID,firstname,lastname,age,phnumber,occupation,city,disease,Adate,Rdate,bill,spec
	switch(edit)
	{
		case 1:{
			cout<<"ID"<<endl;
			cin>>p_ID;
			break;
		}
		case 2:{
			cout<<"First Name:"<<endl;
			cin>>fname;

			break;
		}
		case 3:{
			cout<<"Last Name:"<<endl;
			cin>>lname;

			break;
		}
		case 4:{cout<<"Age:"<<endl;
			cin>>p_age;
			break;
		}
		case 5:{
			cout<<"Phone No.:"<<endl;
   			cin>>phnumber;
			break;
		}
		case 6:{
			cout<<"Occupation:"<<endl;
			cin>>occupation;
			break;
		}
		case 7:{
			cout<<"City:"<<endl;
			cin>>p_city;
			break;
		}

		case 8:{
			cout<<"Disease/Symptoms:"<<endl;
			cin>>dis;
			break;
		}
		case 9:{
			cout<<"Admission date  (DD/MM/YYYY):"<<endl;
			cin>>addDate;
			break;
		}
		case 10:
		{
		cout<<"Release date  (DD/MM/YYYY):"<<endl;
		cin>>relDate;
		}
		case 11:{
			cout<<"Total Bill generated:"<<endl;
			cin>>bill;
			break;
		}
		case 12:{
			cout<<"Kind of Specialization required:"<<endl;
			dept=pat.getDept();
			break;
		}
		default:{
			cout<<"\nEnter a valid option."<<endl;
			break;
		}
	}
	system("cls");
	cout<<right<<setw(50)<<setfill(' ')<<"--Updated Profile--"<<endl<<endl;
	cout<<"1.ID:"<<p_ID<<endl<<"2.First Name:"<<fname<<endl<<"3.Last Name:"<<lname<<endl<<"4.Age"<<p_age<<endl<<"5.Phone No.:"<<phnumber<<endl<<"6.Occupation:"<<occupation<<endl<<"7.City:"<<p_city<<endl<<"8.Disease/Symptoms:"<<dis<<endl<<"9.Admission date(DD/MM/YYYY):"<<addDate<<endl<<"10.Release date(DD/MM/YYYY):"<<relDate<<endl<<"11.Total Bill generated:"<<bill<<endl<<"12.Kind of Specialization required:"<<dept<<endl;
	fstream newObj;
	newObj.open("patient.txt", ios::app);
	 newObj.seekp (0, ios::end);
	 newObj<<p_ID<<endl<<fname<<endl<<lname<<endl<<p_age<<endl<<phnumber<<endl<<occupation<<endl<<p_city<<endl<<dis<<endl<<addDate<<endl<<relDate<<endl<<bill<<endl<<dept<<endl;
	 newObj.close();
	cout<<"\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();
	}
	else
	  exit(0);

}
void displayPat(){
	int x;
	cout<<"\nEnter the ID of the Patient whose profile you want to Display:"<<endl;
	cin>>x;
	fstream patObj("patient.txt");
	patObj.seekg(0);
													//ID,firstname,lastname,age,phnumber,occupation,city,disease,Adate,Rdate,bill,dept
	string fname,lname,occupation,p_city,dis,addDate,relDate,dept;
	int p_age,p_ID,count=0;
	long double phnumber,bill;
	while(patObj>>p_ID>>fname>>lname>>p_age>>phnumber>>occupation>>p_city>>dis>>addDate>>relDate>>bill>>dept)
	{
		if(p_ID==x){
		cout<<"1.ID:"<<p_ID<<endl<<"2.First Name:"<<fname<<endl<<"3.Last Name:"<<lname<<endl<<"4.Age"<<p_age<<endl<<"5.Phone No.:"<<phnumber<<endl<<"6.Occupation:"<<occupation<<endl<<"7.City:"<<p_city<<endl<<"8.Disease/Symptoms:"<<dis<<endl<<"9.Admission date(DD/MM/YYYY):"<<addDate<<endl<<"10.Release date(DD/MM/YYYY):"<<relDate<<endl<<"11.Total Bill generated:"<<bill<<endl<<"12.Kind of Specialization required:"<<dept<<endl;
		count++;
		break;
		}
	}
	patObj.close();
	if(count==0){
		cout<<"\nNo matching records found!"<<endl;
		exit(0);
	}
cout<<"\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();
	}

	else
	  exit(0);
}
void dispPatDatabase(){
	fstream Obj("patient.txt");
	Obj.seekg(0);
	cout<<right<<setw(70)<<setfill(' ')<<"PATIENT DATABASE"<<endl<<endl;
	string fname,lname,occupation,p_city,dis,addDate,relDate,dept;
	int p_age,p_ID,count=0;
	long double phnumber,bill;
	while(Obj>>p_ID>>fname>>lname>>p_age>>phnumber>>occupation>>p_city>>dis>>addDate>>relDate>>bill>>dept)
	{   count++;
		cout<<right<<setw(50)<<setfill(' ')<<"Patient Profile:"<<count<<endl;
		cout<<"1.ID:"<<p_ID<<endl<<"2.First Name:"<<fname<<endl<<"3.Last Name:"<<lname<<endl<<"4.Age"<<p_age<<endl<<"5.Phone No.:"<<phnumber<<endl<<"6.Occupation:"<<occupation<<endl<<"7.City:"<<p_city<<endl<<"8.Disease/Symptoms:"<<dis<<endl<<"9.Admission date(DD/MM/YYYY):"<<addDate<<endl<<"10.Release date(DD/MM/YYYY):"<<relDate<<endl<<"11.Total Bill generated:"<<bill<<endl<<"12.Kind of Specialization required:"<<dept<<endl<<endl;

		}
	Obj.close();
	if(count==0){
		cout<<"\nNo matching records found!"<<endl;
		exit(0);
	}
cout<<"\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();
	}
	else
	  exit(0);

}
void numberofPats(){
	fstream Obj("patient.txt");
	Obj.seekg(0);
	string fname,lname,occupation,p_city,dis,addDate,relDate,dept;
	int p_age,p_ID,count=0;
	long double phnumber,bill;
	while(Obj>>p_ID>>fname>>lname>>p_age>>phnumber>>occupation>>p_city>>dis>>addDate>>relDate>>bill>>dept)
	{
	 count++;
	}
	Obj.close();
	cout<<"\n\n\tThe number of patients in the hospital="<<count<<endl;
cout<<"\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();
	}
	else
	  exit(0);

}
//the main function
int main(){
	password A;
	A.getPassword();
    system("cls");
	cout<<endl;
	cout<<right<<setw(60)<<setfill(' ')<<"WELCOME TO ST.MUNGO'S HOSPITAL MANAGEMENT SYSTEM "<<endl;
	cout<<endl<<endl;
	cout<<right<<setw(60)<<setfill(' ')<<"------------------------------------------------"<<endl;
	cout<<right<<setw(40)<<setfill(' ')<<"1.Main Menu"<<endl;
	cout<<right<<setw(35)<<setfill(' ')<<"2.Exit"<<endl;
	cout<<right<<setw(60)<<setfill(' ')<<"------------------------------------------------"<<endl<<endl;
	cout<<"Enter your choice:"<<endl<<endl;
	int choice1;
	cin>>choice1;

	if (choice1==1){
		 system("cls");
		 int var=chooseMain();
		 system("cls");

		 	switch(var){
			case 1:{
				A.passwordProtect();
				system("cls");
				getDoctorDatabase();
				break;
			}
			case 2:{
			    A.passwordProtect();
				system("cls");
				getPatientDatabase();
				break;

			}
			case 3:{
			    A.passwordProtect();
				system("cls");
				patientQueue();
                break;
			}
			case 4:
				{
				return 0;
				break;
				}
			default:
				cout<<"\nCome on!Enter a valid option."<<endl;
		}

	}
	else if(choice1==2){
		return 0;
	}
	else
	 cout<<"\nCome on!Enter a valid option."<<endl;
}
int chooseMain(){

	int choice2;
	cout<<right<<setw(40)<<setfill(' ')<<"\nMAIN MENU"<<endl<<endl<<endl;
	cout<<right<<setw(80)<<setfill('-')<<"----------"<<endl;
	cout<<"			"<<"1.Enter Into Doctors' Database"<<endl;
	cout<<"			"<<"2.Enter Into Patients' Database"<<endl;
	cout<<"			"<<"3. Patient Queue"<<endl;
	cout<<"			"<<"4.Exit"<<endl<<endl;
	cout<<right<<setw(80)<<setfill('-')<<"----------"<<endl;

	cout<<"\nEnter the number corresponding to your choice:"<<endl;
	cin>>choice2;
	return choice2;

}
void getDoctorDatabase(){
	int choice_doc;
	cout<<"\n                         " <<"WELCOME TO DOCTOR'S DATABASE"<<endl<<endl;
	cout<<"			"<<"1.Add New Doctor's Information"<<endl;
	cout<<"			"<<"2.Display a Doctor's Information"<<endl;
	cout<<"			"<<"3.Display Entire Doctor Database"<<endl;
	cout<<"			"<<"4.Total Number of Doctors"<<endl;
	cout<<"			"<<"5.Exit"<<endl;
	cout<<right<<setw(80)<<setfill('-')<<"----------"<<endl;

	cout<<right<<setw(60)<<setfill(' ')<<"\nEnter the number corresponding to your choice:"<<endl<<endl;
	cin>>choice_doc;
	system("cls");
	switch(choice_doc){
		case 1:{
		    addDoc();
			break;
		}
		case 2:{
			displayDoc();
			break;
		}
		case 3:{
			dispDatabase();
			break;
		}
		case 4:{
			numberofDocs();
			break;
		}
		case 5:{
			exit(0);
			break;
		}

	}
}
void	getPatientDatabase(){
	int choice_pat;
	cout<<"\n                         "<<"WELCOME TO PATIENT'S DATABASE"<<endl<<endl;
	cout<<"			"<<"1.Add New Patient's Information"<<endl;
	cout<<"			"<<"2.Edit a Patient's Information"<<endl;
	cout<<"			"<<"3.Display a Patient's Information"<<endl;
	cout<<"			"<<"4.Display Entire Patient Database"<<endl;
	cout<<"			"<<"5.Total Number of Patients"<<endl;
	cout<<"			"<<"6.Check for doctor availability"<<endl;
	cout<<"			"<<"7.Exit"<<endl;
	cout<<right<<setw(80)<<setfill('-')<<"----------"<<endl;

	cout<<right<<setw(60)<<setfill(' ')<<"\nEnter the number corresponding to your choice:"<<endl<<endl;
	cin>>choice_pat;
	system("cls");
	switch(choice_pat){
		case 1:{
		    addPat();
			break;
		}
		case 2:{
			patient p;
			editPat(p);
			break;
		}
		case 3:{
			displayPat();
			break;
		}
		case 4:{
			dispPatDatabase();
			break;
		}
		case 5:{
			numberofPats();
			break;
		}
		case 6:{
			getDoctor();
			break;
		}
		case 7:{
			exit(0);
			break;
		}

	}
}
void patientQueue()
{
    int i, MenuChoice = 0;
   // define three queues
   Queue departments[6];
   // set department names
   strcpy (departments[0].DepartmentName, "Heart clinic");
   strcpy (departments[1].DepartmentName, "Lung clinic");
   strcpy (departments[2].DepartmentName, "Plastic surgery");
   strcpy (departments[3].DepartmentName, "neuro surgery");
   strcpy (departments[4].DepartmentName, "oncology surgery");
   strcpy (departments[5].DepartmentName, "body surgery");
   int k=0;
   while (MenuChoice != 7)
	{
         system ("CLS");
      	   // print menu
      	   cout << " \nWelcome to Software City Hospital\n";
      	   cout << "\nPlease enter your choice:\n";
          for (i = 0; i < 6; i++)
		{
	 	   // write menu item for department i
	 	   cout << " " << (i+1) << ":  " << departments[i].DepartmentName<<endl;
		}
      	  cout << " 7:  Exit \n";
      	  MenuChoice = ReadNumber();
      		if (MenuChoice >= 1 && MenuChoice <= 6)
		    {
	 		// call submenu for department
	 		// (using pointer arithmetics here:)
	 		DepartmentMenu (departments + (MenuChoice-1));
		    }
}
}
