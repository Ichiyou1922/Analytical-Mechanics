set terminal pngcairo size 800,800 enhanced font 'Verdana,10'
set output "trajectory.png"
set datafile separator ","
set grid

set title "Double Pendulum Trajectory"
set xlabel "x [m]"
set ylabel "y [m]"

# アスペクト比を1:1に固定（これ重要）
set size ratio -1
set xrange [-2.2:2.2]
set yrange [-2.2:2.2]

# 振り子AとBの軌道を重ねて描く
# （例：3,4列目がAのx,y / 5,6列目がBのx,y だとする）
plot "result.csv" using 3:4 every ::1 with lines lw 1 lc rgb "blue" title "Pendulum A", \
     "result.csv" using 5:6 every ::1 with lines lw 1 lc rgb "red" title "Pendulum B"
