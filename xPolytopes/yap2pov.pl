#!/usr/bin/env perl


#
#Divide distorted polygon into a set of smooth_triangles
#

use strict;
my $tri;
if ( $ARGV[0] eq "-t" ){
  $tri = 1;
}
my $color=49;
my $layer=49;
my $radius = 1;#for sphere only
print "#include \"test.inc\"\n";
while(<STDIN>){
    if (/^\@/ ){
	chomp;
	@_ = split;
	$color = $_[1];
    }
    elsif (/^\y/ ){
	chomp;
	@_ = split;
	$layer = $_[1];
    }
    elsif (/^r/ ){
	chomp;
	@_ = split;
	$radius = $_[1];
    }
    elsif (/^p/){
	chomp;
	my @poly = split;
	shift @poly;
	my @radius;
	my $n = shift @poly;
	my ( $cx,$cy,$cz );
	for(my $i=0; $i<$#poly;$i+=3){
	    $cx += $poly[$i];
	    $cy += $poly[$i+1];
	    $cz += $poly[$i+2];
	}
	$cx /= $n;
	$cy /= $n;
	$cz /= $n;
	#
	#relative coord
	#
	for(my $i=0;$i<$n;$i++){
	    $poly[$i*3+0] -= $cx;
	    $poly[$i*3+1] -= $cy;
	    $poly[$i*3+2] -= $cz;
	    my $x = $poly[$i*3+0];
	    my $y = $poly[$i*3+1];
	    my $z = $poly[$i*3+2];
	    $radius[$i] = sqrt( $x*$x + $y*$y + $z*$z );
	}
	push @poly, $poly[0], $poly[1], $poly[2];
	push @radius, $radius[0];
	#
	#calc normal vectors for faces
	#
	my @normal;
	my @cn;
	for(my $i=0;$i<$n;$i++){
	    my @x = @poly[$i*3+0..$i*3+5];
	    my $x = $x[1]*$x[5] - $x[2]*$x[4];
	    my $y = $x[2]*$x[3] - $x[0]*$x[5];
	    my $z = $x[0]*$x[4] - $x[1]*$x[3];
	    my $rr = $radius[$i]*$radius[$i+1];
	    if ( $rr != 0 ){
		$x /= $rr;
		$y /= $rr;
		$z /= $rr;
	    }
	    else{
		$x=$y=$z=0;
	    }
	    push @normal, ($x,$y,$z);
	    $cn[0] += $x;
	    $cn[1] += $y;
	    $cn[2] += $z;
	}
	push @normal, @normal[0..2];
	$cn[0] /= $n;
	$cn[1] /= $n;
	$cn[2] /= $n;
	#
	#calc normal vectors for vertices
	#
	for(my $i=$n-1;0<=$i;$i--){
	    $normal[$i*3+3] += $normal[$i*3+0];
	    $normal[$i*3+4] += $normal[$i*3+1];
	    $normal[$i*3+5] += $normal[$i*3+2];
	    $normal[$i*3+3] /= 2;
	    $normal[$i*3+4] /= 2;
	    $normal[$i*3+5] /= 2;
	}
	$normal[0] = $normal[$n*3+0];
	$normal[1] = $normal[$n*3+1];
	$normal[2] = $normal[$n*3+2];
	for(my $i=0;$i<$n;$i++){
	    my @v;
	    if ( $tri ){
	      push @v, "<" . join(",", $cx, $cy, $cz) . ">";
	      push @v, "<" . join(",", $cx+$poly[$i*3+0], $cy+$poly[$i*3+1], $cz+$poly[$i*3+2]) . ">";
	      push @v, "<" . join(",", $cx+$poly[$i*3+3], $cy+$poly[$i*3+4], $cz+$poly[$i*3+5]) . ">";
	      print "triangle {", join(",\n", @v), "\ntexture {TEX$layer}\n}\n";
	      my @v;
	      push @v, "<" . join(",", $cx, $cy, $cz) . ">";
	      push @v, "<" . join(",", $cx+$poly[$i*3+0], $cy+$poly[$i*3+1], $cz+$poly[$i*3+2]) . ">";
	      print "cylinder{" . join(",",@v) . " RTHIN open texture {TEXTHIN}}\n";
	      my @v;
	      push @v, "<" . join(",", $cx+$poly[$i*3+0], $cy+$poly[$i*3+1], $cz+$poly[$i*3+2]) . ">";
	      push @v, "<" . join(",", $cx+$poly[$i*3+3], $cy+$poly[$i*3+4], $cz+$poly[$i*3+5]) . ">";
	      print "cylinder{" . join(",",@v) . " RTHIN open texture {TEXTHIN}}\n";
	    }
	    else{
	      push @v, "<" . join(",", $cx, $cy, $cz) . ">";
	      push @v, "<" . join(",", @cn[0..2]) . ">";
	      push @v, "<" . join(",", $cx+$poly[$i*3+0], $cy+$poly[$i*3+1], $cz+$poly[$i*3+2]) . ">";
	      push @v, "<" . join(",", $normal[$i*3+0], $normal[$i*3+1], $normal[$i*3+2]) . ">";
	      push @v, "<" . join(",", $cx+$poly[$i*3+3], $cy+$poly[$i*3+4], $cz+$poly[$i*3+5]) . ">";
	      push @v, "<" . join(",", $normal[$i*3+3], $normal[$i*3+4], $normal[$i*3+5]) . ">";
	      print "smooth_triangle {", join(",\n", @v), "\ntexture {TEX$layer}\n}\n";
	    }
	}
    }
    elsif (/^l/){
	chomp;
	#cylinder{<  8.445,  6.856, -5.268>,<  8.534,  6.748, -4.321> ROH open texture {TEXOH}}
	my @poly = split;
	shift @poly;
	my @v;
	push @v, "cylinder{<";
	push @v, join(",", @poly[0..2]);
	push @v, ">,<";
	push @v, join(",", @poly[3..5]);
	#push @v, "> RIM open texture {TEXP}}"; changed 20070914
	push @v, "> R$layer open texture {TEX$layer}}";
	print join(" ", @v), "\n";
    }
    elsif (/^c/){
	chomp;
	my @poly = split;
	shift @poly;
	my @v;
	push @v, "sphere{<";
	push @v, join(",", @poly[0..2]);
	#push @v, ">, $radius texture {TEXP}}"; changed 20070914
	push @v, ">, $radius texture {TEX$layer}}";
	print join(" ", @v), "\n";
    }
}
