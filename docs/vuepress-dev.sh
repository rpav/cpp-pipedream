#!/bin/sh

root=`dirname $0`

cd $root/website
vuepress dev --no-cache --no-clear-screen --debug
