/* Mohammad Fareed Zeedan     1212387         section:4
 * 28-5-2023
 * Project to check the validity of equations,convert it to prefix and evaluate it*/


#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>
//stack for character data
struct node {
    char data;
    struct node *next;
};
//stack for integer data
struct node1 {
    int data;
    struct node1 *next;
};
//Linked List for saving Equations and its properties
struct node2 {
    char Equation [100];
    char preFix[100];
    int vaild;
    struct node2 *next;
};
void push(char,struct node*);
char pop(struct node*);
void push1(int,struct node1*);
int pop1(struct node1*);
void insert_equation(struct node2 *head,char eq[]);
void printeq(struct node2 *head);
int check_bracket(char eq[]);
void Handle(char e[]);
void vaildity(struct node2 *head);
int great(char a);
void to_Prefix(struct node2 *h);
void prefix(struct node2 *head);
struct node2* read_from_file(struct node2 *head,char file_name[]);
int Evalute(char prefix[]);
void Evalute_Equations(struct node2 *head);
void print_Invaild_Equations(struct  node2 *head);
void print_Onfile(struct node2 *head);
int main()
{   //Flags to know when the equations had been read and checked and convert to prefix
    int r=-1,c=-1,p=-1,option;
    char name [35];
    struct node2 *head=NULL;
    //show the menu for the user
    printf("......................Welcome to the calculator app........................\n ");
    printf("Please select one option\n");
    printf("1-Read from File\n");
    printf("2-Check the validity of equations\n");
    printf("3-Convert valid equations from infix to prefix\n");
    printf("4-Evaluate the prefix expressions\n");
    printf("5- Print invalid equations\n");
    printf("6-Print all equations to ta file (output.txt)\n");
    printf("7-Exit\n");
    scanf("%d",&option);
    while (option!=7){
        //determine the option depending on the user
        switch (option) {
            case 1:
                printf("Enter the File name \n");
                scanf("%s",name);
                head=read_from_file(head,name);
                if(head!=NULL){
                printeq(head);
                    printf("..........................................................................\n");
                r=1;
                }
                break;
            case 2:
                if(r==1){
                    vaildity(head);
                    c=1;
                }
                else
                    printf("You need to open the File to read Equations\n");
                printf("..........................................................................\n");
                break;
            case 3:
                if(r!=1)
                    printf("You need to open the File to read Equations\n");

                else if(c!=1)
                    printf("You need to check the validity of Equations\n");
                else{
                    prefix(head);
                    p=1;
                }
                printf("..........................................................................\n");
                break;
            case 4:
                if(r!=1)
                    printf("You need to open the File to read Equations\n");
                else if(c!=1)
                    printf("You need to check the validity of Equations\n");
                else if(p!=1)
                    printf("You need to convert the Equation to prefix\n");
                else
                    Evalute_Equations(head);
                printf("..........................................................................\n");
                break;

            case 5:
                if(r!=1)
                    printf("You need to open the File to read Equations\n");
                else if(c!=1)
                    printf("You need to check the validity of Equations\n");
                else
                    print_Invaild_Equations(head);
                printf("..........................................................................\n");
                break;
            case 6:
                if(r!=1)
                    printf("You need to open the File to read Equations\n");
                else if(c!=1)
                    printf("You need to check the validity of Equations\n");
                else if(p!=1)
                    printf("You need to convert the Equation to prefix\n");
                else
                    print_Onfile(head);
                printf("..........................................................................\n");
                break;
            default:
                printf("Invalid option");
                printf("..........................................................................\n");
        }
        printf("Please select one option\n");
        printf("1-Read from File\n");
        printf("2-Check the validity of equations\n");
        printf("3-Convert valid equations from infix to prefix\n");
        printf("4-Evaluate the prefix expressions\n");
        printf("5- Print invalid equations\n");
        printf("6-Print all equations to ta file (output.txt)\n");
        printf("7-Exit\n");
        scanf("%d",&option);

    }
    return 0;
}
//function to push data into the character stack
void push(char x,struct node *Top){
    struct node *temp=(struct node*)malloc(sizeof(struct node));
    if(temp==NULL)
        printf("Out of space");
    else{
        temp->next=Top->next;
        Top->next=temp;
        Top=temp;
        temp->data=x;
    }

}
//function to push data into the integer stack
void push1(int x,struct node1 *Top){
    struct node1 *temp=(struct node1*)malloc(sizeof(struct node1));
    if(temp==NULL)
        printf("Out of space");
    else{
        temp->next=Top->next;
        Top->next=temp;
        Top=temp;
        temp->data=x;
    }

}
//function to delete the top of stack
char pop(struct node *top){

    if(top->next!=NULL){
        struct node *temp=top->next;
        top->next=top->next->next;

        char c=temp->data;
        free(temp);
        return c;}
}
//function to delete the top of stack
int pop1(struct node1 *top){

    if(top->next!=NULL){
        struct node1 *temp=top->next;
        top->next=top->next->next;

        int x=temp->data;
        free(temp);
        return x;}
}
//function to insert the equation into the linked list
void insert_equation(struct node2 *head,char eq[]){
    struct node2 *temp=(struct node2*)malloc(sizeof(struct node2));
    strcpy(temp->Equation,eq);
    temp->next=NULL;
    struct node2 *ptr=head;

    if(head->next==NULL){

        head->next=temp;
    }
    else{
        while(ptr->next!=NULL)
            ptr=ptr->next;
        ptr->next=temp;
    }}
