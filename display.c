#include "search.h"

void display(hash *arr) 
{
    for(int i=0;i<=26;i++)// iterate through each index of the hash array
    {
        if(arr[i].link == NULL)// if the index is empty, skip to the next index
        {
            continue;
        }
        else
        {
            mainnode *m_temp = arr[i].link;
            while(m_temp)// iterate through the mainnode list at the current index
            {
                printf("[Index: %2d] [Word: %-10s] [Files:%d] ",i,m_temp->word,m_temp->file_count);// display the index, word and file count for the current mainnode
                subnode *s_temp = m_temp->slink;
                while(s_temp)// iterate through the subnode list for the current mainnode
                {
                    printf("[%-5s  Count:%d] ",s_temp->file_name,s_temp->word_count);// display the file name and word count for each subnode
                    s_temp = s_temp->link;
                }
                printf("\n");
                m_temp = m_temp->mlink;
            }
        }
    }
}