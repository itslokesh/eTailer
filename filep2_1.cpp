#include<string.h>
#include<iostream>
#include<stdlib.h>
#include<fstream>
void recent_search(char*);
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
	char ch='y';
	do
	{
		trie *ptr=new trie;
		trie *node=new trie;
		int i=0,j=0,k=0,count=0;
		trie *head=new trie;
		strcpy(ptr->data,"empty");
				file f;
		int c,d=0;
		char given[20];
		int some=1;
		fstream file1;
		file1.open("names.dat",ios::binary|ios::in);
		cout<<"Enter the word to search:";		cin>>given;
		for(int t=0;given[t];t++)
			given[t]=tolower(given[t]);
		k=given[0]-97;
		if(k<0)
			cout<<"No elements found!"<<endl;
		else
		{
			for(c=0;c<3;)
			{
				int abc;
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
					//cout<<ptr->data;
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
					count++;
				}
				if(i>1)
				{
					for(int z=0;z<len-i;z++)
					{
						while(head->link[some]!=NULL)
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
			int m=0,g=0;
			if(count==0 || count==1)
			{
				file1.open("names.dat",ios::in|ios::binary);
				int ascnum[20],r;
				for(int s=0;given[s];s++)
					ascnum[s]=given[s]-97;
				while(file1.read((char *)&f,sizeof(f)))
				{
					g=0;
					int lenfile=strlen(f.name);
					int lengiven=strlen(given);
					for(int z=0;z<lenfile-1;z++)
						for(int y=0;y<lengiven-1;y++)
						{
							if(f.num[z]==ascnum[y])
							{
								if(f.num[++z]==ascnum[++y])
								{
									g++;
								}
							--z;
							--y;
							}
						}
					if(g>1)
					{
						cout<<"Related search:"<<f.name<<endl;
						m++;
					}
				}
			}
			if(i<2 && g<2 && m==0)
				cout<<"No elements found!"<<endl;
		}
		recent_search(given);
		cout<<"do you wish to continue (y/n)??";
		cin>>ch;
	}while(ch!='n');
}
void recent_search(char name[20])
{
	static int top=-1;
	static char search[100][20];
	top++;
	strcpy(search[top],name);
	int i=0,count=0;
	i=top;
	if(top>0)
	{
		top--;
		cout<<"Recent searches:"<<endl;
		while(top>=0)
		{
			cout<<search[top];
			cout<<endl;
			top--;
		}
	}
	top=i;
}
