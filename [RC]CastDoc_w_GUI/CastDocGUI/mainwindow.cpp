#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <QFileDialog>


#define LENGTH 256

int port;/* portul de conectare la server*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');//strrchr ultima aparitie a caracterului in string
    if(!dot || dot == filename) return "";
    return dot + 1;//returneaza tot ce este dupa .
}


 char *get_filename( char *filename) {
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


int check_type(const char *type)
{
    if(strcmp(type,"ps")==0)return 1;
    else
        if(strcmp(type,"pdf")==0)return 2;
        else
            if(strcmp(type,"tex")==0)return 3;
            else
                if(strcmp(type,"html")==0)return 4;
                else
                    if(strcmp(type,"asp")==0)return 5;
                    else
                        if(strcmp(type,"php")==0)return 6;
                        else
                            if(strcmp(type,"djvu")==0)return 7;
    return 0;

}

int connectare(char* c_ip,char* c_port)
{
   int sock_dscrpt;// descriptorul de socket
   struct sockaddr_in server;// structura folosita pentru conectarea la server
   port = atoi (c_port);/* stabilim portul */
   printf("port:%d\n",port);
   /* cream socketul */
   if ((sock_dscrpt = socket (AF_INET, SOCK_STREAM, 0)) == -1)
        {
        perror ("Eroare la socket().\n");
        return 0;
        }

    /* popularea structurii folosite pentru realizarea conexiunii cu serverul */
    server.sin_family = AF_INET; /* familia socket-ului */
    server.sin_addr.s_addr = inet_addr(c_ip);/* adresa IP a serverului */
    server.sin_port = htons (port); /* portul de conectare */
    /* conectarea la server */
    if (connect (sock_dscrpt, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
        {
         perror ("[User client]Eroare la connect().\n");
         return 0;
        }
    return sock_dscrpt;
}

char* convertToChar(QString s){
    QByteArray array = s.toLocal8Bit();
    char* buffer = array.data();
    return buffer;
}

int send_type(int sock_dscrpt,int type)
{
    char answer[5]="\0";

    if (write (sock_dscrpt,&type,sizeof(int)) <= 0)
      {
        perror ("[User client]Eroare la write() spre server.\n");
        return errno;
      }

    /* citirea raspunsului dat de server in legatura cu tipul
       (apel blocant pana cand serverul raspunde) */
    if (read (sock_dscrpt, &answer,sizeof(char[5])) < 0)
      {
        perror ("[User client]Eroare la read() de la server.\n");
        return errno;
      }
    else
    {
        if(strcmp(answer,"okbun")==0)return 1;
        else return 0;
    }
}

int test_conv(int sock_dscrpt)
{

    //primirea mesajului in legatura cu corectitudinea transformarii
    char ans[7];
    if (read (sock_dscrpt, &ans,sizeof(char[7])) < 0)
      {
        perror ("[User client]Eroare la read() de la server.\n");
        return errno;
      }
    printf ("[User client]Mesajul primit este : %s\n", ans);

    if(strcmp(ans,"conv=ok")==0)
        return 1;
    else return 0;
}

int send_file(int sock_dscrpt,char *send_file_name )
{
    int ans=0;
    int fn_size=strlen(send_file_name);
    printf("%s %d",send_file_name,fn_size);
    if(send(sock_dscrpt, &fn_size, sizeof(int), 0) < 0)
      {
          fprintf(stderr, "[User client]: Esuare in trimiterea marimii numelui fisierului %s. (errno = %d)\n", send_file_name, errno);
           return errno;
    }

    if(send(sock_dscrpt, send_file_name, fn_size, 0) < 0)
    {
        fprintf(stderr, "[User client]: Esuare in trimiterea numelui fisierului %s. (errno = %d)\n", send_file_name, errno);
        return errno;
    }

    //mesaj de la server daca fisierul este de tipul corect

    if (read (sock_dscrpt, &ans,sizeof(int)) < 0)
      {
        perror ("[User client]Eroare la read() de la server.\n");
        return errno;
      }

    if(ans==0){ return 0;}

    char fs_buff[LENGTH]="\0";
    FILE* fs = fopen(send_file_name, "r");
    if(fs == NULL)
         {
          //  printf("[User client]ERROR: Fisierul %s nu s-a gasit.\n", send_file_name);
            return errno;
         }

    int fs_block_size=0;
    while((fs_block_size = fread(fs_buff, sizeof(char), LENGTH, fs)) > 0)
         {
            if(send(sock_dscrpt, fs_buff, fs_block_size, 0) < 0)
            {
                fprintf(stderr, "[User client]: Esuare in trimiterea fisierului %s. (errno = %d)\n", send_file_name, errno);
                break;
            }
            memset(fs_buff,0, LENGTH);
          }
    //printf("[User client]Fisierul %s s-a trimis de la Client la Server!\n", send_file_name);

    if (read (sock_dscrpt, &ans,sizeof(int)) < 0)
      {
        perror ("[User client]Eroare la read() de la server.\n");
        return errno;
      }
   return ans;
}

char rec_file_name[150]="\0";

int recv_file(int sock_dscrpt)
{
    printf("[User client]Astept fisierul convertit \n");
    char fr_buff[LENGTH]="\0";

    char path[65]="/home/cornelius/Desktop/fileExamples/";
    strcpy(rec_file_name,path);
    char fname[150]="\0";
    int sizefname=0;

    if(recv(sock_dscrpt, &sizefname, sizeof(int), 0) < 0)
    {
        perror("[User client] Eroare la recv() de la server.\n");
        return 0;
    }
    else
        printf("[User client] Ok filename size %d.\n",sizefname);

    if(recv(sock_dscrpt, &fname, sizefname, 0) < 0)
       {
        perror("[User client] Eroare la recv() de la server.\n");
        return 0;
        }
    else{
//        fname[sizefname] = "\0"; //probleme cu numele fisierului
//        int i;
//        for(i=0;i<150;i++ )
//        if (fname[i] == '\n')
//             fname[i] = '\0';
//        for(i=sizefname;i<150;i++)
//            fname[i] = '\0';
        printf("[User client] OK filename %s \n",fname);
          }

    strcat(rec_file_name,get_filename(fname));

    printf("Numele fisierului ajuns la client %s \n",rec_file_name);

    FILE* fr = fopen(rec_file_name, "w+");//w+ creeaza un fisier gol deschis catre citire si scriere
    if(fr == NULL)
        printf("[User client]Fisierul %s nu poate fi deschis \n", rec_file_name);
    else
        {
           bzero(fr_buff, LENGTH);
           int fr_block_size = 0;
           while((fr_block_size = recv(sock_dscrpt, fr_buff, LENGTH, 0)) > 0)
             {
                int write_size = fwrite(fr_buff, sizeof(char), fr_block_size, fr);
                if(write_size < fr_block_size)
                  {
                     perror("[User client]Citirea fisierului a esuat.\n");
                     return 0;
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
                            printf("[User client] recv() timed out.\n");
                        }
                    else
                        {
                            fprintf(stderr, "recv() failed due to errno = %d\n", errno);
                           return 0;
                        }
                }
                printf("[User client]Fisier primit cu succes!\n");
                fclose(fr);
            }
    //rcv_file=rec_file_name;
    return 1;
}

int sock_dscrpt;

void MainWindow::on_pushButtonConnect_clicked()
{

    QString ip=this->ui->ip->text();
    QString port=this->ui->port->text();
    QByteArray array = ip.toLocal8Bit();
    char* cip = array.data();
    QByteArray array1 = port.toLocal8Bit();
    char* cp = array1.data();

    this->ui->send_msg_box_rcv_file->setText("");
    this->ui->label_rcv_file->setText("");
    this->ui->send_msg_box_3->setText("");
    this->ui->send_msg_box_4->setText("");
    sock_dscrpt=connectare(cip,cp);

    if(sock_dscrpt<=0){

        this->ui->label_connect->setText("Eroare.");

    }
    else {
        this->ui->label_connect->setText("Succes.");
        this->ui->pushButtonChooseFile->setEnabled(true);
    }
}

void MainWindow::on_pushButtonChooseFile_clicked()
{

    QString fileName ;
    loop1:
    fileName= QFileDialog::getOpenFileName(this,
    tr("Open File "), "/home", tr("Files (*.ps *.pdf *.tex *.html *.asp *.php *.djvu)"));

    if(fileName.isEmpty())goto loop1;
    this->ui->file_name_box->setText(fileName);
    this->ui->lineEditConvertingType->setEnabled(true);
    this->ui->pushButtonSendType->setEnabled(false);

    QByteArray array = fileName.toLocal8Bit();
    char* file_name=array.data();
    const char* ext=get_filename_ext(file_name);
    int type=check_type(ext);

    int answer;
    answer=send_type(sock_dscrpt,type);

    if(answer)
    {
        this->ui->send_msg_box->setText("Tipul fisierului este acceptat.");
    }
    else
    {
        this->ui->send_msg_box->setText("Tipul fisierului nu este acceptat.");
    }

    this->ui->pushButtonSendType->setEnabled(true);
}

void MainWindow::on_pushButtonSendType_clicked()
{
    loop2:
    QString type2send=this->ui->lineEditConvertingType->text();

    QByteArray array=type2send.toLocal8Bit();
    char* type_2_send_c=array.data();

    this->ui->pushButtonChooseFile->setEnabled(false);

    int type=check_type(type_2_send_c);

    int answer;
   if(type!=0){
    answer=send_type(sock_dscrpt,type);

    if(answer)
    {
        this->ui->send_msg_box_2->setText("Tipul fisierului este acceptat.");
    }
    else
    {
        this->ui->send_msg_box_2->setText("Tipul fisierului nu este acceptat.");
    }

    answer=test_conv(sock_dscrpt);
    if(answer)
    {
        this->ui->send_msg_box_3->setText("Conversia este posibila.");
        this->ui->pushButtonSEND->setEnabled(true);
    }
    else
    {
        this->ui->send_msg_box_3->setText("Conversia nu este posibila.");
    }
    }
   else{this->ui->send_msg_box_3->setText("Tipul este gresit.");
   goto loop2;}
}

void MainWindow::on_pushButtonSEND_clicked()
{
    QString fileName=this->ui->file_name_box->text();
    QByteArray array=fileName.toLocal8Bit();
    char* fileName_ch=array.data();

    this->ui->pushButtonSEND->setEnabled(false);
    this->ui->pushButtonSendType->setEnabled(false);
    this->ui->file_name_box->setText("file not chosen");
    this->ui->send_msg_box_2->setText("");
    this->ui->send_msg_box_4->setText("");
   //this->ui->test->setText(fileName);

    int answer=send_file(sock_dscrpt,fileName_ch);

    if(answer)
    {

      this->ui->send_msg_box_4->setText("Fisier trimis si convertit.");
      //char* recv_file_name;
      int rcv=recv_file(sock_dscrpt);
       if(rcv==1)
        {
         this->ui->label_rcv_file->setEnabled(true);
         this->ui->send_msg_box_rcv_file->setEnabled(true);
         this->ui->send_msg_box_rcv_file->setText("Primire fisier cu succces.");
         QString recieveFile=QString::fromStdString(rec_file_name);
         this->ui->label_rcv_file->setText(recieveFile);
       }

    }
        else
        {
        this->ui->send_msg_box_4->setText("Eroare trimitere fisier");
        //QString errono = QString::number(answer);
        //this->ui->send_msg_box_4->setText(errono);
    }

}
