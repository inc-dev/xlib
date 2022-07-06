#pragma hdrstop
#include "xSocketsTest.h"
//------------------------------------------------------------------------------
#include "..\..\Communication\xxSockets.h"
//------------------------------------------------------------------------------
using namespace XSPACE;
const char *SocketsTest()
 {
  TxTCPBlockingClient Client;
//  TxTCPBlockingServer Server;
//  Client.Host = "mancomp"; Client.Port = 3000;
  Client.Host = "192.168.0.34"; Client.Port = 1503;
  Client.Connect();
  return 0;
 }
//------------------------------------------------------------------------------
#pragma package(smart_init)
