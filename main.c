/* Author: Ruben Ramirez

   Specs: This program reads in data from a text file and
          counts the frequency of each word. A hash table
          is used to store the data. The hash table stores
          nodes that hold both the word and it's frequency.
          After processing the data, the program displays
          words that appeared more than 250 times.

   Text file acquired from MIT's "Practical Programming in C",
   a course provided by MIT as part of their Open Courseware
   website.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"

int main() {

    FILE *in = fopen("book.txt", "r");
    hashtable *hash = createtable(50000);
    struct node *node = NULL;
    char word[100];
    int length = 0;

    /* Load data from txt file to the hash table */
    while(1) {
        if(fscanf(in, "%s", word) != 1)
            break;
	length = strlen(word) - 1;
        if(ispunct(word[length]))
	    *(word + length) = '\0';
	if(strlen(word) > 0)
            node = add(hash, word, 1);
        node->frequency++;
    }
    fclose(in);
    /* Print words with frequency higher than 250 */
    mostfrequent(hash, 250);
    freetable(hash);
    return 0;
}

