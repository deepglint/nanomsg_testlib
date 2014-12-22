#include <assert.h>
#include <libc.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "sender.h"
#include <nanomsg/nn.h>
#include <unistd.h>
#include <nanomsg/pipeline.h>

// #define NODE0 "node0"
// #define NODE1 "node1"

// int node0 (const char *url)
// {
//   int sock = nn_socket (AF_SP, NN_PULL);
//   assert (sock >= 0);
//   assert (nn_bind (sock, url) >= 0);
//   while (1)
//     {
//       char *buf = NULL;
//       int bytes = nn_recv (sock, &buf, NN_MSG, 0);
//       assert (bytes >= 0);
//       printf ("NODE0: RECEIVED \"%s\"\n", buf);
//       nn_freemsg (buf);
//     }
// }

// int node1 (const char *url, const char *msg)
// {
//   int sz_msg = strlen (msg) + 1; // '\0' too
//   int sock = nn_socket (AF_SP, NN_PUSH);
//   assert (sock >= 0);
//   assert (nn_connect (sock, url) >= 0);
//   printf ("NODE1: SENDING \"%s\"\n", msg);
//   int bytes = nn_send (sock, msg, sz_msg, 0);
//   assert (bytes == sz_msg);
//   return nn_shutdown (sock, 0);
// }
//void sendMessage (struct NanoSenderSession* this, char *msg);
void sendMessage(struct NanoSenderSession* this, char *msg)
{
  int sz_msg = strlen (msg); // '\0' too
  int bytes = nn_send (this->sock, msg, sz_msg, 0);
  printf("send ok\n");
  return;
  //assert (bytes == sz_msg);
  //return nn_shutdown (sock, 0);
}
int connectToSock(struct NanoSenderSession* this){
  //this->url=url;
  printf("connecting...\n");
  int sock=nn_socket(AF_SP,NN_PUSH);
  this->sock=sock;
  assert(sock>=0);
  assert(strlen(this->url)>0);
  assert(nn_connect(sock, this->url) >= 0);
  return sock;
}
int disconnectSock(struct NanoSenderSession* this){
  return nn_shutdown(this->sock,0);
}
struct NanoSenderSession* newNanoSenderSession(char* url){
  struct NanoSenderSession *nss;
  nss=malloc(sizeof(struct NanoSenderSession));
  nss->url=url;
  nss->sendMessage=sendMessage;
  nss->connect=connectToSock;
  nss->disconnect=disconnectSock;
  //nss->this=nss;
  return nss;
}
static char* buf1;
static char* buf2;
static char* buf3;
static struct NanoSenderSession* nss;






void readFile(char* filepath){
  printf("reading file\n");
  //printf("length:%d\n",length );
  FILE *fp1;
  //char* buf;
  buf1=(char*)malloc(450*sizeof(char));
  buf2=(char*)malloc(4500*sizeof(char));
  buf3=(char*)malloc(45000*sizeof(char));
  //char buf[45551];
  fp1=fopen(filepath,"r");
  printf("opening %s\n",filepath );
  fgets(buf1,449,fp1);
  fgets(buf2,4449,fp1);
  fgets(buf3,44449,fp1);
  printf("get out all the byte\n");
  //buf[length-1]='\0';

  fclose(fp1);
  //return buf;
}

void sig_handler(int signo){
  if(signo==SIGINT){
    printf("free the buffers used\n");
    free(buf1);
    free(buf2);
    free(buf3);
    nss->disconnect(nss);
  }
  exit(0);
}

int main (const int argc, const char **argv)
{
  //char* buf1,buf2,buf3;
  printf("%s\n",argv[1]);
  nss=newNanoSenderSession(argv[1]);
  nss->connect(nss);
  printf("connect ok\n");
  // buf1=readFile("./text.txt",450);
  // buf2=readFile("./text.txt",4550);
  // buf3=readFile("./text.txt",45550);
  readFile("./text.txt");
  int m=0;
  if(signal(SIGINT,sig_handler)==SIG_ERR)
    printf("\ncan not catch SIGINT\n");
   while(1){
  //   if(m%3==0){
      //printf("sending buffer 1:---%d\n",strlen(buf1));
      m++;
      nss->sendMessage(nss,buf1);
      //sleep(30);
      m++;
      nss->sendMessage(nss,buf2);
      //sleep(30);
      m++;
      nss->sendMessage(nss,buf3);
      //sleep(30);
    //}else if(m%3==1){
       //printf("sending buffer 2:---%d\n",strlen(buf2));
      //sleep(10);
      //nss->sendMessage(nss,buf2);
    // //}else{
    //   printf("sending buffer 3:---%d\n",strlen(buf3));
      //nss->sendMessage(nss,buf3);
    // //}
    // m++;
    //sleep(30);
      printf("%d msg has sended\n",m );
  }
  //return nss->disconnect(nss);
}