rm -rf times.txt

touch times.txt

echo "05" >> times.txt

for filename in inputs/05/*; do 
    echo "${filename}"
    (time ./project < "${filename}" > /dev/null) &>> times.txt; 
done

echo "\n" >> times.txt
echo "025" >> times.txt

for filename in inputs/025/*; do 
    echo "${filename}"
    (time ./project < "${filename}" > /dev/null) &>> times.txt; 
done