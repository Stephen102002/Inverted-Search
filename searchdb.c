#include "search.h"

void searchdb(hash *arr)  
{
    char data[50];
    printf("Enter the word to search\n");
    scanf("%s",data);

    int index;
    if(data[0] >=65 && data[0]<=90)// check if first character is uppercase letter and calculate index accordingly
    {
        index = data[0] - 'A';
    }
    else if(data[0] >=97 && data[0]<=122)// check if first character is lowercase letter and calculate index accordingly
    {
        index = data[0] - 'a';
    }
    else
    {
        index = 26;
    }
    if(arr[index].link == NULL)
    {
        printf("Data not found!\n");
        return;
    }
    else
    {
       mainnode *m_temp = arr[index].link;
       while(m_temp)
       {
            if(strcasecmp(m_temp->word,data) == 0) // if a matching word is found, display the word and its associated files and counts
            {
                printf("[Index:%2d] [Word: %s] [Files:%d] ",index,data,m_temp->file_count);
                subnode *s_temp = m_temp->slink;
                while(s_temp)
                {
                    printf("[%-5s  Count:%d] ",s_temp->file_name,s_temp->word_count);
                    s_temp = s_temp->link;
                }
                printf("\n");
                break;
            }
            else
            {
                m_temp = m_temp->mlink;
            }
       }
       if(m_temp == NULL)
       printf("Data not found!\n");
    }
}