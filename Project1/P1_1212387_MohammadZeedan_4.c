#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>

/** Mohammad Fareed             19-5-2023

    This code for do math operations on large integers by store them in linked list
    and define  methods for the operations                                       **/







/** here we define a struct to save the digits of the number **/
struct node{
    int s;
    int data;
    struct node *next;
    struct node *prev;
};
/** here we define a new struct to save each number after we enter it's digits in the first struct **/
struct node2{

    struct node *number;
    struct node2 *next;
};
int isEmpty(struct node *L);
int isLast(struct node *L,struct node *p);
struct node* Find(struct node *L,int);
struct node* Find_number(struct node2 *L,int);
struct node* Findprev(struct node *L,int x);
void reverse(struct node *p);
void Delete(struct node *L,int);
struct node* Last_node(struct node *p);
void Insert(struct node *L,int x);
void Insert_last(struct node *L,int x);
void DeleteList(struct node *L);
int num_of_digit(struct node *p);
struct node* MakeEmpty(struct node *L);
void insert_number(struct node2 *L,struct node *n);
int compare(struct node *p1,struct node *p2);
void Del_zero(struct node *p);
struct node2* Read_From_File( struct node2 *h);
struct node* ADD(struct node *n1,struct node *n2);
struct node* SUB(struct node *n1,struct node *n2);
struct node* MUL(struct node *n1,struct node *n2);
struct node* DIV(struct node *n1,struct node *n2,struct node **reminder);
void printnum(struct node *n);
void print(struct node2 *L);
void Print_On_File(struct node *H);
int main()
{   /** Make the menu for the user **/
   printf("..........Welcome to the calculator app........\n");
    printf("Please select option\n");
    printf("1-Read the numbers from the file\n2-Exit\n");
    int s;
    scanf("%d",&s);
     struct node2 *head=NULL;
    if(s==1){
            head=Read_From_File(head);
    while(s!=5){
   print(head);
    printf("Now select operation\n");
    printf("1-Add\n2-Subtract\n3-Multiplay\n4-Divide\n5-exit\n\n");
    scanf("%d",&s);
    /** Check if the operation is valid **/
    while(s>5||s<1){
            printf("invalid operation\n");
            printf("1-Add\n2-Subtract\n3-Multiplay\n4-Divide\n5-exit\n\n");
            scanf("%d",&s);}
    if(s==5)
        break;
    printf("Now select two numbers\n");
    int n1,n2;
    scanf("%d%d",&n1,&n2);
    struct node *res;
    struct node *num1=Find_number(head,n1);
    struct node *num2=Find_number(head,n2);
    struct node *reminder=NULL;
    /** Do the operation he asked **/
    switch(s){
        case 1:res=ADD(num1,num2);
               break;

        case 2:res=SUB(num1,num2);
               break;
        case 3:res=MUL(num1,num2);
               break;
        case 4: res=DIV(num1,num2,&reminder);
                if(reminder!=NULL){
                     printf("Reminder=");
                    printnum(reminder);}
               break;
    }
    /** Print the result and the reminder to the screen  and the file **/
    if(res!=NULL){
            printf("Result=");
            printnum(res);
            Print_On_File(res);
            if(s==4)
               Print_On_File(reminder);
            printf("\n\n");
    }
          }}

    return 0;
}

int isEmpty(struct node *L){

    if(L->next==NULL)return 1;
    return 0;
}
int isLast(struct node *L,struct node *p){

return p->next==NULL;
}
/** Find specific node **/
struct node* Find(struct node *L,int x){

    struct node *ptr=L->next;
    while(ptr!=NULL&&ptr->data!=x){
        ptr=ptr->next;
    }

    return ptr;
};

struct node* Find_number(struct node2 *L,int count){
    struct node2 *ptr=L->next;
    while(count!=1){
        ptr=ptr->next;
        count--;
    }
    return ptr->number;



};
struct node* Findprev(struct node *L,int x){

