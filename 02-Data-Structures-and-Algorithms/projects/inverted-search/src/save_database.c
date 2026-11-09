#include"invert_index.h"
int save_database(hash_t *inverted_HT)
{
	char file_name[100];
	printf("Enter the filename \n");
	scanf("%s", file_name);
	if(!(strcmp(strstr(file_name,"."),".txt")))				//checks if filename has .txt extension or not
	{
		FILE *fptr = fopen(file_name, "w");					//opening file in write mode
		int index;
		for(index = 0; index < 27; index++)
		{
			if(inverted_HT[index].link != NULL)				//checks if hashtable is empty or not
			{
				mainnode_t *temp = inverted_HT[index].link;	//Assigning temp with link part of hash table
				while(temp)									
				{
					subnode_t *temp1 = temp -> subnodelink;
					fprintf(fptr,"#%d;%s;%d;%d;%s;",index, temp -> word, temp -> file_count, temp1 -> word_count, temp1 -> filename);	//prints index, word, filecount, wordcount and filename respectively
					temp1 = temp1 -> link;
					while(temp1)
					{
						fprintf(fptr, "%d;%s;", temp1 -> word_count, temp1 -> filename);
						temp1 = temp1 -> link;
					}
					fprintf(fptr, "#\n");
					temp = temp -> mainnodelink;			//updates temp with link part of mainnode
				}
			}
		}
		fclose(fptr);										//closing the file
	}
	else
		return FAILURE;
	return SUCCESS;
}

