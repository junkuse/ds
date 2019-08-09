#include<iostream>
using namespace std;
struct node
{
    int data;
    node *link;
};
class hash
{
    int nob;
    node **list;
    public:
    hash(int);
    void insert(int,int);
    void find(int,int);
    void del(int,int);
    void display();
};
void hash::display()
{
    int i;
    node *start;
    for(i=0;i<nob;i++)
    {
        cout<<"->";
        start=list[i];
        while(start!=NULL)
        {
            cout<<start->data<<"-";
            start=start->link;
        }
        cout<<"\n";
    }
}
void hash::del(int key,int data)
{
    int value=key%nob;
    node *ptr,*pre;
    if(list[value]->data==data)
    {
        ptr=list[value];
        list[value]=ptr->link;
        delete ptr;
    }
    else
    {
        ptr=list[value]->link;
        pre=list[value];
        while(ptr!=NULL)
        {
            if(ptr->data==data)
            {
                pre->link=ptr->link;
                delete ptr;
            }
            else
            {
                pre=ptr;
                ptr=ptr->link;
            }
        }
    }
}
void hash::find(int key,int data)
{
    int value=key%nob;
    node *start=list[value];
    int flag=0;
    while(start!=NULL)
    {
        if(start->data==data)
        {
            flag=1;
            break;
        }
        start=start->link;
    }
    if(flag==0)
        cout<<"no item found";
    else
        cout<<"yes item found";
}
hash::hash(int size)
{
    nob=size;
    list=new node*[nob];
    for(int i=0;i<nob;i++)
        list[i]=NULL;
}
void hash::insert(int key,int data)
{
    int value=key%nob;
    node *temp=list[value];
    if(list[value]==NULL)
    {
        node *n=new node;
        n->data=data;
        n->link=NULL;
        list[value]=n;
    }

    else
    {
        while(temp->link!=NULL)
        {
            temp=temp->link;
        }
        node *n=new node;
        n->data=data;
        n->link=NULL;
        temp->link=n;
    }
}
int main()
{
    cout<<"enter the no of buckets\n";
    int no,i,key,data;
    cin>>no;
    hash h(no);
    cout<<"enter the no of numbers to be inserted\n";
    cin>>no;
    for(i=0;i<no;i++)
    {
        cout<<"key :";
        cin>>key;
        cout<<"value :";
        cin>>data;
        h.insert(key,data);
    }
    h.display();
    cout<<"enter the key and data to find \n";
    cin>>key>>data;
    h.find(key,data);
    cout<<"enter the key and data to delete \n";
    cin>>key>>data;
    h.del(key,data);
    h.display();
}
