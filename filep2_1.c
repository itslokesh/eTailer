#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;
struct file
{
	char name[27];
	int num[26];
};
class trie
{
	public:
	char data[30];
	trie *link[27];
	trie()
	{
		for(int i=0;i<27;i++)
			link[i]=NULL;
	}
};
int main()
{
	trie *ptr=new trie;
	trie *node=new trie;
	int i=0,j=0,k=0,count=0;
	trie *head=new trie;
	strcpy(ptr->data,"empty");
	head=ptr=node;
	file f;
	int c,d=0;
	char given[20];
	int some=0;
	fstream file1;
	file1.open("names.dat",ios::binary| ios::in);
	cout<<"Enter the word to search:";		cin>>given;
	for(c=0;c<3;)
	{
		int abc=0;
		count=0;
		i=0;
		ptr=head=node;
		file1.read((char*) &f,sizeof(f));
		int len=strlen(f.name);
		while(f.name[i]!='\0')
		{
			k=f.name[i]-97;
			trie *temp=new trie;
			for(j=0;j<=i;j++)
				temp->data[j]=f.name[j];
			temp->data[j]='\0';
			if(i==0)
				node->link[k]=temp;
			ptr->link[k]=temp;
			ptr=temp;
			i++;
		}
		i=0;
		ptr=head=node;
		while(given[i]!='\0')
		{
			k=given[i]-97;
			if(head->link[k]==NULL)
	                      	break;
			head=head->link[k];
			if(strcmp(head->data,"\0")==0)
				break;
			i++;
			count=1;
		}
		if(count==1 && i>2)
		{
			for(int z=0;z<len-i;z++)
			{
				some=0;
				while(head->link[some]==NULL)
				{
					some++;
				}
				head=head->link[some];
			}
			cout<<"Related search:"<<head->data<<endl;
		}
		c++;
	}
	file1.close();
	int m=0;
	if(count==0)
	{
		file1.open("names.dat",ios::in|ios::binary);
		int ascnum[20],r,g=0;
		for(int s=0;given[s];s++)
			ascnum[s]=given[s]-97;
		while(file1.read((char *)&f,sizeof(f)))
		{
			g=0;
			int y=strlen(f.name);
			for(r=0;r<y;r++)
			 	for(int h=0;given[h];h++)
					if(f.num[r]==ascnum[h])
						g++;
		if(g>2)
		{
			cout<<"Related search:"<<f.name<<endl;
			m++;
		}
		}
	}
	if((count==1 && i<2) || m==0)
		cout<<"No elements found!"<<endl;
}
