#!/bin/bash

rm -f *.gv *.png

parse < testing_code/p1.py > p1.gv
parse < testing_code/p2.py > p2.gv
parse < testing_code/p3.py > p3.gv

dot -T png -o p1.png p1.gv
dot -T png -o p2.png p2.gv
dot -T png -o p3.png p3.gv

diff p1.gv example_output/p1.gv
diff p2.gv example_output/p2.gv
diff p3.gv example_output/p3.gv
