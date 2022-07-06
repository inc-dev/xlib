//---------------------------------------------------------------------------
#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxUTF8.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
UnicodeChar TxCodePageUTF8::GetUnicodeChar(const Str& s,int& Pos)
 {
  byte b1 = s.Take(Pos);Pos++;
  if(b1 <= 0x7f) return b1 & 0x7f;
  byte b2 = s.Take(Pos);Pos++;
  if(b1 < 0xe0)return ((b1 & 0x1f) << 6) | (b2 & 0x3f);
  byte b3 = s.Take(Pos);Pos++;
  if(b1 < 0xf0)return ((b1 & 0x0f) << 12) | ((b2 & 0x3f) << 6) | (b3 & 0x3f);
  byte b4 = s.Take(Pos);Pos++;
  if(b1 < 0xf8)return ((b1 & 0x07) << 18) | ((b2 & 0x3f) << 12) | ((b3 & 0x3f)<<6) | (b4 & 0x3f);
  byte b5 = s.Take(Pos);Pos++;
  if(b1 < 0xfc)return ((b1 & 0x03) << 24) | ((b2 & 0x3f) << 18) | ((b3 & 0x3f)<<12)| ((b4 & 0x3f)<<6)|(b5 & 0x3f);
  byte b6 = s.Take(Pos);Pos++;
  return ((b1 & 0x01) << 30) | ((b2 & 0x3f) << 24) | ((b3 & 0x3f) << 18) | ((b4 & 0x3f)<<12)| ((b5 & 0x3f)<<6)|(b6 & 0x3f);
 }
//------------------------------------------------------------------------------
void TxCodePageUTF8::AddUnicodeChar(Str&s,UnicodeChar code)
 {
  if(code<0x80)     {s+=char(code);return;}
  if(code<0x800)    {s+=char(0xC0|(code>>6));s+=char(0x80|(code&0x3f)); return;}
  if(code<0x10000)  {s+=char(0xE0|(code>>12));s+=char(0x80|((code>>6)&0x3f));s+=char(0x80|(code&0x3f)); return;}
  if(code<0x200000) {s+=char(0xF0|(code>>18));s+=char(0x80|((code>>12)&0x3f));s+=char(0x80|((code>>6)&0x3f));s+=char(0x80|(code&0x3f)); return;}
  if(code<0x4000000){s+=char(0xF8|(code>>24));s+=char(0x80|((code>>18)&0x3f));s+=char(0x80|((code>>12)&0x3f));s+=char(0x80|((code>>6)&0x3f));s+=char(0x80|(code&0x3f)); return;}
  s+=char(0xFC|((code>>30)&1));
  s+=char(0x80|((code>>24)&0x3f));
  s+=char(0x80|((code>>18)&0x3f));
  s+=char(0x80|((code>>12)&0x3f));
  s+=char(0x80|((code>>6)&0x3f));
  s+=char(0x80|(code&0x3f));
 }
//------------------------------------------------------------------------------
}
#ifndef __GNUC__
#pragma package(smart_init)
#endif
