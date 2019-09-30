/* cppsrc/main.cpp */
#include <napi.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "ICClib.h"

ICC_lib * myClass;

char tryte_str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void test_nonce() {
	char test_trytes[2673];
	char nonce[27];

	for (int i = 0; i < 10; i++) {
		//printf("TestTrytes:\n");
		for (int k = 0; k < 2673; k++) {
			test_trytes[k] = tryte_str[rand() % 27];
			//printf("%c",test_trytes[k]);
		}
		//printf("\n");

		myClass->doPow(test_trytes, nonce);
		printf("Nonce No.%i:", i);
		for (int j = 0; j < 27; j++) {
			printf("%c", nonce[j]);
		}
		printf("\r\n");
	}
}

void test_addr_gen() {
	char address[81];

	myClass->generateAddress(1, 1, address);
	printf("Security 1 Address: ");
	for (int i = 0; i < 81; i++) {
		printf("%c", address[i]);
	}
	printf("\r\n");

	myClass->generateAddress_seed(
			(char*)"TESTSEEDTESTSEEDTESTSEEDTESTSEEDTESTSEEDTESTSEEDTESTSEEDTESTSEEDTESTSEEDTESTSEEDT",
			1, 2, address);
	printf("Security 2 Address: ");
	for (int i = 0; i < 81; i++) {
		printf("%c", address[i]);
	}
	printf("\r\n");

	myClass->generateAddress(1, 2, address);
	printf("Security 2 Address: ");
	for (int i = 0; i < 81; i++) {
		printf("%c", address[i]);
	}
	printf("\r\n");

	myClass->generateAddress(1, 3, address);
	printf("Security 3 Address: ");
	for (int i = 0; i < 81; i++) {
		printf("%c", address[i]);
	}
	printf("\r\n");
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	void *handle;

	handle = dlopen("/home/pi/lib/ICC_lib.so", RTLD_LAZY);
	if (handle == NULL) {
		printf("dlopen failed\r\n");
	}

	ICC_lib* (*create)();
	void (*destroy)(ICC_lib*);

	create = (ICC_lib* (*)())dlsym(handle, "create_object");
	destroy	= (void (*)(ICC_lib*))dlsym(handle, "destroy_object");

	myClass	= (ICC_lib*) create();
	
  return exports;
}

NODE_API_MODULE(testaddon, InitAll)