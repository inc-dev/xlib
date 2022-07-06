#pragma hdrstop
#include "RC6.h"
//------------------------------------------------------------------------------
#define MAX(x, y) ( ((x)>(y))?(x):(y) )
//надо оптимизировать
#define ROL(x, y) _lrotl(x, y)
#define ROR(x, y) _lrotr(x, y)
#define  BSWAP(x) (ROR(x, 8) & 0xFF00FF00)|(ROL (x, 8) & 0x00FF00FF)
//------------------------------------------------------------------------------
void rc6_key(rc6_ctx *ctx, unsigned char *key)
 {
  u32 L[64], S[50], A, B, i, j, v, s, t, l;
  /* copy the key into the L array */
  for (A = i = j = 0; i < keylen;)
   {
    A = (A << 8) | ((u32) (key[i++] & 255));
    if (!(i & 3)){L[j++] = BSWAP (A); A = 0;}
   }
  /* setup the S array,  fixed at 20 rounds */
  t = 44;  S[0] = 0xB7E15163UL;
  for (i = 1; i < t; i++)
   S[i] = S[i - 1] + 0x9E3779B9UL;
  /* mix buffer */
  s = 3 * MAX (t, j);   l = j;
  for (A = B = i = j = v = 0; v < s; v++)
    {
      A = S[i] = ROL (S[i] + A + B, 3);
      B = L[j] = ROL (L[j] + A + B, (A + B));
      i = (i + 1) % t;
      j = (j + 1) % l;
    }
  /* copy to key */
  for (i = 0; i < t; i++) ctx->skey[i] = S[i];
 }
//------------------------------------------------------------------------------
void crypt(rc6_ctx *ctx,u32 * pt)
 {
  u32 a, b, c, d, t, u;
  int r;
  u32 * skey = &ctx->skey[0];
  a = pt[0];
  b = pt[1];
  c = pt[2];
  d = pt[3];
  b += skey[0];
  d += skey[1];
  for (r = 0; r < 20; r++)
    {
      t = (b * (b + b + 1));
      t = ROL (t, 5);
      u = (d * (d + d + 1));
      u = ROL (u, 5);
      a = ROL (a ^ t, u) + skey[r + r + 2];
      c = ROL (c ^ u, t) + skey[r + r + 3];
      t = a;
      a = b;
      b = c;
      c = d;
      d = t;
    }
  a += skey[42];
  c += skey[43];
  pt[0] = a;
  pt[1] = b;
  pt[2] = c;
  pt[3] = d;
 }
//------------------------------------------------------------------------------
void decrypt(rc6_ctx *ctx,u32 * ct)
 {
  u32 a, b, c, d, t, u;
  int r;
  u32 * skey = &ctx->skey[0];
  a = ct[0];
  b = ct[1];
  c = ct[2];
  d = ct[3];
  a -= skey[42];
  c -= skey[43];
  for (r = 19; r >= 0; r--)
    {
      t = d;
      d = c;
      c = b;
      b = a;
      a = t;
      t = (b * (b + b + 1));
      t = ROL (t, 5);
      u = (d * (d + d + 1));
      u = ROL (u, 5);
      c = ROR (c - skey[r + r + 3], t) ^ u;
      a = ROR (a - skey[r + r + 2], u) ^ t;
    }
  b -= skey[0];
  d -= skey[1];
  ct[0] = a;
  ct[1] = b;
  ct[2] = c;
  ct[3] = d;
 }
//------------------------------------------------------------------------------
void rc6_enc(rc6_ctx *c, unsigned char *inData, unsigned char *OutData, int blocks)
 {
  u32 buf[4];
  for(int i=0;i<blocks;i++)
   {
    buf[0] = *((u32*)inData);
    inData+=4;
    buf[1] = *((u32*)inData);
    inData+=4;
    buf[2] = *((u32*)inData);
    inData+=4;
    buf[3] = *((u32*)inData);
    inData+=4;
    //------
    crypt(c,&buf[0]);
    //------    
    *((u32*)OutData) = buf[0];
    OutData+=4;
    *((u32*)OutData) = buf[1];
    OutData+=4;
    *((u32*)OutData) = buf[2];
    OutData+=4;
    *((u32*)OutData) = buf[3];
    OutData+=4;
   }
}
//------------------------------------------------------------------------------
void rc6_dec(rc6_ctx *c, unsigned char *inData, unsigned char *OutData, int blocks)
 {
  u32 buf[4];
  for(int i=0;i<blocks;i++)
   {
    buf[0] = *((u32*)inData);
    inData+=4;
    buf[1] = *((u32*)inData);
    inData+=4;
    buf[2] = *((u32*)inData);
    inData+=4;
    buf[3] = *((u32*)inData);
    inData+=4;
    //------
    decrypt(c,&buf[0]);
    //------
    *((u32*)OutData) = buf[0];
    OutData+=4;
    *((u32*)OutData) = buf[1];
    OutData+=4;
    *((u32*)OutData) = buf[2];
    OutData+=4;
    *((u32*)OutData) = buf[3];
    OutData+=4;
   }
 }
//------------------------------------------------------------------------------

#pragma package(smart_init)
