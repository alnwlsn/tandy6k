# tandy6k
stuff for my tandy 6000 computer project (and might be applicible to the TRS-80 Model II, TRS-80 Model 12, TRS-80 Model 16 or TRS-80 Model 16B)

## 8inch-adapter-pcb
Single sided, CNC cut PCB for converting the 50 pin 8" floppy disk cable to the more common 34 pin cable. Based on this https://github.com/pski/fd50to34 and made so I could quickly cut one out and start using it. Intended for a Gotek floppy disk emulator with https://github.com/keirf/flashfloppy

It might only work with a Gotek. On that, you can assign pin 34 to Drive Ready, and pin 2 to Disk Changed. On a real 5" or 3.5" drive, pin 34 is usually Disk Changed (but you can sometimes jumper it to drive ready instead), and pin 2 is used to select the density or disk RPM. 

## ps2-keyboard
Converts a ps2 keyboard to one that works with a TRS-80 8-inch system. Made because I was getting impatient waiting to fix the broken keyboard I have. Runs on an Arduino pro micro, but similar things should work. Similar to this converter https://www.smbaker.com/tandy-1000-upgrades-ps2-tandy-keyboard-adapter but for the Tandy 6000 instead of the Tandy 1000, and made more lazily by using the Arduino framework. 