//function tp print the equations
void printeq(struct node2 *head){
    struct node2 *ptr=head->next;
    while(ptr!=NULL){
        printf("%s",ptr->Equation);
        ptr=ptr->next;
    }
    printf("\n");
}
//function to check the validity of equations
int check_bracket(char x[]){
    //the principle of the function when open bracket is found ([ push it into stack and
    // when closed bracket is found pop the top element if it is not the open bracket then it is not valid
    //also it checked some cases like an operation in the end or in the beginning or double operation and other cases
    struct node *Top=(struct  node*)malloc(sizeof(struct node));
    Top->next=NULL;
    int size =strlen(x);
    int end=size-1;
    if (x[end]=='\n')
        end--;
    //checking the beginning of the equations
    if((x[0]=='*'||x[0]=='/'||x[0]=='^')){
        printf("Non vaild operation in the beginning\n");
        return -1;
    }
    //checking the end of equations
    else if(x[end]=='+'||x[end]=='*'||x[end]=='/'||x[end]=='-'||x[end]=='^'){
        printf("Non valid operation in the end\n");
        return -1;
    }
    //loop for checking the bracket
    for(int i=0;i<size;i++){
        //open bracket
        if(x[i]=='('||x[i]=='[')
            push(x[i],Top);
        //closing bracket
        else if(x[i]==')'){
            //searching for cases like this  )8
            if(x[i+1]>=48&&x[i+1]<=58){
                printf("invalid:there is no operator between	%c%c%c\n",x[i-1],x[i],x[i+1]);
                return -1;
            }
            char op=pop(Top);
            if(Top==NULL||op!='('){
                if(op=='[')
                    printf("invalid: [ Not closed \n");
                else
                    printf("invalid: ) not opened \n");
                return -1;}
        }
        else if(x[i]==']'){
            //searching for cases like this  ]8
            if(x[i+1]>=48&&x[i+1]<=58){
                printf("invalid:there is no operator between	%c%c%c\n",x[i-1],x[i],x[i+1]);
                return -1;
            }
            char op=pop(Top);
            if(Top==NULL||op!='['){
                if(op=='(')
                    printf("invalid:( Not closed \n");
                else
                    printf("invalid: ] not opened \n");
                return -1;}
        }
        // solving if character is operator
        else if(x[i]=='+'||x[i]=='-'||x[i]=='*'||x[i]=='/'||x[i]=='^'){
            //if there is + or - and the next is not  */ )] no problem

              if((x[i]=='-'||x[i]=='+')&&x[i+1]!='*'&&x[i+1]!='/'&&x[i+1]!='^'&&x[i+1]!=')'&&x[i+1]!=']'){
                 continue;
             }
                 //if there is * or / and the next is not + - no problem
           else if((x[i]=='*'||x[i]=='/'||x[i]=='^')&&(x[i+1]=='-'||x[i+1]=='+')){
                 continue;
           }
           // //if there is / or * or ^ and the next is  * ^ / invalid
           else if(x[i+1]=='*'||x[i+1]=='/'||x[i+1]=='^'){
            printf("invalid:%c%c double operation\n",x[i],x[i+1]);
            return -1;}
           //checking for case like this [* (/
             else if((x[i-1]=='['||x[i-1]=='(')){
                 printf("invalid:%c%c NO number with operation\n",x[i-1],x[i]);
                 return -1;}
             //checking case like *) -)
             else if((x[i+1]==']'||x[i+1]==')')){
                 printf("invalid:%c%c NO number with operation\n",x[i],x[i+1]);
                 return -1;}
        }
            //searching for cases like this 8( or 8[
        else if(x[i]>='0'&&x[i]<='9'){
            if(x[i+1]=='('||x[i+1]=='['){
                printf("invalid:there is no operator between	%c%c%c\n",x[i],x[i+1],x[i+2]);
                return -1;
            }}


    }
    //checking if the stack is empty
    if(Top->next!=NULL){
        printf("%c Not closed\n ",pop(Top));
        return -1;}
    else printf("vaild\n");
    return 1;
}
//function to check validity of all equations
void vaildity(struct node2 *head){
    struct node2 *ptr=head->next;
    int count=1;
    char b='a';
    while(ptr!=NULL){
        printf("%c. Equation No.%d---->      ",b,count);
        ptr->vaild=check_bracket(ptr->Equation);
        ptr=ptr->next;
        b++;
        count++;
    }

}
//function to handle the signs - + by deciding if it is sign or operator
void Handle(char e[]){
   int start=0;
    char n[100];
    int index=0;
    //checking the first character in the equation if it is - or + than its is sign
    if(e[0]=='-'){
        n[0]='-';
        index++;
        start=1;

    }
    else if(e[0]=='+'){
       start=1;
    }
    //s for determine the sign after sequence of ------
    int s=-1;
    //start looking for - and + if - +is found than check the previous if it is no operator than this - is operator
    //but if there was operator than this is a sign so skip until the last sign
    //for example 6----6 is 6- the there --- become one - 6 - -6 and 6++++6 become 6 + 6
    for(int i=start;i< strlen(e);i++) {
        if(e[i]=='-'&&(e[i-1]>='0'&&e[i-1]<=58||e[i-1]==')'||e[i-1]==']')){
            n[index] = ' ';
            n[index+1] = '-';
            n[index + 2] = ' ';
            index+=3;
        }
       else if(e[i]=='-'&&e[i+1]=='-')
            s*=-1;
        else if(e[i]=='-'&&e[i+1]!='-'){
            if(s==-1){
                n[index]='-';
                index += 1;
            }
            else s=-1;
        }
        else if(e[i]=='+'){
            if((e[i-1]>='0'&&e[i-1]<=58)||(e[i-1]==')'||e[i-1]==']')){
            n[index] = ' ';
            n[index+1] = '+';
            n[index + 2] = ' ';
            index+=3;}
            else
                continue;
        }
        else if (e[i] == '^' || e[i] == '*'  || e[i] == '/') {
            n[index ] = ' ';
            n[index+1] = e[i];
            n[index + 2] = ' ';
            index += 3;
        }

        else {
            n[index] = e[i];
            index++;
        }
    }
    //end the array
    n[index]='\000';
    strcpy(e,n);
}
//function to read from the file
struct node2* read_from_file(struct node2 *head,char File_name[]){
    head=(struct node2*)malloc(sizeof(struct node2));
    head->next=NULL;
    FILE *fin=fopen(File_name,"r");
    char sent[100];
    if(fin){
        //here we read the equation using fgets
    while (fgets(sent,100,fin)){
        insert_equation(head,sent);
    }
    fclose(fin);
    return head;
    }
    else
        printf("There is no File with this name\n");
    return NULL;
}
// function to determine the precedence of operators
int great(char a){
    switch(a){
        case '^':
            return 3;
        case '*':
        case'/':
            return 2;
        case '+':
        case'-':
            return 1;
        default: return 0;
    }
}
//function to convert to prefix
void to_Prefix(struct node2 *ptr){
    //we will need to start from the end of the equation
    //the principle of this function if the character is [( push it or if it ]) keep pop and put in array until find the open bracket
    //if it is operator keep pop()and put in array until find operator greater than it
    //if it is number put in the array
    struct node *Top=(struct  node*)malloc(sizeof(struct node));
    Top->next=NULL;
    char next;
    int index=0;
    char c;
    //array temp to have the equation after handel
    char temp[100];
    strcpy(temp,ptr->Equation);
    Handle(temp);
    //prefix array that will have yhe answer
    char prefix[100];
    int size=strlen(temp)-1;
    if(temp[size]=='\n')
        size--;
    for(int i=size;i>=0;i--){
        c=temp [i];
        switch(c){
            // case open bracket but because we read from the reverse
            case ')':
            case ']':
                push(c,Top);
                break;
             //case closing bracket
            case '(':
                while((next=pop(Top))!=')'){
                    prefix[index]=' ';
                    prefix[index+1]=next;
                    index+=2;}
                break;
            case '[':
                while((next=pop(Top))!=']'){
                   prefix[index]=' ';
                    prefix[index+1]=next;
                    index+=2;
                }
                break;
            //case operations
            case '*':
            case '/':
            case '+':
            case '-':
            case '^':
                //check if - is sign first if it is sign just put it in the array
                if(c=='-'&&temp[i+1]!=' '){
                    prefix[index]='-';
                    index++;
                    continue;
                }
                while(Top->next!=NULL&&great(Top->next->data)>great(c)){
                    prefix[index]=pop(Top);
                    index+=1;
                }
                push(c,Top);
                break;
            //case numbers or spaces
            default:
                prefix[index]=c;
                index++;
        }}
    //put what is left from the stack in the array
    while(Top->next!=NULL){
        prefix[index]=' ';
        prefix[index+1]=pop(Top);
        index+=2;
    }
    strncpy(ptr->preFix,prefix,index);
    //end the array manual way
    ptr->preFix[index]='\000';
}
//function tp prefix all the valid equations in the linked list
void prefix(struct node2 *head){
    struct node2 *ptr=head->next;
    while(ptr!=NULL){
        if(ptr->vaild==1){
            to_Prefix(ptr);
            strrev(ptr->preFix);
            printf("%s",(ptr->preFix));
            printf("\n");

        }
        ptr=ptr->next;
    }
}
//function to evaluate the prefix
int Evalute(char prefix[]){
    //first we need to reverse it
    strrev(prefix);
    //the main principle is when you read number push it into the stack
    //if you read operator pop two numbers and make the operation and push the result
    struct  node1 *Top= (struct node1*)malloc(sizeof (struct node1));
    Top->next=NULL;
    int num=0,count=0;
    for(int i=0;i< strlen(prefix);i++){
        int number1,number2;
        int res;
        char c=prefix[i];
        if(c=='/'){
            number1= pop1(Top);
            number2= pop1(Top);
            if (number2==0){
                printf("Error -1:the divisor cannot be zero \n");
                return -1;
            }
        res=number1/number2;
            push1(res,Top);
        }
        else if(c=='^'){
            number1= pop1(Top);
            number2= pop1(Top);
            res= pow(number1,number2);
            push1(res,Top);
        }
        else if(c=='+'){
            number1= pop1(Top);
            number2= pop1(Top);
            res=number2+number1;
            push1(res,Top);
        }
        else if(c=='-'){
            //here is special case because - can be sign or operator
            //if it was sign we have two case if thw number is on the stack then pop it change the sign and push it
            //second case if the number is not in the stack yet but is saved in variable number so change the sign and push it
            if(prefix[i-1]!=' '){
                int n;
                if(count!=0){
                 n= num*-1;
                num=0;
                count=0;}
                else {
                    n= pop1(Top)*-1;
                }
                push1(n,Top);
            }
            else {
                number1= pop1(Top);
                 number2= pop1(Top);
                res=number1-number2;
                push1(res,Top);}
        }
        else if(c=='*'){
            number1= pop1(Top);
            number2= pop1(Top);
            res=number1*number2;
            push1(res,Top);
        }
        //case number because we read in reverse way we read number in opposite way  like 14 we rad it 41
        //to solve this count from 0 each time the digit is multiply by 10 for count time than increase count
        //take 14  read 4 first multiply by 10 zero time and put it in num, num become 4 and count become 1
        //than read 1 multiply it by 10 one time become 10 add it to num become 14 and count become 2
        else if(c>=48&&c<=58){
            int digit=c-48;
            for(int y=0;y<count;y++)
                digit*=10;
            num+=digit;
            count++;
        }
        //case space to know that the number is finish ,so we can push it now and reset count
        else if(c==' '){
            if(count!=0){
                count=0;
                push1(num,Top);
                num=0;
            }
        }}
    //reverse back the prefix
    strrev(prefix);
    int result=pop1(Top);
    return result;

}
//function to evaluate the prefix ao all valid equations in the linked list
void Evalute_Equations(struct node2 *head){
    struct node2 *ptr=head->next;
    int res,count=1;
    char b ='a';
    while ((ptr!=NULL)){
        if (ptr->vaild==1){
            res= Evalute(ptr->preFix);
            printf("%c. Equation No.%d   --> %d\n",b,count,res);
            b++;
        }
        count++;
        ptr=ptr->next;
    }
}
//function to print all the invalid equations in the linked list
void print_Invaild_Equations(struct  node2 *head){
    struct  node2 *ptr=head->next;
    while (ptr!=NULL){
        if(ptr->vaild==-1)

            printf("%s",ptr->Equation);
        ptr=ptr->next;
    }
    printf("\n");
}
//function to print the information of all equations in the linked list on the output file
void print_Onfile(struct node2 *head){
    FILE *fout= fopen("output.txt","a");
    struct node2 *ptr=head->next;
    while (ptr!=NULL){
        fprintf(fout,"Equation:");
        for(int i=0;i< strlen(ptr->Equation)-1;i++){
            fprintf(fout,"%c",ptr->Equation[i]);
        }
        if(ptr->vaild==1){
            fprintf(fout,"\t\t\tValidity:Yes\t\tPrefix:");
            fprintf(fout,"%s", (ptr->preFix));
            fprintf(fout,"\t\tResult: %d\n", Evalute(ptr->preFix));}
        else
            fprintf(fout,"\t\t\tValidity:No\n");
        fprintf(fout,"......................................................................................................................\n");
        ptr=ptr->next;
    }

    fclose(fout);
}