#!/bin/bash

RULE_FILE_NAME="abRules.csv"
PORT_START=32768
PORT_END=60999

# exit if you do not want to override
if test -f "$RULE_FILE_NAME"; then
    echo "${RULE_FILE_NAME} already exists!"
    read -p "Do you want to override it? (y/n) " -n 1 -r
    echo  # intended new line
    if [[ ! $REPLY =~ ^[Yy]$ ]]
    then
        echo "exiting."
        [[ "$0" = "$BASH_SOURCE" ]] && exit 1 || return 1
    fi

fi

> $RULE_FILE_NAME
for i in $(seq $PORT_START $PORT_END)
do
    echo "6,10.0.2.1,${i},10.0.1.1,80" >> $RULE_FILE_NAME
done
