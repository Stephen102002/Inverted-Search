#include "search.h"

int main(int argc,char *argv[])  
{
    filenode *head = NULL;  // initialize file list pointer
    validate_input(argc,argv,&head);  // validate and load input files
    printf("valid files: ");  
    print_list(head);  // print the list of valid files
    hash arr[27];  // create hash array with 27 elements (26 for letters + 1 for special characters)
    for(int i=0;i<=26;i++)  
    {
        arr[i].link = NULL;  // set bucket link to NULL
    }
    int c_flag = 0;  
    int u_flag = 0;  
    int choice;  
    while(1)  // infinite loop for menu system
    {
        printf("\n--------------------MENU--------------------\n");  
        printf("1. Create Database\n2. Search Database\n3. Display Database\n4. Save Database\n5. Update Database\n6. Exit\n");  

        printf("--------------------------------------------\n");  
        printf("Enter your choice : \n");  
        printf("--------------------------------------------\n");  
        scanf("%d",&choice); 
        switch(choice)  
        {
            case 1:  
                {
                    if(c_flag == 0 || u_flag == 1)  // check if database needs creation
                    {    
                        create(head,arr);  // create: database from files
                        c_flag = 1;  // set creation flag
                    }
                    else  
                    {
                        printf("#create already done#\n");  // display already created message
                    }
                    break;  
                }
            case 2:  
                    searchdb(arr);  // search: word in database
                    break;  
            case 3:  
                    display(arr);  // display: all entries in database
                    break;  
           case 4:  
                    save(arr);  // save: database to file
                    break;  
            case 5:  
                {
                    if(u_flag == 0 && c_flag != 1)  // check if database needs update
                    {    
                        update(&head,arr);  // restore: database from backup file
                        u_flag = 1;  // set update flag
                    }
                    else  
                    {
                       printf("#data base is up-to-date#\n");  // display up-to-date message
                    }
                    break;  
                }
            case 6:  
                    exit(0);  // exit: program
            default:  
                printf("Invalid choice\n");  // display invalid choice message                                               
        }
    }
}