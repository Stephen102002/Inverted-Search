#include "search.h"

mainnode *insert_mainnode(hash *add,char *word)
{
    mainnode *new = malloc(sizeof(mainnode)); // allocate memory for new mainnode
    strcpy(new->word,word); // copy the word to the new node
    new->file_count = 1; // initialize file count to 1
    new->slink = NULL; // initialize subnode link to NULL
    new->mlink = NULL; // initialize mainnode link to NULL

    if(add->link == NULL)// if the hash index is empty, insert the new node
    {
        add->link = new;
        return new;
    }
    mainnode *temp = add->link;
    mainnode *prev = NULL;
    while(temp)
    {
        prev = temp;
        temp= temp->mlink;
    }
    prev->mlink = new;// insert the new node at the end of the mainnode list if there are already nodes present
    return new; // return the address of the new node
}

int insert_subnode(mainnode *head,char *file,int cnt)
{
    subnode *new = malloc(sizeof(subnode));// allocate memory for new subnode
    if(new == NULL)// check for memory allocation failure
    {
        return FAILURE;
    }
    strcpy(new->file_name,file);
    new->word_count = cnt;
    new->link = NULL;

    if(head->slink == NULL)// if there are no subnodes, insert the new node
    {
        head->slink = new;
        return SUCCESS;
    }
    else
    {
        subnode *stemp = head->slink;
        subnode *sprev = NULL;
        while(stemp)
        {
            sprev = stemp;
            stemp = stemp->link;
        }
        sprev->link = new;// insert the new node at the end of the subnode list if there are already nodes present
        return SUCCESS;
    }
}

void create(filenode *head,hash *arr)
{
    filenode *temp = head;
    int flag;
    while(temp)// traverse the list of files
    {
        FILE *fptr = fopen(temp->file,"r");// open the file for reading
        char ch;
        char word[20];
        int i=0;
        while((ch = fgetc(fptr)) != EOF)// read each character until end of file
        {
            if(ch !=' ')// if the character is not a space, add it to the current word
            {
                word[i] = ch;
                i++;
            }
            else
            {
                word[i] = '\0';
                int index;
                if(word[0] >=65 && word[0]<=90)// if the first character is an uppercase letter, calculate the index accordingly
                {
                    index = word[0] - 'A';
                }
                else if(word[0] >=97 && word[0]<=122)// if the first character is a lowercase letter, calculate the index accordingly
                {
                    index = word[0] - 'a';
                }
                else
                {
                    index = 26;// if the first character is not an alphabet, assign it to a special index
                }
                if(arr[index].link == NULL)// if there are no mainnodes at the index, create a new mainnode and insert the subnode
                {
                    mainnode *ret = insert_mainnode(arr+index,word);// create a new mainnode and insert the word
                    insert_subnode(ret,temp->file,1);// insert a new subnode with the file name and word count
                }
                else
                {
                    mainnode *m_temp = arr[index].link;// if there are mainnodes at the index, traverse the list to find a matching word
                    while(m_temp)
                    {
                        if(strcasecmp(m_temp->word,word)== 0)// if a matching word is found, update the subnode list
                        {
                            subnode *ftemp = m_temp->slink;
                            while(ftemp)
                            {
                                flag =0;
                                if(strcmp(ftemp->file_name,temp->file) == 0)// if a matching file is found in the subnode list, update the word count
                                {
                                    ftemp->word_count++;// increment the word count for the file
                                    flag = 1;
                                    break;
                                }
                                ftemp = ftemp->link;// traverse the subnode list to find a matching file
                            }
                            if(flag == 1)
                            {
                                break;
                            }
                            if(ftemp == NULL)
                            {
                                m_temp->file_count++;// if no matching file is found in the subnode list, increment the file count for the mainnode
                                insert_subnode(m_temp,temp->file,1);// if no matching file is found in the subnode list, insert a new subnode with the file name and word count
                                break;
                            }
                        }
                        else
                        {
                           m_temp = m_temp->mlink;// traverse the mainnode list to find a matching word
                        }
                    }
                    if(m_temp == NULL)
                    {
                        mainnode *ret = insert_mainnode(arr+index,word);// if no matching word is found in the mainnode list, create a new mainnode and insert the subnode
                        insert_subnode(ret,temp->file,1);
                    }
                }
                i=0;
                memset(word, 0, sizeof(word));
            }
        }
        // handle the last word in the file if it does not end with a space
        word[i] = '\0';
        int index; 
        if(word[0] >=65 && word[0]<=90)
        {
            index = word[0] - 'A';
        }
        else if(word[0] >=97 && word[0]<=122)
        {
            index = word[0] - 'a';
        }
        else
        {
            index = 26;
        }
        if(arr[index].link == NULL)
        {
            mainnode *ret = insert_mainnode(arr+index,word);
            insert_subnode(ret,temp->file,1);
        }
        else
        {
            mainnode *m_temp = arr[index].link;
            while(m_temp)
            {
                if(strcasecmp(m_temp->word,word)== 0)
                {
                    subnode *ftemp = m_temp->slink;
                    while(ftemp)
                    {
                        flag =0;
                        if(strcmp(ftemp->file_name,temp->file) == 0)
                        {
                            ftemp->word_count++;
                            flag = 1;
                            break;
                        }
                        ftemp = ftemp->link;
                    }
                    if(flag == 1)
                    {
                        break;
                    }
                    if(ftemp == NULL)
                    {
                        m_temp->file_count++;
                        insert_subnode(m_temp,temp->file,1);
                        break;
                    }
                }
                else
                {
                    m_temp = m_temp->mlink;
                }
            }
            if(m_temp == NULL)
            {
                mainnode *ret = insert_mainnode(arr+index,word);
                insert_subnode(ret,temp->file,1);
            }
        }
        temp = temp->link;
    }
}