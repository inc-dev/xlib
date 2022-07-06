//------------------------------------------------------------------------------
#include "xArrayTest.h"
//------------------------------------------------------------------------------
using namespace XSPACE;

int TestDones::Count=0;
TxAtom TestDones::DoneCount=0;
int TestDones::Dones[10000000];
//TxArrayData<TestDones>*pppppp;

void f1()
 {  //временно
    Array<TestDones> a,b;
    TestDones t;
    TestDones tt[10];
    a.Add(tt);
    a.Add(t);
//    a.Assign(t);
    a.Add(t);
    a.Add(t);
    a.Delete(2);
    a.Insert(t,2);
    a.AddItems(5);
    a.InsertItems(2,4);
    a.Delete(2,3);
    b.Assign(a);
    a.Insert(2,a);
    a[1]=a[1];
    b=a;
//    b=t;
    b=tt;
    Array< Array<TestDones> > aa;
    aa.Add(a);
    aa.Add(a);
    aa.Add(b);
    aa.Insert(1,b);
 }

//------------------------------------------------------------------------------
template<typename TestType>
char* TestCapacity()
 {
//  printf("--------- CAPACITY ---------\n");
//  printf("for type size = %d\n",sizeof(TestType));
  Array<TestType> a;
  //a.Reserve(1000000);
//  int LastCapacity=-1;
  TestType* Items=0;
  int NewCount=0;
  for(int i=0;i<1000000;i++)
   {
     if(a.Capacity()<a.Size())return "a.Capacity()<a.Size()";
/*     if(LastCapacity!=a.Capacity())
      {
       if(a.Size())
        printf("Cap=%d Size=%d K=%0.3f\n",a.Capacity(),a.Size(),1.0*a.Capacity()/a.Size());
       else
        printf("Cap=%d Size=%d K=%0.3f\n",a.Capacity(),a.Size(),1.0);
      }*/
//     LastCapacity=a.Capacity();
     //--------------------
     if(Items!=a.GetItems())NewCount++;
     Items=a.GetItems();
     //--------------------
     TestType o;
     a.Add(o);
   }
//  printf("NewCount = %d\n",NewCount);
//  printf("a.Clear()\n");
  a.Clear();
//  printf("a.Capacity() = %d\n",a.Capacity());
  a.Pack();
//  printf("a.Pack()\n");
//  printf("a.Capacity() = %d\n",a.Capacity());
//  printf("----------------------------\n");
  return 0;
 }
//------------------------------------------------------------------------------
template<typename TestType>
 bool er(Array<TestType>& a)
  {if(a.Size()>a.Capacity()||a.RefCount()<1)return true;return false;}
//------------------------------------------------------------------------------
template<class T,class U>
 void ADD(T&a,const U&b)
  {
   a.Add(b);
  }
