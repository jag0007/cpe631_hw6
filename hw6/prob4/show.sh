for ((i = 8; i < 129; i = i+8))
do
echo ${i}
sed -n 16p m5out_${i}/stats.txt
done
