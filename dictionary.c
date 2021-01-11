// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

int size_counter = 0;


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// 122 is the ASCII value of the higher letter in the chart "z" so it should be the max value for buckets
const unsigned int N = ((LENGTH+1) * 122);

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int key_value2 = hash(word);

    for (node *cursor= table[key_value2]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

    }

    return false;
}


// Hashes word to a number
// making the sum of the ASCII values of all the letters of each string for the hash function!

unsigned int hash(const char *word)
{
    int sum_ascii = 0;

    for (int i = 0; i < strlen(word); i+=1)
    {
        sum_ascii+= tolower(word[i]);
    }

    return (sum_ascii % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file_dict = fopen(dictionary, "r");
    if (file_dict == NULL)
    {
        printf("Error while opening dictionary");
        return false;
    }

    char buffer[LENGTH+1];

    while(fscanf(file_dict,"%s", buffer) != EOF)
    {

        node *current_node = malloc(sizeof(node));
        if (current_node == NULL)
        {
            return false;
        }

        size_counter +=1;

        strcpy(current_node->word,buffer);

        current_node->next = NULL;

        int key_value = hash(buffer);

        if(table[key_value] == NULL)
        {
            table[key_value] = current_node;
        }
        else
        {
            current_node -> next = table[key_value];
            table[key_value] = current_node;
        }

//In this case table[key_value] would be the very first node in that key of hash!
// Then you can reset the first element in the linked list to be the new current node!!
    }

    fclose(file_dict);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
// Easiest way to count the size is setting a counter in the loud function!

unsigned int size(void)
{

    return size_counter;

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for ( int i = 0; i< N; i+=1)
    {
        node * current_pointer = table[i];

        while(current_pointer != NULL)
            {
            	node *delete_node = current_pointer;
            	current_pointer = current_pointer -> next;
            	free(delete_node);
            }
    }

return true;

}
