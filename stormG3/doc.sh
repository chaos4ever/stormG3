#!/bin/sh

# $chaos: doc.sh,v 1.1 2002/10/08 19:03:40 per Exp $

doxygen ./doxygen 2> doxygen.log
cat doxygen.log
