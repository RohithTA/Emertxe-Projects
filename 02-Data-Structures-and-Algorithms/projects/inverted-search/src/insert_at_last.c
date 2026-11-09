#include "invert_index.h"

int insert_at_last(slist **head, char *filename)
{
	slist *new = malloc(sizeof(slist));					//creates new node of size slist by allocating memory dynamically
	if(new == NULL)                     				//checks if new node is created or not
	{
		return FAILURE;
	}
	strcpy(new -> filename, filename);					//copies filename to new node filename part
	new -> link = NULL;									//initialize new node link part with NULL

	if(*head == NULL)                 					//checks if list is empty or not
	{
		*head = new;									//Assigning head with new
		return SUCCESS;
	}

	slist *temp = *head;            					//Assigning head value to temp and temp1 pointer
	slist *temp1 = *head;

	while(temp)          								//traverse through the list
	{
		if(temp->filename == filename)					//checks if filenames are same
		{

			return DUPLICATE;							//if same returns MACRO DUPLICATE

		}
		temp1 = temp;									//updates temp1 with temp
		temp = temp ->link;								//updates temp with link part of temp
	}

	temp1 -> link = new;								//updating link part of temp with new node address
	return SUCCESS;
}
