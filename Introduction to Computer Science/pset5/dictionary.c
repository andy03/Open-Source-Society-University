/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

typedef struct node
{
    bool is_word;
    struct node* children[27];
} node;

node* root;
unsigned int dictWords;

#define NEWLINE '\n'

bool freeMemory(node* node);
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* currentNode = root;
    int word_size = strlen(word);
    int childIndex =0;
    
    if(word!= NULL)
    {
        for( int i = 0; i < word_size; i++)
        {
            if (isalpha(word[i]))
            {   
                // get index while ensuring case insensitivity
                childIndex = ((word[i] < 'a') ? word[i] + 32 : word[i]) - 'a';
            }
            else if (word[i] == '\'') 
            {
                childIndex = 26;
            }
            else
            {
                return false;
            }
            
            if(currentNode->children[childIndex] == NULL) 
            {
                return false;
            }
            else
            {
                currentNode = currentNode->children[childIndex];
            }
        } 
        
        return currentNode->is_word;                

    }
    else
    {
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{

    FILE* dictFile = fopen(dictionary, "r");
    
    if(dictFile!=NULL)
    {
        char word[LENGTH +1];
        char currentChar;
        int index=0;
        int childIndex =0;
        dictWords=0;

        root = (node*) malloc(sizeof(node));
        
        if(root == NULL)
        {
            printf("Error allocating memory for root.\n");
            fclose(dictFile);
            return false;
        }
        
        for(int chr = fgetc(dictFile); chr!=EOF; chr= fgetc(dictFile))
        {
            if(chr != NEWLINE)
            {
                word[index] =chr;
                index++;
            }
            else
            {
                word[index] = chr;
                node* currentNode = root;
                
                for(int  i=0; i<=index; i++)
                {
                    currentChar = word[i];
                    
                    if(isalpha(currentChar))
                    {
                        childIndex = tolower(currentChar) -'a';
                        
                        if(currentNode->children[childIndex] == NULL)
                        {
                            currentNode->children[childIndex] = (node*) malloc(sizeof(node));

                            if (currentNode->children[childIndex] == NULL)
                            {
                                printf("Error allocating memory for node.\n");
                                fclose(dictFile);
                                return false;
                            }     
                        }
                           
                        currentNode = currentNode->children[childIndex];   
                    }
                    else if(currentChar == '\'')
                    {
                        if (currentNode->children[26] == NULL)
                        {
                            currentNode->children[26] = 
                                (node*) malloc(sizeof(node));

                            if (currentNode->children[26] == NULL)
                            {
                                printf("Error allocating memory for node.\n");
                                fclose(dictFile);
                                return false;
                            }
                        }
                        
                        
                        currentNode = currentNode->children[26];
                    }
                    else if(currentChar == NEWLINE)
                    {
                        currentNode->is_word = true;
                    }
                }
                
                dictWords++;
                index=0;
            }
        }
        
        fclose(dictFile);
        return true;
        
    }
    else
    {
        printf("Error opening dictionary file %s.\n", dictionary);
        return false;
    }
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictWords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return freeMemory(root);
}


/**
 * frees memory allocated to passed root node and all its child nodes
 *
 * @arg     node*    node    root node to search/free()
 * @return  bool                    true when all nodes are free()'d
 */
bool freeMemory(node* node)
{
    for (int i = 0; i < 27; i++)
    {
        // recursively call freeMemory() for each malloc'd child
        if (node->children[i] != NULL)
        {
            freeMemory(node->children[i]);
        }
    }
    
    // free the parent (this) node
    free(node);

    return true;
}
