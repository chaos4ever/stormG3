#!/bin/bash

# $Id$
# Abstract: Install our programs onto the ramdisk.
# Author: Per Lundberg <per@chaosdev.org>

export PROGRAMS=boot
export ROOT=/tftpboot
export RAMDISK_ROOT=/mnt/chaos-ramdisk

# The mount/umount is neccessary because otherwise the filesystem will
# be marked as dirty -- and we don't mount a dirty filesystem.

mount ${RAMDISK_ROOT}
for e in ${PROGRAMS}
do
  echo "Copying $e"
  install -s ${ROOT}/system/programs/$e ${RAMDISK_ROOT} || (umount ${RAMDISK_ROOT} ; exit 1)
done
umount ${RAMDISK_ROOT}
