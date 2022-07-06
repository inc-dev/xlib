//---------------------------------------------------------------------------
#ifndef xxCRCH
#define xxCRCH
//http://ru.wikipedia.org/wiki/Crc
unsigned char Crc8(unsigned char *pcBlock, unsigned char len);
unsigned short Crc16( unsigned char *pcBlock, unsigned short len );
unsigned long Crc32(unsigned char *buf, unsigned long len);
#endif
