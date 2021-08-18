#!/bin/bash
make clean 
make fullsubmit
git add .
git commit
git push origin main
echo done!
