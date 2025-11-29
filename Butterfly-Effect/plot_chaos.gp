set terminal pngcairo size 1000,600 enhanced font 'Verdana,10'
set output "chaos_divergence.png"
set datafile separator ","
set grid

# カオス解析の肝：縦軸を対数にする
set logscale y

set title "Sensitivity to Initial Conditions (Butterfly Effect)"
set xlabel "Time [s]"
set ylabel "Distance between Trajectories (log scale)"

# 軸の範囲設定（エラー回避のため）
# 距離が0になると対数が取れないので少し下駄を履かせるか、範囲を制限する
set yrange [1e-4:10] 

# プロット
# 列番号は自分のCSVに合わせて変更せよ（例：2列目が距離なら 1:2）
plot "result.csv" using 1:2 every ::1 with lines lw 2 lc rgb "red" title "Distance |r_A - r_B|"
