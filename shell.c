/*MYSHELL
 * @author Keqiu Hu
 */
#include"support.h"
//function declaration part
int myexecu(list*);
void recurPipe(char *argv[],int);
char* rmspace(char *);
//main function
int main()
{
    char * welcome[17];
        printf("                Happy Chinese Lunar New Year!                                            \n");
    welcome[0]="                    /^\\/^\\       Version 1.1     ";
    welcome[1]="                  _|__|  O|      Author Keqiu Hu";
    welcome[2]="         \\/     /~     \\_/ \\     UNI: kh2567";
    welcome[3]="          \\____|__________/  \\   Date: 2/8/2013";    
    welcome[4]="                 \\_______      \\";
    welcome[5]="                         `\\     \\                 \\";
    welcome[6]="                           |     |                  \\";

    welcome[7]="                          /      /                    \\";
    welcome[8]="                         /     /                      \\\\";
    welcome[9]="                       /      /                         \\ \\";

    welcome[10]="                      /     /                            \\  \\";

    welcome[11]="                    /     /             _----_            \\   \\";
    welcome[12]="                   /     /           _-~      ~-_         |   |";
    welcome[13]="                  (      (        _-~    _--_    ~-_     _/   |";
    welcome[14]="                   \\      ~-____-~    _-~    ~-_    ~-_-~    /";
    welcome[15]="                     ~-_           _-~          ~-_       _-~   ";
    welcome[16]="                        ~--______-~                ~-___-~";

    int picture;
    for(picture=0;picture<17;picture++){
        printf("%s",welcome[picture]);
        printf("\n");
    };
    printf("\n");
    int status;
    pid_t pid2; 
    char command[100];
    head=NULL;
    char *bspace=" ";
    printf("myshell$");
    //preloaded path
    addNode("/bin/");
    addNode("/usr/bin/");
    while(1){
        arghead=NULL;
        fflush(stdin); 
        char* cmdBegin;
        char cmd2[4096];
        fgets(cmd2,4096,stdin);
        
        //
        char* cmd=rmspace(cmd2);
        int argc=countSpace(cmd)+1;
        char *argv[argc];

        int space;
        space=strcspn(cmd,bspace);
        //readin all the arguments
        char* arg = strtok(cmd, bspace);
        int count=0;
        while (arg){
            argv[count]=arg;
            arg = strtok(NULL, bspace);
              count++;
       }
        count=argc;
        returnMod(argv[count-1]);
        argv[count]=(char*)0;
        if(strcmp(argv[0],"exit")==0){
            printf("Closing...\n");
            exit(-1); }
       if(strcmp(argv[0],"path")==0){
                if(count==1)
                    printNode();
                else if(strcmp(argv[1],"+")==0){
                    addNode(argv[2]);
                }
                else if(strcmp(argv[1],"-")==0){ 
                    delNode(argv[2]);

                }
                 printf("myshell$");

                continue;


        }


          //self parsed functions
        
        if(strcmp(argv[0],"cd")==0){

            if(chdir(argv[1])<0){
                fprintf(stderr, "error: %s\n", strerror(errno));
            };
            printf("myshell$");

            continue;
        }
        
        
        if((pid2=fork())<0){
             fprintf(stderr, "error: %s\n", strerror(errno));
             return -1;

        }
        if(pid2==0){
             recurPipe(argv,count);
             exit(0);
        }
        else{ 
        wait(&status);
        printf("myshell$");
        }
              

    }
}

