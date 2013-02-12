
/*Support.h 
 * headfile for the support functions.
 *@Author Keqiu Hu
 */
#include <stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include <fcntl.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
typedef struct node{
    char path[100];
    char** arguments;
    struct node *next;
}list;

extern list *head;
extern list *arghead;

char **shortArray(char *str[],int);
char **dividePipe(char **);//divide into several pipes
void printNode();
void addNode(char* str);
void delNode(char* str);
void addNode2(char* str,char **);
void delNode2(char* str,char **);
void printNode2();
int countSpace(char * str);
char *substring(char* ,int,int);
void returnMod(char* str);
void revOrder(char *strp[],int);
