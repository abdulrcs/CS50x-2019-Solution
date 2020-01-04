#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Declare size dictionary to null first
int sizedictionary = 0;
// Declare head
node *head;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        // Check if we ran out of memory
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        // If suceed, copy word into node
        strcpy(new_node->word, word);
        // Create a linked list
        new_node->next = head;
        head = new_node;
        // Determine a bucket with a hash function
        int bucket = hash(word);

        if (hashtable[bucket])
        {
            new_node->next = hashtable[bucket];
        }
        // Insert new_node into current hashtable
        hashtable[bucket] = new_node;
        // Add size every scanning
        sizedictionary++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // If dictionary size is atleast 1, return size
    if (sizedictionary > 0)
    {
        return sizedictionary;
    }
    // If dictionary is 0 then is not loaded, return 0
    else
    {
        return 0;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = head;
    int bucket = hash(word);
    cursor = hashtable[bucket];

    while (cursor != NULL)
    {
        // Compare string
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // Move to next string
        cursor = cursor->next;
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor;
        cursor = hashtable[i];

        while (cursor)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
            return true;
        }

        // Set the hastable to null / clear the hash table every iteration
        hashtable[i] = NULL;
    }
    return false;
}