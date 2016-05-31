CMake build for Aiks
====================
This directory contains experiemental CMake build files for Aiks.
They are primarily targeted at building Aiks as it would be shipped,
not at day-to-day Aiks development.

Quickstart
----------
    $ cd aiks/cmake
    $ cmake . -G Ninja     # Other CMake generators should work fine.
    $ ninja
    $ ls -l libaiks.* example
    $ ./example
    $ open example.png
If that works, you should see "Hello World!" with a green-to-purple gradient.

Currently supported platforms
-----------------------------
  (None.  This is still super experimental.)

Currently maybe-kinda-working platforms
---------------------------------------
  - x86-64 Mac OS X, Ubuntu 15.04