void recurPipe(char *argv[],int count){   
        int status;
        pid_t pid;
        int pipeflag=0;
        int i,j,k;
        int count2;
        for(i=0;i<count;i++){
            if(strcmp(argv[i],"|")==0)
            {
                  pipeflag++;
            }
        }
   


        int total[pipeflag+2];
        total[0]=0;
        total[pipeflag+1]=count;
        int l=0,m=1;

        for(;l<count;l++){
            if(strcmp(argv[l],"|")==0){
                total[m]=l+1;
                m++;
            }
        }
        char **addr;
        char **newaddr;
        int o=0;
        int n=0;
        
        
        
        if(pipeflag==0){
            newaddr=&argv[total[n]];
            o=total[n+1]-total[n];
            addr=shortArray(newaddr,o);
             addNode2(argv[total[n]],addr);

        }
        else{
            for(;n<pipeflag+1;n++){
              newaddr=&argv[total[n]];
              o=total[n+1]-total[n]-1;
              if(n==pipeflag) o++;
              addr=shortArray(newaddr,o);
              addNode2(argv[total[n]],addr);
          }
        }
        //the following part with reference to :
        //http://stackoverflow.com/questions/8389033/implementation-of-multiple-pipes-in-c 
        int p=0;
        int numPipes=pipeflag;
        int pipefds[2*numPipes];

        for(i = 0; i < (numPipes); i++){
            if(pipe(pipefds + i*2) < 0) {
                perror("couldn't pipe");
                exit(1);
            }
        }
        
        while(arghead){
            pid=fork();
            if(pid==0){
                if(arghead->next){
                    if(dup2(pipefds[p*2+1],1)<0){
                        exit(1);

                    }
                }
        

            if(p!=0){
                if(dup2(pipefds[(p-1)*2], 0) < 0){
                    perror(" dup2");
                    exit(1);

                }
            }


            for(i = 0; i < 2*numPipes; i++){
                    close(pipefds[i]);
            }
         
            if( myexecu(arghead)<0)
            {       
                     fprintf(stderr, "error: %s\n", strerror(errno));

                    perror(arghead->path);
                    exit(1);
                
            }
            }
            else if(pid<0){
                perror("error");
                exit(1);
            }
            arghead = arghead->next;
            p++;
        }
              for(i = 0; i < 2 * numPipes; i++){
               close(pipefds[i]);
            }

            for(i = 0; i < numPipes + 1; i++)
                wait(&status);



}
//
char* rmspace(char *raw){
    int temp=0;
    while(raw[temp]==' '){temp++;}
    return &raw[temp];
    /*
    char * temp=raw;
    while(*temp!=' '){
        temp++;

    }
    return temp;*/
}
//function to handle each pipeline
int myexecu(list* top){

        list* it=top;
        char **ars=top->arguments;
        int count=0;
        while(ars[count]!=(char*)0){
            count++;
        }
        int breakpoint=count;

        int tcounter=0;
        while(ars[tcounter]!=(char*)0){
             if(strcmp(ars[tcounter],">")==0 ||strcmp(ars[tcounter],"<")==0 ||strcmp(ars[tcounter],"2>")==0)
             {
                  breakpoint=tcounter;
                  break;
              }
             tcounter++;

        }

        int fileopen;
        int fileread;

        char * argv2[breakpoint+1];
        for(tcounter=0;tcounter<breakpoint;tcounter++){
           argv2[tcounter]=ars[tcounter]; 
        }
        argv2[breakpoint]=(char*)0;

        for(tcounter=0;tcounter<count;tcounter++){
                if(strcmp(ars[tcounter],">")==0)
                {
                
                    tcounter++;
                    if((fileopen=open(ars[tcounter],(O_CREAT|O_RDWR),0644))<0){ 
                         fprintf(stderr, "error: %s\n", strerror(errno));
                         exit(-1);
                    }
                    else{
                        if(dup2(fileopen,1) < 0) {
                             fprintf(stderr, "error: %s\n", strerror(errno));
                             exit(-1);                        }
                    }
    
                }
                
                if(strcmp(ars[tcounter],"<")==0)
                {
                    tcounter++;
                    if((fileopen=open(ars[tcounter],O_RDONLY))<0){ 
                         fprintf(stderr, "error: %s\n", strerror(errno));
                         exit(-1);
                    }
                    
                    else{
                        if(dup2(fileopen,0) < 0) {
                             fprintf(stderr, "error: fail to redirect\n");
                            exit(-1);
                        }
                    }
                        
                }
    
                if(strcmp(ars[tcounter],"2>")==0)
                {
                
                    tcounter++;
                    if((fileopen=open(ars[tcounter],(O_CREAT|O_RDWR),0644))<0){ 
                         fprintf(stderr, "error: %s\n", strerror(errno));
                         exit(-1);
                    }
                    else{
                        if(dup2(fileopen,2) < 0) {
                             fprintf(stderr, "error: %s\n", strerror(errno));
                             exit(-1);
                        }
                    }

                }


            }

          

            //system provided functions
            int retv=0;
            if(head==NULL){
                  fprintf(stderr, "error: No path to execute command\n");
                  exit(0);
            }
            list* iter=head;
            char* command=iter->path;
            strcat(command,top->path);

           
            while((retv=execv(command,argv2)==-1)&&iter!=NULL){
                iter=iter->next;
                command=iter->path;
                if(command==NULL) {
                    fprintf(stderr, "Command %s not found.\n",ars[0]);
                    exit(0);
                }  
                strcat(command,ars[0]);

            }
            close(fileopen);
            exit(0);
             




}
