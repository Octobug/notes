#!/bin/bash

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]:-$0}")" \
    &>/dev/null && pwd 2>/dev/null)"
WORKDIR=$SCRIPT_DIR

logger() {
    echo "[$(date +%Y-%m-%d\ %H:%M:%S)] $1"
}

###############################################################################
untracked_files=""
changed_files=""

# file patterns need to be untracked locally (but not ignored) by git
patterns=(
    "dir/subdir1/*.ext"
    "dir/subdir2/*.ext"
)

list_changed() {
    changed_files=$(git status --porcelain | awk '{print $2}')
}

list_untracked() {
    untracked_files=$(git ls-files -v | grep ^[h] | awk '{print $2}')
}

retrack() {
    list_untracked

    for uf in ${untracked_files}; do
        git update-index --no-assume-unchanged ${uf}
        logger "retracked ${uf}"
    done
}

untrack() {
    list_changed

    for cf in ${changed_files}; do
        for ptn in "${patterns[@]}"; do
            if [[ $cf == $ptn ]]; then
                git update-index --assume-unchanged "${cf}"
                exit_code=$?

                if [ $exit_code -eq 128 ]; then
                    logger "${cf} has never been tracked, add/ignore/delete it."
                elif [ $exit_code -ne 0 ]; then
                    exit $exit_code
                fi

                logger "untracked changed file: ${cf}"
            else
                continue
            fi
        done
    done
}

help() {
    echo "Usage: $0 [-n]"
    echo "    -h display this help and exit"
    echo "    -n git update-index --no-assume-unchanged <all untracked files>"
    exit 0
}

while getopts "hn" opt; do
    case "$opt" in
    h) help ;;
    n)
        retrack
        exit 0
        ;;
    ?) help ;;
    esac
done

main() {
    cd $WORKDIR

    untrack
}

main
