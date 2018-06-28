all:
	ls *.rngs | sed -e s/rngs/pl.rset/ | xargs make
	ls *.rngs | sed -e s/rngs/py.rset/ | xargs make

%.pl.rset: %.rngs
	../polyhed.pl < $< > $@
%.py.rset: %.rngs
	../polyhed.py < $< > $@
