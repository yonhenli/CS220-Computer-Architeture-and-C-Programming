(date && whoami) | tee -a results.txt
make -k test | tee -a results.txt
