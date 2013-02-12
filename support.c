#include"support.h"
//helper functions implementation
//@author Keqiu Hu
//
list *head;
list *arghead;
//function to reverse the order of a linked list
void revOrder(char *strp[],int num){
    num--;
    int i=0;
    for(i=0;i<num/2;i++){
        char *temp=strp[i];
        strp[i]=strp[num-i];
        strp[num-i]=temp;
    }
    
}
//function to take a part of a string
char** shortArray(char *str[],int len){
    char** sarray=(char**)malloc((len+1)*sizeof(char*));
    int i=0;
    for(;i<len;i++){
        sarray[i]=str[i];
    }
    sarray[i]=(char*)0;
    return sarray;
}
//function to walk through a linked list and print values
void printNode(){
    list* it=head;
    while(it!=NULL){
        
        printf("%s:",it->path);
        it=it->next;
    }
    printf("\n");
}

//print function for arguments list
void printNode2(){
    list* it=arghead;
    while(it!=NULL){
        
        printf("%s:",it->path);
        it=it->next;
    }
    printf("\n");
}

//reserved function
char **dividepipe(char *str[]){
    
}

//function to add node to the path list
void addNode(char*str){

    list* next=(list*)malloc(sizeof(list));
    strncpy(next->path, str,100);
    next->next=NULL;
    if(head==NULL){
        head=next;
        return;
    }
    list* it=head;

    while(it->next!=NULL){
        it=it->next;
        // printf("Deadhere\n");
    }
    it->next=next;
    
}

//function to add node to the argument list
void addNode2(char*str,char ** arg){

    list* next=(list*)malloc(sizeof(list));
    strncpy(next->path, str,100);
    next->arguments=arg;
    next->next=NULL;
    if(arghead==NULL){
        arghead=next;
        return;
    }
    list* it=arghead;

    while(it->next!=NULL){
        it=it->next;
        //printf("Deadhere\n");
    }
    it->next=next;
    
}

//function to delete node from path list
void delNode(char *str){
   //: printf("test");
    list* it=head;
    if(head==NULL) {
          fprintf(stderr, "error: path %s not found\n", str);
//        printf("No node!");return;
          return;        

    }
    if(strcmp(head->path,str)==0)
    {
      
        head=head->next;
        free(it);
    }

    else
    {
        while(it->next!=NULL && strcmp(it->next->path,str)!=0 ){
            it=it->next;
            
        }

        if(it->next==NULL||strcmp(it->next->path,str)!=0)
        {
             fprintf(stderr, "error: path %s not found\n", str);

            
//             printf("Path Not Found!\n");
        }
       /* if(it==NULL)
            printf("Path Not Found!\n");*/
        else
        {
            it->next=it->next->next;
            free(it->next);
        }
    
    }

}

//function to delete node from argument list
void delNode2(char *str,char ** arg){
    list* it=head;
    if(head==NULL) {printf("No node!");return;}
    if(strcmp(head->path,str)==0)
    {
        head=head->next;
        free(it);
    }

    else
    {
        while(strcmp(it->next->path,str)!=0 && it!=NULL){
            it=it->next;
            
        }
        if(it==NULL)
            printf("Path Not Found!\n");
        else
        {
            it->next=it->next->next;
            free(it->next);
        }
    
    }

}

//function to take a substring out from the previous string
char* substring(char* str,int a,int b){
    char* ret=(char*)malloc((b-a+2)*sizeof(char));
    int j=0;
    int i=0;
    for(i=a;i<=b;i++){
        ret[j]=str[i];
        j++;
    }
    ret[j]='\0';
    return ret;

}

//function to count the number of spaces in the commands
int countSpace(char * str){
    int i=0;
    int j=0;
    for(;str[i]!='\0';i++){
        if(str[i]==' ' && str[i-1]!=' ' && str[i+1]!='\n')          
        {
            j++;
        }
    }
    return j;

}

//to modify endofline to endoffile
void returnMod(char* str){
    while(1){
        if(*str=='\n'){
            *str='\0';
            return;
        }
        str++;

    }
}
