/* Server TCP concurent care deserveste mai multi clienti
   prin crearea unui thread pentru fiecare client in parte.
   Asteapta un mesaj de la fiecare client si intoarce clientului un
   raspuns cum ca se poate realiza conversia, in caz afirmativ va astepta
   si transmiterea unui fisiser. Va primi fisierul respectiv, il va converti
   si il va transmite inapoi convertit.

   Autor: Corneliu Țuțuianu  <corneliu.tutuianu@info.uaic.ro> (c)2015
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include </home/cornelius/Desktop/[RC]Proiect-CastDoc/functions.h>


extern int errno;/* codul de eroare returnat de anumite apeluri */

typedef struct thData{
	int idThread; //id-ul thread-ului tinut in evidenta de acest program
	int cl; //descriptorul intors de accept
}thData;

static void *treat(void *); /* functia executata de fiecare thread ce realizeaza comunicarea cu clientii */
void raspunde(void *);



int main ()
{


  struct sockaddr_in server;	// structura folosita de server
  struct sockaddr_in from;	
  int sock_dscrpt;	//descriptorul de socket
  pthread_t th[100];    //Identificatorii thread-urilor care se vor crea
  int i=0;
  

  /* crearea unui socket */
  if ((sock_dscrpt = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[CastDOC Server]Eroare la socket().\n");
      return errno;
    }

  /* utilizarea optiunii SO_REUSEADDR ??*/
  int on=1;
  setsockopt(sock_dscrpt,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
  
  /* pregatirea structurilor de date */
  bzero (&server, sizeof (server));
  bzero (&from, sizeof (from));
  
  /* umplem structura folosita de server */
  /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;	
  /* acceptam orice adresa */
    server.sin_addr.s_addr = htonl (INADDR_ANY);
  /* utilizam un port utilizator */
    server.sin_port = htons (PORT);
  
  /* atasam socketul */
  if (bind (sock_dscrpt, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("[CastDOC Server]Eroare la bind().\n");
      return errno;
    }

  /* Serverul asculta clienti sa se conecteze */
  if (listen (sock_dscrpt, 2) == -1)
    {
      perror ("[CastDOC Server]Eroare la listen().\n");
      return errno;
    }
  /* servirea in mod concurent clientii conectati folosind thread-uri */
  while (1)
    {
      int client;
      thData * td; //parametru functiei executate de thread
      int length = sizeof (from);

      printf ("[CastDOC Server]Asteptam la portul %d...\n",PORT);
      fflush (stdout);

      /* acceptarea unui client (stare blocanta pina la realizarea conexiunii) */
      if ( (client = accept (sock_dscrpt, (struct sockaddr *) &from, &length)) < 0)
	{
      perror ("[CastDOC Server]Eroare la accept().CONFIG += thread c++11\n");
	  continue;
	}

    //int idThread; //id-ul threadului
    //int cl; //descriptorul intors de accept

	td=(struct thData*)malloc(sizeof(struct thData));	
	td->idThread=i++;
	td->cl=client;

    pthread_create(&th[i], NULL, &treat, td);

    //printf ("[CastDOC Server]Asteptam alt client...\n");

    }//while
}

int type_read(int descriptor,int th_id){

    int type=0;
    char answer[5]="\0";
    if (read (descriptor, &type,sizeof(int)) <= 0)
            {
              printf("[Thread %d]\n",th_id);
              perror ("Eroare la read() de la client.\n");
              return 0;
            }
    printf ("[Thread %d]Mesajul a fost receptionat. Tipul este :\n",th_id);
    fflush (stdout);
    if((type<1||type>7)&&type!=NULL){
        printf("[Thread %d]Eroare:tip necorespunzator ",th_id);
        strcpy(answer,"notok");
        if (write (descriptor, &answer, sizeof(char[5])) <= 0)
           {
            printf("[Thread %d] ",th_id);
            perror ("[Thread]Eroare la write() catre client.\n");
            return 0;
           }
       else
           printf ("[Thread %d]Mesajul de eroare a fost transmis cu succes.\n",th_id);
    }
    else strcpy(answer,"okbun");
    if(type!=NULL)
       printf("%s \n",check_type(type));
    else
        return 0;
    /* returnam mesajul clientului  */
    fflush (stdout);
    printf("[Thread %d]Trimitem mesajul inapoi %s\n",th_id, answer);
    fflush (stdout);
    if (write (descriptor, &answer, sizeof(char[5])) <= 0)
        {
         printf("[Thread %d] ",th_id);
         perror ("[Thread]Eroare la write() catre client.\n");
         return 0;
        }

    else printf ("[Thread %d]Mesajul %s a fost trasmis cu succes.\n",th_id,answer);

    return type;

}

int conversionCheck(int descriptor,int th_id,int first_type,int second_type)
{
    //Verificarea conversiilor dintre cele 2 formate si trasmiterea unui mesaj la client
    char ans[7]="\0";
    if(check_conv(first_type,second_type)==1)
    {
        strcpy(ans,"conv=ok");
        printf("[Thread %d][transformare=ok]Trimitem mesajul %s inapoi \n",th_id,ans);
        if (write (descriptor, &ans, sizeof(char[7])) <= 0)
            {
             printf("[Thread %d] ",th_id);
             perror ("[Thread]Eroare la write() catre client.\n");
             return 0;
            }
        else printf ("[Thread %d]Mesajul %s a fost trasmis cu succes.\n",th_id,ans);
     }
    else {
    strcpy(ans,"c=notok");
    printf("[Thread %d][transformare=nu e ok]Trimitem mesajul %s inapoi \n",th_id,ans);
    if (write (descriptor, &ans, sizeof(char[7])) <= 0)
        {
         printf("[Thread %d] ",th_id);
         perror("[Thread]Eroare la write() catre client.\n");
         return 0;
        }
    else printf ("[Thread %d]Mesajul %s a fost trasmis cu succes.\n",th_id,ans);
    return 0;
    }
    return 1;
}

static void *treat(void * arg)

{		
        struct thData tdL;
      //  int ok=1;
        tdL= *((struct thData*)arg);
        printf("[Thread %d]Conexiune realizata, se astepta mesajele\n",tdL.idThread);
        fflush (stdout);

        pthread_detach(pthread_self());
        raspunde((struct thData*)arg);

        /* client deservit, inchidem conexiunea */
        close ((int)arg);

		return(NULL);		
}

void raspunde(void *arg)
{
    struct thData tdL;
    tdL= *((struct thData*)arg);
    int ok=1;
    while(ok==1)
  {
    int first_type=0,second_type=0;//mesajele primite initial de la client
    char answer[5]="\0";
    int ans=0;
    printf ("[Thread %d]- Asteptam primul tip de fisier...\n", tdL.idThread);
    first_type=type_read(tdL.cl,tdL.idThread);

    printf ("[Thread %d]- Asteptam al doilea tip de fisier...\n", tdL.idThread);
    second_type=type_read(tdL.cl,tdL.idThread);

    if(second_type==0) return NULL;
    int c=conversionCheck(tdL.cl,tdL.idThread,first_type,second_type);
    if(c==0)return NULL;
    /*Primim fisierul de la client*/
        printf("[Thread %d]Astept fiserul \n",tdL.idThread);

        char fr_buff[LENGTH]="\0";
        char rec_file_name[100]="\0";
        char path[65]="/home/cornelius/Desktop/[RC]Proiect-CastDoc/recFiles/";
        strcpy(rec_file_name,path);
        char fname[50]="\0";
        int sizefname=0;

        if(recv(tdL.cl, &sizefname, sizeof(int), 0) < 0)
        {
            perror("[Thread %d] Eroare la recv() de la client.\n");
            return NULL;
        }
        else
            printf("[Thread %d] Ok filename size %d.\n",tdL.idThread,sizefname);
        if(recv(tdL.cl, &fname, sizefname, 0) < 0)
           {
            perror("[Thread] Eroare la recv() de la client \n");
            return NULL;
            }
        else
            printf("[Thread %d] OK filename %s \n",tdL.idThread,fname);

        fflush (stdout);
        //printf("%s \n",path);
        //printf("%s  \n",get_filename(fname));
        strcat(rec_file_name,get_filename(fname));
        printf("numele fisierului de pe server : %s \n",rec_file_name);

        if(*get_filename_ext(rec_file_name)==*check_type(first_type))
            {
                printf("[Thread %d]Tipul fisierului primit %s este corespunzator \n",tdL.idThread,get_filename(rec_file_name)   );
                ans=1;
                if (write (tdL.cl, &ans, sizeof(int)) <= 0)
                    {
                     printf("[Thread %d] ",tdL.idThread);
                     perror ("[Thread]Eroare la write() catre client.\n");
                     continue;
                    }
                else printf ("[Thread %d]Mesajul %d a fost trasmis cu succes.\n",tdL.idThread,ans);
            }
        else{
            printf("[Thread %d] eroare - tip necorespunzator\n",tdL.idThread);
            ans=0;
            if (write (tdL.cl, &ans, sizeof(int)) <= 0)
                {
                 printf("[Thread %d] ",tdL.idThread);
                 perror ("[Thread]Eroare la write() catre client.\n");
                 return NULL;
                }
            else printf ("[Thread %d]Mesajul %d a fost trasmis cu succes.\n",tdL.idThread,ans);

            return NULL;
            }



        FILE* fr = fopen(rec_file_name, "w+");//w+ creeaza un fisier gol deschis catre citire si scriere
        if(fr == NULL)
            printf("[Thread %d]Fisierul %s nu poate fi deschis \n",tdL.idThread, rec_file_name);
        else
            {
               bzero(fr_buff, LENGTH);
               int fr_block_size = 0;
               while((fr_block_size = recv(tdL.cl, fr_buff, LENGTH, 0)) > 0)
                 {
                    int write_size = fwrite(fr_buff, sizeof(char), fr_block_size, fr);
                    if(write_size < fr_block_size)
                      {
                         error("[Thread %d]Citirea fisierului a esuat.\n",tdL.idThread);
                      }
                    bzero(fr_buff, LENGTH);
                    if (fr_block_size == 0 || fr_block_size != LENGTH)
                        {
                            break;
                        }
                 }
                 if(fr_block_size < 0)
                    {
                        if (errno == EAGAIN)//The socket is marked non-blocking and no connections are present to be accepted.
                            {
                                printf("[Thread %d] recv() timed out.\n",tdL.idThread);
                            }
                        else
                            {
                                fprintf(stderr, "recv() failed due to errno = %d\n", errno);
                                exit(1);
                            }
                    }
                    printf("[Thread %d]Fisier primit cu succes!\n",tdL.idThread);
                    fclose(fr);
                }

        //printf("%s\n", rec_file_name);


        char convert[13]="\0";
        sprintf(convert,"%s%s%s",check_type(first_type),"=",check_type(second_type));
        //printf("!! %s\n",convert);
        char convert_command[35]="\0";
        char converted_file_name[100]="\0";
        strcpy(converted_file_name,rec_file_name);
        removeFilenameExt(converted_file_name);
        strcat(converted_file_name,check_type(second_type));
        //printf("!! %s",converted_file_name);
        if(first_type==2 && second_type==7){
            sprintf(convert_command,"%s %s -o %s",get_utility(convert),rec_file_name,converted_file_name);
            printf("[Thread %d] %s \n",tdL.idThread,convert_command);
            system(convert_command);
        }else{
        sprintf(convert_command,"%s %s %s",get_utility(convert),rec_file_name,converted_file_name);
        printf("[Thread %d] %s \n",tdL.idThread,convert_command);
        system(convert_command);
        }


        if(first_type==3&&second_type==4)
        {
            memset(converted_file_name,0,sizeof(converted_file_name));
            strcpy(converted_file_name,rec_file_name);
            removeFilenameExt(converted_file_name);
            char *folder=get_filename(rec_file_name);
            removeFilenameExt(folder);
            int lenght=strlen(converted_file_name);
            converted_file_name[lenght-1]='\0';
            strcat(converted_file_name,"/");
            strcat(converted_file_name,folder);
            strcat(converted_file_name,check_type(second_type));
            //lex to html creeaza un folder nou problemsolved
        }

        //trimitem fisierul convertit catre client
        //mesaj afirmativ
        ans =1;
        if (write (tdL.cl, &ans, sizeof(int)) <= 0)
            {
             printf("[Thread %d] ",tdL.idThread);
             perror ("[Thread]Eroare la write() catre client.\n");
             return NULL;
            }
        else printf ("[Thread %d]Mesajul %s a fost trasmis cu succes.\n",tdL.idThread,answer);

        //fisier

        int fs_size=0;
        fs_size=strlen(converted_file_name);
        newlineRemover(converted_file_name);//problema cu ultimul caracter

        if(send(tdL.cl, &fs_size, sizeof(int), 0) < 0)
          {
              fprintf(stderr, "[Thread ]: Esuare in trimiterea marimii numelui fisierului %s. (errno = %d)\n", converted_file_name, errno);
          }
          else printf("[Thread %d]:am transmis marimea numelui cu succes %d \n",tdL.idThread ,fs_size);

        if(send(tdL.cl, &converted_file_name, fs_size, 0) < 0)
        {
            fprintf(stderr, "[Thread ]: Esuare in trimiterea numelui fisierului %s. (errno = %d)\n", converted_file_name, errno);
        }
        else printf("[Thread %d]:am transmis numele cu succes %s \n" ,tdL.idThread,converted_file_name);

        FILE* fs = fopen(&converted_file_name, "r");
        if(fs == NULL)
             {
                printf("[Thread %d]ERROR: Fisierul %s nu s-a gasit.\n",tdL.idThread, converted_file_name);
                return errno;
             }
        char fs_buff[LENGTH]="\0";
        bzero(fs_buff, LENGTH);
        int fs_block_size=0;

        while((fs_block_size = fread(fs_buff, sizeof(char), LENGTH, fs)) > 0)
             {
                if(send(tdL.cl, fs_buff, fs_block_size, 0) < 0)
                {
                    fprintf(stderr, "[Thread %d]: Esuare in trimiterea fisierului %s. (errno = %d)\n",tdL.idThread, converted_file_name, errno);
                    return NULL;
                }
                bzero(fs_buff, LENGTH);
              }
        printf("[Thread %d]Fisierul %s s-a trimis de la Server la Client!\n",tdL.idThread, converted_file_name);
//    printf("[Thread %d]Astept alegerea clientului..\n",tdL.idThread);
//    fflush (stdout);
//    if (read (tdL.cl, &ok,sizeof(int)) <= 0)
//         {
//           printf("[Thread %d]\n",tdL.idThread);
//           perror ("Eroare la read() de la client.\n");
//           return NULL;
//         }
//    printf("Alegerea:%d",ok);
   }
  return NULL;
 }