template<typename TestType>
const char* Test1()//тест не полный!!!
 {//init
  Array<TestType> a;
  //int i=a.RefCount();
  if(er(a)||a.Size()!=0)return "1.Bad Size";
  a.Add(TestType(1));
  a.Add(TestType(2));
  a.Add(TestType(3));
  if(er(a)||a.Size()!=3)return "2.Bad Size";
  if(er(a)||a.RefCount()!=1)return "3.Bad RefCount";
  Array<TestType> b(a);
  if(er(a)||a.Size()!=3)return "4.Bad Size";
  if(er(a)||er(b)&&a.RefCount()!=2||b.RefCount()!=2)return "5.Bad RefCount";
  Array<TestType> c(100);
  if(er(c)||c.Capacity()<100)return "6.Bad Capacity";
  TestType StatArray[10];
  Array<TestType> d(StatArray);
  if(er(d)||d.Size()!=10)return "7.Bad a[Size=10]";
  Array<TestType> e(&StatArray[5],3);
  if(er(a)||e.Size()!=3)return "8.Bad a[Size=3]";
  //надо проверить загрузку из других контейнеров
  //Assign
  if(er(a)||a.RefCount()!=2)return "9.Bad RefCount(Assign0)";
//  a.Assign(TestType(10));
  a.Clear();
  a.Add(TestType(10));
  if(a.Size()!=1)return "10.Bad Size(Assign)";
  if(er(a)||a.RefCount()!=1)return "11.Bad RefCount(Assign)";
  if(er(b)||b.RefCount()!=1)return "12.Bad RefCount(Assign)";
  if(er(a)||a[1]!=10)return "13.Bad Assign value";
  TestType StaticArray[15];
  for(int i=0;i<15;i++)StaticArray[i]=i+1;
  a.Assign(StaticArray);
  if(er(a)||a.Size()!=15)return "14.Bad Assign StaticArray1";
  for(int i=1;i<=a.Size();i++)
    if(a[i]!=i)  return "15.Bad Assign StaticArray";
  a.Assign(StaticArray,3);
  if(er(a)||a.Size()!=3)return "16.Bad Assign StaticArray";
  for(int i=1;i<=a.Size();i++)
    if(a[i]!=i)  return "17.Bad Assign StaticArray";
  //-----
  if(er(a)||a.RefCount()!=1)return "18.Bad RefCount(AssignArray)";
  if(er(b)||b.RefCount()!=1)return "19.Bad RefCount(AssignArray)";
  b.Assign(a);
  if(er(a)||a.RefCount()!=2)return "20.Bad RefCount(AssignArray)";
  if(er(b)||b.RefCount()!=2)return "21.Bad RefCount(AssignArray)";
  if(a.GetItems()!=b.GetItems())return "22.Bad Ref(AssignArray)";
  TestType Item;
//  b.Assign(Item);
  b.Clear();
  b.Add(Item);
  if(er(a)||a.RefCount()!=1)return "23.Bad RefCount(AssignArray)";
  if(er(b)||b.RefCount()!=1)return "24.Bad RefCount(AssignArray)";
  if(er(b)||b.Size()!=1)return "25.Bad Assign item";
  if(a.GetItems()==b.GetItems())return "26.Bad Ref(AssignArray)";
  if(er(a)||a.Size()!=3)return "27.Bad Assign item a.Size";
  //надо проверить загрузку из других контейнеров
  //Add
  b.Assign(a);
  if(er(a)||a.RefCount()!=2)return "28.Bad RefCount(AssignArray N)";
  if(er(b)||b.RefCount()!=2)return "29.Bad RefCount(AssignArray N)";
  if(a.GetItems()!=b.GetItems())return "30.Bad Ref(AssignArray N)";
  Item = 4;
  a.Add(Item);
  if(er(b)||b.Size()!=3)return "31.Bad Assign item b.Size";
  if(er(a)||a.Size()!=4)return "32.Bad Assign item a.Size";
  if(er(a)||a.RefCount()!=1)return "33.Bad RefCount(AssignArray)";
  if(er(b)||b.RefCount()!=1)return "34.Bad RefCount(AssignArray)";
  for(int i=1;i<=a.Size();i++)
    if(a[i]!=i)  return "35.Bad Assign Add";
  a.Add(StaticArray);
  if(er(a)||a.Size()!=19)return "36.Bad Assign item a.Size";
  if(er(a)||a.RefCount()!=1)return "37.Bad RefCount(AssignArray)";
  a.Add(StaticArray,5);
  if(er(a)||a.Size()!=24)return "38.Bad Assign item a.Size";
  if(er(a)||a.RefCount()!=1)return "39.Bad RefCount(AssignArray)";
  a.AddItems(6);
  if(er(a)||a.Size()!=30)return "40.Bad Assign item a.Size";
  if(er(a)||a.RefCount()!=1)return "41.Bad RefCount(AssignArray)";
  a.Add(a);
  if(er(a)||a.Size()!=60)return "42.Bad Assign item a.Size";
  if(er(a)||a.RefCount()!=1)return "43.Bad RefCount(AssignArray)";
  b=a;
  if(er(a)||a.RefCount()!=2)return "44.Bad RefCount(AssignArray)";
  for(int i=1;i<=a.Size();i++) a[i]=i;
  if(er(a)||a.RefCount()!=1)return "45.Bad RefCount(AssignArray)";
  b=a;
  if(er(a)||a.RefCount()!=2)return "45.Bad RefCount(AssignArray)";
  a.Delete(0,4); //ошибочные
  a.Delete(70,74); //ошибочные
  a.Delete(30,20); //ошибочные
  if(er(a)||a.RefCount()!=2||a.Size()!=60)return "46.delete";
  a.Delete(1,1);
  if(er(a)||a.RefCount()!=1||a.Size()!=59)return "47.delete";
  for(int i=1;i<=a.Size();i++)
   if(a[i]-1!=i)return "48.delete";
  a.Delete(a.Size());
  if(er(a)||a.RefCount()!=1||a.Size()!=58)return "49.delete";
  for(int i=1;i<=a.Size();i++)
   if(a[i]-1!=i)return "50.delete";
  a.Delete(51,a.Size());
  if(er(a)||a.RefCount()!=1||a.Size()!=50)return "51.delete";
  for(int i=1;i<=a.Size();i++)
   if(a[i]-1!=i)return "52.delete";
  a.Delete(20,29);
  if(er(a)||a.RefCount()!=1||a.Size()!=40)return "53.delete";
  for(int i=1;i<=19;i++)
   if(a[i]-1!=i)return "54.delete";
  for(int i=20;i<=a.Size();i++)
   if(a[i]-11!=i)return "55.delete";
  b=a;
  int oldCapacity=a.Capacity();
  if(er(a)||a.RefCount()!=2||a.Size()!=40)return "56.Clear";
  a.Clear();
  if(er(a)||a.RefCount()!=1||a.Size()!=0)return "57.Clear";
  a.Pack();
  if(er(a)||a.RefCount()!=1||a.Size()!=0||oldCapacity<a.Capacity())return "57.Pack";
  b=a;
  a.Insert(0,Item);
  a.Insert(2,Item);
  if(er(a)||a.RefCount()!=2||a.Size()!=0)return "56.Insert";
  Item=11;
  a.Insert(1,Item);
  if(er(a)||a.RefCount()!=1||a.Size()!=1)return "57.Insert";
  for(int i=0;i<10;i++)StatArray[i]=i+1;
  a.Insert(1,StatArray);
  if(er(a)||a.RefCount()!=1||a.Size()!=11)return "58.Insert";
  for(int i=1;i<=a.Size();i++)if(a[i]!=i)return "59.Insert";
  a.InsertItems(1,3);
  if(er(a)||a.RefCount()!=1||a.Size()!=14)return "60.Insert";
  for(int i=4;i<=a.Size();i++)if(a[i]!=i-3)return "61.Insert";
  ADD(a,a);
  if(er(a)||a.RefCount()!=1||a.Size()!=28)return "62.ADD";
  a.SetSize(30);
  a.SetSize(20);
  return 0;
 }
