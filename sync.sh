#!/bin/sh
commitmem=""
read -p "commit message: " commitmem
git pull
git add .
git commit -m "$commitmem"
git push

