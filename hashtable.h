/*
   Author: Ruben Ramirez
   Hash table interface. The hash table is designed to store
   string and integer value pairs.
*/
#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include <stdbool.h>

/* Node to get stored in the hash table */
struct node {
    char *key;
    int frequency;
    struct node *next;
};

struct hashtable {
    struct node **table;
    int currentsize;
    int tablesize;
};

typedef struct hashtable hashtable;

/**
 * Adds a new node to the hash table.
 * @param hashtable *, pointer to struct containing the hash table.
 * @param char *, the key value to be stored.
 * @param int, the value to be stored.
 * @return the newly created node. If the key value is already
 * in the table, return the node containing that key.
 */
struct node * add(hashtable *, char *, int);

/**
 * Checks is a key value is stored in the table.
 * @param hashtable *, pointer to struct containing the hash table.
 * @param char *, the key value to be searched for.
 * @return true if the key is in the table, false otherwise.
 */
bool contains(hashtable *, char *);

/**
 * Checks is a key value is stored in the table, returns the node if
 * it's found.
 * @param hashtable *, pointer to struct containing the hash table.
 * @param char *, the key value to be searched for.
 * @return the node containing the key value, NULL if the node is not
 * found.
 */
struct node * getnode(hashtable *, char *);

/**
 * Deletes a node from the hash table
 * @param hashtable *, pointer to struct containing the hash table
 * @param char *, the key value to be deleted
 */
void deletenode(hashtable *, char *);

/**
 * Displays the elements from the table that have a higher frequency.
 * value than the integer value given as a parameter.
 * @param hashtable *, pointer to struct containing the hash table.
 * @param int, minimum frequency value.
 */
void mostfrequent(hashtable *, int);

/**
 * Initializes a new hash table. Allocates memory for an array.
 * of pointers. Size parameter determines initial size of the array
 * @param int, the size of the array to be created.
 * @param hashtable *, pointer to the new hashtable.
 */
hashtable * createtable(int);

/**
 * Allocates memory and sets the values for a new node.
 * @param int, the value to be stored in the node.
 * @param char *, the key value to be stored in the node.
 * @return node *, pointer to the new node.
 */
struct node * nalloc(char *, int);

/**
 * Deallocates the memory associated with the hash table, including
 * all of the stored nodes.
 * @param hashtable *, pointer to the hashtable to be deallocated.
 */
void freetable(hashtable *);

#endif // HASHTABLE_H_INCLUDED
