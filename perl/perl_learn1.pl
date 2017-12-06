#!/usr/bin/perl
# perl - Practical Extraction and Report Language

print "This is a test \n";

# variables, simple are string or integer
# '' exact string, "" - substitution possible

$i = 10;
$s1 = ' winter for the last $i months \n';
$s2 = " winter for the last $i months \n";
print  $i;
print  $s1;
print  $s2;

# perl automatically handles the variables and converts them
$a = "10";
print " a is $a   integer\n";
$a1=$a + 20; # + only makes sense as an integer operand
print "a1 is $a1  integer\n";
$a2=$a." months"; # . (concatenation) only makes sense for strings
print "a2 is $a2  string\n";
$a3=$a.$a1;
print " a3 is $a3  string\n";
$a4=$a3-1;
print " a4 is $a4  integer\n";

# Arithmetic operators : + , -, *, /, %, ** (exponent) integers
# unary +, -
# Assignment operators: =, +=, -=, *=, /=,%=, **= integers
# .= strings
# Standard comparisons for integers: <, >, <=, >= , ==, !=
# String comparison: eq, ne, lt, le, gt, ge (alphabetical order)

$t1 = ("10" == 10);
print "-$t1-\n";

print "10" == 10; # automatic conversion of string "10" to integer 10
" 10 " == 10;     # automatic conversion of string " 10 " to int 10
" 10 " eq "10";   # fails: first string has extra spaces
" 10 " eq " "."10"." ";

$t2 = ("abc" lt "cde" ) && ("abc" lt "Abc");
print "--$t2-\n";

$i=1; # prints in order numbers from 1 to 10, on separate lines
if ($i <= 10) {
    print "$i\n"; $i+=1;
}

# loops
print "While loop\n";
$i=1;  
while ($i<=10) { 
    print "$i\n"; 
    $i+=1;
}

print "for loop 1\n";
for $i (2,4,6) {
    print "$i\n"; 
}

print "for loop 2\n";
for ($i=1; $i<=10; $i+=1) {
    print "$i\n";
}

# there is missing yet excercise with opening the files


# time
$end_time = time;
print "Time: $end_time\n";


# array of strings and loop
@detail_time_logs = (['end time','$end_time'],['second','second']);
# push @detail_time_logs, 'third time: $end_time';
push @detail_time_logs, ['end_time: ',$end_time];
#print "@detail_time_logs\n";
#print scalar(@detail_time_logs);

foreach $j (@detail_time_logs){
   print $j;
   print "\n";
}

print "@$_\n" for @detail_time_logs;

my @array = ([1, 2, 3], [4, 5, 6], [7, 8, 9]);
my $top_left     = $array[0][0];  # 1
my $bottom_right = $array[2][2];  # 9

print "@$_\n" for @array;
$array_size = scalar(@array);
$detail_time_logs_size = scalar(@detail_time_logs);
print "Array size: $array_size\n";
print "Detail time logs size: $detail_time_logs_size\n";

# checking of Nan in perl
use Time::HiRes qw( time ); 
my $t_start = time();
my $t_end = undef;

my $t_diff = $t_start - $t_end;
print "Undef variable: $t_end\n";
print "Difference: $t_diff\n";

# undef has default 0 if number, empty string if string
my $t_start_2 = -inf;
print "Infinity: $t_start_2\n";
my $t_diff_2 = $t_start - $t_start_2;
print "Difference with -inf: $t_diff_2\n";

my $logoutput = sprintf("%.2f",$t_start);
print "$logoutput \n";
my $logoutput = sprintf("%.2f",$t_diff_2);
print "$logoutput \n";
my $logoutput = sprintf("Minus two -inf: %.2f", $t_start_2 - $t_start_2);
print "$logoutput \n";

# testing for debug levels
$AA = "info";
$BB = "warning";
$CC = "-info";
$value_debug = ($AA <= 3);
$value_debug2 = ($BB <= 3);
$value_debug_i = $AA +1;
$value_debug_i2 = $BB +1;
$value_debug_i3 = $CC +1;
print "Value of debug evaluation: $value_debug\n";
print "Value of debug evaluation2: $value_debug2\n";
print "Value of debug evaluation i : $value_debug_i\n";
print "Value of debug evaluation i2: $value_debug_i2\n";
print "Value of debug evaluation i3: $value_debug_i3\n";


# syslog priorities verification
@syslog_levels = ('emerg','alert','crit','err','warning','notice','info', 'debug');
print "@syslog_levels";

foreach $ii (@syslog_levels) {
    $value = $ii +1;
    print "value: $value\n";
}
