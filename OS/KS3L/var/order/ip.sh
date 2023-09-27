#!/bin/bash

gateway_ip=$(ip route | awk '/default/ {print $3}')

if [ -n "$gateway_ip" ]; then
    echo "Current network management: $gateway_ip"
    ping -c 4 $gateway_ip
    if [ $? -eq 0 ]; then
        echo "success"
    else
        echo "error"
    fi
else
    echo "not infomation"
fi
