#include<fstream>
#include<iostream>
#include<stdlib.h>
using namespace std;
struct file
{
	char name[27];
	int num[26];
	float price;
	char cat[50];
};
main()
{
	file f;
	fstream file1;
	char ch='y';
	file1.open("names.dat",ios::out);
	file1.seekp(0,ios::end);
	while(ch!='n')
	{
		cin>>f.name;
		cout<<"price";
		cin>>f.price;
		cout<<"category";
		cin>>f.cat;
		for(int j=0;f.name[j];j++)
			f.num[j]=f.name[j]-97;
		file1.write((char*) &f,sizeof(f));
		cout<<"do you wish to continue??(y/n)";
		cin>>ch;
	}
	file1.close();
	int c=0;
	file1.open("names.dat",ios::binary| ios::in);
	while(file1.read((char*) &f,sizeof(f)))
	{
		cout<<f.name<<"   ";
		cout<<f.price<<"   ";
		cout<<f.cat<<"    "<<endl;
		for(int j=0;f.name[j];j++)
			cout<<"  "<<f.num[j];
		cout<<endl;
	}
	file1.close();
}
