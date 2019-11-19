/*
 * ICClib.h
 *
 *  Created on: Sep 12, 2019
 *      Author: marvin
 */

#ifndef _ICCLIB_H_
#define _ICCLIB_H_

#include <stdint.h>

class libicc {
public:
	libicc();
	/* use virtual otherwise linker will try to perform static linkage */
	virtual ~libicc();

	/*
	 * Generates Adresses with selected index and security
	 * Address is a int8_t array with size 81
	 * function to give a seed and dont use the embedded one in the PL
	 * to use the embedded one give a NULL pointer
	 */
	//virtual int generateAddress(uint32_t index, int security, char* address);
	virtual int generateAddress(char* seed_in, uint32_t index, int security,
			char* address);
	/*
	 * doPow takes a transaction as tx_pow with 2673 Trytes as int8_tacters A-Z and 9
	 * gives back a nonce in int8_tacter format with size 28
	 */
	virtual void doPow(char* tx_pow, char* nonce, int mwm);

	/*
	 * CurlHash takes 2673 Trytes as int8_tacters A-Z and 9
	 * gives back a hash in int8_tacter format with size 82
	 */
	virtual void CurlHash(char* trytes, char* hash);

	/*
	 * keccak384 takes an array with size 288
	 * gives back a hash with size 12
	 */
	virtual void keccak384(uint8_t* txdata, uint32_t* hash);

	/*
	 * troika takes an array with size 243
	 * gives back a hash with size 243
	 * input and output are encoded as simple numbers not ascii characters
	 * trits are 0,1,2
	 */
	virtual void troika(unsigned char* input, unsigned char* result);
private:
protected:

};

void throw_exception(char const*, char const*, int);

extern "C" libicc* create_libicc();

extern "C" void destroy_libicc(libicc* object);

#endif /* SRC_ICCLIB_H_ */
