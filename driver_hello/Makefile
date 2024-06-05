# Makefile for driver
# if KERNELRELEASE is defined, we’ve been invoked from the
# kernel build system and can use its language.
ifneq (${KERNELRELEASE},)
	obj-m := hello.o
	# Otherwise we were called directly from the command line.
	# Invoke the kernel build system.
else
	KERNEL_SOURCE := /home/arthur/TPSE/tpse_2/linuxx/linux
	PWD := $(shell pwd)
	# Linux kernel 5.10 (one line)
	CC=/bin/arm-linux-gnueabihf-
	BUILD=boneblack
	CORES=12
	image=zImage
	PUBLIC_DRIVER_PWD= /home/arthur/TPSE/tpse_2/rootfs/lib/modules/5.10.162/kernel/drivers/hello
default:
	# Trigger kernel build for this module
	${MAKE} -C ${KERNEL_SOURCE} M=${PWD} -j${CORES} ARCH=arm \
		LOCALVERSION=${BUILD} CROSS_COMPILE=${CC} ${address} \
		${image} modules
	# copy result to public folder
	cp *.ko ${PUBLIC_DRIVER_PWD}
clean:
	${MAKE} -C ${KERNEL_SOURCE} M=${PWD} clean
endif