const char* StringTest()
 {
  typedef Array<char> Str;
  Str a,b(5);
  if(er(a)||a.Size()!=0||a.Capacity()!=0)return "1.init";
  const char *pc=a.c_str();
  if(*pc)return "1.1.init";
  if(er(b)||b.RefCount()!=1||b.Size()!=0||b.Capacity()==0)return "2.init";
  char *cc1="12345";  const char *cc2="6789";
  Str c(cc1),d(cc2),e("987654321");
  Str f(cc1,2),g(cc2,2),h("987654321",2);
  if(er(c)||c.RefCount()!=1||c.Size()!=5)return "3.init";
  if(er(d)||d.RefCount()!=1||d.Size()!=4)return "4.init";
  if(er(e)||e.RefCount()!=1||e.Size()!=9)return "5.init";
  if(er(f)||f.RefCount()!=1||f.Size()!=2)return "6.init";
  if(er(g)||g.RefCount()!=1||g.Size()!=2)return "7.init";
  if(er(h)||h.RefCount()!=1||h.Size()!=2)return "8.init";
  //----
//  a.Assign('1');
  a='1';
//  a.Clear();
//  a.Add('1');
  if(er(a)||a.RefCount()!=1||a.Size()!=1||a[1]!='1')return "9.Assign";
  a.Assign("12345");
  if(er(a)||a.RefCount()!=1||a.Size()!=5||strcmp(a.c_str(),"12345"))return "10.Assign";
  a.Assign("12345",3);
  if(er(a)||a.RefCount()!=1||a.Size()!=3||strcmp(a.c_str(),"123"))return "11.Assign";
  a.Assign(cc1);
  if(er(a)||a.RefCount()!=1||a.Size()!=5||strcmp(a.c_str(),"12345"))return "12.Assign";
  a.Assign(cc2);
  if(er(a)||a.RefCount()!=1||a.Size()!=4||strcmp(a.c_str(),"6789"))return "13.Assign";
  a.Assign(cc1,2);
  if(er(a)||a.RefCount()!=1||a.Size()!=2||strcmp(a.c_str(),"12"))return "14.Assign";
  a.Assign(cc2,2);
  if(er(a)||a.RefCount()!=1||a.Size()!=2||strcmp(a.c_str(),"67"))return "15.Assign";
  const char cc3[]="12345";
  a.Assign(cc3);
  if(er(a)||a.RefCount()!=1||a.Size()!=5||strcmp(a.c_str(),"12345"))return "16.Assign";
  b=a;
  if(er(a)||a.RefCount()!=2||a.Size()!=5||strcmp(a.c_str(),"12345"))return "17.Assign";
  if(er(b)||b.RefCount()!=2||b.Size()!=5||strcmp(b.c_str(),"12345"))return "18.Assign";
  // ADD
  a.Add("678");
  if(er(a)||a.RefCount()!=1||a.Size()!=8||strcmp(a.c_str(),"12345678"))return "19.Add";
  a.Add('9');
  if(er(a)||a.RefCount()!=1||a.Size()!=9||strcmp(a.c_str(),"123456789"))return "20.Add";
  a.Add("012345",5);
  if(er(a)||a.RefCount()!=1||a.Size()!=14||strcmp(a.c_str(),"12345678901234"))return "21.Add";
  a.AddItems(4);
  if(er(a)||a.RefCount()!=1||a.Size()!=18)return "22.Add";
  a.Delete(10,18);
  if(er(a)||a.RefCount()!=1||a.Size()!=9||strcmp(a.c_str(),"123456789"))return "22.Del";
  a.Add(a);
  if(er(a)||a.RefCount()!=1||a.Size()!=18||strcmp(a.c_str(),"123456789123456789"))return "23.Add";
  const char ccc[]="12345";
  a.Delete(10,18);
  if(er(a)||a.RefCount()!=1||a.Size()!=9||strcmp(a.c_str(),"123456789"))return "24.Del";
  a.Add(ccc);
  if(er(a)||a.RefCount()!=1||a.Size()!=14||strcmp(a.c_str(),"12345678912345"))return "25.Add";
  a.Delete(10,18);
  if(er(a)||a.RefCount()!=1||a.Size()!=9||strcmp(a.c_str(),"123456789"))return "26.Del";
  a.Insert(0,'0');
  a.Insert(11,'0');
  a.Insert(0,"0123");
  a.Insert(11,"0123");
  if(er(a)||a.RefCount()!=1||a.Size()!=9||strcmp(a.c_str(),"123456789"))return "27.Ins";
  a.Insert(1,'0');
  if(er(a)||a.RefCount()!=1||a.Size()!=10||strcmp(a.c_str(),"0123456789"))return "28.Ins";
  a.Insert(11,'A');
  if(er(a)||a.RefCount()!=1||a.Size()!=11||strcmp(a.c_str(),"0123456789A"))return "29.Ins";
  a.Delete(1);
  if(er(a)||a.RefCount()!=1||a.Size()!=10||strcmp(a.c_str(),"123456789A"))return "30.Del";
  a.Delete(10);
  if(er(a)||a.RefCount()!=1||a.Size()!=9||strcmp(a.c_str(),"123456789"))return "31.Del";
  a.Insert(2,"ABCD",3);
  if(er(a)||a.RefCount()!=1||a.Size()!=12||strcmp(a.c_str(),"1ABC23456789"))return "32.Ins";
  a.Delete(2,4);
  if(er(a)||a.RefCount()!=1||a.Size()!=9||strcmp(a.c_str(),"123456789"))return "33.Del";
  a.InsertItems(1,3);
  if(er(a)||a.RefCount()!=1||a.Size()!=12||strcmp(a.c_str()+3,"123456789"))return "34.ins";
  a.Delete(1,3);
  if(er(a)||a.RefCount()!=1||a.Size()!=9||strcmp(a.c_str(),"123456789"))return "35.Del";
  a.Insert(2,a);
  if(er(a)||a.RefCount()!=1||a.Size()!=18||strcmp(a.c_str(),"112345678923456789"))return "36.Ins";
  a.Delete(2,10);
  if(er(a)||a.RefCount()!=1||a.Size()!=9||strcmp(a.c_str(),"123456789"))return "37.Del";
  a.Insert(3,ccc);
  if(er(a)||a.RefCount()!=1||a.Size()!=14||strcmp(a.c_str(),"12123453456789"))return "38.Ins";
  a.Delete(3,7);
  if(er(a)||a.RefCount()!=1||a.Size()!=9||strcmp(a.c_str(),"123456789"))return "39.Del";
//---------------------------------
  Array<Str> ss;
  ss.Add(a);
  ss.Add(b);
  ss.Add("123");
  if(ss.Size()!=3)return "100.Add";
  if(er(ss[3])||ss[3].RefCount()!=1||ss[3].Size()!=3||strcmp(ss[3].c_str(),"123"))return "101.Add";
  return 0;
 }
