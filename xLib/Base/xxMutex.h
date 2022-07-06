#ifndef xxMutexH
#define xxMutexH
//Скопировано из http://demin.ws/blog/russian/2009/02/06/universal-mutex-in-cpp-for-windows-and-unix/
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

// Интерфейс класса Mutex.
// Класс задумывался как маленький и быстрый, поэтому все
// определено прямо в заголовочном файле, и все функции
// объявлены принудительно inline. Это должно уберечь
// от ошибок и предупреждений о двойных символах при
// включении mutex.h в несколько модулей.
class Mutex {
public:
  inline Mutex();
  // Деструктор объявлен как не виртуальный из-за тех же
  // соображений эффективности. Если вы планируете
  // наследоваться от этого класса, то лучше сделать
  // деструктор виртуальным, так как наследование от класса
  // с не виртуальным деструктором потенциально опасно
  // с точки зрения утечек памяти и является одним из
  // больших "no-no" в С++.
  inline ~Mutex();

  // Функция захвата блокировки (вход в комнату и запирание
  // двери ключом изнутри). 
  inline void Lock();

  // Функция освобождения блокировки (отпирание двери и
  // выход из комнаты)
  inline void Unlock();
private:
  MutexType __mutex;

  // Защита от случайного копирования объекта данного класса.
  // Экземпляр этого класса с трудом может быть нормально
  // скопирован, так как он жестко привязан к системному
  // ресурсу. 
  Mutex(const Mutex&);
  void operator=(const Mutex&);
};

#ifdef _WIN32

// Реализация через Windows API

Mutex::Mutex()             { InitializeCriticalSection(&__mutex); }
Mutex::~Mutex()            { DeleteCriticalSection(&__mutex); }
void Mutex::Lock()         { EnterCriticalSection(&__mutex); }
void Mutex::Unlock()       { LeaveCriticalSection(&__mutex); }

#else // WIN32

// UNIX версия через pthread

Mutex::Mutex()             { pthread_mutex_init(&__mutex, NULL); }
Mutex::~Mutex()            { pthread_mutex_destroy(&__mutex); }
void Mutex::Lock()         { pthread_mutex_lock(&__mutex); }
void Mutex::Unlock()       { pthread_mutex_unlock(&__mutex); }

#endif // WIN32
}
//------------------------------------------------------------------------------
#endif
