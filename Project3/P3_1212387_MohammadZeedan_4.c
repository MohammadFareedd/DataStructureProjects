/*  Mohammad Fareed                                                              1212387
 * section 4                                                                      6-6-2023
 *  Program to make a school system using Binary search tree by saving the information of the students  */

/*THERE ARE SOME NOTES YOU SHOULD FOLLOW
* 1-IN THE FILE THE INFORMATION SHOULD BE IN THIS ORDER(NAME,ID,CLASS,DATE,HOME).
 * 2-WHEN YOU ENTER THE CLASS YOU ALSO SHOULD INSERT THE SECTION ALSO NX-->9A,1B,12A....
 * NOT INSERTING THE SECTION WILL BREAK THE PROGRAM SO BE CAREFUL PLEASE -_-
 *                              HAVE FUN!!!!!                                                           */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//A struct to save the information of each student name,id,...
typedef struct {
    char name [100];
    int sid;
    char class [4];
    char date[20];
    char address[20];
}student;
//the struct to represent the tree
struct node{
    student s;
    struct node *right;
    struct node *left;

};
//12 Classes with 4 section -_-
int Classes[12][4];
struct node *root=NULL;
struct node* inset_Student(struct node *root);
struct node* read_fromfile(struct node*);
struct node* getnd(student );
struct node* insert(struct node *r,student);
struct node * search(struct node *r,int x);
struct node* findmin(struct node *r);
void trav(struct node *root);
struct node* del(struct node *r,int x,char[]);
void students_City(struct node*,char city[]);
void class_Student(struct node *root);
void printclass(struct node*,char class[]);
struct node* delete_Student(struct node *root,int id);
void print_onFile(struct node *root);
void printFile(struct node *root,FILE* );
struct node* update (struct node *root,student s);
//MAKE A CLEAR MENU FOR THE USER
int main()
{
    int choice=1,id;
    struct node* Student;
    char city[20];
   root= read_fromfile(root);
    printf("...........WELCOME TO OUR SCHOOL SYSTEM............\n");
    while (choice!=8){
        printf("Select operation\n");
        printf("1-Insert new student\n2-Search for a student\n3-List all students\n"
               "4-List all students from specific city\n5-List the students of each class\n"
               "6-Delete a student from the system\n7-Save the data in a file\n8-Exit\n ");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                root=inset_Student(root);
                break;
            case 2:
                printf("Enter the ID for the student\n");
                scanf("%d",&id);
                Student=search(root,id);
                if(Student!=NULL){
                    printf("Student Found\n");
                    int up;
                    printf("DO you want to make update\n1-YES\n2-NO\n");
                    scanf("%d",&up);
                    if(up==1)
                        root= update(root,Student->s);
                }
                else
                    printf("Student Not found\n");
                break;
            case 3:
                trav(root);
                break;
            case 4:
                printf("Enter the name of the City\n");
                scanf("%s",city);
                students_City(root,city);
                break;
            case 5:
                class_Student(root);
                break;
            case 6:
                printf("Enter the id of the student you Want to delete\n");
                scanf("%d",&id);
                root= delete_Student(root,id);
                break;
            case 7:
                print_onFile(root);
                break;
            case 8:
                break;
            default:
                printf("Invalid selection\n");
        }
        printf("***********************************************\n");
    }
    return 0;
}
//function to insert a new student after taking the information from the user
struct node* inset_Student(struct node *root){
    student s;
    int c,sec;
    printf("Enter the information for the new student\n");
    printf("Enter the ID of the new student\n");
    scanf("%d",&(s.sid));
    if(search(root,s.sid)!=NULL){
        printf("ID already existed\n");
        return root;}
    //clear the buffer and remove the new line from the name
    while (getchar()!='\n');
    printf("Enter the name of the new student\n");
    fgets(s.name,sizeof(s.name),stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    printf("Enter the Class of the new student\n");
    scanf("%s",s.class);
    printf("Enter the date of enrollment of the new student\n");
    scanf("%s",s.date);
    printf("Enter the home address of the new student\n");
    scanf("%s",s.address);
    root=insert(root,s);
    //translate the class to the array.
    c=s.class[0]-48;
    if(s.class[1]=='1'||s.class[1]=='2'||s.class[1]=='0'){

        c=9+s.class[1]-48;
        sec=s.class[2]-65;
    }
    else{

        sec=s.class[1]-65;}
    Classes[c][sec]=1;

    return root;
}
//function to read the student that already saved from the file
struct node* read_fromfile(struct node *root){
    FILE *fin= fopen("students.data","r");
    int s=1;
    int id;
    int c,sec;
    student  s1;
    char star[100];
    //read the  information of the student and remove the new line from its name
    fgets(s1.name,100,fin);
    s=fscanf(fin,"%d",&id);
    s=fscanf(fin,"%s",s1.class);
    s=fscanf(fin,"%s",s1.date);
    s=fscanf(fin,"%s",s1.address);
    s= fscanf(fin,"%s",star);
    getc(fin);
    while (s!=EOF){
        s1.name[strcspn(s1.name, "\n")] = 0;
        s1.sid=id;
        root= insert(root,s1);
        c=s1.class[0]-48;
        //add its class to the array of the classes
        if(s1.class[1]=='1'||s1.class[1]=='2'||s1.class[1]=='0'){
            c=9+s1.class[1]-48;
            sec=s1.class[2]-65;
        }
        else
            sec=s1.class[1]-65;
        Classes[c][sec]=1;
        fgets(s1.name,100,fin);
        s=fscanf(fin,"%d",&id);
        s=fscanf(fin,"%s",s1.class);
        s=fscanf(fin,"%s",s1.date);
        s=fscanf(fin,"%s",s1.address);
        s= fscanf(fin,"%s",star);
        getc(fin);
        }


