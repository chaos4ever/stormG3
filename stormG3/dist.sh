#!/bin/bash

# $chaos$
# Script for creating distributions.

APPEND=$1
VERSION=$2
TMPDIR=/tmp
SRCDIR=$(pwd)

rm -rf $TMPDIR/storm$APPEND-$VERSION
mkdir $TMPDIR/storm$APPEND-$VERSION
cp -r . $TMPDIR/storm$APPEND-$VERSION
tar czf storm$APPEND-$VERSION.tar.gz --exclude \*CVS\* --exclude \*~ --exclude \*.tar\* -C $TMPDIR storm$APPEND-$VERSION
tar cjf storm$APPEND-$VERSION.tar.bz2 --exclude \*CVS\* --exclude \*~ --exclude \*.tar\* -C $TMPDIR  storm$APPEND-$VERSION
rm -rf $TMPDIR/storm$APPEND-$VERSION
ls -l $TMPDIR/storm$APPEND-$VERSION
