Here is a sample to visualize the xPolytopes.

0. Prepare sample.ar3a (coordinates of the graph nodes) and
   sample.ngph (node connectivity;undirected graph).  The sample file
   in this folder contains the structure of supercooled TIP4P/2005 liquid water at 200 K.

1. Make the list of the rings (@RNGS format) from the graph topology
file (@NGPH format).

    ./countrings.py 7 < sample.ngph > sample.rngs

2. Pick up 6- or 7-membered rings only.

    awk '(NF==1)||($1==6)||($1==7){print}' sample.rngs > sample.67.rngs

3. Combine the rings to make the polyhedral fragments
(a.k.a. vitrites)  that the number of rings is not larger than 3.

    ../polyhed.pl -l 3 < sample.67.rngs | fgrep -v @FSEP > sample.48.rset

Now you get the 3-hedrons made of 6- and 7-membered rings only.  It is
known that only the vitrites type #4 and #8 satisfy these conditions.



