# Simulated-CPU

**Partial implementation of a 6502 8-bit CPU**

Left out instructions for logical shifts, compare, clear flags, etc

This cpu can only do the most basic calculations, such as looping (infinitely), adding and subtracting, etc.

Architecture specifics are in cpuarch.txt

Round robin scheduling: no clock implemented, burst time for each process is one fetch cycle
