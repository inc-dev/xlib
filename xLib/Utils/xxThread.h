#ifndef xxThreadH
#define xxThreadH
//from material from Universal http://demin.ws/ streams in C + + for Windows and UNIX
#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <signal.h>
#endif
//------------------------------------------------------------------------------
namespace XSPACE
{
#ifdef _WIN32
typedef HANDLE ThreadType;
#else
typedef pthread_t ThreadType;
#endif
class TxThread
 {
  public:
   TxThread() {}
   virtual ~TxThread();
   void Start();
   virtual void Execute() = 0;
   void WaitStop();
   void Break();
  private:
   ThreadType __handle;
   TxThread(const TxThread&);
   void operator=(const TxThread&);
};
}
//------------------------------------------------------------------------------
#endif
