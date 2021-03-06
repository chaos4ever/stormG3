# $chaos: compile.sh,v 1.7 2002/11/13 20:13:15 per Exp $
# Abstract: Quick and dirty hack to compile everything.

# The source root.
ROOT=$(pwd)
INSTALL_PREFIX=/tftpboot/chaos
STORM_OPTIONS="root=$INSTALL_PREFIX"

# Set up the link so we will know which architecture is the
# current. FIXME: Add an architecture check perhaps?? :-)
rm -f $ROOT/stormG3/include/storm/current-arch
#ln -sf $ROOT/stormG3/include/storm/ia32 $ROOT/stormG3/include/storm/current-arch
cd $ROOT/stormG3/include/storm || exit
ln -sf ia32 current-arch
cd - || exit

# Build stormG3
cd $ROOT/stormG3 || exit
cons $STORM_OPTIONS || exit

# Set up the link in the installed root as well.
rm -f $INSTALL_PREFIX/data/programming/c/headers/storm/current-arch
#ln -sf $INSTALL_PREFIX/data/programming/c/headers/storm/ia32 $INSTALL_PREFIX/data/programming/c/headers/storm/current-arch
cd $INSTALL_PREFIX/data/programming/c/headers/storm || exit
ln -sf ia32 current-arch
cd - || exit

# Build the rest (order is important).
cd $ROOT/libraries
cons root=$INSTALL_PREFIX || exit
cd $ROOT/programs
cons root=$INSTALL_PREFIX || exit
./install.sh
cd $ROOT/modules
cons root=$INSTALL_PREFIX || exit
cd $ROOT
