#include <iostream>
#include <cstring>
using namespace std;
struct node
{
    char key;
    string value;
    bool tombstone;
};

struct Hash_Table
{
    int capacity;
    int number_of_elements;
    struct node **array;
};

void Intialize_Hash(struct Hash_Table *HT)
{
    HT->number_of_elements = 0;
    HT->capacity = 26;
    HT->array = (struct node **)malloc(sizeof(struct node *) * HT->capacity);

    //intialize to null values
    for (int i = 0; i < HT->capacity; i++)
    {
        HT->array[i] = NULL;
    }
    return;
}

void Intialize_Node(struct node *node, string value)
{
    int length = value.length();
    node->key = value[length - 1];
    node->value = value;
    node->tombstone = false;
}

int Hash_Value(char last_letter)
{
    return last_letter - 'a';
}

int Search(struct Hash_Table *HT, char key)
{
    int pos = Hash_Value(key);

    // If the position and the next are both NULL
    if ((HT->array[pos] == NULL) && (HT->array[(pos + 1) % HT->capacity] == NULL))
    {
        //its not in the table
        return -1;
    }

    //linear probing
    int loop_counter = 0;
    while (loop_counter <= HT->capacity) 
    {
        //checking if the keys match
        if (HT->array[pos] != NULL && !HT->array[pos]->tombstone && HT->array[pos]->key == key)
        {
            return pos;
        }

        //go to next element in array
        pos = (pos + 1) % HT->capacity; 
        loop_counter++;
    }

    //key not found in table
    return -1;
}

void Delete(struct Hash_Table *HT, string value)
{
    char last_letter = value[value.length() - 1];
    int pos = Search(HT, last_letter);
    if(pos == -1)
    {
        //key not found
        return;
    }
    
    while(HT->array[pos] != NULL && !HT->array[pos]->tombstone)
    {
        if(HT->array[pos]->value == value)
        {
            HT->array[pos]->tombstone = true;
    
        }
        pos = (pos + 1) % HT->capacity; 
    }
    
}
void Insert(struct Hash_Table *HT, string value)
{

    char last_letter = value[value.length() - 1];
    // check key already exists
    int pos = Search(HT, last_letter);

    // key already exists
    if (pos != -1)
    {
       // return;
    }
    else
    {
        //key doesn't exist
        pos = Hash_Value(last_letter);
    }
    
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    Intialize_Node(new_node, value);

    // linear probing
    int loop_counter = 0;
    while (HT->array[pos] != NULL && !HT->array[pos]->tombstone)
    {
        
        if (loop_counter >= HT->capacity)
        {
            return;
        }
        // modulo to wrap around
        pos = (pos + 1) % HT->capacity;
        loop_counter++;
    }

    HT->array[pos] = new_node;
    HT->number_of_elements++;
    return;
}

void Display_Hash_Table(struct Hash_Table* HT) {
    for (int i = 0; i < HT->capacity; i++) {
        if (HT->array[i] != NULL && !HT->array[i]->tombstone) {
            cout << HT->array[i]->value << " ";
        } 
    }
}

int main()
{
    struct Hash_Table HT;
    Intialize_Hash(&HT);
    string input;
    getline(cin, input);
    int last_space = 0;
    int length = input.length();

    for(int i = 0; i <= length; i++)
    {
        if (i == input.length() || input[i] == ' ')
        {
            string values = input.substr(last_space, i - last_space);  // Extracting the word correctly
            last_space = i + 1;

            if (values[0] == 'A')
            {
                string val = values.substr(1);  // Extract the value after 'A'
                Insert(&HT, val);
            }
            else if (values[0] == 'D')
            {
                string val = values.substr(1);  // Extract the value after 'D'
                Delete(&HT, val);
            }
        }
    }

    Display_Hash_Table(&HT);

    return 0;
}