#!/usr/bin/env bash

SECOND_IN_WEEK=604800
CURRENT_TIME=`date +%s`

lookup() {
    for path in $1/*; 
    do
        [[ -L "$path" && ! -e "$path" && $(( CURRENT_TIME - `stat -f%m "$path"` )) -ge SECOND_IN_WEEK ]] && echo $path
        [[ -d "$path" ]] && lookup $path
    done
}

lookup $1
