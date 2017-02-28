for file in map{1..100}.pf
do
  echo "This file is ${file}" > ${file}
done

