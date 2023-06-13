#include "curve25519_donna.c"

#include "hardware/flash.h"


#define FLASH_TARGET_OFFSET (256 * 1024)

int set_secretkey(const uint8_t *secret) {
    uint8_t e[32];
    for (int i = 0; i < 32; ++i) e[i] = secret[i];
    // E: "clamping"
    e[0] &= 248; // E: clears the 3 least significant bits of secret, so it's a multiple of 8
    // this helps in preventing potential timing side-channel attacks
    e[31] &= 127; // E: clears the most significant bit
    // prevents potential attacks related to small-subgroup confinement
    e[31] |= 64; // E: sets bit 6 to 1, ensuring the result is at least 64

  // Copy the 32 bytes to flash memory
  flash_range_program(FLASH_TARGET_OFFSET, e, 32);
}

// Obviously this has to be protected, just for testing
uint8_t* get_secret_key() {
  return (uint8_t *) FLASH_TARGET_OFFSET;
}

int get_pubkey(
      uint8_t *mypublic, 
      const uint8_t *basepoint) {
  
  const uint8_t *secret = get_secret_key();

  int64_t bp[10], x[10], z[11], zmone[10];
  int i;

  fexpand(bp, basepoint); // E: litle endian 32-byte number is put into polynomial form into bp
  cmult(x, z, secret, bp); // E: secret*bp storing x and z coordinate (e contains secret)
  crecip(zmone, z); // E: storing the multiplicative inverse of z in  zmone
  fmul(z, x, zmone); // E: z = x*zmone, which is the "normal form" of the resulting x coordinate
  fcontract(mypublic, z); // E: convert polynomial form number back to little-endian 32-byte array
  // E: the resulting mypublic is the  x coordinate of the point
  // ( scalar is the secret, resulting point is the public key)
  // this uniquely defines the complete point
  return 0;
}
