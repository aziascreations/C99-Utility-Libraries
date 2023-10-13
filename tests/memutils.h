#pragma once

#include <stddef.h>

/**
 * Get the byte size of given allocated memory block.
 * @param ptr Pointer to the memory block.
 * @return Size of the block in bytes.
 */
size_t memUtils_getSize(void *ptr);
