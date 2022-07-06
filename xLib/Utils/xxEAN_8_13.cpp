#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxEAN_8_13.h"
const unsigned char  A=0,B=1,C=2;
const unsigned char	M[3][10] = {
  {0x0D, 0x19, 0x13, 0x3D, 0x23, 0x31, 0x2F, 0x3B, 0x37, 0x0B},	// A
  {0x27, 0x33, 0x1B, 0x21, 0x1D, 0x39, 0x05, 0x11, 0x09, 0x17},	// B
  {0x72, 0x66, 0x6C, 0x42, 0x5C, 0x4E, 0x50, 0x44, 0x48, 0x74}	// C
  };
const unsigned char MM[10][12] = { //для EAN13
     {A,A,A,A,A,A,C,C,C,C,C,C}, //0
     {A,A,B,A,B,B,C,C,C,C,C,C}, //1
     {A,A,B,B,A,B,C,C,C,C,C,C}, //2
     {A,A,B,B,B,A,C,C,C,C,C,C}, //3
     {A,B,A,A,B,B,C,C,C,C,C,C}, //4
     {A,B,B,A,A,B,C,C,C,C,C,C}, //5
     {A,B,B,B,A,A,C,C,C,C,C,C}, //6
     {A,B,A,B,A,B,C,C,C,C,C,C}, //7
     {A,B,A,B,B,A,C,C,C,C,C,C}, //8
     {A,B,B,A,B,A,C,C,C,C,C,C}  //9
};
void AddbitsToBuf(unsigned char*des,unsigned char source,int&NumBit,int CountBitLine,int Bits=7)
 {
    for(int i=Bits-1;i>=0;i--)
     for(int j=0;j<CountBitLine;j++)
      {
       if((source>>i)&1)des[NumBit>>3]|=1<<(7-(NumBit&7));
       NumBit++;
      }
 }
void DecodeEAN13(unsigned char*des,unsigned char*s,int CountBitLine,int SkipBitForBegin)
 {//95bit
  //----- контрольная сумма ---------------------------------
  unsigned char CONTROL=(s[1]+s[3]+s[5]+s[7]+s[9]+s[11])*3+s[0]+s[2]+s[4]+s[6]+s[8]+s[10];
  CONTROL = 10*long((CONTROL+9)/10)-CONTROL;
  s[12]=CONTROL;
  //----- перекодировка -------------------------------------
  unsigned char source[12];
  for(int i=0;i<=11;i++)
   source[i]=M[MM[s[0]][i]][s[i+1]];
  //----- внесение бит --------------------------------------
  for(int i=0;i<12*CountBitLine;i++) des[i]=0;//очистка буфера
  int NumBit=SkipBitForBegin&7;
  unsigned char term=5;
  AddbitsToBuf(des,term,NumBit,CountBitLine,3);
  for(int i=0;i<6;i++)
   AddbitsToBuf(des,source[i],NumBit,CountBitLine,7);
  term=10;
  AddbitsToBuf(des,term,NumBit,CountBitLine,5);
  for(int i=6;i<12;i++)
   AddbitsToBuf(des,source[i],NumBit,CountBitLine,7);
  term=5;
  AddbitsToBuf(des,term,NumBit,CountBitLine,3);
  //---------------------------------------------------------
 }
void DecodeEAN13_(unsigned char*des,int CountBitLine,int SkipBitForBegin)
 {
  for(int i=0;i<12*CountBitLine;i++) des[i]=0;//очистка буфера
  int NumBit=SkipBitForBegin&7;
  unsigned char term=5;
  AddbitsToBuf(des,term,NumBit,CountBitLine,3);
  NumBit+=6*7*CountBitLine;
  term=10;
  AddbitsToBuf(des,term,NumBit,CountBitLine,5);
  NumBit+=6*7*CountBitLine;
  term=5;
  AddbitsToBuf(des,term,NumBit,CountBitLine,3);
  //---------------------------------------------------------
 }

//------------------------------------------------------------------
void DecodeEAN8(unsigned char*des,unsigned char*s,int CountBitLine,int SkipBitForBegin)
 {//67bit
  //----- контрольная сумма ---------------------------------
  unsigned char CONTROL=s[1]+s[3]+s[5]+(s[0]+s[2]+s[4]+s[6])*3;
  CONTROL = 10*int((CONTROL+9)/10)-CONTROL;
  s[7]=CONTROL;
  //----- перекодировка -------------------------------------
  unsigned char source[7];
  for(int i=0;i<4;i++)
   source[i]=M[A][s[i]];
  for(int i=4;i<8;i++)
   source[i]=M[C][s[i]];
  //----- внесение бит --------------------------------------
  for(int i=0;i<9*CountBitLine;i++) des[i]=0;//очистка буфера
  int NumBit=SkipBitForBegin&7;
  unsigned char term=5;
  AddbitsToBuf(des,term,NumBit,CountBitLine,3);
  for(int i=0;i<4;i++)
   AddbitsToBuf(des,source[i],NumBit,CountBitLine,7);
  term=10;
  AddbitsToBuf(des,term,NumBit,CountBitLine,5);
  for(int i=4;i<8;i++)
   AddbitsToBuf(des,source[i],NumBit,CountBitLine,7);
  term=5;
  AddbitsToBuf(des,term,NumBit,CountBitLine,3);
 }
//------------------------------------------------------------------
void DecodeEAN8_(unsigned char*des,int CountBitLine,int SkipBitForBegin)
 {
  for(int i=0;i<9*CountBitLine;i++) des[i]=0;//очистка буфера
  int NumBit=SkipBitForBegin&7;
  unsigned char term=5;
  AddbitsToBuf(des,term,NumBit,CountBitLine,3);
  NumBit+=4*7*CountBitLine;
  term=10;
  AddbitsToBuf(des,term,NumBit,CountBitLine,5);
  NumBit+=4*7*CountBitLine;
  term=5;
  AddbitsToBuf(des,term,NumBit,CountBitLine,3);
 }

#ifndef __GNUC__
#pragma package(smart_init)
#endif
