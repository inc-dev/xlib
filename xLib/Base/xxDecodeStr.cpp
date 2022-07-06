#ifndef __GNUC__
#pragma hdrstop
#endif

#include "xxDecodeStr.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
int StrToInt(const char*ch)      //------int StrToInt(char*ch){return atoi(ch);};
 {
  int Res = 0;
  bool isSing = *ch=='-';
  if(isSing)ch++;
  while(*ch>='0'&&*ch<='9')
   {
    Res = (Res*10)+*ch-'0';
    ch++;
   }
  if(isSing)return -Res;
  return Res;
 }
//---------------------------------------------------------
double StrToDouble(const char*ch)
 {
  double Res = 0;
  bool isSing = *ch=='-';
  if(isSing)ch++;
  while(*ch>='0'&&*ch<='9')
   {
    Res = (Res*10.0)+*ch-'0';
    ch++;
   }
  if(*ch=='.'||*ch==',')   
   {
    ch++;
    double koef=1;
    while(*ch>='0'&&*ch<='9')
     {
      Res = (Res*10.0)+*ch-'0';
      ch++;koef=koef*0.1;
     }
    Res=Res*koef;
   }
  if(isSing)return -Res;
  return Res;
 }
//---------------------------------------------------------
int64 StrToInt64(const char*ch)
 {
   int64 R=0;
   bool isSign= *ch=='-';
   if(isSign)ch++;
   while(*ch>='0'&&*ch<='9')
    {
     R=R*10+*ch-48;
     ch++;
    }
  if(isSign)return -R;
  return R;
 }
NumToStr::NumToStr(int  i)
 {
  if(i==0)
   {
    Shift = 0;Len = 1;
    Data[0]='0';Data[1]=0;
    return;
   }
  div_t div_res;
  Shift=31;
  Data[Shift]=0;
  bool isSingl = i<0;
  if(isSingl)i=-i;
  while(i)
   {
    div_res = div(i,10);
    Shift--;Len++;
    Data[Shift]=char(div_res.rem+48);
    i = div_res.quot;
   }
  if(isSingl)
   {
    Shift--;Len++;
    Data[Shift]= '-';
   }
 }
//---------------------------------------------------------
NumToStr::NumToStr(unsigned int  i)
 {
  if(i==0)
   {
    Shift = 0;Len = 1;
    Data[0]='0';Data[1]=0;
    return;
   }
  div_t div_res;
  Shift=31;
  Data[Shift]=0;
  while(i)
   {
    div_res = div(i,10);
    Shift--;Len++;
    Data[Shift]=char(div_res.rem+48);
    i = div_res.quot;
   }
 }
NumToStr::NumToStr(double i,int CountAfterPoint)
 {
//  Begin=Buf;
  if(CountAfterPoint>=0)
   {
    double e=0.5*pow(10.0,-CountAfterPoint);
    if(i>=0)i=i+e;else i=i-e;
   }
  sprintf(Data,"%f",i);
  char* ch = strchr(Data,'.');
  if(ch==0){ch = strchr(Data,',');}
  if(ch)
   {
    ch[0]='.';
    int i=ch-Data;
    if(CountAfterPoint>0)i+=CountAfterPoint+1;
    if(i>=int(sizeof(Data)))i=sizeof(Data)-1;
    Data[i]=0;
    if(CountAfterPoint)
     {
      while(Data[--i]=='0')Data[i]=0;
      if(Data[i]=='.')Data[i]=0;
     }
   }
  Len =byte(strlen(Data));
 }
//---------------------------------------------------------
NumToStr::NumToStr(int64 i)
 {
  if(i==0)
   {
    Shift = 0;Len = 1;
    Data[0]='0';Data[1]=0;
    return;
   }
  Shift=31;
  Data[Shift]=0;
  bool isSingl = i<0;
  if(isSingl)i=-i;
  while(i)
   {
    Shift--;Len++;
    Data[Shift]=char((i%10)+48);
    i = i/10;
   }
  if(isSingl)
   {
    Shift--;Len++;
    Data[Shift]= '-';
   }
 }
