#ifndef INVERTED_H
#define INVERTED_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<ctype.h>

/* MACRO defination */
#define SUCCESS 0
#define FAILURE -1
#define NOELEMENT -2
#define EMPTYLIST -3
#define DUPLICATE -4
#define FILE_EMPTY -5
#define NOT_PRESENT -6

#define SIZE 27
#define BUFF_SIZE 255
#define NAMELENGTH 50

/*creation of structures*/
typedef struct file_node
{
	char filename[NAMELENGTH];
	struct file_node *link;
}slist;

typedef struct sub_node
{
	char filename[NAMELENGTH];
	int word_count;
	struct sub_node *link;
}subnode_t;

typedef struct main_node
{
	char word[NAMELENGTH];
	struct main_node *mainnodelink;
	struct sub_node *subnodelink;
	int file_count;
}mainnode_t;

typedef struct hashtable
{
	int key;
	struct main_node *link;
}hash_t;

/*function prototypes*/
mainnode_t *create_main_node(char *, char *);
int create_database(hash_t *inverted_HT, slist **head);
subnode_t *create_sub_node(char *fptr);
int read_and_validate(int argc, char *argv[], slist **head);
int insert_at_last(slist **head, char *filename);
int main(int argc, char **argv);
int display_database(hash_t *inverted_HT);
int search_database(hash_t *inverted_HT, char *word);
int save_database(hash_t *inverted_HT);
int update_database(hash_t *inverted_HT);
#endif
