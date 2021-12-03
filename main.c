#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

void displaymenu(void);
void currenttime(void);
void addbooks(void);
void rembooks(void);
void editbooks(void);
void searchbooks(void);
void password(void);
void list(void);
void setting(void);
void gotoxy(int,int);
int checkid(int);
void exitapp(void);


char* branch[]={"Computer Science and Engineering","Electronics & Communication","Mechanical Engineering","Electrical Engineering","Civil Engineering"};
FILE *fp;
char passor[20]="12345";

struct book{
char* br;
int bookid;
char title[50];
char author[50];
float price;
int quantity;
}b1;

int main()
{
    system("color 71");
    password();
    return 0;
}


void displaymenu(void)
{
    system("cls");
    printf("======================================================================\n\t\t\t  MAIN MENU\n======================================================================\n\n\n");
    printf("   1. ADD BOOKS\n\n   2. REMOVE BOOKS\n\n   3. EDIT BOOKS\n\n");
    printf("   4. SEARCH BOOKS\n\n   5. VIEW LIST\n\n   6. SETTINGS\n\n   7. EXIT\n\nDate and time :- ");
    currenttime();
    printf("Enter Choice \t");
    switch(getch())
    {
    case '1' :
        {
        addbooks();
        break;
        }
    case '2':
        {
        rembooks();
        break;
        }
    case '3':
        {
        editbooks();
        break;
        }
    case '4':
        {
        searchbooks();
        break;
        }
    case '5':
        {
        list();
        break;
        }
    case '6':
        {
        setting();
        break;
        }
    case '7':
        {
        exitapp();
        break;
        }
    default :{
        printf("Invalid choice");
        getch();
        displaymenu();
    }
    }
}

void currenttime(void)
{
	time_t stime;
	time(&stime);
	printf("%s",ctime(&stime));
}


int checkid(int id)
{
    rewind(fp);
    while(fread(&b1,sizeof(b1),1,fp)!=0)
      if(id==b1.bookid)
        return 0;
      return 1;
}
void addbooks(void)
{
    int choice,tempid;
    system("cls");
    printf("\t\t\t\tSelect Branch\n\n");
    printf("  1. Computer Science and Engineering\n\n  2. Electronics & Communication\n\n  3. Mechanical Engineering\n\n");
    printf("  4. Electrical Engineering\n\n  5. Civil Engineering\n\n  6. Back To Main Menu\n\n  Enter your Choice\t");
    scanf("%d",&choice);
    if(choice<1||choice>6){
        printf("INVALID Choice\n");
        getch();
        addbooks();
    }
    if(choice==6)
        displaymenu();

    do{
    system("cls");
    fp=fopen("DataBase.txt","ab+");
    b1.br=branch[choice-1];
    printf("\n\n\t\t\t\t\tEnter the following details\nEnter ZERO(0) in BookID to Go Back\n\n");
    printf("Branch :-%s\n\n",b1.br);
    printf("\t\t\t1. Book ID\t");
    scanf("%d",&b1.bookid);
    if(b1.bookid<=0){addbooks();}
    tempid=b1.bookid;
    if(checkid(b1.bookid)==0){
        printf("\n\tBook Already Exists");
        getch();
        addbooks();
    }
    b1.bookid=tempid;
    b1.br=branch[choice-1];
    printf("\n\t\t\t2. Title\t");
    fflush(stdin);
    gets(b1.title);
    printf("\n\t\t\t3. Author\t");
    fflush(stdin);
    gets(b1.author);
    printf("\n\t\t\t4. Price\t");
    fflush(stdin);
    scanf("%f",&b1.price);
    printf("\n\t\t\t5. Quantity\t");
    scanf("%d",&b1.quantity);
    fwrite(&b1,sizeof(b1),1,fp);
    fclose(fp);
    printf("\n\n\tWant To Enter More Books (y/n)\t");
    }while(getch()=='y');
    addbooks();
}


void list(void)
{
    int sl=0;
    system("cls");
    printf("\t\t\t\t\t\tBOOK LIST\nSl No.\tBranch\t\t\t\t\tBook ID\t\tTitle\t\t\t\tAuthor\t\tPrice\t\tQuantity\n");
    fp=fopen("DataBase.txt","rb");
    while(fread(&b1,sizeof(b1),1,fp)!=0){
    printf("\n%d\t%s",++sl,b1.br);
    gotoxy(50,(sl+2));
    printf("%d",b1.bookid);
    gotoxy(64,(sl+2));
    printf("%s",b1.title);
    gotoxy(96,(sl+2));
    printf("%s",b1.author);
    gotoxy(112,(sl+2));
    printf("%.2f",b1.price);
    gotoxy(128,(sl+2));
    printf("%d",b1.quantity);
    }
    fclose(fp);
    printf("\n\nPress any Key to Continue.....");
    while(getch())
        displaymenu();
    }

