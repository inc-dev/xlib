#pragma hdrstop
#include "IDEA.h"
#include<mem.h>
#ifndef TRUE
#define FALSE 0
#define TRUE (!FALSE)
#endif
#ifndef min
#define min(a,b)   (   (a)<(b)   ?   (a)   :   (b)   )
#define max(a,b)   (   (a)>(b)   ?   (a)   :   (b)   )
#endif
#define low16(x)  ((x) & 0xFFFF)
typedef byte *byteptr;
//------------------------------------------------------------------------------
static uint16 mul(register uint16 a,   register uint16 b)
 {
   register word32 p;
   p =  (word32)a * b;
   if (p)
    {
     b = low16(p); a = p>>16;
     return   (b - a)   +   (b < a);
    } else
   if (a)
    { return 1-b; }
   else  {return 1-a;}
} /* mul */
//------------------------------------------------------------------------------
static uint16 mulInv(uint16 x)
 {
  uint16 t0, t1;
  uint16 q,  y;
  if (x <= 1) return x;
  t1 = 0x10001L / x;
  y = 0x10001L % x;
  if (y == 1)return low16(1-t1);
  t0 = 1;
  do{
   q = x / y; x = x % y; t0 += q * t1;
   if (x == 1)return t0;
   q = y / x; y = y % x; t1 += q * t0;
  } while (y != 1);
  return low16(1-t1);
 }   /* mukInv */
//------------------------------------------------------------------------------
static void ideaExpandKey(byte const *userkey,  word16 *EK)
 {
  int i,j;
  for(j=0;j<8;j++)
   {
    EK[j] = (userkey[0]<<8)+userkey[1];
    userkey += 2;
   }
  for(i=0; j<IDEAKEYLEN;j++)
   {
    i++;
    EK[i+7]   = EK[i & 7]   <<  9   |   EK[i+1 & 7]   >> 7;
    EK += i & 8;
    i &= 7;
   }
 }   /*  ideaExpandKey */
//------------------------------------------------------------------------------
static void ideaInvertKey(word16 const *EK, word16 DK[IDEAKEYLEN])
 {
  int i;
  uint16 t1,  t2,  t3;
  word16 temp[IDEAKEYLEN];
  word16 *p = temp + IDEAKEYLEN;
  t1 = mulInv(*EK++);
  t2 = -*EK++;
  t3 = -*EK++;
  *--p = mulInv(*EK++);
  *--p = t3;
  *--p = t2;
  *--p = t1;
  for(i = 0; i < IDEAROUNDS-1;i++)
   {
    t1 = *EK++;
    *--p = *EK++;
    *--p = t1;
    t1 = mulInv(*EK++);
    t2 = -*EK++;
    t3 = -*EK++;
    *--p = mulInv(*EK++);
    *--p = t2;
    *--p = t3;
    *--p = t1;
   }
  t1 = *EK++;
  *--p = *EK++;
  *--p = t1;
  t1 = mulInv(*EK++);
  t2 = -*EK++;
  t3 = -*EK++;
  *--p = mulInv(*EK++);
  *--p = t3;
  *--p = t2;
  *--p = t1;
  memcpy(DK, temp, sizeof(temp));
//  for(i=0;i<IDEAKEYLEN;i++)temp[i]=0;
 }   /*  ideaInvertKey */
//------------------------------------------------------------------------------
#define MUL(x,y)  (x = mul(low16(x),y))
static void ideaCipher(byte *inbuf,  byte *outbuf,  word16 *key)
 {
  register uint16 x1,  x2,  x3,  x4,   s2,   s3; word16 *in,   *out;
  register uint16 t16;
  register word32 t32;
  int r = IDEAROUNDS;
  in =   (word16 *)inbuf; x1 = *in++;    x2 = *in++; x3 = *in++;    x4 = *in;
  do
   {
    MUL(x1,*key++);
    x2 += *key++;
    x3 += *key++;
    MUL(x4,   *key++);
    s3 = x3;
    x3 ^= x1;
    MUL(x3,   *key++);
    s2 = x2;
    x2 ^= x4;
    x2 += x3;
    MUL(x2,   *key++);
    x3 += x2;
    x1 ^= x2;  x4 ^= x3;
    x2 ^= s3;  x3 ^= s2;
   } while (--r);
  MUL(x1,   *key++);
  x3 += *key++;
  x2 += *key++;
  MUL(x4, *key);
  out =   (word16 *)outbuf;
  *out++ = x1;
  *out++ = x3;
  *out++ = x2;
  *out = x4;
}   /*  ideaCipher */
//------------------------------------------------------------------------------
void idea_key(idea_ctx *c,  unsigned char *key)
 {
  ideaExpandKey(key,c->ek);
  ideaInvertKey(c->ek,c->dk);
 }
//------------------------------------------------------------------------------
void idea_enc(idea_ctx *c, unsigned char *inData, unsigned char *OutData, int blocks)
 {
  for(int i=0;i<blocks;i++)
   {
    ideaCipher(inData,OutData,c->ek);
    inData+=8;
    OutData+=8;
   }
}
//------------------------------------------------------------------------------
void idea_dec(idea_ctx *c, unsigned char *inData, unsigned char *OutData, int blocks)
 {
  for(int i=0;i<blocks;i++)
   {
    ideaCipher(inData,OutData,c->dk);
    inData+=8;
    OutData+=8;
   }
 }
//------------------------------------------------------------------------------ 
#pragma package(smart_init)
