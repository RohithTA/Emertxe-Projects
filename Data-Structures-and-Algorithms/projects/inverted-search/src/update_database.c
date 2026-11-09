#include"invert_index.h"
int update_database(hash_t *inverted_HT)
{
	char ch[100], word[20];									//declaration of variables
	int key,f_c;
	char filename[100];
	FILE *fptr;
	printf("Enter the filename \n");
	scanf("%s", filename);
	
		if((strcmp(strstr(filename,"."), ".txt")) == 0)		//checks if file is .txt extension or not
		{
			fptr = fopen(filename , "r");					//opening the file in read mode
			if(fptr != NULL)								//checks if file is present or not
			{
				fseek(fptr, 0, SEEK_END);
				if(ftell(fptr) != 0)						//checks if file is empty or not
				{
					fseek(fptr, 0, SEEK_SET);
					while((fscanf(fptr, "%s",ch)) != EOF)	//loop to fetch data which run till end of the file
					{
						if(ch[0] == '#')					//checks if starting character is # or not
						{
							char *str1 = strtok(ch, "#;");	//store the str1 in variable which is fetched from file separated by delimiter
							int count = 0, file_count = 0, wordcount = 0, key;

							mainnode_t *m_new = malloc(sizeof(mainnode_t));		//create new node by allocating memory dynamically
							subnode_t *s_new = malloc(sizeof(subnode_t));
							subnode_t *g_new = malloc(sizeof(subnode_t));
							
							while(str1 != NULL)				//checks if str1 is NULL or not
							{
								if(count == 0)
								{	
									key = atoi(str1);		//converts character to interger by using ascii value
								}
								if(count == 1)
								{
									strcpy(m_new -> word, str1);
									m_new -> subnodelink = s_new;
									m_new -> mainnodelink = NULL;
									s_new -> link = NULL;

									if(inverted_HT[key].link == NULL)		//checks if link part of hash table is NULL or not
									{
										inverted_HT[key].link = m_new;		//update the hash table link part with new main node address
									}
									else
									{
										mainnode_t *m_temp = inverted_HT[key].link;
										while(m_temp -> mainnodelink != NULL)	//traverse through the main node
										{
											m_temp = m_temp -> mainnodelink;	//update temp with main node link
										}
										m_temp -> mainnodelink = m_new;

									}
								}
								if(count == 2)
								{
									file_count = atoi(str1);
									m_new -> file_count = file_count;
								}
								if(count == 3)
								{
									wordcount = atoi(str1);
									if(s_new ->link == NULL)				//checks if sub node link is null or not
									{
										s_new -> word_count = wordcount;	//update sub node word count with wordcount
									}
									else
									{
										g_new -> word_count = wordcount;
									}
								}

								if(count == 4)
								{
									if(s_new -> link == NULL)				//checks if sub node link part is NULL or not
									{
										strcpy(s_new -> filename, str1);
									}
									else
									{
										strcpy(g_new -> filename, str1);
									}
								}
								if(file_count > 1 && count == 4)			//checks file count is greater then 1 and count equal to 4
								{
									subnode_t *s_temp = s_new -> link;
									subnode_t *prev = s_new;
									while(s_temp)							//traverse through the sub node
									{
										prev = s_temp;
										s_temp = s_temp -> link;
									}
									g_new = malloc(sizeof(subnode_t));
									g_new -> link = NULL;
									prev -> link = g_new;
									file_count--;							//decrements the file count
									count = 2;
								}
								count++;									//increments the count
								str1 = strtok(NULL,"#;");					//store the tokens to the variable str1
							}
						}
						else
							return FAILURE;
					}
					fclose(fptr);											//closing the file
					return SUCCESS;
				}
				else
					return FAILURE;
			}
			else
				return FAILURE;
		}
}