////////////////////////////////////////////////////////////////////////////////
// GOST                                                                       //
//  Из книги Брюса Шнайдера Прикладная криптография                           //
////////////////////////////////////////////////////////////////////////////////
#ifndef GOSTH
#define GOSTH
//------------------------------------------------------------------------------
#include "CriptSimplTypes.h"
typedef struct
 {
  u32 k[8];
  char k87[256],k65[256],k43[256],k21[256];
 } gost_ctx;
//------------------------------------------------------------------------------
// key 32 байт или 32*8=256 бит
// BLOCKSIZE 8
void gost_key(gost_ctx *c, unsigned char *key);                         
void gost_enc(gost_ctx *c, unsigned char *inData, unsigned char *OutData, int blocks);
void gost_dec(gost_ctx *c, unsigned char *inData, unsigned char *OutData, int blocks);
//------------------------------------------------------------------------------
#endif