    fclose(fin);
    return  root;
}
//function to make a new leaf node
struct node* getnd(student s){
    struct node *n=malloc(sizeof(struct node));
    n->s=s;
    n->left=NULL;
    n->right=NULL;
    return n;

};
//function to insert to the tree the main principle in the inserting function that we have PK by combine the name and the id of the student
//first we compare depending on  the name if they are equal we compare the id for example if we have student Ahmad with ID 100, and we
//insert a new student called also ahmad 101 when we compare the twe name we find that they are equal, so we compare the two ID 101>100
//so we insert the new Ahamd to the right of the old Ahmad
struct node* insert(struct node *root, student s){
    if (root==NULL)
        root=getnd(s);

    else if(strcmp(root->s.name,s.name)==1)
        root->left=insert(root->left,s);
    else if(strcmp(root->s.name,s.name)==-1)
        root->right=insert(root->right,s);
    else{
        if(root->s.sid>s.sid)root->left=insert(root->left,s);
        else root->right=insert(root->right,s);
    }
    return root;

}
//function to find a student with a specific ID
struct node* search(struct node *root,int x){
    if(root==NULL)return NULL;
    else if(root->s.sid==x)return root;
    else{
        struct node *temp=search(root->left, x);
        if(temp!=NULL)return temp;
        return  ( search(root->right, x));


    }
}
//function to return the min student
struct node* findmin(struct node *root){
    if(root==NULL){
        printf("empty");
        exit(1);
    }
    if(root->left==NULL)return root;
    else return findmin(root->left);
}
//function to print the student preorder to print them ordered
void trav(struct node *root){
    if(root!=NULL){
        trav(root->left);
        printf("%d  ",root->s.sid);
        printf("%s  ",root->s.name);
        printf("%s  ",root->s.class);
        printf("%s  ",root->s.date);
        printf("%s\n",root->s.address);
        trav(root->right);}
}
//function to delete a student by searching with the name and the ID since we build our tree depending on the name and ID
struct node* del(struct node *root,int x,char name[]){
    if (root ==NULL)return root;
    else if(strcmp(name,root->s.name)==1||(strcmp(name,root->s.name)==0&&x>root->s.sid))
        root->right=del(root->right,x,name);
    else if(strcmp(name,root->s.name)==-1||(strcmp(name,root->s.name)==0&&x<root->s.sid))
        root->left=del(root->left,x,name);
    else{
        //case no children
        if(root->right==NULL&&root->left==NULL){
            free(root);
            root=NULL;
        }
        //case one child
        else if(root->right==NULL){
            struct node *temp=root;
            root=root->left;
            free(temp);
            temp=NULL;
        }
        //also case one child
        else if(root->left==NULL){
            struct node *temp=root;
            root=root->right;
            free(temp);
            temp=NULL;
        }
        //case two children we find the min of right subtree
        else{
            struct node *temp=findmin(root->right);
            root->s=temp->s;
            root->right=del(root->right,temp->s.sid,temp->s.name);


        }
    }
    return root;

}
//function to print all the students from specific city
void students_City(struct node* root,char city[]){
    if(root!=NULL){
        students_City(root->left,city);
    if(strcmp(root->s.address,city)==0)
        printf("%d %s\n",root->s.sid,root->s.name);
        students_City(root->right,city);
}}
//function to print the student of each class ordered
void class_Student(struct node *root){
    //here we translate the class from integer to string ,so we can compare it with students class
    for(int i=0;i<12;i++)
        for(int j=0;j<4;j++)
            if(Classes[i][j]==1){
                if(i>=10){
                char c=(13-i)+48;
                char s=j+65;
                char class[4]={'1',c,s};
                    printf("%s\n",class);
                    printclass(root,class);}

                else {

                    char c=i+48;
                    char s=j+65;
                    char class[3]={c,s};

                printf("%s\n",class);
                printclass(root,class);}
                printf(".............\n");
            }

}
//in this function we compare the class we want to the class of each student
void printclass(struct node *root,char class[]){
    if(root!=NULL){
        printclass(root->left,class);
        if(strcmp(root->s.class,class)==0)
            printf("%d %s\n",root->s.sid,root->s.name);
        printclass(root->right,class);
    }
}
//here we delete a student with an ID by find his name first than sent them to the del function
struct node* delete_Student(struct node *root,int id){
    if(search(root,id)!=NULL){
    student s= search(root,id)->s;
    return del(root,id,s.name);}
    else
        printf("No student with this ID\n");
    return root;

}
//in this function we print the students from the tree to the file to save their information
void print_onFile(struct node *root){
    FILE *fout= fopen("students.data","w");
    printFile(root,fout);
    fclose(fout);


}
//print to the in inorder  traversal that causes that the student print not ordered if we print them ordered (preorder)
//when we reopen the program and construct the tree that will make it O(n) because it will keep inserting to the right
void printFile(struct node *root,FILE *f ){
    if(root!=NULL){
        fprintf(f,"%s\n%d\n%s\n%s\n%s\n",root->s.name,root->s.sid,
                root->s.class,root->s.date,root->s.address);
        fprintf(f,"******************************************************************************\n");
        printFile(root->left,f);
        printFile(root->right,f);

    }
}
//in this function we improve updating the information of a student if we found it by deleting the student first
struct node* update (struct node *root, student s){
    int se;
    root= delete_Student(root,s.sid);
    printf("Select the information you want to update\n ");
    printf("1-ID\n2-Name\n3-Class\n4-Date od admission\n5-City\n6-exit update\n");
    scanf("%d",&se);
    while (se!=6){
        switch (se) {
            case 1:
                printf("Enter the new ID of the  student\n");
                scanf("%d",&(s.sid));
                //handle if the ID already existed
                while (search(root,s.sid)!=NULL){
                    printf("ID already existed\n");
                    printf("Enter the new ID of the  student\n");
                    scanf("%d",&(s.sid));
                }
                break;
            case 2:
                while (getchar()!='\n');
                printf("Enter the new name of the  student\n");
                fgets(s.name,sizeof(s.name),stdin);
                s.name[strcspn(s.name, "\n")] = 0;
                break;
            case 3:
                printf("Enter the new Class of the  student\n");
                scanf("%s",s.class);
                break;
            case 4:
                printf("Enter the new date of enrollment of the  student\n");
                scanf("%s",s.date);
                break;
            case 5:
                printf("Enter the new home address of the  student\n");
                scanf("%s",s.address);
                break;
            default:
                printf("invalid selection\n");

        }
        printf("1-ID\n2-Name\n3-Class\n4-Date od admission\n5-City\n6-exit update\n");
        scanf("%d",&se);
    }
    root=insert(root,s);
    return root;
}
