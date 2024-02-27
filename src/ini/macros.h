/** @file */

#if !defined(NP_ONCE_C99_GOODIES_INI_MACROS)
#define NP_ONCE_C99_GOODIES_INI_MACROS

#include "../text.h"

#if defined(NP_GOODIES_INI_USE_WCHAR) || defined(NP_GOODIES_ALL_USE_WCHAR)

#define np_ini_L(str) L##str

#define np_ini_char wchar_t

#define np_ini_strlen wcslen
//#define np_ini_strcmp wcscmp

#define np_ini_areStringsEqual text_areStringsEqualW
#define np_ini_copyString text_copyW

#else

#define np_ini_L(str) str

#define np_ini_char char

#define np_ini_strlen strlen
//#define np_ini_strcmp strcmp

#define np_ini_areStringsEqual text_areStringsEqual
#define np_ini_copyString text_copy

#endif


// TODO: Add support for more hashmap types once implemented !
#include "../hashmaps/chained/hashmap.h"
#define np_ini_hashmap ChainedHashMap

#define np_ini_hashmapCreate(sizePower) hashmap_chained_create(sizePower)
#define np_ini_hashmapGetByHash(hashMap, hash) hashmap_chained_getByHash(hashMap, hash)
#define np_ini_hashmapOverwriteByHash(hashMap, data, hash, cb_freeData) hashmap_chained_overwriteByHash(hashMap, data, hash, cb_freeData)
#define np_ini_hashmapDeleteByHash(hashMap, hash, cb_freeData) hashmap_chained_deleteByHash(hashMap, hash, cb_freeData)
#define np_ini_hashmapFree(hashMap, cb_freeData) hashmap_chained_free(hashMap, cb_freeData)

#endif //NP_ONCE_C99_GOODIES_INI_MACROS
