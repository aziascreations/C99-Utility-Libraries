#pragma once

#include <stddef.h>

/**
 * Get the byte size of given allocated memory block.
 * @param ptr Pointer to the memory block.
 * @return Size of the block in bytes.
 * @warning May return sizes bigger or equal to the block's size on UNIX platforms !
 */
size_t memUtils_getSize(void *ptr);
