#ifndef xxTxtProviderH
#define xxTxtProviderH
#include "../xxBase.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
class IxBaseTxtProvider
 {
  public:
   Str LastError;
   IxBaseTxtProvider(){Line = 1; Col = 1;}
   virtual bool OpenForRead(){Line = 1; Col = 1; Undo.Clear(); return true;};
   virtual bool OpenForWrite(){Line = 1; Col = 1; Undo.Clear(); return true;};
   virtual bool Close(){return true;};
   virtual bool Seek(int i,int FromWhere = SEEK_SET)=0;// SEEK_SET, SEEK_CUR, SEEK_END
   virtual int  Position()=0;
   int GetLine();
   int GetCol();
   //чтение
   char Get();
   inline void UnGet(char c){Undo.Push(c);}; //imitation of returning the character to a stream
   char GetOther(const char*);//returns the first not from the input string
   void SkipTo(const char*s);//passes including S (eg comments)
   void AddToStrTermStr(Str&s,const char* term); //add a line separator until term (str)
   char AddToStrTermChar(Str&s,const char* term); //add a line until one (char) of the separators term (char), Resume. Concrete. separator
   //WRITE
   virtual bool Write(Str)=0;
  protected:
   virtual char InternalGet()=0; //obtaining internal character
   int Line,Col;//really a matter of row and column, net of returns
   Stack<char> Undo;
 };
//------------------------------------------------------------------------------
//  source and destination of the data, use the container Str
class TxStrTxtProvider: public IxBaseTxtProvider
 {
  protected:
   int Pos; //position in the string
   virtual char InternalGet();
  public:
   Str str;
   virtual bool OpenForRead(){Pos = 1; return IxBaseTxtProvider::OpenForRead();};
   virtual bool OpenForWrite(){Pos = 1; return IxBaseTxtProvider::OpenForWrite();};
   virtual bool Seek(int i,int FromWhere = SEEK_SET);
   virtual int  Position(){return Pos-Undo.Size();};
   virtual bool Write(Str);
 };
//------------------------------------------------------------------------------
//  source and destination of the data, use a container file
class TxFileTxtProvider: public IxBaseTxtProvider
 {
  public:
   Str FileName;
   virtual bool OpenForRead();
   virtual bool OpenForWrite();
   virtual bool Close();
   virtual bool Seek(int i,int FromWhere = SEEK_SET);
   virtual int  Position();
   virtual bool Write(Str);
  protected:
   int File;
   int BufPos; 
   Str Buff;
   bool isToWrite;
   bool WriteBuffer();
   bool ReadTobuff();
   virtual char InternalGet();
 };
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
#endif
