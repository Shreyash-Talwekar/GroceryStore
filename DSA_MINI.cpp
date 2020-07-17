// Grocery store 
#include<iostream>
#include<fstream>
#define max 20
using namespace std;
class node{
	node *next;
	string name;
	string item;
	int quantity,tot;
	double telw;
	int pri;
	int price;
	public:
	node(string a,int b)
	{
		item=a;
		price=b;
		next =NULL;
	}
	node(int c,string b)
	{
	item=b;
	quantity=c;	
	next= NULL;
	}
	node(string a,double b,int c,int d)
	{
		name=a;
		telw=b;
		pri=c;
		tot=d;
		next=NULL;
	}
	friend class customer;
	friend class store;
	friend class Que;
};
class store{
	node *head;
	char ch;
	string na;
	double ph;
	public:
	store()
	{
		head=NULL;
	}
	void directory()
	{
		ofstream outfile;
		outfile.open("xyz.txt",ios::out);
		outfile.seekp(0,ios::beg);
		char ch;
		do{
			cout<<"enter name";
			cin>>na;
			outfile<<na<<" ";
			cout<<"enter phone";
			cin>>ph;
			outfile<<ph<<endl;
			cout<<"want to enter"<<endl;
			cin>>ch;
		}while(ch=='y');
	}
	void create()
	{
		cout<<"List of items avialable in the Store"<<endl;
		string a;
		int b;
		do{
			cout<<"Enter the item name"<<endl;
			cin>>a;
			cout<<"Enter its price"<<endl;
			cin>>b;
			if(head==NULL)
			{
			node *n=new node(a,b);	
			head=n;
			}
			else
			{
			node *curr=head;
			   while(curr->next!=NULL)
			   {
			   	curr=curr->next;
			   }
			  node* temp=new node(a,b);
			  curr->next=temp;
			}
			cout<<"Do you have more stuff"<<endl;
			cin>>ch;
		}while(ch=='y');
	}
	void display()
	{
		node *ptr=head;
		cout<<"Item :"<<"\t"<<"Price:"<<endl;
		while(ptr!=NULL)
		{
			cout<<ptr->item<<"\t"<<ptr->price<<endl;
			ptr=ptr->next;
		}
	}
	friend class customer;
};
class customer
{
	node *Head;
	char ca;
	public:
	customer()
	{
		Head=NULL;
	}

	node * create1()
	{
		string b;
		int c;
		do{
			cout<<"Enter the item name"<<endl;
			cin>>b;
			cout<<"Enter its Quantity"<<endl;
			cin>>c;
			if(Head==NULL)
			{
			node *n=new node(c,b);	
			Head=n;
			}
			else
			{
			node *curr=Head;
			   while(curr->next!=NULL)
			   {
			   	curr=curr->next;
			   }
			  node* temp=new node(c,b);
			  curr->next=temp;
			}
			cout<<"Want to buy some more stuff"<<endl;
			cin>>ca;
		}while(ca=='y');
		return Head;
	}
	void display1()
	{
		node *ptr=Head;
		cout<<endl<<ptr->name<<endl<<"ph no."<<ptr->telw<<endl;
		ptr=ptr->next;
		cout<<"Item :"<<"  "<<"Quantity:"<<endl;
		while(ptr!=NULL)
		{
			cout<<ptr->item<<"     "<<ptr->quantity<<endl;
			ptr=ptr->next;
		}
	}
	int priority(node *Head)
	{
		return Head->pri;
	}
	node * billing(store s)
	{   
		int total=0;
		int t,prio;
		string person;
		double tel;
		node *temp=s.head;
		node *tem=Head;
			for(;tem!=NULL;tem=tem->next)
		{
			for(temp=s.head;temp!=NULL;temp=temp->next)
			{
				if(tem->item==temp->item)
				{
					t=tem->quantity*temp->price;
					total=total+t;
				}
				else{
					continue;
				}
			}
		}
		fstream infile;
		infile.open("xyz.txt",ios::in);
		string name1;
		double ph1,ph2;
		cout<<"Enter phone number of customer"<<endl;
		cin>>ph1;
		while (!infile.eof())
		{
			infile>>name1;
			infile>>ph2;
			if(ph1==ph2)
			{
				cout<<"ALready a customer"<<endl;
				cout<<"Name:"<<name1<<endl;
				cout<<"Enter customer Priority"<<endl;
				cin>>prio;
				node *n=new node(name1,ph1,prio,total);
				n->next=Head;
				Head=n;
				//display1();
				break;
			}
		}
		if(infile.eof())
		{
		cout<<"Enter name"<<endl;
		cin>>person;
		cout<<"Enter customer Priority"<<endl;
		cin>>prio;
		node *n=new node(person,ph1,prio,total);
		n->next=Head;
		Head=n;
		}
		//display1();
		//	cout<<person<<endl<<"Phone no."<<tel<<endl;*/
		cout<<"Total :"<<total;
		return Head;
	}
	friend class Que;
};
class Que
{
	int front,rear;
	node * queue[max];
	public:
	Que()
	{
		front=-1;
		rear=-1;
	}
		bool full()
	{
		if(rear==max-1)
		return true;
		return false;
	}
	bool empty()
	{
		if(front==-1)
		return true;
		return false;
	}
	void enqueue(node *head)
	{
		if(!full())
		{
			if(empty())
			{
				front++;
				queue[front]=head;
			}
			rear++;
			queue[rear]=head;
		}
		else
		{
			cout<<endl<<"List is full"<<endl;
		}
	}
	void show(node *head)
	{
		node *ptr=head;
		cout<<endl<<"Name :"<<ptr->name<<endl<<"ph no."<<ptr->telw<<endl;
		ptr=ptr->next;
		cout<<"Item :"<<"  "<<"Quantity:"<<endl;
		while(ptr!=NULL)
		{
			cout<<ptr->item<<"     "<<ptr->quantity<<endl;
			ptr=ptr->next;
		}
		cout<<endl<<"Total :"<<head->tot;
	}	
};
	
int main()
{
	store s;
	s.create();
	s.display();
	s.directory();
	int n;
	int arr[n];
	cout<<"Enter number of customers to be served"<<endl;
	cin>>n;
	node * a[n];
	customer c[n];
	for(int i=0;i<n;i++)
	{
		cout<<"For customer "<<i+1<<endl;
		a[i]=c[i].create1();
	}
	for(int i=0;i<n;i++)
	{
		cout<<endl<<"For person "<<i+1<<endl;
		a[i]=c[i].billing(s);
	}
	for(int i=0;i<n;i++)
	{
		arr[i]=c[i].priority(a[i]);
	}
	Que q;
	int d=1;
		cout<<endl<<"------------------------------------------------------------"<<endl;
		cout<<"Order Delivery List:"<<endl;
		cout<<endl<<"------------------------------------------------------------"<<endl;
	do{
		for(int i=0;i<n;i++)
		if(d==arr[i])
		{
			q.enqueue(a[i]);
			q.show(a[i]);
			cout<<endl<<"------------------------------------------------------------"<<endl;
		}
		d++;
	}while(d<max);
	return 0;
}
