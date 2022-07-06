#ifndef xxGTLGeometryH
#define xxGTLGeometryH
namespace GTL
{
template <class T>
class TxTPoint
 {
  public:
   T X,Y;
   TxTPoint(){};
   TxTPoint(T iX,T iY){X = iX; Y = iY;}
   bool inRegion(const TxTPoint<T>p,T delta)
    {
      return p.X>=X-delta&&p.X<=X+delta&&p.Y>=Y-delta&&p.Y<=Y+delta;
    }
 };
template <class T>
class TxTRect
 {
  public:
   T X1,Y1,X2,Y2;
   TxTRect(T iX1,T iY1,T iX2,T iY2);
    bool inRect(const TxTPoint<T>&p)const;
    bool isCrossed(const TxTRect<T>&r)const;
 };
template <class T>
TxTRect<T>::TxTRect(T iX1,T iY1,T iX2,T iY2)
 {
  if(iX1<iX2){X1 = iX1; X2 = iX2;}else{X1 = iX2; X2 = iX1;}
  if(iY1<iY2){Y1 = iY1; Y2 = iY2;}else{Y1 = iY2; Y2 = iY1;}
 }
template <class T>
 bool TxTRect<T>::inRect(const TxTPoint<T>&p)const
 {
  return X1<=p.X&&p.X<=X2&&Y1<=p.Y&&p.Y<=Y2;
 }
template <class T>
 bool TxTRect<T>::isCrossed(const TxTRect<T>&r)const
 {
  return  inRect(TxTPoint<T>(r.X1,r.Y1))||inRect(TxTPoint<T>(r.X2,r.Y1))||
          inRect(TxTPoint<T>(r.X1,r.Y2))||inRect(TxTPoint<T>(r.X2,r.Y2))||
          r.inRect(TxTPoint<T>(X1,Y1))||r.inRect(TxTPoint<T>(X2,Y1))||
          r.inRect(TxTPoint<T>(X1,Y2))||r.inRect(TxTPoint<T>(X2,Y2))||
          X1<r.X1&X2>r.X2&Y1>r.Y1&Y2<r.Y2||
          X1>r.X1&X2<r.X2&Y1<r.Y1&Y2>r.Y2;
 }
typedef TxTPoint<int>  TxPoint;
typedef TxTRect<int>   TxRect;
}
#endif
