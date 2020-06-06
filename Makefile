CC=gcc
NAME=libmd380_vocoder.a
INSTALL_PATH=/usr/local/lib
INCLUDE_PATH=/usr/local/include
OBJECTS=firmware.o ram.o md380_vocoder.o

all: md380_vocoder

md380_vocoder: $(OBJECTS)
	$(AR) rcs $(NAME) $(OBJECTS)

firmware.o:
	wget -N http://www.dudetronics.com/radio/md380fw.img
	objcopy \
		-I binary md380fw.img \
		--change-addresses=0x0800C000 \
		--rename-section .data=.firmware \
		--add-symbol ambe_encode_thing=0x08050d91 \
		--add-symbol ambe_unpack=0x08048c9d \
		--add-symbol ambe_decode_wav=0x08051249 \
		-O elf32-littlearm -B arm firmware.o
ram.o:
	wget -N http://www.dudetronics.com/radio/md380ram.img
	objcopy \
		-I binary md380ram.img \
		--change-addresses=0x20000000 \
		--rename-section .data=.sram \
		--add-symbol ambe_inbuffer=0x20011c8e \
		--add-symbol ambe_outbuffer0=0x20011aa8 \
		--add-symbol ambe_outbuffer1=0x20011b48 \
		--add-symbol ambe_mystery=0x20011224 \
		--add-symbol ambe_en_mystery=0x2000c730 \
		--add-symbol wav_inbuffer0=0x2000de82 \
		--add-symbol wav_inbuffer1=0x2000df22 \
		--add-symbol ambe_outbuffer=0x2000dfc6 \
		-O elf32-littlearm -B arm ram.o

clean:
	rm -f *.o *.a *.img *~

install:
	cp $(NAME) $(INSTALL_PATH)
	cp *.h $(INCLUDE_PATH)

