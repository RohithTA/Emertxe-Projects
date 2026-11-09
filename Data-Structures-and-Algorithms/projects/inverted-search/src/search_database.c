#include"invert_index.h"
int search_database(hash_t *inverted_HT, char *word)
{

	int key = (tolower(word[0]) % 97), flag = 0;					//fetches words converts to lower case and then performs modulus operation
	if(key >= 26)
		key = 26;
	if(inverted_HT[key].link != NULL)								//checks if hash table is empty or not
	{
		mainnode_t *temp = inverted_HT[key].link;					//Assigning temp with link part of hash table
		while(temp)
		{
			if(!strcmp(temp -> word, word))							//checks if the word present is same or not  
			{
				flag = 1;
				subnode_t *temp1 = temp -> subnodelink;				//updates temp1 with subnodelink part of temp
				printf("%s\t%d\t%d\t%s", word, temp -> file_count, temp1 -> word_count, temp1 -> filename);		//fetches word, filecount, wordcount and respective filename and prints it
				temp1 = temp1 -> link;								//updates temp1 with link part of temp1
				while(temp1)
				{
					printf("%d\t%s\t", temp1 -> word_count, temp1 -> filename);
					temp1 = temp1 -> link;
				}
			}
			printf("\n");
			temp = temp -> mainnodelink;							//updates temp with mainnode link part of temp
		}
	}
	if(flag == 1)
		return SUCCESS;
	else
		return FAILURE;
}
