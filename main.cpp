#include <iostream>
#include <cstring>
using namespace std;
struct node {
    char key;
    string value;
    bool tombstone;
};

struct Hash_Table {
    int capacity = 26;
    int number_of_elements;
    struct node** array;
};

void Intialize_Hash(struct Hash_Table* HT)
{
    HT->number_of_elements = 0;
    HT->array = (struct node**)malloc(sizeof(struct node*) * HT->capacity);
    return;
}

void Intialize_Node(struct node* node, string value)
{
    int length = value.length();
    node->key = value[length -1];
    node->value = value;
    node->tombstone = false;
}

int Hash_Value(char last_letter)
{
    string alphabet;
    int index = 0;
    for (char c = 'a'; c <= 'z'; ++c) {
        if(last_letter == c)
        {
            return index;
        }

        alphabet += c;
        index++;
    }
    return -1;
}
void Insert(struct Hash_Table* HT, string value)
{
    //do search
    
    char last_letter = value[value.length() -1];
    int pos = Hash_Value(last_letter);

    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    Intialize_Node(new_node, value);
    //linear probing
    int loop_counter =0;
    while(HT->array[pos] != NULL && !HT->array[pos]->tombstone)
    {
        if(loop_counter > HT->capacity)
        {
            cout<<"no space";
            return;
        }
        //modulo to wrap around
        pos = (pos + 1) % HT->capacity;
        cout<<pos;
        loop_counter++;

    }

    HT->array[pos] = new_node;
    HT->number_of_elements++;
    return;
    
}


void Display_Hash_Table(struct Hash_Table* HT) {
    for (int i = 0; i < HT->capacity; i++) {
        if (HT->array[i] != NULL && !HT->array[i]->tombstone) {
            cout << "Index: " << i << " | Key: " << HT->array[i]->key << " | Value: " << HT->array[i]->value << endl;
        } else {
            cout << "Index: " << i << " | Empty" << endl;
        }
    }
}

int main()
{
    struct Hash_Table HT;
    Intialize_Hash(&HT);
    for(int i = 0; i < 30; i++)
    {
        Insert(&HT, "apple");

    }
    Display_Hash_Table(&HT);
    return 0;
    


}