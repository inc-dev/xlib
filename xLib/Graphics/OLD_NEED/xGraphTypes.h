//---------------------------------------------------------------------------

#ifndef xGraphTypesH
#define xGraphTypesH
//---------------------------------------------------------------------------
#include "xTypes.h"
#include "xGeometry.h"
class TxGraphFixFloat
 {
  public:
   int Value;
   TxGraphFixFloat(int iValue){Value = iValue;}
   inline int GetBeforePoint(){return Value>>8;}
   inline byte GetAfterPoint(){return Value&255;}
 };
union TxGraphColor
 {
  struct
   {
    byte B,G,R,A;
   }Detail;
   dword RGBA;
  TxGraphColor(){};
  TxGraphColor(dword iRGBA):RGBA(iRGBA){};
  TxGraphColor(byte iB,byte iG,byte iR,byte iA){Detail.B = iB;Detail.G = iG;Detail.R = iR;Detail.A = iA;}
 };
//уменьшение интенсивности в зависимости от A
#define Alpha(i, A) (((i&0xFF00FF00)>>8)*((A)+1)&0xFF00FF00|(((i&0x00FF00FF)*((A)+1))>>8)&0x00FF00FF)
//уменьшение интенсивности в зависимости от противоположной A(для подложки)
#define NegAlpha(i, A) ((((i&0xFF00FF00)>>8)*(256-(A)))&0xFF00FF00|(((i&0x00FF00FF)*(256-(A)))>>8)&0x00FF00FF)
//сравнение пикселей с определенной точностью
inline bool CompareGraphColor(TxGraphColor C1,TxGraphColor C2,byte Delta)
 {
   uint DeltaX2=Delta+Delta;
   return ((uint)((int)C1.Detail.B+Delta-(int)C2.Detail.B)<=DeltaX2 &&
           (uint)((int)C1.Detail.G+Delta-(int)C2.Detail.G)<=DeltaX2 &&
           (uint)((int)C1.Detail.R+Delta-(int)C2.Detail.R)<=DeltaX2 &&
           (uint)((int)C1.Detail.A+Delta-(int)C2.Detail.A)<=DeltaX2);
 }
inline bool qCompareGraphColor(TxGraphColor C1,TxGraphColor C2)
 {
//  return C1.RGBA==C2.RGBA;
/*   uint c1=(C1.RGBA&0xFEFEFEFE)>>1;   dword c2=(C2.RGBA&0xFEFEFEFE)>>1;
   c1+=0x01010101;
   c1-=c2;
   return (c1&0xFCFCFCFC)==0;*/
   //return (( ((C1.RGBA&0xFEFEFEFE)>>1)+0x01010101 - ((C2.RGBA&0xFEFEFEFE)>>1) )&0xFCFCFCFC)==0;
  return (( ((C1.RGBA&0xFCFCFCFC)>>2)+0x01010101 - ((C2.RGBA&0xFCFCFCFC)>>2) )&0xFCFCFCFC)==0; //7,11
 }
#endif

/*inline bool q3CompareGraphColor(TxGraphColor C1,TxGraphColor C2)
 {
   return
 !((uint8(int8(C1.Detail.R-C2.Detail.R)>int8(4))+
    uint8(int8(C2.Detail.R-C1.Detail.R)>int8(4))+
    uint8(int8(C1.Detail.G-C2.Detail.G)>int8(4))+
    uint8(int8(C2.Detail.G-C1.Detail.G)>int8(4))+
    uint8(int8(C1.Detail.B-C2.Detail.B)>int8(4))+
    uint8(int8(C2.Detail.B-C1.Detail.B)>int8(4))+
    uint8(int8(C1.Detail.A-C2.Detail.A)>int8(4))+
    uint8(int8(C2.Detail.A-C1.Detail.A)>int8(4)))>0);
 }    */
