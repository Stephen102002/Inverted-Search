#include "search.h"

void update(filenode **head,hash *arr)  
{
    char backup[50];
    printf("Enter the backup filename\n");
    fflush(stdout);
    scanf("%s",backup);

    FILE *fptr = fopen(backup,"r"); //open backup file for reading
    if(fptr == NULL)
    {
        printf("Invalid backup file\n");
        exit(0);
    }
    char ch = fgetc(fptr);// read first character to check if file is in correct format
    if(ch != '#')
    {
        return;
    }
    else
    {
        rewind(fptr);// reset file pointer to beginning of file
        int index;
        char str[10];
        int f_count;
        while((fscanf(fptr,"#%d;%[^;];%d;",&index,str,&f_count)) != -1)// read index, word and file count from backup file
        {
            mainnode  *ret = insert_mainnode(arr+index,str); // create a new mainnode and insert the word
            ret->file_count = f_count;// set the file count for the mainnode

            int w_cnt;
            char fname[20];
            for(int i=0;i<f_count;i++)
            {
                fscanf(fptr,"%[^;];%d;",fname,&w_cnt);// read file name and word count for each file from backup file
                delete_file_node(head,fname);//delete updated file from file list
                insert_subnode(ret,fname,w_cnt);// insert a new subnode with the file name and word count
                memset(fname,0,sizeof(fname));
            }
            fscanf(fptr,"#\n");
            memset(str,0,sizeof(str));
        }
    }
    fclose(fptr); // close: file
}

void delete_file_node(filenode **head,char *fname)
{
    filenode *temp = *head;
    while(temp)
    {
        if(strcmp(temp->file,fname) == 0)
        {
            *head = temp->link;
            free(temp); // free memory
            break;
        }
        temp = temp->link;
    }
}

