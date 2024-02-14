//DALUMPINES, SOPHIA J. || BSCS 1B-M

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

FILE *fp;

typedef struct
{
    char name[50];
    int math;
    int english;
    int science;
    int id;
}studentRecord;

void menu();
void studentFile(FILE *fp);

int main()
{
    studentRecord record[100];
    int n=0;
    int i, j;
    int menu_resp;
    char yes_no;

    printf("===============================================================================\n");
    printf("\n\t\t   WELCOME TO STUDENT GRADE MANAGEMENT!\n\n");
    menu();

    do{
        printf("\nEnter a number: ");
        scanf("%d", &menu_resp);
    }while(menu_resp<=0 || menu_resp>5);

    while(menu_resp!=5)
    {
        if(menu_resp == 1)
        {
            fp = fopen("test.txt","a");
            if(!fp)
            {
                printf("Error opening file!\n");
                exit(1);
            }
            printf("\n============================ADD STUDENT========================================\n");

            printf("\nHow many students do you want to add? ");
            scanf("%d", &n);
            for(i=0; i<n; i++)
            {
                printf("\n[%d] Enter the student's name: ", i+1);
                scanf(" %[^\n]s", record[i].name);
                printf("\n    Math grade: ");
                scanf("%d", &record[i].math);
                printf("\n    English grade: ");
                scanf("%d", &record[i].english);
                printf("\n    Science grade: ");
                scanf("%d", &record[i].science);

                srand(time(0));
                record[i].id = rand();
                printf("\n    Here is %s's student ID: %d\n", record[i].name, record[i].id);
            }
            for(j=0;j<n;j++)
            {
                fprintf(fp,"%d\t\t%s\t\t%d\t%d\t%d\n", record[j].id, record[j].name, record[j].math, record[j].english, record[j].science);
            }

            if(n>1)
            {
                printf("\n  %d students were successfully added!\n", n);
            }
            else if(n<=1)
            {
                printf("\n  %d student was successfully added!\n", n);
            }
            fclose(fp);

            printf("\n");
            menu();
            do{
                printf("\nEnter a number: ");
                scanf("%d", &menu_resp);
            }while(menu_resp<=0 || menu_resp>5);
        }

        if(menu_resp == 2)
        {
            fp = fopen("test.txt","r");
            if(!fp)
            {
                printf("Error opening file!\n");
                exit(1);
            }

            printf("\n============================OPEN RECORDS=======================================\n");
            printf("\nSTUDENT ID\tNAME\t\tMATH\tENGLISH\tSCIENCE\n");
            studentFile(fp);
            fclose(fp);

            printf("\n");
            menu();
            do{
                printf("\nEnter a number: ");
                scanf("%d", &menu_resp);
            }while(menu_resp<=0 || menu_resp>5);
        }

        if(menu_resp == 3)
        {
            fp = fopen("test.txt","r");
            if(!fp)
            {
                printf("Error opening file!\n");
                exit(1);
            }

            printf("\n============================EDIT RECORDS=======================================\n");

            char line[500];
            char *token;
            char new_name[50];
            int new_math, new_eng, new_sci;
            int i, j, stud_id;
            int found = 0;

            printf("\nEnter the student's ID: ");
            scanf("%d", &stud_id);

            while(fgets(line,500,fp))
            {
                token = strtok(line,"\t");
                record[i].id = atoi(token);
                token = strtok(NULL,"\t");
                sprintf(record[i].name, "%s", token);
                token = strtok(NULL,"\t");
                record[i].math = atoi(token);
                token = strtok(NULL,"\t");
                record[i].english = atoi(token);
                token = strtok(NULL,"\t");
                record[i].science = atoi(token);
                i++;
            }

            for(i=0; i<n; i++)
            {
                if(record[i].id==stud_id)
                {
                    found=1;
                    printf("\nYou are about to edit the record of %s .\n", record[i].name);
                    printf("\n   Enter new name: ");
                    scanf(" %[^\n]s", new_name);
                    strcpy(record[i].name,new_name);
                    printf("\n   New math grade: ");
                    scanf("%d", &new_math);
                    record[i].math = new_math;
                    printf("\n   New english grade: ");
                    scanf("%d", &new_eng);
                    record[i].english = new_eng;
                    printf("\n   New science grade: ");
                    scanf("%d", &new_sci);
                    record[i].science = new_sci;
                    printf("\nStudent's record successfully edited!\n");
                }
            }
            if(found!=1)
            {
                printf("\nStudent ID does not exist!\n");
            }
            fclose(fp);

            fp = fopen("test.txt","w");
            if(!fp)
            {
                printf("Error opening file!\n");
                exit(1);
            }

            for(i=0; i<n; i++)
            {
                fprintf(fp,"%d\t\t%s\t\t%d\t%d\t%d\n", record[i].id, record[i].name, record[i].math, record[i].english, record[i].science);
            }
            fclose(fp);

            printf("\n");
            menu();
            do{
                printf("\nEnter a number: ");
                scanf("%d", &menu_resp);
            }while(menu_resp<=0 || menu_resp>5);
        }

        if(menu_resp==4)
        {
            fp = fopen("test.txt","r");
            if(!fp)
            {
                printf("Error opening file!\n");
                exit(1);
            }

            printf("\n============================DELETE RECORDS======================================\n");

            char line[500];
            char *token;
            int a, stud_idDel;
            int found = 0;

            while(fgets(line,500,fp))
            {
                token = strtok(line,"\t\n");
                record[i].id = atoi(token);
                token = strtok(NULL,"\t\n");
                sprintf(record[i].name, "%s", token);
                token = strtok(NULL,"\t\n");
                record[i].math = atoi(token);
                token = strtok(NULL,"\t\n");
                record[i].english = atoi(token);
                token = strtok(NULL,"\t\n");
                record[i].science = atoi(token);
                a = i++;
            }

            printf("\nEnter the student's ID: ");
            scanf("%d", &stud_idDel);

            for(i=0; i<a; i++)
            {
                if(record[i].id==stud_idDel)
                {
                    found=1;
                    record[i].id = 0;
                    sprintf(record[i].name,"%s","\0");
                    record[i].math = 0;
                    record[i].english = 0;
                    record[i].science = 0;
                }
            }
            if(found=0)
            {
                printf("\nStudent ID does not exist!\n");
            }
            fclose(fp);

            fp = fopen("test.txt","w");
            if(!fp)
            {
                printf("Error opening file!\n");
                exit(1);
            }

            for(i=0; i<n; i++)
            {
                if(record[i].id!=0)
                    {
                        fprintf(fp,"%d\t\t%s\t\t%d\t%d\t%d\n", record[i].id, record[i].name, record[i].math, record[i].english, record[i].science);
                    }
            }
            fclose(fp);

            printf("\nStudent's record successfully deleted!\n");
            printf("\n");
            menu();
            do{
                printf("\nEnter a number: ");
                scanf("%d", &menu_resp);
            }while(menu_resp<=0 || menu_resp>5);
        }
    }

    if(menu_resp==5)
    {
        printf("\n===============================================================================\n");
        printf("\n\t      THANK YOU FOR VIEWING THE STUDENT GRADE MANAGEMENT!\n\n");
        printf("===============================================================================\n");
    }

    return 0;
}

void menu()
{
    printf("===============================================================================\n");
    printf("\n\t\t\t\tMENU\n");
    printf("\t\t\t[1] Add student\n");
    printf("\t\t\t[2] Open records\n");
    printf("\t\t\t[3] Edit records\n");
    printf("\t\t\t[4] Delete records\n");
    printf("\t\t\t[5] Exit\n");
    printf("\n===============================================================================\n");
}

void studentFile(FILE *fp)
{
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }
}
