#include "search.h"

void save(hash *arr)  
{
    char file[50];
    skip:
    printf("Enter the file to save data\n");
    scanf("%s",file);
    int flag = 0;
    for(int k=0;k<strlen(file);k++)// check if the file name has a .txt extension
    {
        if(file[k]=='.')// if a dot is found, check if the extension is .txt
        {
            if(strcmp(file+k,".txt") == 0)
            {
                flag = 1;
                break;
            }
        }
    }
    if(flag == 0)
    {
        goto skip;
    }
    FILE *fptr = fopen(file,"w"); //open file for writing mode

    for(int i=0;i<=26;i++)// iterate through each index of the hash array
    {
        if(arr[i].link == NULL)// if the index is empty, skip to the next index
        {
            continue;
        }
        else
        {
            mainnode *m_temp = arr[i].link;
            while(m_temp)// iterate through the mainnode list at the current index and write the data to the file in a specific format
            {
                fprintf(fptr,"#");
                fprintf(fptr,"%d;",i);
                fprintf(fptr,"%s;",m_temp->word);
                fprintf(fptr,"%d;",m_temp->file_count);

                subnode *s_temp = m_temp->slink;
                while(s_temp)// iterate through the subnode list for the current mainnode and write the file name and word count for each subnode to the file
                {
                    fprintf(fptr,"%s;",s_temp->file_name);
                    fprintf(fptr,"%d;",s_temp->word_count);
                    s_temp = s_temp->link;// move to the next subnode in the list
                }
                fprintf(fptr,"#");
                fprintf(fptr,"\n");
                m_temp = m_temp->mlink;// move to the next mainnode in the list
            }
        }
    }
    fclose(fptr); // close: file
}