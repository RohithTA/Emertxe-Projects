#include"invert_index.h"
int create_database(hash_t *inverted_HT, slist **head)
{
	slist *temp = *head;											//Assigning temp with head 
	char ch[100];
	while(temp)														
	{
		FILE *fptr = fopen(temp -> filename, "r");					//opening file in read mode 
		while( fscanf(fptr, "%s", ch) != EOF)						//reading the file until end of file
		{
			int key = tolower(ch[0]) % 97 ;							//obtaining key or index value by using modulus operation 
			if(key >= 26)
				key = 26;
			if(inverted_HT[key].link == NULL)						//checks if hashtable is empty
			{
				inverted_HT[key].link = create_main_node(ch, temp -> filename);	//function call for main node
			}
			else
			{
				mainnode_t *temp1 = inverted_HT[key].link;			//Assigning temp1 with hashtable link part and prev1 with NULL
				mainnode_t *prev1 = NULL;							

				while(temp1)
				{
					prev1 = temp1;
					if(strcmp(temp1 -> word, ch) == 0)				//checks if word is already present
					{
						subnode_t *temp2 = temp1 -> subnodelink;	//update temp2 with subnode link part of temp1
						subnode_t *prev2 = NULL;					//update prev2 with NULL
						while(temp2)
						{
							prev2 = temp2;							
							if(strcmp(temp2 -> filename, temp -> filename) == 0)	//checks if the filename is same or not
							{
								temp2 -> word_count = temp2 -> word_count + 1;		//increments word count
								break;
							}
							else
							{
								temp2 = temp2 -> link;				//updates temp2 with link part of temp2
							}
						}
						if(temp2 == NULL)							//checks if temp2 equal to NULL
						{
							prev2 -> link = create_sub_node(temp -> filename);	//function call for sub node creation
							(temp1 -> file_count)++;				//increments filecount
							break;
						}
						else
							break;
					}
					temp1 = temp1 -> mainnodelink;					//updates temp1 with mainnode link part of temp1
				}
				if(temp1 == NULL )									//checks if temp1 equal to NULL
				{
					prev1 -> mainnodelink = create_main_node(ch, temp -> filename);	//function call for main node creation
				}
			}

		}

		temp = temp -> link;										//updates temp with link part of temp
		fclose(fptr);												//closing the file
	}
	return SUCCESS;
}

