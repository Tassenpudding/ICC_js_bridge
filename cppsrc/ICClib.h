/*
 * ICClib.h
 *
 *  Created on: Sep 12, 2019
 *      Author: marvin
 */

#ifndef SRC_ICCLIB_H_
#define SRC_ICCLIB_H_

#include <stdint.h>

class ICC_lib {
public:
	ICC_lib();
	/* use virtual otherwise linker will try to perform static linkage */
	virtual ~ICC_lib();

	/*
	 * Generates Adresses with selected index and security
	 * Address is a int8_t array with size 81
	 * alternative overloaded function to also give a seed and dont use the embedded one in the PL
	 */
	virtual int generateAddress(uint32_t index, int security, char* address);
	virtual int generateAddress_seed(char* seed_in, uint32_t index, int security, char* address);
	/*
	 * doPow takes a transaction as tx_pow with 2673 Trytes as int8_tacters A-Z and 9
	 * gives back a nonce in int8_tacter format with size 28
	 */
	virtual void doPow(char* tx_pow, char* nonce);

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

	/*virtual void attachToTangle_lib(const int8_t* trunkTransaction,
	 const int8_t* branchTransaction, int minWeightMagnitude, int8_t* trytes,
	 int numTrytes);*/
	virtual void test_all1();
private:
	bool validateTrytes(int8_t* trytes, int len, bool checkzero);
};

#endif /* SRC_ICCLIB_H_ */
