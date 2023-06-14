#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/regs/rosc.h"
#include "hardware/regs/addressmap.h"

#include "curve25519_helper.c"

#include "sha256/sha256.c"

#define LED_PIN  25 // GPIO of built-in LED

// Just for testing, not suitable for cryptography
uint8_t rnd(){
  // Example from https://forums.raspberrypi.com//viewtopic.php?f=145&t=302960
    int k, random=0;
    volatile uint8_t *rnd_reg=(uint8_t *)(ROSC_BASE + ROSC_RANDOMBIT_OFFSET);
    
    for(k=0;k<8;k++){
      random = random << 1;
      random = random + (0x01 & (*rnd_reg));
    }

    return random;
}

// Just for testing, not suitable for cryptography
void get_random_data(uint8_t *buf, uint16_t len) {
    for(int i = 0; i < len; i=i+1)
    {
        buf[i] = rnd();
    }
}

void sha256(const unsigned char *input, size_t ilen, unsigned char output[32]) {
    mbedtls_sha256(input, ilen, output, 0);
}

// Testing https://www.rfc-editor.org/rfc/rfc8235.html#section-3.2
int main()
{
    stdio_init_all();
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);
    printf("ON\n");
    // sleep_ms(1000);
    
    while(true) {
      // PREP: priv/pub keys

      // Alice generates 32 random bytes
      // this gets set as secret key (clamping in helper file)
      uint8_t secret_key_a[32];
      get_random_data(secret_key_a, 32);

      // WORKS this tests testvectors
      // puts(mbedtls_sha256_self_test(secret_key_a[0]));
      uint8_t hashed_secret_key_a[32];
      
      // WORKS This does 1 hash
      mbedtls_sha256(secret_key_a, 32, hashed_secret_key_a, 0);
      puts(hashed_secret_key_a);

//       // Store in flash memory (raw data for now, should be different)
//       set_secretkey(secret_key_a);
//       uint8_t* a = get_secret_key();

// // x coordinate 9
//       unsigned char basepoint_G[32] = {9};
//       uint8_t pubkey[32];
//       get_pubkey(pubkey, basepoint_G);


      // puts("Hello, world!");

      // uint8_t randomness[32];
      // get_random_data(randomness, 32);

      // puts(randomness);

      // gpio_put(LED_PIN, 1);
      // printf("ON\n");
      sleep_ms(1000);
    }

    return 0;
}
