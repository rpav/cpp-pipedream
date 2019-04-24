#!/bin/sh
CMD_DIR=`dirname $0`
ROOT=`realpath $CMD_DIR/..`
CMD="./doxyproc.sh"

cd $CMD_DIR

$CMD || exit 1

waitfile -r \
         -d "$ROOT/include" \
         -d "$CMD_DIR/doxyproc" \
         -f "$CMD_DIR/Doxyfile" \
         -g '*.md' \
         -g '*.rst' \
         -g '*.hpp' \
         "$CMD"
