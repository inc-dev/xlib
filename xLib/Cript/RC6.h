#ifndef RC6H
#define RC6H
#include <stdlib.h>
//------------------------------------------------------------------------------
#include "CriptSimplTypes.h"
#define num_rounds 20
#define keylen 64
//------------------------------------------------------------------------------
typedef struct
 {
  u32 skey[44];
 } rc6_ctx;
//------------------------------------------------------------------------------
// key 64 байт или 64*8=512 бит
// BLOCKSIZE 16
void rc6_key(rc6_ctx *c, unsigned char *key);                         
void rc6_enc(rc6_ctx *c, unsigned char *inData, unsigned char *OutData, int blocks);
void rc6_dec(rc6_ctx *c, unsigned char *inData, unsigned char *OutData, int blocks);
//------------------------------------------------------------------------------
#endif
