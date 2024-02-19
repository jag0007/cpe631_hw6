for i in 1 2 4 8 128; 
do
    for j in 1 2 4 8 1024; 
    do 
        echo $i $j
        sed -n 16p m5out_${i}_${j}/stats.txt       
    done
done

#for (( i =  112;  i < 129; i = i+8))
#do
#    gem/build/X86/gem5.opt two_level_prob2.py Mm_serial_static_var.out 64 $i
#    mv m5out m5out_${i}
#done
#gem/build/X86/gem5.opt two_level_prob2.py Mm_serial_static_var.out 64 8 