template<typename TestType>
void ArrayProp(Array<TestType> a)
 {
  printf("cap=%d size=%d ref=%d\n",a.Capacity(),a.Size(),a.RefCount());
 }
template<typename TestType>
const char* NumberTest()
 {
  Array<TestType> a,b(5);
  if(er(a)||a.Capacity()!=0||a.Size()!=0)return "1.init";
  if(er(b)||b.Capacity()<5||b.Size()!=0)return "2.init";
//  a=5;
  a.Clear();
  a.Add(5);
  if(er(a)||a.RefCount()!=1||a.Capacity()<1||a.Size()!=1)return "3.=";
  a.Add(6);
  if(er(a)||a.RefCount()!=1||a.Capacity()<2||a.Size()!=2)return "3.Add";
  a.Delete(1,a.Size());
  if(er(a)||a.RefCount()!=1||a.Capacity()<2||a.Size()!=0)return "4.del";
  const TestType tt[]={1,2,3,4,5};
  a.Add(tt);
  if(er(a)||a.RefCount()!=1||a.Size()!=5)return "5.Add";
  a.Add(a);
  a.Insert(1,a);
//  ArrayProp(a);
  if(er(a)||a.RefCount()!=1||a.Size()!=20)return "6.Add ins";
  return 0;
 }
