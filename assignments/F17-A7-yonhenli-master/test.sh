(date && whoami) | tee -a results.txt
make test 2>&1 | tee -a results.txt
./test | tee -a results.txt
