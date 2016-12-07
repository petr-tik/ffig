
#pragma once

#define Int_RC_SUCCESS 0
#define Int_RC_FAIL 1

#define EXPORT __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C"
{
#endif
EXPORT void Int_clear_error();
EXPORT const char* Int_error();
EXPORT void Int_dispose(const void* myInt);

EXPORT int Int_Int_create(int value, const void** rv); 

EXPORT int Int_value(const void* myInt, int* rv);
 
#ifdef __cplusplus
}
#endif
