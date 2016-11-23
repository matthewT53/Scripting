#!/usr/bin/perl -w

@a = (1..5);
@b = grep { $_ = $_ - 3; $_ > 0} @a;
print "@a\n";
print "@b\n";

@vec = map { $_ ** 2 } (1,2,3,4,5);
print "@vec\n";

printf "%d\n", 2**5;
