#!/bin/sh
set -x
tftp 192.168.1.10 <<END_SCRIPT
binary
get $1
q
END_SCRIPT

