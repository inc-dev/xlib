////////////////////////////////////////////////////////////////////////////////
// IDEA                                                                       //
//  Из книги Брюса Шнайдера Прикладная криптография                           //
////////////////////////////////////////////////////////////////////////////////
#ifndef IDEAH
#define IDEAH
//------------------------------------------------------------------------------
#include "CriptSimplTypes.h"
#define IDEAKEYSIZE 16
#define IDEABLOCKSIZE 8
#define IDEAROUNDS 8
#define IDEAKEYLEN   (6*IDEAROUNDS+4)
//вспомогательная структура для хранения преобразованых
//ключей использующихся в шифрации и дешифрации
typedef struct
 {
  word16 ek[IDEAKEYLEN],dk[IDEAKEYLEN];
 } idea_ctx;
//------------------------------------------------------------------------------
// key 16 байт или 16*8=128 бит
// BLOCKSIZE 8
void idea_key(idea_ctx *c, unsigned char *key);                         
void idea_enc(idea_ctx *c, unsigned char *inData, unsigned char *OutData, int blocks);
void idea_dec(idea_ctx *c, unsigned char *inData, unsigned char *OutData, int blocks);
//------------------------------------------------------------------------------
#endif
