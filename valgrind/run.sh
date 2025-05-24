#!/usr/bin/env bash

# -------------------------------------------------------------------------------------------- #
#                                            run.sh                                            #
# -------------------------------------------------------------------------------------------- #
#                                                                                              #
#   [!] This script should be run from the project root (`./valgrind/run.sh`). [!]             #
#                                                                                              #
#   This script runs the native executable of the game through valgrind, suppressing any       #
#   suppressions listed in 'valgrind/supp/valgrind.supp'. A log is written to                  #
#   'valgrind/log/valgrind.log'.                                                               #
#                                                                                              #
# -------------------------------------------------------------------------------------------- #

SUPP_FILE="valgrind/supp/valgrind.supp"
SUPP_FLAG=""
if [ -e $SUPP_FILE ]; then
    SUPP_FLAG="--suppressions=$SUPP_FILE"
fi

LOG_FILE="valgrind/log/valgrind.log"
EXEC="build/out/native/blinks-thinks"

valgrind --leak-check=full --track-origins=yes \
    "$SUPP_FLAG" \
    --log-file="$LOG_FILE" "$EXEC"