void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}


void exitapp(void)
{
    printf("\n\nDo you Want to Exit (y/n)\n");
    if(getch()=='y'){
            system("cls");
            printf("\n\n\t\t\tDeveloped by :-\n\n\t\t\t================\n\t\t\t Govind Naresh\n\t\t\t================\n\n\n\tPress any Key To Exit....");
            getch();
            exit(0);
    }
    else
        displaymenu();
}


void searchbooks(void)
{
    int id;
    system("cls");
    printf("\t\t\t\tSEARCH\n\n\tEnter Book ID to Search\t");
    scanf("%d",&id);
    fp=fopen("DataBase.txt","rb");
    while(fread(&b1,sizeof(b1),1,fp)!=0){
        if(id==b1.bookid){
            printf("\n\n\tRecord FOUND\n\tBook ID : %d\n\tTitle : %s\n\tAuthor : %s\n\tPrice : %.2f\n\tQuantity : %d\n",b1.bookid,b1.title,b1.author,b1.price,b1.quantity);
            break;}
    }
        if(fread(&b1,sizeof(b1),1,fp)==0)
        printf("\n\tNO Record Found\n");
        fclose(fp);
        printf("\nPress any Key To Continue...\n");
        while(getch())
        displaymenu();
    }


void editbooks(void)
{
    int id;
   system("cls");
   printf("======================================================================\n\t\t\t\tEDIT BOOK\n======================================================================\n");
    printf("\n\tEnter Book ID to Edit\t");
    scanf("%d",&id);
    fp=fopen("DataBase.txt","rb+");
    while(fread(&b1,sizeof(b1),1,fp)!=0){
        if(id==b1.bookid){
            printf("\n\n\tRecord FOUND\n\tBook ID : %d\n\tTitle : %s\n\tAuthor : %s\n\tPrice : %.2f\n\tQuantity : %d\n",b1.bookid,b1.title,b1.author,b1.price,b1.quantity);
            printf("\n\tEnter\n\tNew Title : ");
            fflush(stdin);
            gets(b1.title);
            printf("\n\tNew Author : ");
            fflush(stdin);
            gets(b1.author);
            printf("\n\tNew Price : ");
            fflush(stdin);
            scanf("%f",&b1.price);
            printf("\n\tNew Quantity : ");
            fflush(stdin);
            scanf("%d",&b1.quantity);
            fseek(fp,ftell(fp)-sizeof(b1),0);
            fwrite(&b1,sizeof(b1),1,fp);
            break;}
    }
        if(fread(&b1,sizeof(b1),1,fp)==0)
        printf("\n\tNO Record Found\n");
        fclose(fp);
        printf("\nPress any Key To Continue...\n");
        while(getch())
        displaymenu();

}


void rembooks(void)
{
        int id,count=0;
        FILE *ft=fopen("Temp.dat","wb");
        system("cls");
        printf("\n\t\tEnter Book ID to Remove Book\t");
        scanf("%d",&id);
        fp=fopen("DataBase.txt","rb");
        while(fread(&b1,sizeof(b1),1,fp)!=0){
                if(id!=b1.bookid){
                fwrite(&b1,sizeof(b1),1,ft);
                }
                else if(id==b1.bookid)
                    count++;
        }
        if(count==0)
            printf("\n\t\tNO Record Found\n");
        fclose(fp);
        fclose(ft);
        remove("DataBase.txt");
        rename("Temp.dat","DataBase.txt");
        printf("\n\t\tPress any key to continue...");
}


void password(void)
{
        char pass[20];
        char ch;
        int i=0;
        system("cls");
        gotoxy(15,5);
        printf("Enter PASSWORD  ");
        while(ch!=13)
        {
            ch=getch();
            if(ch!=13&&ch!=8){
            putch('*');
            pass[i]=ch;
            i++;
            }
        }
        pass[i]='\0';
        if(strcmp(passor,pass)==0)
        {
            printf("\n\n\t\tPASSWORD MATCHED\n\tPress any key to continue...");
            getch();
            displaymenu();
        }
        else{
            printf("\n\n\tINCORRECT PASSWORD\n\tTRY AGAIN");
            getch();
            password();
        }

}



