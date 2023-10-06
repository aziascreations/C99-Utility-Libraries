# Benchmarks
These benchmarks serve as justifications for some of my choices in some small pieces of code throughout my library.

Unless someone can find more efficient ways to perform these actions,
 I will not accept modifications to these bits of code.<br>
And especially not if *"mUh ClEaN cOdE iS bEtTeR"* is waived around.

**Test machine:**
* Windows 11 22H2
* Ryzen 5 3600
* 16 GB RAM @ 2133 MHz

More test machines will be added once the hashmaps are done.<br>
There should be Win32 and Linux x64, and ARM64 Linux.

**Test conditions:**
* Using `RELEASE` target.
* Test is ran 2 times before to prevent any caching and prefetch BS.
* Ran through a non-admin CLI.

**Programming ???:**
* Assembly-level optimisations can be done but aren't prioritised.
* Intrinsics aren't allowed in generic tests.
  * They are often CPU/architecture dependant.
  * They should be done in their own parallel test.
* We're using a trash value to prevent zero-code optimisations.
  * Slow down the tests by one bitwise AND instruction for each iteration.
  * Prevents having cumbersome compiler directives and linker options to prevent it.
* Non-removal of zero-code is checked through a quick look in Ghidra.
* Optimisations through CPU ISA extensions isn't done yet.
  * Requires more complex setup.
  * Currently only interested in results that apply to the library.

## Calculating powers of 2
Compares the performances between the 2 following pieces of code:
* `pow(2, exponent)`
* `2 << (exponent - 1)`

**Results:**
* Iterations: 100.000.000
* Bitwise: 1421 ms
* Pow():   3780 ms

**Remarks:**
* Pow takes **266.01%** of the time Bitwise takes.
* Bitwise takes **37.59%** of the time Pow takes.
* Results, and bitwise method, cannot be applied to powers of any number who isn't itself a power of 2.
* Can't they actually...

**Limitations:**
* Cannot be done with `exponent == n` if `n` is our integer bit size/width.
* The exponent cannot be negative.
 
[Source Code (bm_powers_of_two.c)](./bm_powers_of_two.c)