//---------------------------------------------------------
NumToStr::NumToStr(uint64 i)
 {
  if(i==0)
   {
    Shift = 0;Len = 1;
    Data[0]='0';Data[1]=0;
    return;
   }
  Shift=31;
  Data[Shift]=0;
  while(i)
   {
    Shift--;Len++;
    Data[Shift]=char((i%10)+48);
    i = i/10;
   }
 }
//------------------------------------------------------------------------------
int IntToChars(char*d,int i) //itoa
 {
  div_t div_res;
  if(i==0){d[0]=48;d[1]=0;return 1;}
  int len=0;
  if(i>=0)
   {
    char *cur=d;
    while(i)
     {
      div_res = div(i,10);
      *cur=div_res.rem+48;
      cur++;
      i = div_res.quot;
      len++;
     }
    d[len]=0;
    //переварачиваем
    char c,*end = d+len-1;
    while(d<end)
     {
      c = *end;
      *end = *d;
      *d = c;
      d++;end--;
     }
    return len;
   }else
   {
    i=-i;*d='-';d++;len++;
    char *cur=d;
    while(i)
     {
      div_res = div(i,10);
      *cur=div_res.rem+48;
      cur++;
      i = div_res.quot;
      len++;
     }
    d[len-1]=0;
    //переварачиваем
    char c,*end = d+len-1-1;
    while(d<end)
     {
      c = *end;
      *end = *d;
      *d = c;
      d++;end--;
     }
    return len;
   }
 }
//------------------------------------------------------------------------------
int UIntToChars(char*d,unsigned int i)
 {
  div_t div_res;
  if(i==0){d[0]=48;d[1]=0;return 1;}
  int len=0;
  char *cur=d;
  while(i)
   {
    div_res = div(i,10);
    *cur=div_res.rem+48;
    cur++;
    i = div_res.quot;
    len++;
   }
  d[len]=0;
  //overturn
  char c,*end = d+len-1;
  while(d<end)
   {
    c = *end;
    *end = *d;
    *d = c;
    d++;end--;
   }
  return len;
 }
//------------------------------------------------------------------------------
void UIntToCharsBySize(char*d,unsigned int i,unsigned int size)
 {
  div_t div_res;
  char *cur=d+size-1;
  d[size]=0;
  d[size-1]='0';
  while(i)
   {
    div_res = div(i,10);
    *cur=div_res.rem+48;
    cur--;
    i = div_res.quot;
   }
  while(d<=cur)
   {
    *cur = '0';
    cur--;
   }
 }
//------------------------------------------------------------------------------
int Int64ToChars(char*Buf,int64 i)
 {
  uint64 ii;char*cur=Buf;bool H=false;
  if(i<0){Buf[0]='-';cur++;i=-i;}
  cur[0]=0;
  ii=i/100000000000ll;
  if(ii){cur+=IntToChars(cur,ii);H=true;i=i-ii*100000000000ll;}
  //---------
  ii=i/100000;
  if(H){UIntToCharsBySize(cur,ii,6);cur+=6;}
  else if(ii)cur+=IntToChars(cur,ii);
  if(ii){i=i-ii*100000;H=true;}
  //---------
  if(H){UIntToCharsBySize(cur,i,5);cur+=5;}
  else cur+=IntToChars(cur,i);
  return cur-Buf;
 }
//------------------------------------------------------------------------------
int UInt64ToChars(char*Buf,uint64 i)
 {
  uint64 ii;char*cur=Buf;bool H=false;
  cur[0]=0;
  ii=i/100000000000ll;
  if(ii){cur+=IntToChars(cur,ii);H=true;i=i-ii*100000000000ll;}
  //---------
  ii=i/100000;
  if(H){UIntToCharsBySize(cur,ii,6);cur+=6;}
  else if(ii)cur+=IntToChars(cur,ii);
  if(ii){i=i-ii*100000;H=true;}
  //---------
  if(H){UIntToCharsBySize(cur,i,5);cur+=5;}
  else cur+=IntToChars(cur,i);
  return cur-Buf;
 }