    struct node *ptr=L->next;
    while(ptr->next!=NULL&&ptr->next->data!=NULL){
        ptr=ptr->next;
    }
return ptr;
};
/** this node reverse the linked list **/
void reverse(struct node *p){
     struct node *n=p->next;
    struct node *ptr1=n->next;
    struct node *ptr2=ptr1;
    n->next=NULL;
    n->prev=ptr1;
while(ptr1!=NULL){
    ptr2=ptr2->next;
    ptr1->next=n;
    ptr1->prev=ptr2;
    n=ptr1;
    ptr1=ptr2;
}
n->prev=p;
p->next=n;
}
/** this method delete a node with specific data **/
void Delete(struct node *L,int x){
    struct node *ptr=Find(L,x);
    if(ptr!=NULL){
    ptr->prev->next=ptr->next;
    if(!isLast(L,ptr))
        ptr->next->prev=ptr->prev;
        free(ptr);}
};
/** this method return the last node of the linked list **/
struct node* Last_node(struct node *p){

struct node*ptr=p;
while(ptr->next!=NULL)
    ptr=ptr->next;
return ptr;
};
/** this method insert a new node in the beginning of the linked list **/
void Insert(struct node *L,int x){
    struct node *temp=(struct node*)malloc(sizeof(struct node));
    temp->data=x;
    temp->next=L->next;
    temp->prev=L;
    if(!isEmpty(L))
        L->next->prev=temp;
    L->next=temp;
    Del_zero(L);
}
/** this method insert a new node in the end of the linked list **/
void Insert_last(struct node *L,int x){
    struct node *temp=(struct node*)malloc(sizeof(struct node));
    struct node *LastN=Last_node(L);
    temp->data=x;
    temp->next=NULL;
    temp->prev=LastN;
    LastN->next=temp;
}
/** this method delete the whole linked list **/
void DeleteList(struct node *L){

    struct node *ptr=L->next;
    struct node *temp;
    while(ptr!=NULL){
        temp=ptr->next;
        free(ptr);
        ptr=temp;
    }

}
/** this method return the number of digits of a number **/
int num_of_digit(struct node *p){
struct node *ptr1=Last_node(p);
int c=0;
while(ptr1!=NULL){
    c++;
    ptr1=ptr1->prev;
}
return c;
}
/**this method is used to empty the linked list **/
struct node* MakeEmpty(struct node *L){

    L=(struct node*)malloc(sizeof(struct node));
    if(L==NULL)
        printf("Out of memory");
    L->next=NULL;
    L->prev=NULL;
    L->s=1;
    return L;
};
/**this method is used for entering the whole number (double linked list) int the single linked list **/
void insert_number(struct node2 *L,struct node *p){
    struct node *num=p;
     struct node2 *ptr=L;
    while(ptr->next!=NULL)
        ptr=ptr->next;
    struct node2 *temp=(struct node2*)malloc(sizeof(struct node2));
    temp->number=num;
    temp->next=NULL;
    ptr->next=temp;
}
/**this method is for comparing between two numbers **/
int compare(struct node *p1,struct node *p2){
    /**first we compare the number of digits of the two numbers **/
    if(num_of_digit(p1)>num_of_digit(p2))
        return 1;
    else if(num_of_digit(p1)<num_of_digit(p2))
        return -1;
    /**because the number of digits are equal we start to compare the most significant digits **/
    struct node *n1=Last_node(p1);
    struct node *n2=Last_node(p2);
    while (n1!=p1||n2!=p2){
        if(n1->data>n2->data)
            return 1;
        else if(n1->data<n2->data)
            return -1;
         else{
            n1=n1->prev;
            n2=n2->prev;
         }

    }

return 0;
}
/**this method deletes the zero from the beginning of the number 00123 become 123 **/
void Del_zero(struct node *p){

reverse(p);
struct node *temp=p->next;
while(temp->data==0&&temp->next!=NULL){
    temp=temp->next;
    Delete(p,0);
}
reverse(p);


};
/**this method for reading numbers from file**/
struct node2* Read_From_File(struct node2 *head2){
     struct node *head=NULL;
    head2=(struct node2*)malloc(sizeof(struct node2));
   head2->next=NULL;
   head=MakeEmpty(head);
/**here we open the file and start reading and store it in variable x if x was a number just insert it,
if it was a sign then change the flag sign and if it was any thing else end the number and save it **/
FILE *fin=fopen("Numbers.txt","r");
   char x;
  int e= fscanf(fin,"%c",&x);
   while(e!=EOF){
    /** here we change the car to int by subtracting 48 **/
    if(x>=48&&x<=57){
    Insert(head,x-48);
                }
    /** declare the sign**/
    else if(x=='-')head->s=-1;
    else if(x=='+')head->s=1;
    else{
        /**here we enter the number into numbers linked list**/
        insert_number(head2,head);
        head=MakeEmpty(head);}
        e= fscanf(fin,"%c",&x);}

     insert_number(head2,head);
    fclose(fin);
    return head2;

};
/** This method for Adding two numbers **/
struct node* ADD(struct node *p1,struct node *p2){
    struct node *n1;
    struct node *n2;
    struct node *ans=NULL;
    int c=0;
    ans=MakeEmpty(ans);

