for i in $(seq 3 10); do
    for j in $(seq 1 10); do
        ./driver.out $i 1
        python3 driver.py $i 1
    done
done