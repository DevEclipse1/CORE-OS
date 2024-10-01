# CORE-OS
CORE (Console Output Rendering Environment), an barebones operating system, that you operate using your mouse!


How to build it yourself:
1. Download WSL (If on windows), or download a linux virtual machine if you dont already have one
2. Run WSL, or your linux virtual machine (Dedicated users main linux)

ALL THE STEPS NOW ARE GONNA HAVE TO BE FOLLOWED IN THE LINUX VM/WSL!
1. Download the source
2. CD into the source folder
3. Run this command(s): ```sudo make kernel.bin && sudo make iso```
4. Now in the root directory of the source you get CORE.iso, that is your bootable iso!


Credits:
1. https://www.youtube.com/watch?v=1rnA6wpF0o4&ab_channel=WriteyourownOperatingSystem (Providing me the boot stuff, using c++)
2. https://www.gnu.org/software/grub/ (Bootloader)


The code is very messy, probably unoptimized too, would be great if anyone would clean it up!
