//------------------------------------------------------------------------------
#ifndef xxDataAccessH
#define xxDataAccessH
//------------------------------------------------------------------------------
struct TxExternSerialAccess
  {
   //int First();
   //int Next();
   //T Get();
  };
struct TxSizeAccess
  {
   //int Size();
   //bool isEmpty();
  };
struct TxUpdateAccess
  {
   //void PrepareUpdate(int NewCapacity=0,bool MayClear=false);
   //void Set(int i,const T&obj)const;
   //Insert - ?
   //Delete - ?
  };
//------------------------------------------------------------------------------
struct TxSerialAccess
  {
   //int First();
   //int Next(int i);
   //T Get(int i);
  };
struct TxSizeSerialAccess:public TxSerialAccess,TxSizeAccess{};
struct TxUpdateSerialAccess:public TxSerialAccess,TxUpdateAccess{};
struct TxUpdateSizeSerialAccess:public TxSerialAccess,TxSizeAccess,TxUpdateAccess{};
//------------------------------------------------------------------------------
struct TxBidirectionalAccess:public TxSerialAccess
  {
   //int Last();
   //int Previos(int i);
  };
struct TxSizeBidirectionalAccess:public TxBidirectionalAccess,TxSizeAccess{};
struct TxUpdateBidirectionalAccess:public TxBidirectionalAccess,TxUpdateAccess{};
struct TxUpdateSizeBidirectionalAccess:public TxBidirectionalAccess,TxSizeAccess,TxUpdateAccess{};
//------------------------------------------------------------------------------
//fast access to the elements but posledovatelnost elements may be different (for example, in the reverse order)
struct TxRandomAccess:public TxSizeBidirectionalAccess
  {
   //operator[](int i);
  };
struct TxUpdateRandomAccess:public TxRandomAccess,TxUpdateAccess{};
//------------------------------------------------------------------------------
//monolithic structure in which the elements are one by one
struct TxMonolithAccess:public TxRandomAccess
  {
   //T*GetItems()
   //int Capacity();
  };
struct TxUpdateMonolithAccess:public TxMonolithAccess,TxUpdateAccess{};  
//------------------------------------------------------------------------------
enum{xMinCapacity=1<<5};//degree 2ki 5 -> 32

#endif
