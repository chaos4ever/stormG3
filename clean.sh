# $chaos: $
# Abstract: Clean things up in order for a full rebuild to proceed.

ROOT=$PWD

cd stormG3 && cons -r ; cd $ROOT
cd libraries && cons -r ; cd $ROOT
cd modules && cons -r ; cd $ROOT
cd programs && cons -r ; cd $ROOT
