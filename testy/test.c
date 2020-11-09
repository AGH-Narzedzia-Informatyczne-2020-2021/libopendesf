#include <stdio.h>
#include <stdint.h>
#include <time.h>
// Enable ECB, CTR and CBC mode. Note this can be done before including aes.h or at compile-time.
// E.g. with GCC by using the -D flag: gcc -c aes.c -DCBC=0 -DCTR=1 -DECB=1
#define CBC 1

#include "../src/aes.h"

static void wyswietl(uint8_t* tab, uint32_t n)
{
    uint8_t max = 16;
    for (uint32_t i = 0; i <n; ++i)
    {
        if(i%max == 0)
            putchar('\n');
        printf("%.2X ", tab[i]);
    }
}

static inline uint8_t losuj()
{
    return rand()%256;
}

static void przesun(uint8_t* tab, uint32_t n)
{
    for(int i = n -1;i>0;--i)
    {
        tab[0] ^= tab[i];
        tab[i] ^= tab[0];
        tab[0] ^= tab[i];
    }
}

int main(void)
{
    srand(time(0));

    uint8_t s1[] =      { 0xAA, 0x00 };
    uint8_t tmp16[16];
    uint8_t tmp32[32];

    uint8_t karta[16] = { 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xFF };
    uint8_t serwer[16]= { 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xFF };

    uint8_t klucz[] =   { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  =     { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    struct AES_ctx ctx_karta;
    struct AES_ctx ctx_serwer;
    AES_init_ctx_iv(&ctx_karta, klucz, iv);
    AES_init_ctx_iv(&ctx_serwer, klucz, iv);

    printf("[klucz]: ");
    wyswietl(klucz,16);
    printf("\n\n");

    printf("[iv]: ");
    wyswietl(iv,16);
    printf("\n\n");

    printf("[karta]: ");
    wyswietl(karta,16);
    printf("\n\n");

    printf("[serwer]: ");
    wyswietl(serwer,16);
    printf("\n\n");

    printf("-----------------------------------------------\n");
//-------s->k---------
    printf("[serwer]$ ");
    wyswietl(s1,2);
    printf("\n\n");
//-------k->s---------
    memcpy(tmp16,karta,16);
    AES_CBC_encrypt_buffer(&ctx_karta, tmp16, 16);

    printf("[karta_]$ ");
    wyswietl(tmp16,16);
    printf("\n\n");
//-------s->k---------
    AES_CBC_decrypt_buffer(&ctx_serwer, tmp16, 16);
    przesun(tmp16,16);
    memcpy(tmp32,tmp16,16);
    memcpy(tmp32+16,serwer,16);
    AES_CBC_encrypt_buffer(&ctx_serwer, tmp32, 32);
    printf("[serwer]$ ");
    wyswietl(tmp32,32);
    printf("\n\n");
//--------k->s-------------
    AES_CBC_decrypt_buffer(&ctx_karta, tmp32, 32);
    memcpy(tmp16,tmp32+16,16);
    przesun(tmp16,16);
    AES_CBC_encrypt_buffer(&ctx_karta, tmp16, 16);
    printf("[karta_]$ ");
    wyswietl(tmp16,16);
    printf("\n\n");
//-------wynik---------
    AES_CBC_decrypt_buffer(&ctx_serwer, tmp16, 16);
    printf("[serwer]< ");
    wyswietl(tmp16,16);
    printf("\n\n");
    /**/
    return 0;
}


