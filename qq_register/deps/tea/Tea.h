#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <time.h>

//#define CRYPT_ONE_BYTE
#define GET_TEA_BUFSIZE(l) ((((8 - (((l) + 10) & 0x07)) & 0x07)+(l) + 10))


typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;

typedef struct tagTEACTX
{
    uint8 buf[8];
    uint8 bufPre[8];
    const uint8* pKey; //指向16字节的key 
    uint8* pCrypt;
    uint8* pCryptPre;
} TEACTX, *LPTEACTX;

uint16 Host2NetShort(uint16 usHost);
uint16 Net2HostShort(uint16 usNet);
uint32 Host2NetLong(uint32 ulHost);
uint32 Net2HostLong(uint32 ulHost);
void EnCipher(const uint32*const v, const uint32*const k, uint32*const w);
void DeCipher(const uint32*const v, const uint32*const k, uint32*const w);
static void EncryptEach8Bytes(TEACTX* pCtx);
uint32 Encrypt(TEACTX* pCtx, const uint8* pPlain, uint32 ulPlainLen, const uint8* pKey, uint8* pOut, uint32* pOutLen);
static void DecryptEach8Bytes(TEACTX* pCtx);
uint32 Decrypt(TEACTX* pCtx, const uint8* pCipher, uint32 ulCipherLen, const uint8* pKey, uint8* pOut, uint32* pOutLen);
