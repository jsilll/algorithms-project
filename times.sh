rm -rf times.txt
touch times.txt

for filename in inputs/tests/*; do 
    echo "${filename}" >> times.txt
    (time ./main.out < "${filename}" >> times.txt) # &>> times.txt; 
done

# echo "\n" >> times.txt
# echo "025" >> times.txt

# for filename in inputs/025/*; do 
#     echo "${filename}"
#     (time ./project < "${filename}" > /dev/null) &>> times.txt; 
# done
