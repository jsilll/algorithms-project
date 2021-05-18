rm -rf times.txt
touch times.txt

for filename in inputs/*; do 
    echo "${filename}"
    (time ./main.out < "${filename}" > /dev/null) &>> times.txt; 
done

# echo "\n" >> times.txt
# echo "025" >> times.txt

# for filename in inputs/025/*; do 
#     echo "${filename}"
#     (time ./project < "${filename}" > /dev/null) &>> times.txt; 
# done