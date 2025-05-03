#!/usr/bin/env bash

valgrind --leak-check=full --track-origins=yes \
    --suppressions=./supp/valgrind.supp \
    --log-file=./log/valgrind.log ../build/blinks-thinks
