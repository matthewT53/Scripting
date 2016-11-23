#!/usr/bin/perl -w
$perl = '#!/usr/bin/perl -w%c$perl = %c%s%c%c$python = %c%s%c%c$perlOutput = sprintf($perl, 10, 34, $perl, 34, 10, 34, $python, 34, 10, 10);%cprintf $python, 10, $perl, 10, 10;%c';
$python = '#!/usr/bin/python3.5%cpl = "%s"%cprint (pl);%c';
$perlOutput = sprintf($perl, 10, 34, $perl, 34, 10, 34, $python, 34, 10, 10, 10);
printf $python, 10, $perlOutput, 10, 10;
