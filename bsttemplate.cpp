#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>

using namespace std;

template <typename T>
struct Node
{
        T data;
        Node<T> *left;
        Node<T> *right;
};

template<typename T>
class Bst
{
        Node<T> *root;
        public:
        Node<T> *getNode(T elt);
        Node<T> *getRoot();
        bool insert(T elt);
        bool insert(T*elts,int n);
        bool deletion(T elt);
        bool search(T elt);
        void inorder(Node<T> *N);
        Bst()
        {
                root = NULL;
        }
};

template <typename T>
Node<T>* Bst<T>::getNode(T elt)
{
        Node<T> *N = new Node<T>;
        N->data = elt;
        N->left = NULL;
        N->right = NULL;
        return N;
}

template <typename T>
Node<T>* Bst<T> :: getRoot()
{
        return root;
}

template<typename T>
bool Bst<T>:: insert(T elt)
{
        Node<T> *ptr;
        Node<T> *prev;
        Node<T> *N = getNode(elt);
        ptr = root;
        if(root == NULL)
        {
                root = N;
                root->left = NULL;
                root->right = NULL;
                return true;
        }
        else
        {
                while(ptr !=NULL )
                {
                        prev = ptr;
                        if(ptr->data < elt)
                                ptr = ptr->right;
                        else
                                ptr = ptr->left;
                }
                if(prev->data < elt)
                        prev->right = N;
                else
                        prev->left = N;
                return true;
        }
}

template<typename T>
bool Bst<T>:: insert(T *elts, int n)
{
        for(int i=0; i<n; i++)
                insert(elts[i]);
        return true;
}

template<typename T>
bool  Bst<T>::search(T elt)
{
        Node<T> *ptr = root;
        while(ptr != NULL)
        {
                if(ptr->data == elt)
                {
                        cout<<"Found";
                        return true;
                }
                else if( ptr->data > elt)
                        ptr = ptr->left;
                else
                        ptr = ptr->right;
        }
        cout<<"Not found";
        return false;
}

template<typename T>
void  Bst<T>::inorder( Node<T> *N)
{
        Node<T> *ptr = N;
        if(ptr == NULL)
                return;
        else
        {
                inorder(ptr->left);
                cout<< ptr->data<<" ";
                inorder(ptr->right);
        }
}

template<typename T>
bool  Bst<T>::deletion(T elt)
{
        Node<T> *prev; Node<T> *ptr = root;
        while(ptr->data != elt)
        {
                prev = ptr;
                if(ptr->data < elt)
                        ptr = ptr->right;
                else
                        ptr = ptr->left;
        }
        if(ptr->left == NULL && ptr->right ==NULL)
        {
                if(ptr == prev->left)
                        prev->left = NULL;
                else
                        prev->right = NULL;
                delete(ptr);
                return true;
        }

        else if(ptr->left == NULL)
        {
                if( ptr == prev->right)
                {
                        prev->right = ptr->right;
                        ptr->right = NULL;
                }
                else
                {
                        prev->left = ptr->right;
                        ptr->right = NULL;
                }
                delete(ptr);
                return true;
        }
        else if(ptr->right == NULL)
        {
                if( ptr == prev->right)
                {
                        prev->right = ptr->left;
                        ptr->left = NULL;
                }
                else
                {
                        prev->left = ptr->left;
                        ptr->left = NULL;
                }
                delete(ptr);
                return true;
        }
        else
        {
                Node<T> *rep = (ptr->right)->left;
                Node<T> *temp;
                while(rep->left != NULL)
                {
                        temp = rep;
                        rep = rep->left;
                }
                temp->left = rep->right;
                rep->left = ptr->left;
                rep->right = ptr->right;
                ptr->left = NULL;
                ptr->right = NULL;
                delete(ptr);
                if(prev->data < rep->data)
                        prev->right = rep;
                else
                        prev->left = rep;
                return true;
        }
}

void readfile(int *a,int j)
{
        int i=0;
        fstream fin;
        fin.open("inputbstelt.txt",ios::in);
        while(!fin.eof())
        {
                fin>>a[i];
                i++;
        }
        cout<<endl;
        fin.close();
}

int main()
{
        Bst<int> tree;
        int j;
        cout<<"\n Enter the number of elements: ";
        cin>>j;
        int nums[j];
        cout<<"\n Enter the elements: ";
        for(int i=0;i<j;i++)
            cin>>nums[i];
        fstream fout;
        fout.open("inputbstelt.txt",ios::out);
        for(int i=0; i<j; i++)
                fout<<nums[i]<<endl;
        fout.close();;
        int elts[j];readfile(elts,j);

        tree.insert(elts,j);
        Node<int> *r;
        r = tree.getRoot();
//        tree.deletion(38);
//        tree.insert(elt);
//        tree.search(elt);
        tree.inorder(r);
        return 0;
}