const char *ArrayOperTest()
 {
  Str s1("123"),s2("123");
  if(s1!=s2)return "ArrayOper s1!=s2";
  if(!(s1==s2))return "ArrayOper s1==s2";
  if(s1!="123"||"123"!=s2)return "ArrayOper s1!=chars";
  if(!(s1=="123"&&"123"==s2))return "ArrayOper s1==chars";
  s1+="45";
  s1+='6';
  if(s1!="123456")return "ArrayOper s1!=123456";
  s2=s2+"45"+"6"+'7';
  if(s2!="1234567")return "ArrayOper s1!=1234567";
  return 0;
 }
const char *ArrayDecodeStrTest()
 {//пока в упрощенном варианте
  if(Trunc(5.5)!=5)return "DecodeStr Trunc(5.5)!=5";
  if(Round(5.5)!=6||Round(5.4)!=5)return "DecodeStr Round(5.5)!=6||Round(5.4)!=5";
  if(Abs(5)!=5||Abs(-5)!=5)return "DecodeStr Abs(5)!=5||Abs(-5)!=5";
  if(Max(5,6)!=6||Max(5.6,6)!=6||Max(5,6.6)!=6.6)return "DecodeStr Max(5,6)!=6||Max(5.6,6)!=6||Max(5,6.6)!=6.6";
  if(StrToInt("123")!=123)return "DecodeStr StrToInt";
  if(StrToInt(Str("123"))!=123)return "DecodeStr StrToInt(str)";
  if(StrToInt64(Str("12345678901234567890"))!=12345678901234567890)return "DecodeStr StrToInt64(str)";
  if(StrToInt("123")!=123)return "DecodeStr StrToInt";
  double t_double = StrToDouble("123.56");
  if(t_double>=123.56 && t_double<=123.5600001 )return "DecodeStr xStrToDouble";
  if(Str(NumToStr(-12345))!="-12345")return "DecodeStr NumToStr 1";
//  if(Str(NumToStr(-12345.666666))!="-12345.66667")return "DecodeStr NumToStr 2";
  int64 u=-123456789123456789;
  if(Str(NumToStr(u))!="-123456789123456789")return "DecodeStr NumToStr 3";
  SmallStr s;
  Str ss(s);
  if(ss!="")return "DecodeStr SmallStr";
  ss+=s;
  if(ss!="")return "DecodeStr SmallStr";
  int i=0x1234;
  if(BinToHexStr(&i,2)!="3412")return "DecodeStr BinToHexStr";
  HexStrToBin(&i,Str("7856"),2);
  if(i!=0x5678)return "DecodeStr HexStrToBin";
  return 0;
 }
