#pragma hdrstop
#include "xxSockets.h"
namespace XSPACE
{
//------------------------------------------------------------------------------
bool TxBlockingSocket::Write(char *Data, int len)
 {
  if(RealTimeOutMilisec!=TimeOutMilisec)SetTimeOut(TimeOutMilisec);
  int total = 0;  int n;
  while(total < len)
   {
     n = Send(Data+total, len-total);
     if(n == -1) {return false;}
     total += n;
   }
  return true;
 }
bool TxBlockingSocket::Read(char *Data, int len)
 {
  if(RealTimeOutMilisec!=TimeOutMilisec)SetTimeOut(TimeOutMilisec);
  int total = 0;  int n,ZerroAttempt=0;
  while(total < len)
   {
     n = Recv(Data+total, len-total);
     if(n==0){ZerroAttempt++;xSleep(50);}else ZerroAttempt = 0;
     if(n == -1 ||ZerroAttempt>3) {return false;}
     total += n;
   }
  return true;
 }
bool TxBlockingSocket::SetTimeOut(int milisec)
 {
   RealTimeOutMilisec = milisec; TimeOutMilisec = milisec;
   struct timeval timeout;
   timeout.tv_sec = milisec / 1000;
   timeout.tv_usec = (milisec % 1000)*1000;
   return 0 == setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeval));
 }
//------------------------------------------------------------------------------
bool TxTCPBlockingClient::Connect()
 {
  if(Socket.sock != INVALID_SOCKET)DisConnect();
  //------
  struct sockaddr_in addr;  
  struct hostent *pinfo = gethostbyname(Host.c_str());
  if(pinfo==0)return false;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(Port);
  addr.sin_addr = *((in_addr*)pinfo->h_addr_list[0]);
  //------
  int temp = socket(AF_INET, SOCK_STREAM, 0);
  if(temp<0){ErrorCode = temp; Socket.sock = INVALID_SOCKET; return false;}
   else Socket.sock = temp;
  ErrorCode = connect(Socket.sock, (struct sockaddr *)&addr, sizeof(addr));
  if(ErrorCode<0){xCloseSocket(Socket.sock);Socket.sock = INVALID_SOCKET;}
  return ErrorCode>=0;
 }
bool TxTCPBlockingClient::DisConnect()
 {
  if(Socket.sock == INVALID_SOCKET)return true;
  ErrorCode = shutdown(Socket.sock,2);
  if(ErrorCode<0){return false;}
  ErrorCode = xCloseSocket(Socket.sock);
  return ErrorCode>=0;
 }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class TxSupportSockets
 {
  public:
   TxSupportSockets();
   ~TxSupportSockets();
   inline bool isInited(){return Error == 0;}
   inline int GetError(){return Error;}
  protected:
    int Error;
 };
TxSupportSockets::~TxSupportSockets()
 {
  #ifdef _WIN32
  WSACleanup();
  #endif
 }
TxSupportSockets::TxSupportSockets()
 {
      #ifdef _WIN32
      WORD wVersionRequested = MAKEWORD( 2, 0 );
      WSADATA wsaData;
      Error = WSAStartup( wVersionRequested, &wsaData );
      if ( Error != 0 ) return;
      if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 0 )
        { Error = -1; WSACleanup(); return;}
      #endif
      Error = 0;
 }
static TxSupportSockets SupportSockets;
//------------------------------------------------------------------------------
}
#pragma package(smart_init)
