#!/bin/sh
# Generate proto.h, with doxygen headers.
gawk -f ../../util/awk/mkproto.awk psnr.c >proto.h
