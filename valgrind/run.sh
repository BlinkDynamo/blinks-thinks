#!/usr/bin/env bash

# This script should be run from the project root (`./valgrind/run.sh`).

SUPP_FILE="valgrind/supp/valgrind.supp"
LOG_FILE="valgrind/log/valgrind.log"
EXEC="build/blinks-thinks"

valgrind --leak-check=full --track-origins=yes \
    --suppressions="$SUPP_FILE" \
    --log-file="$LOG_FILE" "$EXEC"
