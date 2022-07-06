#ifndef xxSocketsH
#define xxSocketsH
//------------------------------------------------------------------------------
//по материалам  http://rsdn.ru/
namespace XSPACE
{
#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
typedef int SOCKET;
#endif
#include "..\xxBase.h"
#include "xxThread.h"
using namespace XSPACE;
//------------------------------------------------------------------------------
class TxBlockingSocket
 {
  public:
   SOCKET sock;
   int TimeOutMilisec;
   Str LastError;
   inline TxBlockingSocket():RealTimeOutMilisec(0),sock(0){}
   inline int Send(char *Data, int len){return send(sock,Data, len,0);}
   inline int Recv(char *Data, int len){return recv(sock,Data, len,0);}
   bool SetTimeOut(int milisec);
   //-----------------
   bool Write(char *Data, int len);
   bool Read(char *Data, int len);
  protected:
   int RealTimeOutMilisec;
 };
class TxTCPBlockingClient
 {
  public:
   Str Host;
   int Port;
   TxBlockingSocket Socket;
   int ErrorCode;
   TxTCPBlockingClient(){Socket.sock = INVALID_SOCKET;}
   ~TxTCPBlockingClient(){DisConnect();}
   bool Connect();
   bool DisConnect();
  protected:
 };

class TxTCPBlockingServerClient
 {
  public:
   virtual ~TxTCPBlockingServerClient(){}
   TxBlockingSocket Socket;
   void inline SetSocket(SOCKET s){Socket.sock = s;}
   SOCKET inline GetSocket(){return Socket.sock;}
   void virtual Execute() = 0;
 };
class TxEchoServerClient:public TxTCPBlockingServerClient
 {
  public:
   void virtual Execute()
    {

    }
 };
inline int xCloseSocket(SOCKET socket)
 {
    #ifdef _WIN32
    return closesocket(socket);
    #else
    return close(socket);
    #endif
 }
template<class TCPBlockingServerClient>
class TxTCPBlockingServer: public TxThread
 {
  public:
   int Port;
    TxTCPBlockingServer():inLine(false){;}
//  void inline(){inLine = false;}
    bool inline inListen(){return inLine;}
  protected:
   bool inLine;
   virtual void Execute();
   class TxThreadTCPBlockingServerClient:public TxThread
    {
     public:
      void SetSocket(SOCKET s){Client.SetSocket(s);}
     protected:
      TCPBlockingServerClient Client;
      virtual void Execute(){Client.Execute();xCloseSocket(Client.GetSocket());};
    };
   List<TxThreadTCPBlockingServerClient> ClientList;
 };

template<class TCPBlockingServerClient>
void TxTCPBlockingServer<TCPBlockingServerClient>::Execute()
 {
  int sock, listener;
  struct sockaddr_in addr;
  listener = socket(AF_INET, SOCK_STREAM, 0);
  if(listener < 0)
   {
      //  perror("socket");
     return;
   }
  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
   {
        //perror("bind");
     return;
   }
  listen(listener, 1);
  inLine = true;
  while(inLine)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
         inLine = false;
        }else
        {
         ClientList.
        }

        while(1)
        {
            bytes_read = recv(sock, buf, 1024, 0);
            if(bytes_read <= 0) break;
            send(sock, buf, bytes_read, 0);
        }

        close(sock);
    }


 }

/*
setsockopt
select   FIONREAD

tv.tv_usec    = 0;
tv.tv_sec    = x*1000;
setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(struct timeval));

int RecvWithTimeout(
int Socket, 
char *Buffer, 
int Len, 
long Timeout, 
int *bTimedOut 
){ 
fd_set ReadSet ; 
int n ; 
struct timeval Time ; 

FD_ZERO(&ReadSet) ; 
FD_SET(Socket,&ReadSet) ; 
Time.tv_sec = Timeout ; 
Time.tv_usec = 0 ; 
*bTimedOut = FALSE ; 
n = select(Socket+1,&ReadSet,NULL,NULL,&Time) ; 
if (n > 0) {
return recv(Socket,Buffer,Len,0);
}
if (n == 0) {
*bTimedOut = TRUE ;
}
return(n) ;
}



 SO_OOBINLINE       enables reception of out-of-band data in band
           SO_SNDBUF          set buffer size for output
           SO_RCVBUF          set buffer size for input
           SO_SNDLOWAT        set minimum count for output
           SO_RCVLOWAT        set minimum count for input
           SO_SNDTIMEO        set timeout value for output
           SO_RCVTIMEO       ------ set timeout value for input
           SO_ACCEPTFILTER    set accept filter on listening socket
           SO_NOSIGPIPE       controls generation of SIGPIPE for the socket
           SO_TIMESTAMP       enables reception of a timestamp with datagrams
           SO_BINTIME         enables reception of a timestamp with datagrams
           SO_ACCEPTCONN      get listening status of the socket (get only)
           SO_TYPE            get the type of the socket (get only)
           SO_ERROR           get and clear error on the socket (get only)


struct timeval timeout; bzero(&timeout, sizeof(timeval));
                        timeout.tv_sec= 1;
                        setsockopt(sclient, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeval));
 */
//------------------------------------------------------------------------------
}
#endif
