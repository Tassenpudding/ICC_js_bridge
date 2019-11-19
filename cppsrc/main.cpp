/* cppsrc/main.cpp */
#include <napi.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "ICClib.h"
#include <string>
#include <iostream>

using namespace std;

libicc* libHandle;

Napi::String doPow(const Napi::CallbackInfo& info)	{
	Napi::Env env = info.Env();
	if (info.Length() != 2 || !info[0].IsString() || !info[1].IsNumber() ) {
		Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
	}
	Napi::String n_api_trytes = info[0].As<Napi::String>();	
	string trytes = n_api_trytes.Utf8Value();	
	
	Napi::Number mwm = info[1].As<Napi::Number>();
	
	char nonce[28];
	nonce[27] = '\0';
	libHandle->doPow((char*)trytes.c_str(), nonce, mwm.Int32Value());	
	string* ret = new string(nonce);
	
	Napi::String returnValue = Napi::String::New(env, *ret);	
	return returnValue;	
}

Napi::String generateAddress(const Napi::CallbackInfo& info){ //string seed, int index, int security) {
	Napi::Env env = info.Env();
	if (info.Length() != 3 || !info[0].IsString() || !info[1].IsNumber() || !info[2].IsNumber()) {
		Napi::TypeError::New(env, "String or Number expected").ThrowAsJavaScriptException();
	}
	Napi::String n_api_seed = info[0].As<Napi::String>();
	string seed = n_api_seed.Utf8Value();	
	Napi::Number index = info[1].As<Napi::Number>();
	Napi::Number security = info[2].As<Napi::Number>();
	
	char address[82];	
	libHandle->generateAddress((char*)seed.c_str(), index.Int32Value(), security.Int32Value(), address);
	address[81] = '\0';
	string* ret = new string(address);
	
	Napi::String returnValue = Napi::String::New(env, *ret);	
	return returnValue;
}

/*Napi::Object deInit(){
	destroy(libHandle);
}*/

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	//void *handle;

	//handle = dlopen("/home/pi/lib/ICC_lib.so", RTLD_LAZY);
	//if (handle == NULL) {
	//	printf("dlopen failed\r\n");
	//}

	//ICC_lib* (*create)();
	//void (*destroy)(ICC_lib*);

	//create = (ICC_lib* (*)())dlsym(handle, "create_object");
	//destroy	= (void (*)(ICC_lib*))dlsym(handle, "destroy_object");

	libHandle	= (libicc*) create_libicc();
	
	exports.Set("doPow", Napi::Function::New(env, doPow));
	exports.Set("generateAddress", Napi::Function::New(env, generateAddress));
	//exports.Set("deInit", Napi::Function::New(env, deInit));	
	
	return exports;
}

NODE_API_MODULE(ICC, Init)