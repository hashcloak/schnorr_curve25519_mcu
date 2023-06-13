#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/regs/rosc.h"
#include "hardware/regs/addressmap.h"

#include "curve25519_helper.c"

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
      // Alice generates 32 random bytes
      // this gets set as secret key (clamping in helper file)
      uint8_t secret_key_a[32];
      get_random_data(secret_key_a, 32);
      // Store in flash memory (raw data for now, should be different)
      set_secretkey(secret_key_a);

      // 1. Alice chooses v
      uint8_t v[32];
      get_random_data(v, 32);
      // TODO this might be out of range

      // 2. Bob chooses a challenge c
      uint8_t c[32];
      get_random_data(c, 32);

      // 3. Alice computes r = v - a * c mod n
      unsigned char e1[32] = {3};
      unsigned char basepoint_G[32] = {9};

      // gpio_put(LED_PIN, 0);
      // printf("OFF\n");
      sleep_ms(1000);

      puts("Hello, world!");

      uint8_t randomness[32];
      get_random_data(randomness, 32);

      puts(randomness);

      // gpio_put(LED_PIN, 1);
      // printf("ON\n");
      sleep_ms(1000);
    }

    return 0;
}
