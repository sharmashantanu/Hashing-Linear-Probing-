#include <iostream>

using namespace std;
const int TABLE_SIZE = 10;

class LinkedHash
{
	public:
        int key, value;
        LinkedHash *next;
        LinkedHash(int key, int value)
        {
            this->key = key;
            this->value = value;
            this->next = NULL;
        }
};

class HashMap
{
    private:
        LinkedHash **htable;
    public:
        HashMap()
        {
            htable = new LinkedHash*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
            {
                htable[i] = NULL;
            }
        }

        int HashFunc(int key)
		{
            return key % TABLE_SIZE;
        }

        void Insert(int key, int value)
        {
            int hash_val = HashFunc(key);
            if (htable[hash_val] == NULL)
                htable[hash_val] = new LinkedHash(key, value);
            else
            {
                LinkedHash *entry = htable[hash_val];
                while (entry->next != NULL)
                    entry = entry->next;
                    if (entry->key == key)
                        cout<<"Error. Primary Key already present. Delete original key first to insert new value at this key!"<<endl;
                    else
                        entry->next = new LinkedHash(key, value);
            }
        }

        int Find(int key)
        {
            int hash_val = HashFunc(key);
            if (htable[hash_val] == NULL)
                return -1;
            else
            {
                LinkedHash *entry = htable[hash_val];
                while (entry != NULL && entry->key != key)
                    entry = entry->next;
                if (entry == NULL)
                    return -1;
                else
                    return entry->value;
            }
        }

        void Delete(int key)
        {
            int hash_val = HashFunc(key);
            if (htable[hash_val] != NULL)
            {
                LinkedHash *entry = htable[hash_val];
                LinkedHash *prev = NULL;
                while (entry->next != NULL && entry->key != key)
                {
                    prev = entry;
                    entry = entry->next;
                }
                if (entry->key == key)
                {
                    if (prev == NULL)
                    {
                        LinkedHash *next = entry->next;
                        delete entry;
                        htable[hash_val] = next;
                    }
                    else
                    {
                        LinkedHash *next = entry->next;
                        delete entry;
                        prev->next = next;
                    }
                }
            }
        }
};

int main()
{
    HashMap hash;
    int key, value;
    int choice;
    while(1)
    {

        cout<<"Operations on Hash Table : "<<endl;

        cout<<"1.Insert element into the table"<<endl;
        cout<<"2.Search element from the key"<<endl;
        cout<<"3.Delete element at a key"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter element to be inserted: ";
            cin>>value;
            cout<<"Enter key at which element to be inserted: ";
            cin>>key;
            hash.Insert(key, value);
            break;
        case 2:
            cout<<"Enter key of the element to be searched: ";
            cin>>key;
            if (hash.Find(key) == -1)
            cout<<"No element found at key "<<key<<endl;
            else
            {
                cout<<"Element at key "<<key<<" : ";
                cout<<hash.Find(key)<<endl;
            }
            break;

        case 3:
            cout<<"Enter key of the element to be deleted: ";
            cin>>key;
            if (hash.Find(key) == -1)
                cout<<"Key "<<key<<" is empty, nothing to delete"<<endl;
            else
            {
                hash.Delete(key);
                cout<<"Entry Deleted"<<endl;
            }
            break;
        case 4:
            break;
        default:
           cout<<"\nEnter correct option\n";
       }
    }
    return 0;
}
