# Exhaustive Search for Polyhedral Fragments (Vitrites)
## Counting policy

* The program looks up all the "polyhedral fragments"
  (a.k.a. vitrites) in the given random almost 4-connected undirected graph.
* It counts the fragments purely topologically. It does not use geometrical information.
* Edge direction is not considered. (Undirected graph)

## Algorithm

1. Choose 2 adjacent (i.e. edge-sharing) rings in the original graph.  We
   call this set of rings "faces".
1. Define the perimeter of the faces.
1. Choose one of the ring that shares three successive vertices (two successive edges) with the perimeter.
1. Add the ring to the faces, and extend the perimeter.
1. Repeat 1 .. 4 until the perimeter closes.  Now we get a polyhedron.
1. Exclude the polyhedron if any following test is not satisfied.
    1. Re-count the number of vertices, edges, and rings included in
       the polyhedron.  They must satisfy the Euler's characteristics:
       f-e+v=2.
	1. The polyhedron must not divide the original graph into two or
       more compositions.
1. Repeat 1 .. 6 until all the pairs of rings are consulted.

## Requirements

* Python 3
* NetworkX (a graph theory library for Python)
* A ring statistics algorithm (See https://github.com/vitroid/CountRings)

## Usage
Input data must be in <a href="http://theochem.chem.okayama-u.ac.jp/wiki/wiki.cgi/matto?page=%40RNGS">@RNGS</a> format (which is an output of the ring statistics algorithm https://github.com/vitroid/CountRings ). Output data will be in <a href="http://theochem.chem.okayama-u.ac.jp/wiki/wiki.cgi/matto?page=%40RSET">@RSET</a> format.

    % ./polyhed.py < test.rngs > test.rset

Note that Perl version (`polyhed.pl`) is now outdated.  Future supports
and updates will be made to the Python version (`polyhed.py`).
## Sample
The following is the expression of a cubic graph, which should have
six 4-cycles and a polyhedron.

    @RNGS
    8
    4 0 1 2 3
    4 0 1 5 4
    4 1 2 6 5
    4 2 3 7 6
    4 3 0 4 7
    4 4 5 6 7
    0

## Known Problems
The current definition of the rings depends on the context; that is,
if you cut out a polyhedral subgraph out of a large graph, the number
of rings in the subgraph is not always same as the number of rings at
the correspoding part of the large graph.
It happens because there might be a shortcut on the large graph that
prevents counting a ring in the subgraph.
(I will put here an illustration.)

## To Cite It

* M. Matsumoto, A. Baba, and I. Ohmine, Topological building blocks of hydrogen bond network in water, J. Chem. Phys. 127, 134504 (2007); [doi:10.1063/1.2772627](http://dx.doi.org/doi:10.1063/1.2772627)
