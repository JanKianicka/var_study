#!/usr/bin/perl
# PDL - Perl Data Language

# We will do excersises from 
# http://www.perlmonks.org/?node_id=598007
# Article: 
# RFC: Getting Started with PDL (the Perl Data Language)
# by lin0

use PDL;
$a = pdl [1..10];
# For online help use pdl> ? inv, or for searching simillar functions
# use apropo (?? inverse e.g.)
# See also pdl>demo , and >demo PDL
#
$scalar_piddle = pdl 42;
$one_dimensional_piddle = pdl(1,2,3);
$two_dimensional_piddle = pdl([1,2,3],[4,5,6]);
print $two_dimensional_piddle;
# In pdl>p $two_dimensional_piddle can be used
$pdl_of_zeroes = zeroes(10,2);
print "zeros:";
print $pdl_of_zeroes;

$pdl_of_ones = ones(5,3);
print "ones:";
print $pdl_of_ones;

$pdl_identity = identity(4,4);
print "identity:";
print $pdl_identity;

# Other function for initialization of piddles:
# random, grandom, randsym, sequence, xvals, yvals, zvals, 
# xlinvals, ylinvals, zlinvals, rvals, axisvals, allaxisvals

# Deafult is double, but other types are:
# byte, ushort, short, float, long

$new_pdl_of_zeroes  = zeroes(byte, 10, 2);
print "zeros_new:";
print $new_pdl_of_zeroes;

print "Size of byte matrix:\n";
$shape = $new_pdl_of_zeroes->shape;
print "Shape:",$shape,"\n";
print "Get_datatype:",$new_pdl_of_zeroes->get_datatype,"\n"; # get data type does not work reliably for byte type - in general PDL is very clumsy
$size_new_pdl_of_zeroes = prod($shape)*$new_pdl_of_zeroes->get_datatype;
print "Actual size:",$size_new_pdl_of_zeroes;


