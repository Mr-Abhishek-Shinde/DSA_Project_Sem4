set size 4, 4
set multiplot layout 1, 2

set xrange [0:20]
set yrange [0:20]

# Read coordinates from a data file
set datafile separator ","   # Specify the separator used in your data file

unset key
set title ("Previous Route")
plot "data/previous_route" u 1:2 w lp pt 20, "data/previous_route" using 1:2:(sprintf("(%g,%g)", $1, $2)) with labels offset 1,1 notitle, 

unset key
set title ("New Route")
plot "data/new_route" u 1:2 w lp pt 20, "data/new_route" using 1:2:(sprintf("(%g,%g)", $1, $2)) with labels offset 1,1 notitle  

