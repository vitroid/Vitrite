all:
	-make 1h.rngs
	ls *.rngs | sed -e s/rngs/py.rset/ | xargs make
	ls *.rngs | sed -e s/rngs/pl.rset/ | xargs make

#special
1h.py.rset: 1h.rngs
	../polyhed.py -l 5 < $< > $@
#general
%.pl.rset: %.rngs
	../polyhed.pl < $< > $@
%.py.rset: %.rngs
	../polyhed.py < $< > $@
1h.ngph:
	genice 1h -f graph -r 2 2 2 > $@
%.rngs: %.ngph
	../../CountRings/countrings.x < $< > $@


clean:
	-rm *.rset 1h.ngph 1h.rngs
