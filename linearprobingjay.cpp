#include<iostream>
using namespace std;
struct node
{
    int data,key;
};
class hash
{
    int nob;
    node **list;
    public:
    hash(int);
    void insert(int,int);
    void find(int);
    void del(int);
    void display();
};
void hash::display()
{
    int i;
    for(i=0;i<nob;i++)
    {
        cout<<"->";
        if(list[i]!=NULL&&list[i]->key!=-1)
        {
            cout<<list[i]->data;
        }
        cout<<"\n";
    }
}
void hash::del(int key)
{
    int value=key%nob;
    while(list[value]!=NULL)
    {
        if(list[value]->key==key)
        {
            list[value]->key=-1;
        }
        else
        {
            value++;
            value=value%nob;
        }
    }
}
void hash::find(int key)
{
    int value=key%nob;
    int flag=0;
    while(list[value]!=NULL)
    {
        int counter =0;
        if(counter++>nob)
            return;
        if(list[value]->key==key)
        {
            cout<<list[value]->data;
            flag=1;
            break;
        }
        value++;
        value %=nob;
    }
    if(flag==0)
        cout<<"no elt found\n";
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
    node *temp=new node;
    temp->key=key;
    temp->data=data;
    while(list[value]!=NULL&&list[value]->key!=-1)
    {
        value++;
        value=value%nob;
    }
    if(list[value]==NULL||list[value]->key==-1)
    {
        list[value]=temp;
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
    cout<<"enter the key to be deleted";
    cin>>key;
    h.del(key);
    h.display();
    cout<<"enter the key to be find";
    cin>>key;
    h.find(key);
}
