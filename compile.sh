# $chaos$
# Abstract: Quick and dirty hack to compile everything.

# The source root.
ROOT=$(pwd)
INSTALL_PREFIX=/tftpboot

# Set up the link so we will know which architecture is the
# current. FIXME: Add an architecture check perhaps?? :-)
rm -f $ROOT/stormG3/include/storm/current-arch
ln -sf $ROOT/stormG3/include/storm/ia32 $ROOT/stormG3/include/storm/current-arch

cd $ROOT/stormG3 || exit
cons $STORM_OPTIONS || exit

# Set up the link in the installed root as well.
rm -f $INSTALL_PREFIX/data/programming/c/headers/storm/current-arch
ln -sf $INSTALL_PREFIX/data/programming/c/headers/storm/ia32 $INSTALL_PREFIX/data/programming/c/headers/storm/current-arch

cd $ROOT/libraries
cons || exit
cd $ROOT/programs
cons || exit
./install.sh
cd $ROOT/modules
cons || exit
cd $ROOT
