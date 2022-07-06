////////////////////////////////////////////////////////////////////////////////
//the book C + + Templates, authors David and Nicholas Vandevurd M.Dzhosatis
////////////////////////////////////////////////////////////////////////////////
#ifndef xxTypeInfoH
#define xxTypeInfoH
#include"xxTypes.h"
#include<stddef.h>
//------------------------------------------------------------------------------
#define STATIC_CHECK(condition) { char dummy[ (condition)  ? 1 : 0]; (void)(dummy);}
enum TxStaticTypeInfo{xTypeUnDef, xTypeSimple,xTypeStaticPtr, xTypeStaticArray,xTypeStaticRef,xTypeStaticClassPtr,xTypeStaticClass};
template<typename T>
struct xGetTypeInfo{enum{Type=xTypeUnDef};};
#define REG_SIMPLE_TYPE(T) template<>struct xGetTypeInfo<T>{enum{Type=xTypeSimple}; };
//------------------------------
REG_SIMPLE_TYPE(bool)
REG_SIMPLE_TYPE(         char)
REG_SIMPLE_TYPE(signed   char)
REG_SIMPLE_TYPE(unsigned char)
REG_SIMPLE_TYPE(signed   short)
REG_SIMPLE_TYPE(unsigned short)
REG_SIMPLE_TYPE(signed   int)
REG_SIMPLE_TYPE(unsigned int)
REG_SIMPLE_TYPE(signed   long)
REG_SIMPLE_TYPE(unsigned long)
REG_SIMPLE_TYPE(         int64)
REG_SIMPLE_TYPE(         uint64)
REG_SIMPLE_TYPE(float)
REG_SIMPLE_TYPE(double)
REG_SIMPLE_TYPE(long double)
#undef REG_SIMPLE_TYPE
//------------------------------
#if defined(_WIN32_WCE)
#define REG_POINT_TYPE(T) template<>struct xGetTypeInfo<T>{enum{Type=xTypeStaticPtr}; };
REG_POINT_TYPE(void*)
REG_POINT_TYPE(bool*)
REG_POINT_TYPE(         char*)
REG_POINT_TYPE(signed   char*)
REG_POINT_TYPE(unsigned char*)
REG_POINT_TYPE(signed   short*)
REG_POINT_TYPE(unsigned short*)
REG_POINT_TYPE(signed   int*)
REG_POINT_TYPE(unsigned int*)
REG_POINT_TYPE(signed   long*)
REG_POINT_TYPE(unsigned long*)
REG_POINT_TYPE(         int64*)
REG_POINT_TYPE(         uint64*)
REG_POINT_TYPE(float*)
REG_POINT_TYPE(double*)
REG_POINT_TYPE(long double*)
#undef REG_POINT_TYPE
//------------------------------
#else
template<typename T>
struct xGetTypeInfo<T[]>{enum{Type=xTypeStaticArray};};
//------------------------------
template<typename T>
struct xGetTypeInfo<T*>{enum{Type=xTypeStaticPtr};};
//------------------------------
template<typename T>
struct xGetTypeInfo<T&>{enum{Type=xTypeStaticRef};};
//------------------------------
template<typename T,typename C>
struct xGetTypeInfo<T C::*>{enum{Type=xTypeStaticClassPtr};};
//------------------------------
template<typename T>
struct xGetStaticArraySize {enum{Count=0};};
//------------------------------
template<typename T,int N>
struct xGetStaticArraySize<T[N]>{enum{Count=N};};
//------------------------------
#endif
//------------------------------
template<typename T> struct xIsStringItem      {enum{Yes=0};};
template<> struct xIsStringItem<         char> {enum{Yes=1};};
template<> struct xIsStringItem<signed   short>{enum{Yes=1};};
template<> struct xIsStringItem<unsigned short>{enum{Yes=1};};
template<> struct xIsStringItem<signed   int>  {enum{Yes=1};};
template<> struct xIsStringItem<unsigned int>  {enum{Yes=1};};
///------------------------------
template<typename T> struct xIsChar{enum{Yes=0};};
template<> struct xIsChar<char>    {enum{Yes=1};};
///------------------------------
template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];
#define arraysize(array) (sizeof(ArraySizeHelper(array)))
///------------------------------
#endif
