#pragma hdrstop
#include "xxThread.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
static void ThreadCallback(TxThread* who)
 {
  #ifndef _WIN32
  // Make a thread to "kill" a pthread_cancel.
  int old_thread_type;
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &old_thread_type);
  #endif
  who->Execute();
 }

#ifdef _WIN32

TxThread::~TxThread()
 {
  CloseHandle(__handle);
 }
void TxThread::Start()
 {
  __handle = CreateThread(0, 0,reinterpret_cast<LPTHREAD_START_ROUTINE>(ThreadCallback), this,0, 0);
 }
void TxThread::WaitStop()
 {
  WaitForSingleObject(__handle,  INFINITE);
 }

void TxThread::Break()
 {
  TerminateThread(__handle, 0);
 }
#else                        
extern "C"               
typedef void *(*pthread_callback)(void *);
void TxThread::Start()
 {
  pthread_create(&__handle, 0,reinterpret_cast<pthread_callback>(ThreadCallback),this);
 }
void TxThread::WaitStop()
 {                              
  pthread_join(__handle, 0);
 }
                             
void TxThread::Break()
 {
  pthread_cancel(__handle);
 }
#endif
}
//------------------------------------------------------------------------------
#pragma package(smart_init)
