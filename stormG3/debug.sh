#!/bin/sh
# Use this script to debug the kernel.
# $chaos$

gdb -x remote.gdb source/ia32/stormG3