void setting(void)
{
    system("cls");
    char passch[20],ch;
    int choice,font,theme,flag=0,i=0;
    printf("\t\t\t\tSETTINGS\n\n\t1. Change Theme\n\n\t2. Change Font Color\n\n\t3. Change Password\n\n\t4. Back To Main Menu\n\n\tEnter Your Choice\t");
    scanf("%d",&choice);
    if(choice==1){
        system("cls");
        A: printf("\n\t1. LIGHT THEME\n\n\t2. DARK THEME\n\n\t3. Back\n\nEnter ...\n");
        scanf("%d",&theme);
        if(theme==1){
        system("color 71");
        flag=0;}
        else if(theme==2){
        system("color 07");
        flag=1;}
        else if(theme==3)
            setting();
        else {
        printf("\nInvalid Choice");
        getch();
        system("cls");
        goto A;
        }
        system("cls");
        goto A;
    }
    else if(choice==2){
        system("cls");
        B: printf("\n\t1. Black\n\n\t2. Blue\n\n\t3. Gray\n\n\t4. Green\n\n\t5. Red\n\n\t6. White\n\n\t7. Back To Settings\n\nEnter...\n");
        scanf("%d",&font);
        switch(font){
    case 1:
        {
            if(flag==0)
         system("color 70");
        printf("ARE YOU SURE TO KEEP THIS COLOR (y/n)\t");
        if(getch()=='y'){system("cls");
        goto B;
            break;
        }
        else{if(flag==0){system("color 71"); system("cls"); goto B; break;}
        if(flag==1){system("color 01"); system("cls"); goto B; break;}
        }
        }
    case 2:
        {
            if(flag==0)
         system("color 71");
        printf("ARE YOU SURE TO KEEP THIS COLOR (y/n)\t");
        if(getch()=='y'){system("cls");
        goto B;
            break;
        }
        else{if(flag==0){system("color 71"); system("cls"); goto B; break;}
        if(flag==1){system("color 01"); system("cls"); goto B; break;}
        }
        }

    case 3:
        {
            if(flag==0)
         system("color 78");
        printf("ARE YOU SURE TO KEEP THIS COLOR (y/n)\t");
        if(getch()=='y'){system("cls");
        goto B;
            break;
        }
        else{if(flag==0){system("color 71"); system("cls"); goto B; break;}
        if(flag==1){system("color 08"); system("cls"); goto B; break;}
        }
        }
    case 4:
        {
            if(flag==0)
         system("color 72");
        printf("ARE YOU SURE TO KEEP THIS COLOR (y/n)\t");
        if(getch()=='y'){system("cls");
        goto B;
            break;
        }
        else{if(flag==0){system("color 71"); system("cls"); goto B; break;}
        if(flag==1){system("color 02"); system("cls"); goto B; break;}
        }
        }
    case 5:
        {
            if(flag==0)
         system("color 74");
        printf("ARE YOU SURE TO KEEP THIS COLOR (y/n)\t");
        if(getch()=='y'){system("cls");
        goto B;
            break;
        }
        else{if(flag==0){system("color 71"); system("cls"); goto B; break;}
        if(flag==1){system("color 04"); system("cls"); goto B; break;}
        }
        }
    case 6:
        {
            if(flag==0)
         system("color 7F");
        printf("ARE YOU SURE TO KEEP THIS COLOR (y/n)\t");
        if(getch()=='y'){system("cls");
        goto B;
            break;
        }
        else{if(flag==0){system("color 71"); system("cls"); goto B; break;}
        if(flag==1){system("color 0F"); system("cls"); goto B; break;}
        }
        }

        case 7:
        {
        setting();
        }
    }
}

else if(choice==4){
     displaymenu();
    }
else if(choice==3)
{
    system("cls");
    printf("\tEnter Current password\t");
        while(ch!=13)
        {
            ch=getch();
            if(ch!=13&&ch!=8){
            putch('*');
            passch[i]=ch;
            i++;
            }
        }
        passch[i]='\0';
        if(strcmp(passor,passch)==0)
        {
          printf("\n\tEnter New Password : ");
          fflush(stdin);
          gets(passor);
          printf("\n\n\tPassword Changed Successfully !!\n\n\tPress any key to continue...");
          getch();
          setting();
        }
        else{
            printf("\n\tINCORRECT Password\n\n\tTRY AGAIN...");
            getch();
            setting();
        }

}
    else {
     printf("\nInvalid Choice\n");
     getch();
     setting();
    }
}
