#ifndef xxTypesH
#define xxTypesH
//--- определения типов -------------------------------------------------
typedef unsigned char      uint8;
typedef signed   char      int8;
//------------------------------------------------------------------------------
typedef unsigned short     uint16;
typedef signed   short     int16;
//------------------------------------------------------------------------------
typedef unsigned int       uint32;
typedef signed   int       int32;
//------------------------------------------------------------------------------
typedef signed long long   int64;
typedef unsigned long long uint64;
//--- общепринятые --------------------------------------------------------------
typedef uint8              byte;
typedef uint16             word;
typedef uint32             dword;
typedef unsigned int       uint;
//---------------------------------------------------------------------------

/*#ifdef __GNUC__
#else*/
#define UNUSED(x) (void)(x)
//inline void * operator new(uint, void *p) { return (p); }
//inline void * operator new[](uint, void *p) { return (p); }
#endif
