OBJECTS = src/bootloader/boot.o src/kernel/kernel.o

.PHONY: all clean install

all: kernel.bin CORE.iso

%.o: %.cpp
	rm -f $@
	g++ -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -o $@ -c $<

%.o: %.s
	as --32 -o $@ $<

kernel.bin: linker.ld $(OBJECTS)
	ld -melf_i386 -T $< -o $@ $(OBJECTS)
	mkdir -p /isofiles/boot
	cp kernel.bin /mnt/d/projects/CORE_os/kernel.bin

iso: kernel.bin
	mkdir -p /isofiles/boot
	cp $< /isofiles/boot/$<
	grub-mkrescue -o CORE.iso isofiles

clean:
	rm -f $(OBJECTS) kernel.bin CORE.iso
