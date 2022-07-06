#ifndef xxMutexH
#define xxMutexH
//����������� �� http://demin.ws/blog/russian/2009/02/06/universal-mutex-in-cpp-for-windows-and-unix/
//------------------------------------------------------------------------------
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#include <windows.h>
#else
#include <stdlib.h>
#include <pthread.h>
#endif
namespace XSPACE
{

#ifdef _WIN32
  typedef CRITICAL_SECTION MutexType;
#else
  typedef pthread_mutex_t MutexType;
#endif

// ��������� ������ Mutex.
// ����� ����������� ��� ��������� � �������, ������� ���
// ���������� ����� � ������������ �����, � ��� �������
// ��������� ������������� inline. ��� ������ �������
// �� ������ � �������������� � ������� �������� ���
// ��������� mutex.h � ��������� �������.
class Mutex {
public:
  inline Mutex();
  // ���������� �������� ��� �� ����������� ��-�� ��� ��
  // ����������� �������������. ���� �� ����������
  // ������������� �� ����� ������, �� ����� �������
  // ���������� �����������, ��� ��� ������������ �� ������
  // � �� ����������� ������������ ������������ ������
  // � ����� ������ ������ ������ � �������� ����� ��
  // ������� "no-no" � �++.
  inline ~Mutex();

  // ������� ������� ���������� (���� � ������� � ���������
  // ����� ������ �������). 
  inline void Lock();

  // ������� ������������ ���������� (��������� ����� �
  // ����� �� �������)
  inline void Unlock();
private:
  MutexType __mutex;

  // ������ �� ���������� ����������� ������� ������� ������.
  // ��������� ����� ������ � ������ ����� ���� ���������
  // ����������, ��� ��� �� ������ �������� � ����������
  // �������. 
  Mutex(const Mutex&);
  void operator=(const Mutex&);
};

#ifdef _WIN32

// ���������� ����� Windows API

Mutex::Mutex()             { InitializeCriticalSection(&__mutex); }
Mutex::~Mutex()            { DeleteCriticalSection(&__mutex); }
void Mutex::Lock()         { EnterCriticalSection(&__mutex); }
void Mutex::Unlock()       { LeaveCriticalSection(&__mutex); }

#else // WIN32

// UNIX ������ ����� pthread

Mutex::Mutex()             { pthread_mutex_init(&__mutex, NULL); }
Mutex::~Mutex()            { pthread_mutex_destroy(&__mutex); }
void Mutex::Lock()         { pthread_mutex_lock(&__mutex); }
void Mutex::Unlock()       { pthread_mutex_unlock(&__mutex); }

#endif // WIN32
}
//------------------------------------------------------------------------------
#endif
