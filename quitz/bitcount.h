#ifndef BITCOUNT_H_INCLUDED
#define BITCOUNT_H_INCLUDED

int bitCountByRemainder(unsigned int);
int bitCountByBitOp(unsigned int);
int bitCountByBitOp2(unsigned int);
int bitCountFast(unsigned int);
int bitCountByDynamicTable(unsigned int);
int bitCountStatic4bitTable(unsigned int);
int bitCountStatic8bitTable(unsigned int);
int bitCountBy3bitGroup(unsigned int);
int bitCountParalell(unsigned int);
int bitCountParalell2(unsigned int);
int bitCountByByteStruct(unsigned int);
int bitCountByCPU(unsigned int);

#endif // BITCOUNT_H_INCLUDED
