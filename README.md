# powerkernel 

## Maintainer

## Info

## File Structure

platform/ folder should contains platform specific bringup & utility functions,
not generic functions should allowed in there

src/ folder should contains generic routines, using platform specific API's
these codes should be able to run in every supported platform.

## Serial Debugging

from now on, i'll be using multiplexed monitor/serial setup, which is basically
2 in 1 system. for changing between monitor mode and serial monitor, simply
press ctrl+a c. for old mode, edit makefile, change line -serial mon:stdio to
-monitor stdio -serial pty and save it


## Root Makefile Targets

make assemble --> Assembles bootloader for target architecture

make compile --> Compiles all sources to object files

make link --> Links all object files into a single kernel binary

make iso --> Prepares a bootable ISO that includes kernel & bootloader

make clean --> Removes all object files

make prune --> Removes all object files & end products

make boot --> Executes qemu with produced ISO file

