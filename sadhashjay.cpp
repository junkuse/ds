#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
struct Node
{
  bool isEmpty = true;
  int element;
};

class HashTable
{
public:
  int bucket_size,slot_size;
  Node **table,**test;
  void insert(int);
  int HashFunction(int);
  void input_bucket_size();
  void display();
  void search(int);
  void del(int);
  void Rehash();
  int reHashFunction(int);
  void dele()
  {
    for (int i = 0; i < bucket_size; ++i)
      delete [] table[i];
    delete [] table;
    table = test;
  }
  HashTable(int bucket_size,int slot_size)
  {
    this->bucket_size = bucket_size;
    this->slot_size = 2;
    table = new Node*[bucket_size];
    for(int i=0;i<bucket_size;i++)
      table[i] = new Node[slot_size];
    test = new Node*[2*bucket_size];
    for(int i=0;i<26;i++)
      test[i] = new Node[slot_size];
  }
};


void HashTable::del(int value)
{
  int index = HashFunction(value);
  int y = index - 1;
  int j = index,i=0;
  while(1)
  {
    if(table[j][i].element == value)
    {
      table[j][i].isEmpty = true;
      cout << "\nThe element was deleted in " << j << "," << i <<endl;
      break;
    }
    else if( table[j][i+1].element == value)
    {
      table[j][i+1].isEmpty = true;
      cout << "\nThe element was deleted in " << j << "," << i <<endl;
      break;
    }
    else
    {
      j++;
      j = j % bucket_size;
    }
    if(y == j)
    {
      cout << "\nThe element you entered is not found and therefore not deleted" << endl;
      break;
    }
  }
}
int HashTable::HashFunction(int value)
{
  int personal_1,personal_2,index;
  personal_1 = (1 + value) % (bucket_size - 2);
  personal_2 = (value) % bucket_size;
  index = (personal_1 + personal_2) % bucket_size;
  return index;
}

int HashTable::reHashFunction(int value)
{
  int personal_1,personal_2,index;
  personal_1 = (1 + value) % (bucket_size - 2);
  personal_2 = (value) % (bucket_size * 2);
  index = (personal_1 + personal_2) % (bucket_size * 2);
  return index;
}
void HashTable::Rehash()
{
  int i = 0;
  int index;
  bucket_size = bucket_size * 2;
  while(i < bucket_size)
  {
    if(!table[i][0].isEmpty)
    {
      index = reHashFunction(table[i][0].element);
      int y = index - 1;
      while(1)
      {
        if(test[index][0].isEmpty)
        {
          test[index][0].element = table[i][0].element;
          test[index][0].isEmpty = false;
          break;
        }
        else if(test[index][1].isEmpty)
        {
          test[index][1].element = table[i][0].element;
          test[index][1].isEmpty = false;
          break;
        }
        else
        {
          index = (index + 1) % bucket_size;
        }
        if(index == y)
        {
          cout << "\nTable Full";
          Rehash();
          break;
        }
      }
    }
    if(!table[i][1].isEmpty)
    {
      index = reHashFunction(table[i][1].element);
      int y = index - 1;
      while(1)
      {
        if(test[index][0].isEmpty)
        {
          test[index][0].element = table[i][1].element;
          test[index][0].isEmpty = false;
          break;
        }
        else if(test[index][1].isEmpty)
        {
          test[index][1].element = table[i][1].element;
          test[index][1].isEmpty = false;
          break;
        }
        else
        {
          index = (index + 1) % bucket_size;
        }
        if(index == y)
        {
          cout << "\nTable Full";
          break;
        }
      }
    }
    i++;
  }
  dele();
}
void HashTable::search(int value)
{
  int index = HashFunction(value);
  int y = index - 1;
  int j = index,i=0;
  while(1)
  {
    if(table[j][i].element == value || table[j][i+1].element == value)
    {
      cout << "\nThe element is found and found in " << j << endl;
      break;
    }
    else
    {
      j++;
      j = j % bucket_size;
    }
    if(y == j)
    {
      cout << "\nThe element is not found in the hash table" << endl;
      break;
    }
  }
}
void HashTable::insert(int value)
{
  int i = 0,y;
  int index = HashFunction(value);
  y = index;
  while(1)
  {
    if(table[index][i].isEmpty)
    {
      table[index][i].element = value;
      table[index][i].isEmpty = false;
      break;
    }
    else if(table[index][i+1].isEmpty)
    {
      table[index][i+1].element = value;
      table[index][i+1].isEmpty = false;
      break;
    }
    else
    {
      index = (index + 1)% bucket_size;
    }
    if(index == y)
    {
      cout << "\nTable Full";
      Rehash();
      break;
    }
  }
}

void HashTable::display()
{
  for(int i=0;i<bucket_size;i++)
  {
    if(!table[i][0].isEmpty)
    {
      cout << i << " " << table[i][0].element << endl;
      if(!table[i][1].isEmpty)
        cout << i << " " << table[i][1].element << endl;
    }
  }
  cout << endl;
}

int main()
{
  int bucket_size,slot_size,i;
  cout << "\nEnter the bucket size : ";
  cin >> bucket_size;
  cout << "\nEnter the slot size : ";
  cin >> slot_size;
  HashTable T(bucket_size,slot_size);
  int value;
  int no_of_variables;
  int choice;
  while(1)
  {
    cout << "\nEnter 1 to insert in the hash table";
    cout << "\nEnter 2 to display the hash table";
    cout << "\nEnter 3 to search any values";
    cout << "\nEnter 4 to delete any value in hash table";
    cout << "\nEnter 5 to exit your program";
    cout << "\nEnter your choice : ";
    cin >> choice;
    switch(choice)
    {
    case 1:
      cout << "\nEnter the number of values to be entered : ";
      cin >> no_of_variables;
      for(i=0;i<no_of_variables;i++)
      {
        cout << "\nEnter value (i+1)" << i + 1 << " : " ;
        cin >> value;
        T.insert(value);
      }
      break;
    case 2:
      T.display();
      break;
    case 3:
      cout << "\nEnter the value to be searched : ";
      cin >> value;
      T.search(value);
      break;
    case 4:
      cout << "\nEnter the value to be deleted : ";
      cin >> value;
      T.del(value);
      break;
    case 5:
      exit(0);
    default:
      cout << "\nInvalid choice entered....Enter again";
    break;
    }
  }
  return 0;
}

