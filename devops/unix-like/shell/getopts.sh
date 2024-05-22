#!/bin/bash

set -e

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]:-$0}")" \
    &>/dev/null && pwd 2>/dev/null)"
WORKDIR=$(dirname $SCRIPT_DIR)
ENV_FILE="${WORKDIR}/.env"

help() {
    echo
    echo "Usage: $0 [-n]"
    echo "    -h display this help and exit"
    echo "    -n run npm install"
    exit 0
}

run_npm=false

while getopts "hn" opt; do
    case "$opt" in
    h) help ;;
    n) run_npm="$OPTARG" ;;
    ?) help ;;
    esac
done

logger() {
    echo "[$(date +%Y-%m-%d\ %H:%M:%S)] $1"
}

load_env() {
    logger "Loading environment variables from: ${ENV_FILE}"
    source ${ENV_FILE}
    logger "ENV: ${ENV}"
}

setup_prisma() {
    logger "Generating prisma client..."
    npx prisma generate

    logger "Running prisma migrate..."
    npx prisma migrate deploy
}

setup_nodejs() {
    NODE_VERSION=$(cat .nvmrc | xargs)
    PATH=/opt/node/${NODE_VERSION}/bin:$PATH
    current_node=$(node --version | xargs)
    if [[ "v${NODE_VERSION}" != $current_node ]]; then
        error="Current Nodejs ${current_node} is not the required version, "
        error+="exiting."
        logger $error

        exit 1
    fi
    logger "Current Nodejs Version: ${current_node}"
}

main() {
    load_env
    cd $WORKDIR
    setup_nodejs
}

main
