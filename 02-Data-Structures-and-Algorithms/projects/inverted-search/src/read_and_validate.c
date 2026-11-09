#include "invert_index.h"
int read_and_validate(int argc, char *argv[], slist **head)
{
	for(int index = 1; index < argc; index++ )								//loop runs till argc - 1 since index starts from 1
	{
		if(!(strcmp(strstr(argv[index],"."),".txt")))						//checks if given file has .txt extension
		{
			FILE *fp = fopen(argv[index], "r");								//opens file in read mode

			if(fp != NULL)													//checks opened file is present or not
			{
				fseek(fp,0,SEEK_END);										//file pointer is set to 0th address 
				int var = ftell(fp);										//current position is stored to var
				if(var == 0)												//checks if file is empty or not
				{
					printf("The file %s is empty\n", argv[index]); 
				}
				else
				{
					if(insert_at_last(head, argv[index])==SUCCESS)			//function call for insert at last
					{

						printf("SUCCESSFULL : inserting file %s into linked list\n",argv[index]);
					}
					else if(insert_at_last(head, argv[index]) == FAILURE)
					{
						printf("FAILURE : inserting file %s int linked list\n", argv[index]);
					}
					else
					{
						printf("The file %s is already present so no need of insertion again\n", argv[index]);
					}
				}

			}
			else
			{
				printf("The file %s is not present\n", argv[index]);
			}
		}
		else
		{
			printf("the file %s is not .txt file\n", argv[index]);
		}

	}
	return SUCCESS;
}
