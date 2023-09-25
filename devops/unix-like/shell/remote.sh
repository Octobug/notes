#!/bin/bash

ssh HostName -t "command"
rsync -r LocalDir HostName:RemoteDir \
    --rsync-path 'sudo -u HostName rsync'

