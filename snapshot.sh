#!/bin/sh

cd ..
rm -rf chaos-$(date +%Y%m%d) 
mkdir chaos-$(date +%Y%m%d) || exit 1
echo "Copying..."
cp -r chaos/* chaos-$(date +%Y%m%d) || exit 1
echo "Cleaning..."
cd chaos-$(date +%Y%m%d) && ./clean.sh && cd ..
echo "Creating archive..."
tar --exclude CVS -cjf chaos-$(date +%Y%m%d).tar.bz2 chaos-$(date +%Y%m%d)
rm -rf chaos-$(date +%Y%m%d) || exit 1
cd chaos