//------------------------------------------------------------------------------
int DoubleToChars(char*d,double i,int CountAfterPoint)
 {
  if(CountAfterPoint>=0)
   {
    double e=0.5*pow(10.0,-CountAfterPoint);
    if(i>=0)i=i+e;else i=i-e;
   }
  sprintf(d,"%f",i);
  char* ch = strchr(d,'.');
  if(ch==0){ch = strchr(d,',');}
  if(ch)
   {
    ch[0]='.';
    int i=ch-d;
    if(CountAfterPoint>0)i+=CountAfterPoint+1;
    d[i]=0;
    if(CountAfterPoint)
     {
      while(d[--i]=='0')d[i]=0;
      if(d[i]=='.')d[i]=0;
     }
   }
  return strlen(d);
 }
//------------------------------------------------------------------------------
Str SPrintf(const char* format, ...)
 {
  Str s;
  va_list paramList;
  va_start(paramList, format);
  int size = vsnprintf(NULL, 0, format, paramList);
  s.AddItems(size);
  vsnprintf((char*)s.c_str(), size + 1, format, paramList);
  va_end(paramList);
  return s;
 }
//------------------------------------------------------------------------------
Str BinByteToStr(byte b)
 {
   Str s;
   if(b&128)s='1';else s='0';
   if(b&64)s+='1';else s+='0';
   if(b&32)s+='1';else s+='0';
   if(b&16)s+='1';else s+='0';
   if(b&8)s+='1';else s+='0';
   if(b&4)s+='1';else s+='0';
   if(b&2)s+='1';else s+='0';
   if(b&1)s+='1';else s+='0';
   return s;
 }
int BitsToChars(char*d,uint64 i)
 {
   for(int j=0;j<64;j++)
   {
    if(i&0x8000000000000000ll)
     *d = '1';
     else
     *d = '0';
    d++;i=i<<1;
   }
  *d=0;
  return 64;
 }
//------------------------------------------------------------------------------
Str OnlyDigit(const Str&s)
 {
  Str t;
  for(int i=1;i<=s.Size();i++)
   {
    char c = s.QGET(i);
    if(c>='0'&&c<='9')t.Add(c);
   }
  return t;
 }
//------------------------------------------------------------------------------
Str BinToHexStr(void *Buffer,int BufSize)
 {
  Str s;
  byte H,L;
  for(int i=0;i<BufSize;i++)
   {
    H=L=((char*)Buffer)[i];
    L&=15;H=H>>4;
    if(L<10)L+=48;else L+=55;
    if(H<10)H+=48;else H+=55;
    s+=(char)H;s+=(char)L;
   }
  return s;
 }
//------------------------------------------------------------------------------
bool  HexStrToBin(void *Buffer,const Str&s,int BufSize)
 {
  char H,L;
  if(BufSize*2>(int)s.Size())return false;
  byte*str = (byte*)s.c_str();
  for(int i=0;i<BufSize;i++)
   {
    H = str[i*2]; L = str[i*2+1];
    if(H>='0'&&H<='9')H-='0'; else
    if(H>='A'&&H<='F')H-='A'-10; else
    if(H>='a'&&H<='f')H-='a'-10; else return false;
    //-------------------------------
    if(L>='0'&&L<='9')L-='0'; else
    if(L>='A'&&L<='F')L-='A'-10; else
    if(L>='a'&&L<='f')L-='a'-10; else return false;
    ((char*)Buffer)[i]=(H<<4)+L;
   }
  return true;
 }
int HexStrToInt(const Str&s)
 {
  char L;int Res = 0;
  byte*str = (byte*)s.c_str();
  for(int i=0;i<s.Size();i++)
   {
    L = str[i];
    if(L>='0'&&L<='9')L-='0'; else
    if(L>='A'&&L<='F')L-='A'-10; else
    if(L>='a'&&L<='f')L-='a'-10; else return 0;
    Res = (Res<<4)+L;
   }
  return Res;
 }