const char *TrimTest()
 {
  Str s;
  s=" qwerty  ";
  if(Trim(s)!="qwerty")return "Trim 1";
  s="   ";
  if(Trim(s)!="")return "Trim 2";
  s="";
  if(Trim(s)!="")return "Trim 3";

  s="   ";
  if(TrimLeft(s)!="")return "TrimLeft 1";
  s="";
  if(TrimLeft(s)!="")return "TrimLeft 2";
  s=" qwerty  ";
  if(TrimLeft(s)!="qwerty  ")return "TrimLeft 3";

  s="   ";
  if(TrimRight(s)!="")return "TrimRight 1";
  s="";
  if(TrimRight(s)!="")return "TrimRight 2";
  s=" qwerty  ";
  if(TrimRight(s)!=" qwerty")return "TrimRight 3";

  return 0;
 }
const char *ArrayTest()
 {
//------------------------------------------------------------------------------
   #ifdef _DEBUG
     printf("---=DEBUG=---\n");
   #else
     printf("---=RELEASE=---\n");
   #endif
   if(sizeof("123")!=4)return "bad char[] size";
   if(xIsChar<unsigned char>::Yes)return "char==unsigned char";
   if(xIsChar<signed char>::Yes)return "char==signed char";

   const char*Error = Test1<int>();
   if(Error)return Error;

   Error = Test1<TestDones>();
   if(Error)return Error;
//-----------------------------------
   Error = TestCapacity<char>();
   if(Error)return Error;
   Error = TestCapacity<int>();
   if(Error)return Error;
   Error = TestCapacity<TestDones>();
   if(Error)return Error;
//   printf("String\n");
   Error = StringTest();
   if(Error)return Error;
   Error = NumberTest<int>();
   if(Error)return Error;
//   printf("short\n");
   Error = NumberTest<short>();
   if(Error)return Error;
   f1();
   if(TestDones::isBad())return "class.count!=0";

   Error = ArrayOperTest();
   if(Error)return Error;

   Error = ArrayDecodeStrTest();
   if(Error)return Error;


   Error = TrimTest();
   if(Error)return Error;

   return 0;
 }

//------------------------------------------------------------------------------
