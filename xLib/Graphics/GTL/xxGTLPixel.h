#ifndef xxGTLPixelH
#define xxGTLPixelH
#include "xxTypes.h"
namespace GTL
{
template<class iTypeItem>
 struct TxAbstractPixel{ typedef iTypeItem TypeItem;};
template<class iTypeItem>
 struct TxPixelRGBA:public TxAbstractPixel<iTypeItem>{  iTypeItem B,G,R,A; };
template<class iTypeItem>
 struct TxPixelRGB:public TxAbstractPixel<iTypeItem> {  iTypeItem B,G,R;   };
template<class iTypeItem>
 struct TxPixelGray:public TxAbstractPixel<iTypeItem>{  iTypeItem Value;   };
template<class iTypeItem>
 struct TxPixelCMYK:public TxAbstractPixel<iTypeItem>{  iTypeItem C,M,Y,K; };
template<class iTypeItem>
 struct TxPixelCMY:public TxAbstractPixel<iTypeItem> {  iTypeItem C,M,Y; };
//-------------------------------------
typedef TxPixelRGBA<byte> TxPixelRGBA8;
typedef TxPixelRGB <byte> TxPixelRGB8;
typedef TxPixelGray<byte> TxPixelGray8;
//-------------------------------------
typedef TxPixelRGBA<word> TxPixelRGBA16;
typedef TxPixelRGB <word> TxPixelRGB16;
typedef TxPixelGray<word> TxPixelGray16;
//-------------------------------------
typedef TxPixelRGBA<float> TxPixelRGBA_F;
typedef TxPixelRGB <float> TxPixelRGB_F;
typedef TxPixelGray<float> TxPixelGray_F;
//-------------------------------------
/*template<class iTypeItem1,class iTypeItem2>
inline void DecodePixel(TxPixelRGBA<iTypeItem1> & dPixel ,const TxPixelRGBA<iTypeItem2> & sPixel)
 {dPixel.B = sPixel.B;dPixel.G = sPixel.G;dPixel.R = sPixel.R;dPixel.A = sPixel.A;};
template<class iTypeItem1,class iTypeItem2>
inline void DecodePixel(TxPixelRGB<iTypeItem1> & dPixel ,const TxPixelRGB<iTypeItem2> & sPixel)
 {dPixel.B = sPixel.B;dPixel.G = sPixel.G;dPixel.R = sPixel.R;};
template<class iTypeItem1,class iTypeItem2>
inline void DecodePixel(TxPixelRGB<iTypeItem1> & dPixel ,const TxPixelRGBA<iTypeItem2> & sPixel)
 {dPixel.B = sPixel.B;dPixel.G = sPixel.G;dPixel.R = sPixel.R;};
template<class iTypeItem1,class iTypeItem2>
inline void DecodePixel(TxPixelRGBA<iTypeItem1> & dPixel ,const TxPixelRGB<iTypeItem2> & sPixel)
 {dPixel.B = sPixel.B;dPixel.G = sPixel.G;dPixel.R = sPixel.R; dPixel.A = 255;};
//позже добавить коеффициенты
template<class iTypeItem1,class iTypeItem2>
inline void DecodePixel(TxPixelRGBA<iTypeItem1> & dPixel ,const TxPixelGray<iTypeItem2> & sPixel)
 {dPixel.B = sPixel.Value;dPixel.G = sPixel.Value;dPixel.R = sPixel.Value; dPixel.A = 255;};
template<class iTypeItem1,class iTypeItem2>
inline void DecodePixel(TxPixelRGB<iTypeItem1> & dPixel ,const TxPixelGray<iTypeItem2> & sPixel)
 {dPixel.B = sPixel.Value;dPixel.G = sPixel.Value;dPixel.R = sPixel.Value; };
template<class iTypeItem1,class iTypeItem2>
inline void DecodePixel(TxPixelGray<iTypeItem1> & dPixel ,const TxPixelRGB<iTypeItem2> & sPixel)
 { dPixel.Value = (sPixel.B+sPixel.G+sPixel.R)/3;};
//позже cmyk                                       */

//fixed point for item calc
template<class iTypeItem>
 struct FractionWrap
  {
  };
template<>
 struct FractionWrap<byte>
  {
     inline byte & Value(){return *((byte*)(&WrapValue)+2);}
     inline void Clear(){WrapValue = 0;};     
     inline void Add(FractionWrap<byte> a){WrapValue+=a.WrapValue;}
     inline void Sub(FractionWrap<byte> a){WrapValue-=a.WrapValue;}
     inline void Divide(int Count){WrapValue/=Count;};
     inline void Multiplication(int Count){WrapValue*=Count;};
     inline FractionWrap(const byte & a){Clear();Value() = a;}
     inline FractionWrap(){Clear();}    
    protected:
     int WrapValue;
  };
template<>
 struct FractionWrap<word>
  {
     inline word & Value(){return *((word*)(&WrapValue)+2);}
     inline void Clear(){WrapValue = 0;};     
     inline void Add(FractionWrap<word> a){WrapValue+=a.WrapValue;}
     inline void Sub(FractionWrap<word> a){WrapValue-=a.WrapValue;}
     inline void Divide(int Count){WrapValue/=Count;};
     inline void Multiplication(int Count){WrapValue*=Count;};
     inline FractionWrap(const word & a){Clear();Value() = a;}
     inline FractionWrap(){Clear();}    
    protected:
     int WrapValue;
  };
template<>
 struct FractionWrap<float>
  {
     inline float & Value(){return WrapValue;}
     inline void Clear(){WrapValue = 0;};     
     inline void Add(FractionWrap<float> a){WrapValue+=a.WrapValue;}
     inline void Sub(FractionWrap<float> a){WrapValue-=a.WrapValue;}
     inline void Divide(int Count){WrapValue/=Count;};
     inline void Multiplication(int Count){WrapValue*=Count;};
     inline FractionWrap(const float & a){Clear();Value() = a;}
     inline FractionWrap(){Clear();}    
    protected:
     float WrapValue;
  };
//AccumulationWrap
//аккуму... не правильно
/*template<class iTypeItem>
 struct AccumulationWrap
  {
  };
template<>
 struct AccumulationWrap<byte>
  {
     inline AccumulationWrap(){Clear();}
     inline void Clear(){WrapValue = 0;}
     inline void Add(const byte & a){register int i=a; i+=1<<20;WrapValue+=i;}
//     inline byte GetValue(){register int i = (WrapValue&0x000FFFFF)/(WrapValue>>20);}
    protected:     // cccccccc ccccvvvv vvvvvvvv vvvvvvvv   c 21 бита счетчик
     int WrapValue;
  };*/

}
#endif
