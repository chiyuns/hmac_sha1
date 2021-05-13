#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "sha1.h"
#include "hmac.h"

char message[] = "a";

void print_hex(uint8_t *ptr, int len)
{
    int i;
    for (i = 0; i < len; i++)
        printf("%2.2x", ptr[i]);
    printf("\n");
}


void sha1_test()
{
    int len;
    uint8_t hash[SHA1_DIGEST_SIZE];
    sha1_ctx_t ctx;
    sha1Init(&ctx);

    len = strlen(message);

    sha1Update(&ctx, message, len);
    sha1_finish(&ctx, hash);

    printf("************SHA-256*************\n");
    printf("message:\n%s\n", message);
    printf("digest:\n");
    print_hex(hash, SHA1_DIGEST_SIZE);
}

  
//十六进制字符串转换为字节流
void HexStrToByte(const char* source, unsigned char* dest)
{
    short i;
    unsigned char highByte, lowByte;
    for (i = 0; i < strlen(source); i += 2)
    {
        highByte = toupper(source[i]);
        lowByte = toupper(source[i + 1]);
 
        if (highByte > 0x39)
            highByte -= 0x37;
        else
            highByte -= 0x30;
 
        if (lowByte > 0x39)
            lowByte -= 0x37;
        else
            lowByte -= 0x30;
 
        dest[i / 2] = (highByte << 4) | lowByte;
    }
}

void hmac_sha1_test()
{
    printf("msg:%s\n", message);
    char key[] = "00112233445566778899AABBCCDDEEFF";
	printf("key:%s\n", key);
	
    uint8_t mac[SHA1_DIGEST_SIZE];
	
	uint8_t hexkey[16];  //
	HexStrToByte((const char*)key, (unsigned char*)hexkey);

	int i = 0;
	for(i = 0; i<16;i++)
    {
        printf("%d ",hexkey[i]);
    }
	
	printf("\n");

    printf("************HMAC-SHA-1*************\n");
    hmac_sha1(message, strlen(message), hexkey, MASTER_KEY_SIZE/2, mac);
	
    print_hex(mac, SHA1_DIGEST_SIZE);
}




int main()
{
	//sha1_test();
    hmac_sha1_test();
    return 0;
}
