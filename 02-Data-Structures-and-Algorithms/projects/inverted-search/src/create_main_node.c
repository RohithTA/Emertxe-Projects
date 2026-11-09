#include"invert_index.h"
mainnode_t *create_main_node(char *word, char *filename)
{
	mainnode_t *new = malloc(sizeof(mainnode_t));			//creates new node of size mainnode dynamically
	if(new == NULL)											//checks if new node is created or not
	{
		return NULL;
	}
	new -> file_count = 1;									//initialize filecount with 1
	strcpy(new -> word, word);								//copies word to new node of word part
	new -> subnodelink = create_sub_node(filename);			//function call for subnode creation and store to new nodes subnode link part
	new -> mainnodelink = NULL;								//initialize mainnodelink with NULL
	return new;												//returns address of new node
}
