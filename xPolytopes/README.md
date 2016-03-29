Here is a sample to visualize the xPolytopes.

0) Prepare sample.ar3a (coordinates of the graph nodes) and sample.ngph (node connectivity;undirected graph).  The sample file in this folder contains the structure of supercooled TIP4P/2005 liquid water at 200 K.

1) Make the list of the rings (@RNGS format) from the graph topology
file (@NGPH format).

    ./countrings.py 7 < sample.ngph > sample.rngs

2) Pick up 6- or 7-membered rings only.

    awk '(NF==1)||($1==6)||($1==7){print}' sample.rngs > sample.67.rngs

3) Combine the rings to make the polyhedral fragments
(a.k.a. vitrites)  that the number of rings is not larger than 3.

    ../polyhed.pl -l 3 < sample.67.rngs | fgrep -v @FSEP > sample.48.rset

Now you get the 3-hedrons made of 6- and 7-membered rings only.  It is
known that only the vitrites type #4 and #8 satisfy these conditions.
That is, you get the ingredients of the xPolytopes.

4) Convert the set of the rings to the set of the edges.

    ./rset2ngph.pl -a sample.ngph sample.67.rngs < sample.48.rset > sample.48.rset.ngph

5) Calculate the twist of each vitrites.

    ./fragmentchirality.py sample.48.rset.ngph < sample.ar3a > sample.twi.vmrk
	
6) Give integers to the twist values as the color palette (used for visualization).

    awk 'BEGIN{getline;print;getline;print}{x=int($1*2*8+8+0.5); if(x<0)x=0;if(x>16){x=16}print x+3}' sample.twi.vmrk > sample.twi.color2.vmrk

7) Obtain the lists of right- and left-twisted vitrites.

    paste sample.twi.vmrk sample.48.rset | awk '(NF==2){$1="";print}(NF==1){print $1}(NF>2)&&($1>0.25){$1="";print}' | sed -e 's/^ //' > sample.48R.rset
    paste sample.twi.vmrk sample.48.rset | awk '(NF==2){$1="";print}(NF==1){print $1}(NF>2)&&($1<-0.25){$1="";print}' | sed -e 's/^ //' > sample.48L.rset

8) Convert the positions of the fragment into the PovRay data.

    cat sample.48.rset sample.ar3a sample.67.rngs  | ./rset2yap.py -R -s 0.8 -G sample.twi.color2.vmrk |  grep -v '^y' | sed -e 's/^@ \([0-9]*\)/y \1/' | ./yap2pov.pl | fgrep -v test.inc |  sed -e '/cylinder/s/R[0-9]*/RFrame/' -e '/cylinder/s/TEX[0-9]*/TEXFrame/' > sample.48.pov

9) Render the povray file.

    povray +w1000 +h1000 +FN     +Q9  +A0.3 +AM2   +D -Lbin -L/include +HIview.inc -isample.48.pov -Osample.48.sq1.png

Please consult the software for details.
