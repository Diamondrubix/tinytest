This is a fork of tinytest.

The project itself is called tinytest.h,
the other files are only there to test tinytest.h and make sure that the unit
testing framework works as intended.

This code works like the original tinytest except that now instead of stopping at the first error found
it will go continue and display all of the errors at the end.

The program does this by storing all the error information in a linked list. (used to be a dynamicArrayClass)