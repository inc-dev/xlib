#ifndef AESH
#define AESH
// AES(Rijndael)
//------------------------------------------------------------------------------
#include "CriptSimplTypes.h"
#define MAXKC	(256/32)
#define MAXKB	(256/8)
#define MAXNR	14
//------------------------------------------------------------------------------
typedef struct
 {
  u32 ek[4*(MAXNR + 1)];
  u32 dk[4*(MAXNR + 1)];
 } AES_ctx;
//------------------------------------------------------------------------------
// key 32 байт или 32*8=256 бит
// BLOCKSIZE 16
void AES_key(AES_ctx *c, unsigned char *key);
void AES_enc(AES_ctx *c, unsigned char *inData, unsigned char *OutData, int blocks);
void AES_dec(AES_ctx *c, unsigned char *inData, unsigned char *OutData, int blocks);
//------------------------------------------------------------------------------
#endif
