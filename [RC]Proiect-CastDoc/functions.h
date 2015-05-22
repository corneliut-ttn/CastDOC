#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <sys/stat.h>

#define LENGTH 256
#define PORT 2809/* portul folosit */

void newlineRemover(char *name)
{
    int i ;
    int lenght = strlen(name);
    for(i = 0 ; i < lenght ; i++)
     {
        if(name[i] == '\n')
            name[i] = '\0' ;
     }
}

char doc_convert[7][7]={{'x','o','x','x','x','x','x'},
                       {'o','x','x','x','x','x','o'},
                       {'x','x','x','o','x','x','x'},
                       {'x','x','o','x','x','x','x'},
                       {'x','x','x','x','x','o','x'},
                       {'x','x','x','x','x','x','x'},
                       {'x','o','x','x','x','x','x'}};

int check_conv(int first_type,int second_type)
{
    if(doc_convert[first_type-1][second_type-1]=='o')
        return 1;
    else return 0;
}

const char *check_type(int nr)
{
    switch(nr){
    case 1:return "ps"; break;
    case 2:return "pdf"; break;
    case 3:return "tex"; break;
    case 4:return "html"; break;
    case 5:return "asp"; break;
    case 6:return "php"; break;
    case 7:return "djvu"; break;
    default: break;}
}

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');//strrchr ultima aparitie a caracterului in string
    if(!dot || dot == filename) return "";
    return dot + 1;//returneaza tot ce este dupa .
}

const char *get_filename(const char *filename) {
    char *fname;
    char *backslash = strrchr(filename, '/');
    if(!backslash || backslash == filename) return "";
    fname=backslash + 1; //returneaza tot ce este dupa slash
    int lenght = strlen(fname),i;
    for(i = 0 ; i < lenght ; i++)
     {
        if(fname[i] == '\n')
            fname[i] = '\0' ;
     }
    return fname;
}

void removeFilenameExt(char *filename)
{
  int lenght=strlen(filename);
  int i=lenght-1;
  while(filename[i]!='.')
  {
    filename[i]='\0';
    i--;
  }
}

char *get_utility(const char *conv)
{
    FILE *fp;
    char line[20];
    char *utility;
    if((fp = fopen("/home/cornelius/Desktop/[RC]Proiect-CastDoc/castdoc.cfg", "r")) == NULL)
    {
        printf("Eroare citire fisier de configurare");
        return NULL;
    }
    while(fgets(line, 20, fp) != NULL)
    {
        if((strstr(line, conv)) != NULL)
        {
           char *space=strrchr(line,' ');
           if(!space||space==line)return "";
           utility=space+1; //primeste tot ce este dupa ' '
           int lenght = strlen(utility),i;
           for(i = 0 ; i < lenght ; i++)
            {
               if(utility[i] == '\n')
                   utility[i] = '\0' ;
            }
           return utility;
        }
    }
    if(fp)
    {
      fclose(fp);
    }
    return(0);
}

int testFileExists(const char* filename){
    printf("!!%s\n",filename);
    FILE *file=fopen(&filename, "r");
    printf("\n!%d!\n",file);
    if (file == NULL)
    {
        printf("file not ok \n");
        return 0;
    }
    else {
        printf("file ok\n");
        fclose(file);
        return 1;

    }
}


#endif // FUNCTIONS_H

