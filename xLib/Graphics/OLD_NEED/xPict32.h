#ifndef xPict32H
#define xPict32H
#include "xGraphTypes.h"
#define MaxPictHeight 1000
//------------------------------------------------------------------------------
class TxProviderPict
 {
  protected:
   TxGraphColor*Buffer;
  public:
   int ShiftLines;
   dword Width, Height;
   TxGraphColor *Pixels[MaxPictHeight]; //Pixels[y][x] - опасная но быстрая операция
   void Init(dword iWidth,dword iHeight,void*iBuffer,int iShiftLines);
   void SetPixel(dword x,dword y,TxGraphColor c);
   TxGraphColor GetPixel(dword x,dword y);
   void Draw(int x,int y,TxProviderPict*p);
   void CopyRect(int x,int y,TxRect PictRect,TxProviderPict*p);
   void Bar(const TxRect&r,TxGraphColor c);
 };
//------------------------------------------------------------------------------
#endif
