#pragma hdrstop
#include "xPict32.h"
//------------------------------------------------------------------------------
void TxProviderPict::Init(dword iWidth,dword iHeight,void*iBuffer,int iShiftLines)
 {
  Width = iWidth;  Height = iHeight;
  Buffer = (TxGraphColor*)iBuffer;  ShiftLines = iShiftLines;
  if(Height>MaxPictHeight)Height = MaxPictHeight;
  for(dword i=0;i<Height;i++)
   {
    Pixels[i]=(TxGraphColor*)iBuffer;
    iBuffer = (char*)iBuffer + iShiftLines;
   }
 }
//------------------------------------------------------------------------------
void TxProviderPict::SetPixel(dword x,dword y,TxGraphColor c)
 {
  if(x>=Width||y>=Height)return;
  Pixels[y][x] = c;
 }
//------------------------------------------------------------------------------
TxGraphColor TxProviderPict::GetPixel(dword x,dword y)
 {
  if(x>=Width||y>=Height)
   {
    TxGraphColor r; r.RGBA = 0;
    return r;
   }
  return Pixels[y][x];
 }
//------------------------------------------------------------------------------
void TxProviderPict::Draw(int x,int y,TxProviderPict*p)
 {
  if(p)CopyRect(x,y,TxRect(0,0,p->Width-1,p->Height-1),p);
 }
//------------------------------------------------------------------------------
void TxProviderPict::CopyRect(int x,int y, TxRect PictRect,TxProviderPict*p)
 {
  if(!p)return;
  dword FromX = 0,FromY = 0;
  //- скорректировали PictRect
  if(PictRect.X1<0){x+=PictRect.X1;PictRect.X1=0;}
  if(PictRect.Y1<0){y+=PictRect.Y1;PictRect.Y1=0;}
  if(PictRect.X2>=(int)p->Width)PictRect.X2=p->Width-1;
  if(PictRect.Y2>=(int)p->Height)PictRect.Y2=p->Height-1;
  //- ровняем левую вернюю части
  if(x>0)FromX = x;
  else {PictRect.X1=PictRect.X1-x;}
  if(y>0)FromY = y;
  else {PictRect.Y1=PictRect.Y1-y;}
  //- ровняем правую нижнюю части 
  if(FromX+PictRect.X2>=Width)PictRect.X2 = Width - FromX-1;
  if(FromY+PictRect.Y2>=Height)PictRect.Y2 = Height - FromY-1;
  //- проверяем вырохженность
  int ToX = PictRect.X2-PictRect.X1,ToY = PictRect.Y2-PictRect.Y1;
  if(ToX<=0||ToY<=0)return;
  //- рисуем -
  ToY = FromY+ToY;
  for(;FromY<=(dword)ToY;FromY++)
   {
    TxGraphColor *Line=&Pixels[FromY][FromX];
    TxGraphColor *LineTo=Line+ToX;
    TxGraphColor *LinePict=&p->Pixels[PictRect.Y1][PictRect.X1];
    //- линия
    for(;Line<=LineTo;Line++,LinePict++)
      Line->RGBA = LinePict->RGBA+NegAlpha(Line->RGBA,LinePict->Detail.A);
    PictRect.Y1++;
   }
 }
//------------------------------------------------------------------------------
void TxProviderPict::Bar(const TxRect&r,TxGraphColor c)
 {
   if(r.X2<0||r.Y2<0)return;
   dword FromX = 0,FromY = 0;
   dword ToX,ToY;
   if(r.X1>=0)FromX = r.X1;
   if(r.Y1>=0)FromY = r.Y1;
   if((dword)r.X2>=Width)ToX=Width-1;else ToX=r.X2;
   if((dword)r.Y2>=Height)ToY=Height-1;else ToY=r.Y2;
   ToX = ToX-FromX;
   if(c.Detail.A==255)
    {
     for(dword y=FromY;y<=ToY;y++)
      {
      TxGraphColor *Line=&Pixels[y][FromX];
      TxGraphColor *LineTo=Line+ToX;
      for(;Line<=LineTo;Line++) *Line=c;
      }
    }else
    {
     byte A = c.Detail.A;
     for(dword y=FromY;y<=ToY;y++)
      {
       TxGraphColor *Line=&Pixels[y][FromX];
       TxGraphColor *LineTo=Line+ToX;
        for(;Line<=LineTo;Line++)
         Line->RGBA = c.RGBA+NegAlpha(Line->RGBA,A);
      }
    }
 }
//------------------------------------------------------------------------------
#pragma package(smart_init)