    n1=p1;
    n2=p2;
/**This is the first case when the two numbers are both positive or both negative so we can add them **/
if((n1->s==1&&n2->s==1)||(n1->s==-1&&n2->s==-1)){
        n1=p1->next;
        n2=p2->next;
/** The working rule of this method by adding the first digit with the first digit with the carry
    if sum was greater than 9 the carry change to 1 else the carry remains 0 **/
while (n1!=NULL||n2!=NULL){
    int dg1;
    int dg2;
    /** Here we check if any number us NULL it's digit be 0 **/
   if(n1==NULL){
        dg1=0;
        dg2=(n2->data);
    }
    else if(n2==NULL){
        dg2=0;
        dg1=(n1->data);
    }
    else {
        dg1=(n1->data);
        dg2=(n2->data);
    }
    /** Move to the next digit **/
    if(n1!=NULL)n1=n1->next;
    if(n2!=NULL)n2=n2->next;
    /** Determine the sum **/
    int y=dg1+dg2+c;
    /** Change the carry **/
    if(y<=9)c=0;
    else{
        c=1;
        y=y-10;
    }
    /** Insert the sum to the answer linked list**/
    Insert_last(ans,y);
}
    /** Checking if there is carry to insert **/
    if(c==1)
        Insert_last(ans,c);}
/** Here is the second case when one of the two numbers is negative so we call  the Subtraction method **/
else{
   /** Here I changed the sign for the negative number temporary 5+-5 =5-5 not 5--5 **/
   int s=1;
    if(n1->s==-1){
            s=-1;
            n1->s=1;}
    else n2->s=1;
    ans =SUB(n1,n2);
    /** Return the original sign for the numbers **/
    if(s==-1)n1->s=-1;
    else n2->s=-1;
}
/** Here I declare the answer sign by checking the sign of the two numbers**/
 if(compare(p1,p2)==1&&p1->s==-1)
    ans->s=-1;
else  if(compare(p2,p1)==1&&p2->s==-1)
    ans->s=-1;
else if(p1->s==-1&&p2->s==-1)
    ans->s=-1;
return ans;
};
/** This method for subtracting two numbers **/
struct node* SUB(struct node *p1,struct node *p2){
    int comp=compare(p1,p2);
    struct node *n1;
    struct node *n2;
    struct node *ans=NULL;
    int c=0;
    int sign=1;
    ans=MakeEmpty(ans);
    /** Determine the larger number to subtract in correct way **/
    if(comp==-1){
            n1=p2->next;
            n2=p1->next;
    }
    else {
        n1=p1->next;
        n2=p2->next;
    }

/** Here I declare the answer sign by checking the sign of the two numbers**/
if((n1==p1->next&&n1->prev->s==-1)||(n1==p2->next&&n1->prev->s==1)){
        sign=-1;}
/**This is the first case when the two numbers are both positive or both negative so we can subtract them **/
if((p1->s==1&&p2->s==1)||(p1->s==-1&&p2->s==-1)){
    /** The working rule of this method by subtracting  the first digit with the first digit with the carry
    if sub was less than 0 the carry change to -1 and we add 10 to the sub else the carry remains 0 **/
    while (n1!=NULL||n2!=NULL){
    int dg1;
    int dg2;
if(n1==NULL){
        dg1=0;
        dg2=(n2->data);
    }
    else if(n2==NULL){
        dg2=0;
        dg1=(n1->data);
    }
    else {
        dg1=(n1->data);
        dg2=(n2->data);
    }
     /** Move to the next digit **/
    if(n1!=NULL)n1=n1->next;
    if(n2!=NULL)n2=n2->next;
     /** Determine the sub **/
    int y=dg1-dg2+c;
     /** Change the carry **/
    if(y>=0)
        c=0;
    else{
        c=-1;
        y=y+10;
    }
    /** Insert the sub to the answer linked list**/
     Insert_last(ans,y);
}}
/** Here is the second case when one of the two numbers is negative so we call  the ADD method **/
else{
     /** Here I changed the sign for the negative number temporary 5--5 =5+5 not 5+-5 **/
     int s=1;
    if(n1->prev->s==-1){
            s=-1;
            n1->prev->s=1;}
    else
            n2->prev->s=1;
    ans =ADD(n1->prev,n2->prev);
    /** Return the original sign for the numbers **/
    if(s==-1){
            n1->prev->s=-1;}
    else
            n2->prev->s=-1;
}
/**Here we delete the zero from the beginning of the ans 999-999=0 instead of 000 **/
Del_zero(ans);

ans->s=sign;
return ans;

};
/**This method for multiply two numbers **/
struct node* MUL(struct node *p1,struct node *p2){
    int count=0;
 int comp=compare(p1,p2);
    struct node *n1;
    struct node *n2;
    struct node *ans=NULL;
    ans=MakeEmpty(ans);
    /**Give the ans initial value 0 to use it in the first time **/
    Insert_last(ans,0);
    if(comp==-1){
            n1=p2->next;
            n2=p1->next;
    }
    else {
        n1=p1->next;
        n2=p2->next;
    }
    struct node *p=NULL;
   int m,r=0;
    struct node *ptr;
    /** the principle work of this method to take each digit off the second number and multiply it with all digits
        of the first number  **/
    while(n2!=NULL){
        ptr=n1;
     p= MakeEmpty(p);
    /** This loop for adding zeroes to the  number each level **/
    for(int i=0;i<count;i++)
        Insert_last(p,0);
    /** The multiplication loop **/
    while(ptr!=NULL){
      m=ptr->data*n2->data;
    /** Determine the multiply answer and the reminder (as carry) **/
      Insert_last(p,((m%10)+r));
      r=m/10;
      ptr=ptr->next;
    }
    /** Make sure of last Carry not zero to insert it **/
    if(r!=0)
        Insert_last(p,r);
    r=0;
    /** Update the answer each level **/
    ans=ADD(p,ans);
    /** free the answer of each level to store the ans of the next level **/
    DeleteList(p);
    /** Move to the next digit **/
    n2=n2->next;
    /** The counter is used in adding zeros first time one zero than two zero **/
    count++;
    }
/** Declare the answer sign be checking if one number only is negative **/
if((p1->s==1&&p2->s==1)||(p1->s==-1&&p2->s==-1))ans->s=1;
else ans->s=-1;
/** Delete the zeros from the beginning of the answer  235*0=0 instead of 000 **/
Del_zero(ans);
return ans;
};
/** This method for divide two numbers **/
struct node* DIV(struct node *p1,struct node *p2, struct node **reminder){
    int s=1;
    struct node *n1;
    struct node *n2=MakeEmpty(n2);
    Insert(n2,0);
        /** Check if divisor is 0 **/
        if(compare(p2,n2)==0){
            printf("Can not make the division  \n");
            return NULL;}
     n1=p2;
    n2=Last_node(p1);
    /** change the divisor sign to positive to it in correct way in the sub method **/
    if(n1->s==-1){
        s=-1;
        n1->s=1;}
    struct node *res=NULL;
    res=MakeEmpty(res);
    *reminder=MakeEmpty(*reminder);
    *reminder=p1;
    struct node *ptr=NULL;
    ptr=MakeEmpty(ptr);
    int count ;
 struct node *temp=NULL;
 temp=MakeEmpty(temp);
 /** The main principle by finding the first number that can divide 990/90 the first is 99
    then find the reminder and subtract it than insert the next digit **/
while(n2!=p1){

        count =1;
    Insert(ptr,n2->data);
    /** Checking if the divisor is great than the dividend so enter 0 to the quotient **/
    if(compare(n1,ptr)==1){
        Insert(res,0);
        Insert(temp,0);
        *reminder=ptr;
    }
    /** the divisor is less or equal to the dividend so find the quotient and reminder
    70/2 take the 7 divide it by 2 the quotient =3 and the reminder 1 **/
    else{
    /** using the sun method to find the quotient and the reminder **/
    struct node *t=SUB(ptr,n1);
    *reminder=t;
while(compare(t,n1)!=-1){
            count++;
            t=SUB(t,n1);
            *reminder=t;

        }
        /** used count to save the quotient and insert it in the result linked list **/
        Insert(temp,count);
        Insert(res,count);
        /** Find reminder and save  it in the reminder variable **/
        t=MUL(temp,n1);
        ptr=SUB(ptr,t);
    }
    /** Move to the next digit **/
    n2=n2->prev;
    /** Use temp to save the quotient to use it in the multiply **/
    temp=temp->next;
    temp->s=1;
}
/** Delete the zero from the result 990/10=99 instead of 0099 **/
Del_zero(res);
/** Return the original sign for the divisor **/
n1->s=s;
/** Declare the answer sign be checking if one number is negative **/
if((p1->s==1&&p2->s==1)||(p1->s==-1&&p2->s==-1)){
        res->s=1;}
else {
    res->s=-1;}
return res;
};
/** method for print the digit of the number **/
void printnum(struct node *h){
    /** check the sign of the number be checking the flag **/
    struct node *ptr=Last_node(h);
     if(h->s==-1){
            printf("%d",-1*ptr->data);
            ptr=ptr->prev;
     }

    while(ptr!=h){
        printf("%d",ptr->data);
        ptr=ptr->prev;
    }
    printf("\n");

}
/** Print all the numbers on the screen **/
void print(struct node2 *L){
    int count =1;
    struct node2 *ptr=L->next;
    while(ptr!=NULL){
        printf("%d- ",count);
        printnum(ptr->number);
        ptr=ptr->next;
        count++;
    }
}
/** Print the result on the file  **/
void Print_On_File(struct node *head){

FILE *fout=fopen("Result.txt","a");
     struct node *ptr=Last_node(head);
     if(head->s==-1){
            fprintf(fout,"%d",-1*ptr->data);
            ptr=ptr->prev;
     }
    while(ptr!=head){
        fprintf(fout,"%d",ptr->data);
        ptr=ptr->prev;
    }
    fprintf(fout,"\n");
    fclose(fout);
}
