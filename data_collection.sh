for i in $(seq 3 10); do
    for j in $(seq 1 3); do
        ./driver $i $j
        python3 driver.py $i $j
    done
done