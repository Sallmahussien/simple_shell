#!/bin/bash

test_files=$(find . -name "*.bash")
for test_file in $test_files; do
    if [ "$test_file" != "./checker.bash" ] && [ "$test_file" != "./test_all.bash" ]; then
        echo "Running test: $test_file"
        ./checker.bash ./hsh "$test_file"
        echo "---------------------------"
    fi
done