//------------------------------------------------------------------------------
Str xDateToStr(int64 Date)
 {
   tm t = xDecodeDateTime(Date);
   Str res,temp;
   temp = NumToStr(t.tm_mday);
   if(temp.Size()==1)res+='0';
   res+=temp; res+='.';
   temp = NumToStr(t.tm_mon+1);
   if(temp.Size()==1)res+='0';
   res+=temp; res+='.';
   res+=NumToStr(t.tm_year+1900);
   return res;
 }
int64 xStrToDate(const Str& s)
 {
   if(s.Size()!=10)return 0;
   tm D; memset(&D,0,sizeof(D));
   D.tm_mday = (s[1]-48)*10+(s[2]-48);
   D.tm_mon = (s[4]-48)*10+(s[5]-48)-1;
   D.tm_year = ((s[7]-48)*1000+(s[8]-48)*100+(s[9]-48)*10+(s[10]-48))-1900;
   return xCodeDateTime(D);
 }
//------------------------------------------------------------------------------
Str   xDateTimeToFileNameStr(int64 Date)//yymmdd_hhnnss
 {
   tm t = xDecodeDateTime(Date);
   Str res,temp;
   res=NumToStr(t.tm_year+1900-2000);
   temp = NumToStr(t.tm_mon+1);
   if(temp.Size()==1)res+='0';
   res+=temp;
   temp = NumToStr(t.tm_mday);
   if(temp.Size()==1)res+='0';
   res+=temp;
   res+='_';
   temp = NumToStr(t.tm_hour);
   if(temp.Size()==1)res+='0';
   res+=temp;
   temp = NumToStr(t.tm_min);
   if(temp.Size()==1)res+='0';
   res+=temp;
   temp = NumToStr(t.tm_sec);
   if(temp.Size()==1)res+='0';
   res+=temp;
   return res;
 }

Str xDateTimeToStr(int64 Date)
 {
   tm t = xDecodeDateTime(Date);
   Str res,temp;
   temp = NumToStr(t.tm_mday);
   if(temp.Size()==1)res+='0';
   res+=temp; res+='.';
   temp = NumToStr(t.tm_mon+1);
   if(temp.Size()==1)res+='0';
   res+=temp; res+='.';
   res+=NumToStr(t.tm_year+1900);
   res+=' ';
   temp = NumToStr(t.tm_hour);
   if(temp.Size()==1)res+='0';
   res+=temp; res+=':';
   temp = NumToStr(t.tm_min);
   if(temp.Size()==1)res+='0';
   res+=temp; res+=':';
   temp = NumToStr(t.tm_sec);
   if(temp.Size()==1)res+='0';
   res+=temp;
//   t.tm_isdst;
   return res;
 }
int64 xStrToDateTime(const Str& s)
 {
   if(s.Size()!=19)return 0;
   tm D; memset(&D,0,sizeof(D));
   D.tm_mday = (s[1]-48)*10+(s[2]-48);
   D.tm_mon =  (s[4]-48)*10+(s[5]-48)-1;
   D.tm_year = ((s[7]-48)*1000+(s[8]-48)*100+(s[9]-48)*10+(s[10]-48))-1900;
   int64 Date = xCodeDateTime(D);
   D = xDecodeDateTime(Date);
   D.tm_hour = (s[12]-48)*10+(s[13]-48);
   D.tm_min =  (s[15]-48)*10+(s[16]-48);
   D.tm_sec =  (s[18]-48)*10+(s[19]-48);
   return xCodeDateTime(D);
 }
bool isOnlyDigit(const Str&s)
 {
  if(s.Size()==0)return false;
   for(int i=1;i<=s.Size();i++)
    if(s[i]<'0'||s[i]>'9')return false;
  return true;
 }
}
#ifndef __GNUC__
#pragma package(smart_init)
#endif
