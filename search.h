#ifndef SEARCH
#define SEARCH

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct subnode
{
    char file_name[50];
    int word_count;
    struct subnode *link;
}subnode;

typedef struct mainnode
{
    char word[50];
    int file_count;
    subnode *slink;
    struct mainnode *mlink;
}mainnode;

typedef struct hash
{
    mainnode *link;
}hash;


typedef struct filenode
{
    char file[50];
    struct filenode *link;
}filenode;

void validate_input(int argc,char **argv,filenode **head);
int insert_last(char *file,filenode **head);
void print_list(filenode *head);
void create(filenode *filename,hash *arr);
mainnode *insert_mainnode(hash *add,char *word);
int insert_subnode(mainnode *head,char *file,int cnt);
void display(hash *arr);
void save(hash *arr);
void searchdb(hash *arr);
void update(filenode **head,hash *arr);
void delete_file_node(filenode **head,char *fname);
#endif