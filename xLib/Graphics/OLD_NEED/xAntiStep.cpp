#pragma hdrstop
#include "xAntiStep.h"
#include "xGraphTypes.h"
#define  HalfAlpha 128

inline int LineInBorder(TxGraphColor*fon,TxGraphColor*line,int MaxCount)
 {
  int Count=1;
  TxGraphColor c=*line; fon++;line++;
  while(MaxCount>=Count&&qCompareGraphColor(c,*line)&&!qCompareGraphColor(*fon,*line))
   {
    Count++;
    c=*line;
    fon++;line++;
   }
  return  Count;
 }
void CorrectLine(TxGraphColor*Template,TxGraphColor*TemplateThis,TxGraphColor*Line,byte Afrom,byte Ato,int count)
 {
  int A=Afrom<<16,dA=((Ato<<16)-A)/count;
  for (int i=0;i<count;i++)
   {
    Line->RGBA=Alpha(Template->RGBA, (A>>16))+NegAlpha(TemplateThis->RGBA,(A>>16));
    Line++;
    Template++;
    TemplateThis++;
    A+=dA;
   }
 }
void LineDeleteStepInUpBorder(int Y,TxProviderPict&d,TxProviderPict&s)
 {
  TxGraphColor LastPixel=s.Pixels[Y][0];
  int X=1; int LeftCount=0,CountRight;
  while(X<d.Width-1)
   {
     if(!qCompareGraphColor(s.Pixels[Y-1][X],s.Pixels[Y][X])&&qCompareGraphColor(LastPixel,s.Pixels[Y][X]))
      {
       int CountLeft=LineInBorder(&s.Pixels[Y-1][X],&s.Pixels[Y][X],d.Width-X-2-2);
       if(CountLeft>1)
        {
         if(qCompareGraphColor(s.Pixels[Y-1][X+CountLeft],s.Pixels[Y][X+CountLeft-1])&&!qCompareGraphColor(s.Pixels[Y-1][X+CountLeft],s.Pixels[Y-2][X+CountLeft]))
          { //вверх
           CountRight=LineInBorder(&s.Pixels[Y-2][X+CountLeft],&s.Pixels[Y-1][X+CountLeft],d.Width-X-2-CountLeft);
           if(CountRight>1)
            {
             X+=CountLeft;
             CorrectLine(&s.Pixels[Y][X-1-CountLeft/2],&s.Pixels[Y-1][X-1-CountLeft/2],&d.Pixels[Y-1][X-1-CountLeft/2],0,HalfAlpha,CountLeft/2+1);
             CorrectLine(&s.Pixels[Y-2][X],&s.Pixels[Y-1][X],&d.Pixels[Y-1][X],HalfAlpha,0,CountRight/2+1);
            }
          }else
         if(qCompareGraphColor(s.Pixels[Y+1][X+CountLeft],s.Pixels[Y][X+CountLeft-1])&&!qCompareGraphColor(s.Pixels[Y+1][X+CountLeft],s.Pixels[Y][X+CountLeft]))
          { //вниз
           CountRight=LineInBorder(&s.Pixels[Y][X+CountLeft],&s.Pixels[Y+1][X+CountLeft],d.Width-X-2-2-CountLeft);
           if(CountRight>1)
            {
             X+=CountLeft;
//            void CorrectLine(TxGraphColor*Template,TxGraphColor*TemplateThis,TxGraphColor*Line,byte Afrom,byte Ato,int count)
             CorrectLine(&s.Pixels[Y-1][X-1-CountLeft/2],&s.Pixels[Y][X-1-CountLeft/2],&d.Pixels[Y][X-1-CountLeft/2],0,HalfAlpha,CountLeft/2+1);
             CorrectLine(&s.Pixels[Y][X],&s.Pixels[Y+1][X],&d.Pixels[Y][X],HalfAlpha,255,CountRight/2+1);
            }

          }else X+=CountLeft;
        }
      }
     X++;
    LastPixel=s.Pixels[Y][X];
   }
 }
void LineDeleteStepInDownBorder(int Y,TxProviderPict&d,TxProviderPict&s)
 {
  TxGraphColor LastPixel=s.Pixels[Y][0];
  int X=1; int LeftCount=0,CountRight;
  while(X<d.Width-1)
   {
     if(!qCompareGraphColor(s.Pixels[Y+1][X],s.Pixels[Y][X])&&qCompareGraphColor(LastPixel,s.Pixels[Y][X]))
      {
       int CountLeft=LineInBorder(&s.Pixels[Y+1][X],&s.Pixels[Y][X],d.Width-X-2-2);
       if(CountLeft>1)
        {
         if(qCompareGraphColor(s.Pixels[Y+1][X+CountLeft],s.Pixels[Y][X+CountLeft-1])&&!qCompareGraphColor(s.Pixels[Y+1][X+CountLeft],s.Pixels[Y+2][X+CountLeft]))
          { //вниз
           CountRight=LineInBorder(&s.Pixels[Y+2][X+CountLeft],&s.Pixels[Y+1][X+CountLeft],d.Width-X-2-2-CountLeft);
           if(CountRight>1)
            {
             X+=CountLeft;
             CorrectLine(&s.Pixels[Y+1][X-1-CountLeft/2],&s.Pixels[Y][X-1-CountLeft/2],&d.Pixels[Y+1][X-1-CountLeft/2],255,HalfAlpha,CountLeft/2+1);
             CorrectLine(&s.Pixels[Y+2][X],&s.Pixels[Y+1][X],&d.Pixels[Y+1][X],HalfAlpha,0,CountRight/2+1);
            }
          }else
         if(qCompareGraphColor(s.Pixels[Y-1][X+CountLeft],s.Pixels[Y][X+CountLeft-1])&&!qCompareGraphColor(s.Pixels[Y-1][X+CountLeft],s.Pixels[Y][X+CountLeft]))
          { //вверх
           CountRight=LineInBorder(&s.Pixels[Y][X+CountLeft],&s.Pixels[Y-1][X+CountLeft],d.Width-X-2-CountLeft);
           if(CountRight>1)
            {
             X+=CountLeft;
      //void CorrectLine(TxGraphColor*Template,TxGraphColor*TemplateThis,TxGraphColor*Line,byte Afrom,byte Ato,int count)
             CorrectLine(&s.Pixels[Y+1][X-1-CountLeft/2],&s.Pixels[Y][X-1-CountLeft/2],&d.Pixels[Y][X-1-CountLeft/2],0,HalfAlpha,CountLeft/2+1);
             CorrectLine(&s.Pixels[Y][X],&s.Pixels[Y-1][X],&d.Pixels[Y][X],HalfAlpha,255,CountRight/2+1);
            }
          }else X+=CountLeft;
        }
      }
     X++;
    LastPixel=s.Pixels[Y][X];
   }
 }
void xDeleteSteps(TxProviderPict&d,TxProviderPict&s)
 {
    //DeleteStepInUpBorder
   for(int Y=3;Y<d.Height-3;Y++)
      LineDeleteStepInUpBorder(Y,d,s);

    //DeleteStepInBottomBorder
   for(int Y=3;Y<d.Height-3;Y++)
      LineDeleteStepInDownBorder(Y,d,s);

   //DeleteStepInLeftBorder
   //DeleteStepInRightBorder
 }

#pragma package(smart_init)

