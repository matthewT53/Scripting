#!/usr/bin/perl -w
$a = '#!/usr/bin/perl -w%c$a = %c%s%c;%cprintf $a, 10, 39, $a, 39, 10, 10;%c';
printf $a, 10, 39, $a, 39, 10, 10;
