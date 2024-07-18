#include <stdio.h>

#include "../src/text.h"

#include "../src/platform.h"

/**
 * This example illustrates how the ??? macros work with the "text" module.
 * If `UNICODE` is defined, all macros will point to their `W` variants instead of the `A` ones.
 */
int main() {
    // Defined a `char` or `wchar_t` string with an automatic `L` prefix for the string.
    // If the Win32API aren't included, the `TEXT` macros is automatically defined.
    text_char *myString = NP_TEXT("Hello World !");

    // Getting some low-level info
    // We can use the `UNICODE` and `NP_UNICODE` definitions to check if unicode is enabled.
    #if defined(NP_UNICODE)
    printf("Input: %ls\n", myString);
    #else
    printf("Input: %s\n", myString);
    #endif

    // We should get the same number in both ascii and unicode.
    printf("Chars: %llu\n", text_strlen(myString));

    // Be carefull with this one once UTF-8 support is enabled in 2.0.0 !
    printf("Bytes: %llu\n", text_strlen(myString) * sizeof(text_char));

    // From now on, you can assume any non `A` or `W` variant will resolve to
    //  the appropriate one during compilation.
    // This shouldn't cause any issues unless you forget to use macros when needed.

    return 0;
}
