#!/usr/bin/env perl

#
#Convert polyheral fragments into @NGPH format.
#modified from rset2yap.pl.
#

use strict;

sub usage{
    print STDERR "usage: $0 [-a graph.ngph] ringlist.rngs < polyhedra.rset\n";
    print STDERR "-a ngph\tOutput fragment with absolute node IDs.\n";
    die;
}

my $abso=0;
if ( $ARGV[0] eq '-a' ){
    shift;
    $abso=shift || usage();
}

my $rngs = shift || usage();

#just for num of nodes
my $totalnodes;
if ($abso ){
    open NGPH, "<$abso";
    while(<NGPH>){
	if ( /^\@NGPH/){
	    $totalnodes = <NGPH>;
	    last;
	}
    }
}

open RNGS, "<$rngs";

while(<STDIN>){
    if (/^\@RSET/){
	#
	#Read ring list
	#
	my @rngs;
	while(<RNGS>){
	    if ( /^\@RNGS/ ){
		my $n = <RNGS>;
		while(<RNGS>){
		    chomp($_);
		    @_ = split();
		    last if $_[0] == 0;
		    shift @_;
		    push @rngs, [ @_ ];
		}
		last;
	    }
	}

	#
	#Read polyhedra (ring sets)
	#
	my $nrings = <STDIN>;
	die "Inconsistency in num of rings $nrings $#rngs.\n" if ( $nrings != $#rngs + 1 );
	while(<STDIN>){
	    chomp;
	    my @rings = split();
	    last if $rings[0] == 0;
	    shift @rings;

	    #
	    #Extract nodes used by a polyhedron
	    #
	    my %edges;
	    my %members;
	    my $nnodes = 0;
	    foreach my $ring ( @rings ){
		my @nodes = @{$rngs[$ring]};
		foreach my $node ( @nodes ){
		    if ( ! defined $members{$node} ){
			$members{$node} = $nnodes;
			$nnodes ++;
		    }
		}
		push @nodes, $nodes[0];
		for(my $i=0;$i<$#nodes;$i++){
		    $edges{$nodes[$i]}{$nodes[$i+1]}++;
		    $edges{$nodes[$i+1]}{$nodes[$i]}++;
		}
	    }
	    if ( $abso ){
		#
		#w/o renumber
		#
		print "\@NGPH\n";
		print $totalnodes;
		foreach my $i ( keys %edges ){
		    foreach my $j ( keys %{$edges{$i}} ){
			if ( $i < $j ){
			    print $i, " ", $j, "\n";
			}
		    }
		}
		print "-1 -1\n";
	    }
	    else{
		print "\@NGPH\n$nnodes\n";
		foreach my $i ( keys %edges ){
		    foreach my $j ( keys %{$edges{$i}} ){
			if ( $i < $j ){
			    print $members{$i}, " ", $members{$j}, "\n";
			}
		    }
		}
		print "-1 -1\n";
	    }
	}
    }
}



