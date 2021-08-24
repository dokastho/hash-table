#!/bin/bash
make clean 
make
git add .
git commit
git push origin main
echo done!
