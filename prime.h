#ifndef PRIME_H_INCLUDED
#define PRIME_H_INCLUDED

#include "common.h"

void testPrime();


bool isPrime(unsigned long long n);
bool isPrime2(unsigned long long n) ;
bool isPrime64(const unsigned long long n);
void primeUsingBit();
void primeUsingBit2();
unsigned int* primeUsingBit2(unsigned long long capacity);
void prime(int ordinal) ;
bool* primes(unsigned long long size);
bool isPrimeFilter(int n);


unsigned int getBit(int index);
void setBit(unsigned int& num,int index,int value);
void printBit(unsigned int num);

#endif // PRIME_H_INCLUDED
