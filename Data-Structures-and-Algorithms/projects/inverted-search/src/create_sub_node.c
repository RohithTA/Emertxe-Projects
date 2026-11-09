#include"invert_index.h"

subnode_t *create_sub_node(char *fptr)
{
	subnode_t *new_sub = malloc(sizeof(subnode_t));			//creates new node of size subnode_t by allocating memory dynamically 
	if (new_sub == NULL)									//checks if new node is created or not
		return NULL;

	new_sub -> word_count = 1;								//initialize wordcount with 1
	strcpy(new_sub -> filename, fptr);						//copies filename to new nodes filename part
	new_sub -> link = NULL;									//subnode's link part is initialized with NULL

	return new_sub;											//returns address of new subnode
}
