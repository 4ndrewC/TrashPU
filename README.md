# TrashPU

**Tried to write a 16-bit CPU**

Left out instructions for logical shifts, compare, clear flags, etc

This cpu can only do the most basic calculations, such as looping (infinitely), adding and subtracting, etc.

Architecture specifics are in cpuarch.txt (not accurate lol)

Round robin scheduling (multi-tasking): no clock implemented, burst time for each process is one fetch cycle
- instr1-3.in are input instructions
- paged + virtual memory for multi-tasking
- doesn't fully work
