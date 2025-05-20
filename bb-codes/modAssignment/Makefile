obj-m  += mod3p.o
 
ifdef ARCH
  #You can update your Beaglebone path here.
  KSRC = ../../build-kernel/linux
else
  KSRC = /lib/modules/$(shell uname -r)/build
endif
 
all:
	make -C $(KSRC)  M=$(shell pwd) modules
 
clean:
	make -C $(KSRC)  M=$(shell pwd) clean
