#!/bin/bash

while true; do
    echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr0/brightness
    echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr1/brightness
    echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr2/brightness
    echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr3/brightness

    echo 1 > /sys/devices/platform/leds/leds/beaglebone:green:usr0/brightness
    echo 1 > /sys/devices/platform/leds/leds/beaglebone:green:usr1/brightness
    echo 1 > /sys/devices/platform/leds/leds/beaglebone:green:usr2/brightness
    echo 1 > /sys/devices/platform/leds/leds/beaglebone:green:usr3/brightness

    sleep 1

    echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr0/brightness
    echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr1/brightness
    echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr2/brightness
    echo 0 > /sys/devices/platform/leds/leds/beaglebone:green:usr3/brightness

    sleep 1
done

