#include"invert_index.h"
int display_database(hash_t *inverted_HT)
{
	mainnode_t *temp1;
	subnode_t *temp2;
	int index = 0, flag = 0;										//declaration of variables
	printf("[index]\tword\tfilecount\twordcount\tfilename\n");
	for(index = 0; index < 27; index++)
	{
		if(inverted_HT[index].link != NULL)							//checks if hash table is empty or not
		{
			flag = 1;
			temp1 = inverted_HT[index].link;						//update temp1 with link part of hashtable
			while(temp1)
			{
				temp2 = temp1 -> subnodelink;
				printf("  %d\t %s\t %d\t\t %d\t\t%s\t", index, temp1 -> word, temp1 -> file_count, temp2 -> word_count, temp2 -> filename);	//fetches the hashtable content and prints it
				temp2 = temp2 -> link;
				while(temp2)
				{
					printf("\t%d\t%s\t", temp2 -> word_count, temp2 -> filename);			//prints hash table content if the element present in same index
					temp2 = temp2 -> link;
				}
				printf("\n");
				temp1 = temp1 -> mainnodelink;						//updates temp1 with mainnode link part of temp1
			}
		}
	}
	if(flag == 1)
		return SUCCESS;
	else
		return FAILURE;
}

