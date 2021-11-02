$DATA << EOD
#Language             Records #     Bulding time  Sorting time  Testing time  Total time        RSS memory usage
"cpp optimized"          100,000,000 B:   0.944 s, S:   9.957 s, T:   0.011 s, Total:  11.040 s, Mem: 1.5 GB (1565676 kB)
"cpp debug"              100,000,000 B:   2.436 s, S:  56.625 s, T:   0.061 s, Total:  60.540 s, Mem: 1.5 GB (1565704 kB)
"c optimized"            100,000,000 B:   0.919 s, S:  31.706 s, T:   0.033 s, Total:  32.790 s, Mem: 3.0 GB (3126516 kB)
"c debug"                100,000,000 B:   1.836 s, S:  40.860 s, T:   0.043 s, Total:  43.010 s, Mem: 3.0 GB (3126384 kB)
"go"                     100,000,000 B:   0.727 s, S:  30.036 s, T:   0.031 s, Total:  31.150 s, Mem: 1.5 GB (1614904 kB)
"java"                   100,000,000 B:   1.849 s, S:  77.551 s, T:   0.086 s, Total:  85.740 s, Mem: 3.9 GB (4062540 kB)
"python"                  20,000,000 B:  26.594 s, S:  54.847 s, T:   0.163 s, Total: 162.790 s, Mem: 9.0 GB (9466100 kB)
EOD

set title "Generating and sorting" 
set xlabel "Language"
set ylabel "Processing time"
set y2label "Memory used"

XVAL=0.5
YVAL=0.8
set label "* Python test with limited amount of records" at screen XVAL,screen YVAL
set key at screen 0.4,screen YVAL

set terminal png size 1200,600
set output 'Results.png'

set boxwidth 0.5 relative 
set style fill solid 0.5
set xtics rotate

set style data histograms
set style histogram clustered gap 1

#set style line 1 linecolor rgb("#AA0000")
set y2tics

plot $DATA  using 13:xtic(1) title "Processing time" lc rgb("#CC0000"), \
     $DATA  using 16:xtic(1) axis x1y2 title "Memory usage" lc rgb("#009900"), \
     $DATA  using ($0 - 1. / 5):($13 + 10):(sprintf("%.1f s", $13)) with labels title "" textcolor rgb("#CC0000") font "Times,9", \
     $DATA  using ($0+ 1. / 5):($16 + 0.5):(sprintf("%.1f GB", $16)) axis x1y2  with labels title "" textcolor rgb("#009900") font "Times,9", \
     10 title ""

#     $DATA2  using ($2 / 300.0) linestyle 1 axis x1y2 with lines title "CVS retrieval MB/s"
