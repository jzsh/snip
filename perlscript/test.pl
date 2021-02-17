use strict;
use warnings;

sub say { print @_, "\n" }
# String
my $string = "start learning perl";

print uc "$string\n";      # hello
say lc $string;

say index $string, 'earn'; #index function have 2 args

# Number
my $x = 4;
my $y = 5.7;
$y = int $y;
my $z = $x + $y**2; # square
print "$x + $y^2 = $z\n";

## get random
say int rand 100;

for (my $i=0; $i<=9; $i++) {
	say $i;
}

foreach my $i (0..9) {
	say $i;
}
