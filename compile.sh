# $Id$
# Abstract: Quick and dirty hack to compile everything.

ROOT=$(pwd)
cd $ROOT/stormG3 || exit
cons || exit
cd $ROOT/libraries
cons || exit
cd $ROOT/modules
cons || exit
cd $ROOT/programs
cons || exit
cd $ROOT
