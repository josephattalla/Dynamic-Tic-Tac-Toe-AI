for i in $(seq 3 6); do
    for j in $(seq 1 4); do
        for _ in $(seq 0 5); do
            ./driver $i $j
            python3 driver.py $i $j
        done
    done
done