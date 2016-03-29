COUNTRINGS=~/github/CountRings
VITRITE=..

all: sample.ngph sample.rngs sample.67.rngs sample.48.rset sample.48.rset.ngph sample.twi.vmrk sample.twi.color2.vmrk sample.48R.rset sample.48L.rset sample.48.pov sample.48.sq1.png
	echo Done.

#Lookup rings in the network (max. 7-membered)
%.rngs: %.ngph
	./countrings.py 7 < $< > $@
#Filter 6- or 7-membered rings only
%.67.rngs: %.rngs
	awk '(NF==1)||($$1==6)||($$1==7){print}' $< > $@
#Lookup the xpolytopes (vitrites ID #4 (6^3) or ID #8 (67^2)).
%.48.rset: %.67.rngs
	$(VITRITE)/polyhed.pl -l 3 < $< | fgrep -v @FSEP > $@
#Express the fragments as a set of edges. (@NGPH format)
%.48.rset.ngph: %.48.rset %.67.rngs %.ngph
	./rset2ngph.pl -a $*.ngph $*.67.rngs < $*.48.rset > $@
#Twist of the vitrites #4 and #8
%.twi.vmrk: %.ar3a %.48.rset.ngph
	./fragmentchirality.py $*.48.rset.ngph < $*.ar3a > $@
#Conversion from twist value to the color palette number
%.twi.color2.vmrk: %.twi.vmrk #$(MAKEFILE)
	awk 'BEGIN{getline;print;getline;print}{x=int($$1*2*8+8+0.5); if(x<0)x=0;if(x>16){x=16}print x+3}' $< > $@
#Right-twisted xPolytopes (twist > +0.25)
%.48R.rset: %.twi.vmrk %.48.rset
	paste $^ | awk '(NF==2){$$1="";print}(NF==1){print $$1}(NF>2)&&($$1>0.25){$$1="";print}' | sed -e 's/^ //' > $@
#Left-twisted xPolytopes (twist < -0.25)
%.48L.rset: %.twi.vmrk %.48.rset
	paste $^ | awk '(NF==2){$$1="";print}(NF==1){print $$1}(NF>2)&&($$1<-0.25){$$1="";print}' | sed -e 's/^ //' > $@
#visualize by povray
%.48.pov: %.48.rset %.ar3a %.67.rngs %.twi.color2.vmrk
	cat $*.48.rset $*.ar3a $*.67.rngs  | ./rset2yap.py -R -s 0.8 -G $*.twi.color2.vmrk |  grep -v '^y' | sed -e 's/^@ \([0-9]*\)/y \1/' | ./yap2pov.pl | fgrep -v test.inc |  sed -e '/cylinder/s/R[0-9]*/RFrame/' -e '/cylinder/s/TEX[0-9]*/TEXFrame/' > $@
%.sq1.png: %.pov view.inc common.inc
	povray +w1000 +h1000 +FN     +Q9  +A0.3 +AM2   +D -Lbin -L$(BIN)/include +HIview.inc -i$*.pov -O$@






#prepare scripts(private)
TRAJTOOLS=~/github/TrajTools
prepare: rset2ngph.pl fragmentchirality.py rset2yap.py rsetadjacency.py countrings.py
fragmentchirality.py: ../tools/fragmentchirality.py
	ln -s $<
rset2ngph.pl: ../tools/rset2ngph.pl
	ln -s $<
rset2yap.py: ../tools/rset2yap.py
	ln -s $<
rsetadjacency.py: ../tools/rsetadjacency.py
	ln -s $<
%.py: $(COUNTRINGS)/%.py
	cp $< .
#%.pl: $(TRAJTOOLS)/%.pl
#	cp $< .
