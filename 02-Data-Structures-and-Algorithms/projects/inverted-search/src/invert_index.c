/*
Name: Rohith T A
Date: 08/04/2023
Description: The purpose of storing an index is to optimize speed and performance in finding relevant documents for a search query.
			 Without an index, the search engine would scan every document in the corpus, which would require considerable time and computing power.
 */

#include "invert_index.h"

int main(int argc, char **argv)
{
	int choice, i;									//declaration of variables
	char option;
	slist *head = NULL;								//Assigning head with NULL

	hash_t inverted_HT[27];

	/*creating hashtable*/
	for(int i = 0; i < 27; i++)
	{
		inverted_HT[i].key = i;
		inverted_HT[i].link = NULL;
	}


	int file_count = 0, flag = 0;

	char searchword[40], filename[20];

	if(argc < 2)									//checks if number of arguments passed is atleast two
	{
		printf("Invalid number of arguments.\n");
		return -1;
	}
	else
	{
		read_and_validate( argc, argv, &head);		//function call for validation
	}

	do
	{
		printf("choose from below option\n");
		printf("1. Create database \n2. Display Database \n3. Search for a word \n4. Save the database\n5. Update to existing database\n");	

		printf("Enter the Choice: ");
		scanf("%d", &choice);
		switch(choice)								//switch case for which function should be called
		{
			case 1:
				file_count = argc - 1;
				flag = 1;
				if(create_database(inverted_HT, &head) == SUCCESS)
				{
					printf("SUCCESS: Database is created\n");
				}
				else
				{
					printf("FAILURE: Database is not created\n");
				}
				break;

			case 2: 
				if(display_database(inverted_HT) == SUCCESS)
				{
					printf("SUCCESS: Database is displayed\n");
				}
				else
				{
					printf("FAILURE: Database cannot be displayed\n");
				}
				break;

			case 3:
				printf("Enter the word that needs to be searched in the database: ");
				scanf("%s", searchword);
				if(search_database(inverted_HT, searchword) == SUCCESS)
				{
					printf("SUCCESS: Element found\n");
				}
				else
				{
					printf("FAILURE: Element not found\n");
				}
				printf("\n");
				break;

			case 4:

				if(save_database(inverted_HT) == SUCCESS)
				{
					printf("SUCCESS: File saved in 'backup_database.txt'\n");
				}
				else
					printf("FAILURE: File not saved");
				break;

			case 5:
				printf("Enter the filename from user\n");
				if(flag == 0)
				{
					if(update_database(inverted_HT) == SUCCESS)
					{
						printf("SUCCESS: Database is updated\n");
					}
				}
				else
				{
					printf("FAILURE: Database is already created\n");
				}
				break;

			default:
				printf("Invalid option\n");
				break;
		}
		printf("Continue (y/n): ");
		scanf("\n%c", &option);
	} while (option == 'y');
	return 0;	
}
