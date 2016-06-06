/*
   Author: Ruben Ramirez
   Implements the interface provided by the hashtable.h file.
   The hash table uses chaining to store items and provides
   functions that perform add, search and delete operations.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

/**
 * Generates a hash code value created from a string value.
 * @param char *, the string to be hashed.
 * @return a positive integer value.
 */
int hashcode(char *);

/**
 * Deallocates the memory of a node.
 * @param struct node *, the node to be deallocated.
 */
void freenode(struct node *);

/* Adds a new node to the hash table*/
struct node * add(hashtable *h, char *key, int freq) {
    struct node *newnode;
    int index = hashcode(key) % h->tablesize;
    struct node *current = h->table[index];

    /* Search for duplicate value */
    while(current != NULL) {
        if(strcmp(key, current->key) == 0)
            return current;
        current = current->next;
    }
    /* Create new node if no duplicate is found */
    newnode = nalloc(key, freq);
    newnode->next = h->table[index];
    h->table[index] = newnode;
    h->currentsize = h->currentsize + 1;
    return newnode;
}

/* Searches for a key, returns true if it finds it */
bool contains(hashtable *h, char *key) {
    int index = hashcode(key) % h->tablesize;
    struct node *current = h->table[index];

    while(current != NULL) {
        if(strcmp(key, current->key) == 0)
            return true;
        current = current->next;
    }
    return false;
}

/* Returns a pointer to a node that matches the given key value */
struct node * getnode(hashtable *h, char *key) {
    int index = hashcode(key) % h->tablesize;
    struct node *current = h->table[index];

    while(current != NULL) {
        if(strcmp(key, current->key) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

/* Deletes a node whose key matches the string parameter */
void deletenode(hashtable *h, char *key) {
    int index = hashcode(key) % h->tablesize;
    struct node *current = h->table[index];
    struct node *previous = NULL;

    if(current == NULL)
        return;
    /* Scan the linked list until  match is found or the end is reached */
    while(current != NULL && strcmp(key, current->key) != 0) {
        previous = current;
        current = current->next;
    }
    /* Item not found */
    if(current == NULL)
        return;
    /* Item is in the first position */
    else if(current == h->table[index])
        h->table[index] = current->next;
    /* Item is in the last position */
    else if(current->next == NULL)
        previous->next = NULL;
    /* Item is in the middle of the list */
    else
        previous->next = current->next;
    /* Deallocate memory for the deleted node */
    freenode(current);
}

/* Prints values that have a value higher than the integer parameter */
void mostfrequent(hashtable *h, int freq) {
    struct node *current = NULL;
    int i;
    printf("\n  Word       Frequency\n");
    printf("  --------------------\n");
    for(i = 0; i < h->tablesize; i++) {
        current = h->table[i];
        while(current != NULL) {
            if(current->frequency > freq)
                printf("  %-14s %d\n", current->key, current->frequency);
            current = current->next;
        }
    }
}

/* Returns a positive integer hash value generated from a string value */
int hashcode(char *key) {
    int i, hash = 7;
    int length = strlen(key);

    for(i = 0; i < length; i++)
        hash = (hash * 31) + *(key + i);
    return hash & 0x7FFFFFFF;  /* Make value positive */
}

/* Returns a pointer to a newly allocated hash table */
struct hashtable * createtable(int size) {
    int i;
    if(size < 1)
        return NULL;
    hashtable *table = (hashtable *) malloc(sizeof(hashtable));
    table->table = (struct node **) malloc(sizeof(struct node *) * size);

    if(table != NULL) {
        table->currentsize = 0;
        table->tablesize = size;
    }
    /* Set all pointers to NULL */
    for(i = 0; i < size; i++)
        table->table[i] = NULL;
    return table;
}

/* Allocates memory for a new node. Initializes the new node's members */
struct node * nalloc(char *key, int freq) {
    struct node *p = (struct node *) malloc(sizeof(struct node));

    if(p != NULL) {
        p->key = strdup(key);
        p->frequency = freq;
        p->next = NULL;
    }
    return p;
}

/* Deallocates memory of the string stored in the node and the
   node itself */
void freenode(struct node *node) {
    free(node->key);
    free(node);
}

/* Deallocates all of the memory associated with the hash table */
void freetable(hashtable *h) {
    struct node *current = NULL;
    int i;

    for(i = 0; i < h->tablesize; i++) {
        current = h->table[i];
        if(current == NULL)
            continue;
        /* Deallocate memory of every node in the table */
        while(current->next != NULL) {
            h->table[i] = h->table[i]->next ;
            freenode(current);
            current = h->table[i];
        }
        freenode(current);
    }
    /* Free the hash table */
    free(h->table);
    free(h);
}


