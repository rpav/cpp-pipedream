#!/bin/sh

root=`dirname $0`
output="$1"

if [ ! -d "$output" ]; then
    echo "Error: path not given or not a directory"
    echo "usage: deploy.sh <deploy-path>"
    exit 1
fi

cd $root/website
vuepress build && (rm -rf $output/*; mv .vuepress/dist/* $output/ && rmdir .vuepress/dist)
