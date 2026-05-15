#include "search.h"


void print_list(filenode *head) 
{
    if(head == NULL)
    {
		printf("INFO : List is empty\n");
    }
    else
    {
        while(head != NULL)
        {
            printf("%s ",head->file);
            head = head->link;
        }
    } 
    printf("\n");
}

int insert_last(char *file,filenode **head)
{
    filenode *new = malloc(sizeof(filenode)); // allocate memory for new file node
    if(new == NULL)
    {
        return FAILURE;
    }
    strcpy(new->file,file);
    new->link = NULL;
    if(*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }
    else
    {
        filenode *temp = *head;
        filenode *prev = NULL;
        int flag = 0;
        while(temp != NULL)
        {
            if(strcmp(temp->file,file) != 0)
            {
                prev = temp;
                temp= temp->link;
            }
            else
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            prev->link = new;
            return SUCCESS;
        }
    }
}

void validate_input(int argc,char **argv,filenode **head)
{
    for(int i=1;i<argc;i++)
    {
        char *str = argv[i];// get the file name from command line arguments
        FILE *fptr = fopen(argv[i],"r"); // open file for reading
        if(fptr == NULL)// check if file was opened successfully
        {
            continue;
        }
        else
        {
            for(int j=0;j<strlen(str);j++)// check if the file name has a .txt extension
            {
                if(str[j] == '.')
                {
                    if(strcmp(str+j,".txt") == 0)
                    {
                        char ch;
                        int ret = fscanf(fptr,"%c",&ch);
                        if(ret != -1)//check the file is not empty
                        {
                            insert_last(argv[i],head);// insert the valid file name into the linked list of files
                        }
                    }
                }
            }
        }
        rewind(fptr);
    }
}



