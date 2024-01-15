#!/bin/bash
ARG=$(./generate_random_list.sh $1); ./push_swap $ARG | ./checker_linux $ARG
