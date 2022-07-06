#ifndef xxEAN_8_13H
#define xxEAN_8_13H
void DecodeEAN13(unsigned char*des,unsigned char*source,int CountBitLine=2,int SkipBitForBegin=0);//(12+1bytes)*CountBitLine
void DecodeEAN8(unsigned char*des,unsigned char*source,int CountBitLine=2,int SkipBitForBegin=0); // (9+1bytes)*CountBitLine
//----------------------------------------------------------------------------------------------------
void DecodeEAN13_(unsigned char*des,int CountBitLine=2,int SkipBitForBegin=0);//(12+1bytes)*CountBitLine
void DecodeEAN8_(unsigned char*des,int CountBitLine=2,int SkipBitForBegin=0); // (9+1bytes)*CountBitLine
#endif
