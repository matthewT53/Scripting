# Author: Matthew Ta
# This perl script receives a perl script as input and 
# outputs an equivalent python script.

#!/usr/bin/perl -w
# stores the python output
@python = ();

# holds all the python import libraries
%imports = ();

# data structure declaration, sometimes perl programmers don't declare their data structures
%declarations = ();

# stores the perl input
@perlInput = <>;

# keeps track of all the variables used for variable interpolation
%variablesUsed = ();

# constants for common data types
$INTEGER = 0;
$FLOATING = 1;
$STRING = 2;

# keeps track of the global indent level
$indent_level = 0;

# indicates whether we are debugging on lab or home pc
$debug_lab = 1;
$debug = 0;

# keeps track of the current line number
$line_number = 1;

# quick lookup table for file modes
%fileModes = (
    "<" => "r",
    ">" => "w",
    ">>" => "a",
    "+<" => "r+",
    "+>" => "w+",
    "+>>" => "a+",
);

# read input from the perl file
while (@perlInput){
    $line = $perlInput[0];
    # print "Line = $line\n";
    push @python, translate_statement($line, $indent_level)."\n";
    $line_number++;
}

$linePrinted = 0;
# print the python output
foreach $line (@python){
    print $line;
    $linePrinted++;
    if ($linePrinted == 1){
        # print all the import libraries
        for $import (keys % imports){
            print "$import";
        }

        # print all the array and hash declarations
        for $declaration (keys % declarations){
            print "$declaration";
        }
    }
}

# translate all the lines read
sub translate_statement{
    my ($statement, $indent_level) = @_;
    # print "statement: $statement and indent: $indent_level\n";
    #$statement =~ s/;$//g; # remove the trailing semi-colon
    # the line has some logical operators in it
    # the below line rmeoves !, |, &

    my $sideComment = "";
    if ($statement =~ /[\;\)\{\}](\s*\#.*)$/){
        $sideComment = $1;
        $statement =~ s/\Q$sideComment//g;
    }

    $toPrint = $statement;
    chomp $toPrint;
    print "\nStatement: $toPrint\n" if $debug == 1;# and indent: $indent_level\n" if $debug == 1;
    if ($statement =~ /^#!/ && $line_number == 1){
        shift @perlInput;
        if ($debug_lab == 1){ # the starting line is different for different machines
            return "#!/usr/local/bin/python3.5 -u\n";
        }

        else{
            return "#!/usr/bin/python3.5 -u\n";
        }
    }
    # ignore comment statements
    elsif ($statement =~ /^\s*#/ || $statement =~ /^\s*$/){
        shift @perlInput;
        chomp $statement;
        return $statement;
    }

    # handle print statments
    elsif ($statement =~ /^\s*print\b/){
        return translate_print($statement, $indent_level)."$sideComment";
    }

    # handle if statements
    elsif ($statement =~ /^\s*if\b/){
        return translate_if($statement, $indent_level)."$sideComment";
    }

    # handle elsif statements
    elsif ($statement =~ /\s*elsif\b/){
        return translate_elsif($statement, $indent_level)."$sideComment";
    }

    # handle else statements
    elsif ($statement =~ /^\s*else\b/){
        return translate_else($statement, $indent_level)."$sideComment";
    }

    # handle while loops
    elsif ($statement =~ /^\s*while\b/){
        return translate_while($statement, $indent_level)."$sideComment";
    }

    # handle for loops
    elsif ($statement =~ /^\s*for\b/){
        return translate_for($statement, $indent_level)."$sideComment";
    }

	# deal with foreach loops
    elsif ($statement =~ /^\s*foreach\b/){
        return translate_foreach($statement, $indent_level)."$sideComment";
    }

    # deal with the statement "last"
    elsif ($statement =~ /^\s*last\b/){
        shift @perlInput;
        return "\t" x $indent_level . "break"."$sideComment";
    }

    # handle the next statmeent which is equivalent to python's continue
    elsif ($statement =~ /^\s*next\b/){
        shift @perlInput;
        return "\t" x $indent_level . "continue"."$sideComment";
    }

    # handle chomp
    elsif ($statement =~ /^\s*chomp\b/){
        shift @perlInput;
        my $perl_expression = $statement;
        $perl_expression =~ /^\s*chomp\s*\$(.*);/;
        my $string = $1;
        return "\t" x $indent_level . "$string = $string.rstrip('\\n')"."$sideComment";
    }

    # handle calls to exit
    elsif ($statement =~ /^\s*exit\s*/){
        shift @perlInput;
        my $exit_statement = $statement;
        $exit_statement =~ /^\s*exit\s*\(?\s*(\d*)\s*\)?\s*;/;
        my $exit_condition = $1;
        my $python_exit_statement = "sys.exit($exit_condition)";
        my $importLibrary = "import sys\n";
        $imports{$importLibrary} = 0;
        return "\t" x $indent_level . $python_exit_statement."$sideComment";
    }

    # translate simple printf statements
    elsif ($statement =~ /^\s*printf\b/){
        return translate_printf($statement, $indent_level)."$sideComment";
    }

    # translate perl open functions to python equivalent
    elsif ($statement =~ /^\s*open\b/){
        return translate_open($statement, $indent_level)."$sideComment";
    }

    elsif ($statement =~ /^\s*close\s*(.*);/){
        my $python_close = $1;
        shift @perlInput;
        $python_close =~ s/\(//;
        $python_close =~ s/\)//;
        return "\t" x $indent_level . "$python_close.close()"."$sideComment";
    }

    elsif ($statement =~ /^\s*return\s*(.*);?/){
        shift @perlInput;
        my $return_statement = "return $1";
        $return_statement =~ s/\s*;\s*//g; # remove the semi-colon
        $return_statement =~ s/\$//g; # remove scalar symbol
        $return_statement =~ s/\@//g; # remove array symbol
        $return_statement =~ s/^\s*//g; # remove indentation
        print "Return statement = $return_statement\n" if $debug == 1;
        return "\t" x ($indent_level) . $return_statement."$sideComment";
    }

    # handle expressions
    elsif ($statement =~ /^\s*[^=]*$/){
		shift @perlInput;
        # print "Translating perl expression.\n";
        return translate_expressions($statement, $indent_level)."$sideComment";
    }

    # translate regex statements
    elsif ($statement =~ /^\s*([^=]*)\s*=~\s*([^=]*);\s*$/){
        # print "Translating regex expressions.\n";
        shift @perlInput;
        $imports{"import re\n"} = 0;
        return translate_regex($statement, $indent_level)."$sideComment";
    }

    # handle assignment statements
    elsif ($statement =~ /^\s*.*=\s*.*\s*$/){
        return translate_assignment($statement, $indent_level)."$sideComment";
    }

    # translate perl functions to python functions
    elsif ($statement =~ /^\s*sub\b/){
        return translate_function($statement, $indent_level)."$sideComment";
    }

    # handle everything else
    else{
        chomp $statement;
        shift @perlInput;
        return "# $statement not recognised\n";
    }
}

sub translate_open{
    my ($perl_open, $indent) = @_;
    my @python_open = ();
    my $python_open_str = "";
    shift @perlInput;
    print "Translating perl open statement.\n" if $debug == 1;
    if ($perl_open =~ /^\s*open\s*\(?(.*)?;?/){
        my $after_open = $1;
        my $open_params = "";
        my $message_failed = "";
        my $handle = "";
        my $mode = "";
        my $file = "";
        print "Parameters: $after_open\n" if $debug == 1;
        # need to detect the 2 way open vs the 3 way open
        if ($after_open =~ /(.*)\)?\s*or die (.*)/){
            $open_params = $1;
            $message_failed = $2;
            print "Open params: $open_params\n" if $debug == 1;
            print "Message for failed: $message_failed\n" if $debug == 1;
        }

        else{
            $open_params = $after_open;
        }

        my @split_params = split /,/, $open_params;
        # get the length of the array
        my $length = @split_params;
        # test file using old method of open
        if ($length == 2){
            print "Old style of file parameters\n" if $debug == 1;
            # need to extract the file mode (harder)
            $handle = $split_params[0];
            if ($split_params[1] =~ /\s*"([\>\<\+]*)\s*(.*)"\s*/){
                $mode = $1;
                $file = $2;
                if ($file !~ /^\s*\$/){
                    $file = "\"$file\"";
                }
            }

            print "Filename = $file and mode = $mode and handle = $handle\n" if $debug == 1;
        }

        # test file using new method of open
        elsif ($length == 3){
            print "New style of open file\n" if $debug == 1;
            # need to extract the file mode (easy)
            $handle = $split_params[0];
            $mode = $split_params[1];
            $file = $split_params[2];
            $file =~ s/ //g;
            $file =~ s/;//g;
            $mode =~ s/ //g;
            $mode =~ s/"//g;
            print "Filename = $file and mode = $mode and handle = $handle\n" if $debug == 1;
        }

        # convert all the parameters to python equivalent
        $file =~ s/\$//g;
        $file =~ s/\@//g;
        $python_open_str = "$handle = open($file, \"$fileModes{$mode}\")";
    }

    return "\t" x $indent . $python_open_str;
}

# translate perl subroutines to python subroutines
sub translate_function{
    my ($perl_function, $indent) = @_;
    my @python_function = ();
    shift @perlInput;
    print "Translating perl function.\n" if $debug == 1;
    if ($perl_function =~ /^\s*sub\s*(.*)\{\s*/){
        my $functionName = $1;
        my $functionParameters = "";
        my $return_statement = "";
        my $functionDeclaration = "";
        print "Function Name = $functionName\n" if $debug == 1;
        # need to extract the paramters

        while (@perlInput && $perlInput[0] !~ /\s*\}\s*/){
            # extract the function parameters
            if ($perlInput[0] =~ /^\s*my\s*\((.*)\)\s*=\s*\@\_/){
                $functionParameters = $1;
                $functionParameters =~ s/;//g;
                $functionParameters =~ s/\$//g;
                $functionParameters =~ s/\@//g;
                print "Function parameters = $functionParameters\n" if $debug == 1;
                $functionDeclaration = "def $functionName ($functionParameters):";
                shift @perlInput;
            }

            else{
                push @python_function, translate_statement($perlInput[0], $indent + 1);
            }
        }

        # now construct the function header and return statement
        if ($functionDeclaration ne ""){
            unshift @python_function, "\t" x ($indent) . $functionDeclaration;
        }

        # determine if we have reached a closing brace for the function
        if ($perlInput[0] =~ /\s*\}\s*$/){
            shift @perlInput;
        }

        else{
            $perlInput[0] =~ s/\s*\}\s*//g;
        }
    }

    # join the function into a single string
    $python_function_string = join("\n", @python_function);
    return $python_function_string;
}

# translate pelr regex to python regex expressions
sub translate_regex{
    my ($perl_regex_statement, $indent) = @_;
    my $python_regex_statement = "";

    # all variables used to translate perl -> python regex
    my $lineToTest = "";
    my $regex = "";
    my $function = "";
    my $replaceWith = "";

    # ensure it is a regex statement before translation
    if ($perl_regex_statement =~ /\s*([^\s]*)\s*=~\s*\/(.*)\/g?;?\s*$/){
        $lineToTest = $1;
        $regex = $2;
        $function = "re.search";

        $lineToTest =~ s/\$//g; # remove scalar symbols
        $lineToTest =~ s/\@//g; # remove array symbols

        if ($perl_regex_statement =~ /\/g/){
            $function = "re.findall";
        }
        # consider: using uniq variable names for match object
        $python_regex_statement = "match = $function(r\"$regex\", $lineToTest)";
        $imports{"import re\n"} = 0;
    }

    # substitution type regex
    elsif ($perl_regex_statement =~ /\s*([^\s]*)\s*=~\s*s\/(.*)\/(.*)\/g?;?\s*$/){
        $lineToTest = $1;
        $regex = $2;
        $replaceWith = $3;

        $lineToTest =~ s/\$//g; # remove scalar symbols
        $lineToTest =~ s/\@//g; # remove array symbols

        $python_regex_statement = "$lineToTest = re.sub(r\"$regex\", r\"$replaceWith\", $lineToTest)";
        $imports{"import re\n"} = 1;
    }

    else{
        print "#Failed to translate regex from perl to python: Not recognished\n" if $debug == 1;
    }

    return "\t" x $indent . $python_regex_statement;
}

sub translate_reverse{
    my ($perl_reverse_statement, $indent) = @_;
    my $python_reverse_statement = "";
    # determine if we are reversing an array or scalar
    # stack overflow helped with this: http://stackoverflow.com/questions/13059540/using-python-reverse-an-integer-and-tell-if-palindrome
    if ($perl_reverse_statement =~ /\s*reverse\s*\$([^;]*)/){
        my $scalarName = $1;
        $python_reverse_statement = "str($scalarName)[::-1]";
    }

    elsif ($perl_reverse_statement =~ /\s*reverse\s*\@([^;]*)/){
        my $arrayName = $1;
        $python_reverse_statement = "$arrayName.reverse()";
    }

    else{
        print "# Not a reverse statement.\n" if $debug == 1;
    }

    return "\t" x $indent . $python_reverse_statement;
}

sub translate_push{
    my ($perl_push_statement, $indent) = @_;
    my $python_push_statement = "";
    my $array = "";
    my $valueToPush = 0;
    print "Translating push.\n" if $debug == 1;
    #shift @perlInput;
    if ($perl_push_statement =~ /^\s*push\s*\(?@([\w]+[\w\d]*)\s*,\s*([^;]*);/){
        $array = $1;
        $valueToPush = form_python_list($2);
        print "Python list result: $valueToPush\n" if $debug == 1;
        $python_push_statement = "$array.extend($valueToPush)";
    }

    return "\t" x $indent . $python_push_statement;
}

sub translate_pop{
    my ($perl_pop_statement, $indent) = @_;
    my $python_pop_statement = "";
    my $array = "";
    #shift @perlInput;

    if ($perl_pop_statement =~ /\s*pop\s*@([\w]+[\w\d]*)\s*/){
        $array = $1;
        $python_pop_statement = "$array.pop()";
    }

    return "\t" x $indent . $python_pop_statement;
}

sub translate_shift{
    my ($perl_shift_statement, $indent) = @_;
    my $python_shift_statement = "";
    my $array = "";
    #shift @perlInput;

    if ($perl_shift_statement =~ /\s*shift\s*@([\w]+[\w\d]*)\s*/){
        $array = $1;
        $python_shift_statement = "$array.pop(0)";
    }

    return "\t" x $indent . $python_shift_statement;
}

sub translate_unshift{
    my ($perl_unshift_statement, $indent) = @_;
    my $python_unshift_statement = "";
    my $array = "";
    my $valuesToInsert = "";
    #shift @perlInput;

    # print "Translating unshift:\n";
    if ($perl_unshift_statement =~ /^\s*unshift\s*\(?@([\w]+[\w\d]*)\s*,\s*([^;]*;)/){
        $array = $1;
        $valuesToInsert = form_python_list($2);
        # print "Python list result: $valuesToInsert\n";
        $python_unshift_statement = "$array.insert(0, $valuesToInsert)";
    }

    return "\t" x $indent . $python_unshift_statement;
}

# given some perls items (variable or array), this function forms a python list
sub form_python_list{
    my ($arguments) = @_;
    my @list = ();
    my @final_string = ();
    my $temp = "";
    my $python_arguments_list = "";

    @allArguments = split /\s*,\s*/, $arguments;
    foreach $arg (@allArguments){
        # we have a variable so just add
        $temp = "";
        if ($arg =~ /\$([\w]+[\w\d]*)\s*/){
            push @list, $1;
        }

        # this is already a list so just join it
        elsif ($arg =~ /\@([\w]+[\w\d]*)\s*/){
            # join the previous array containing the list args
            if ($#list >= 0){
                $temp = "[" . join(",", @list) . "]";
                push @final_string, $temp;
            }
            push @final_string, $1;
            @list = ();
        }

        # arg is a string, number or anything else
        else{
            $arg =~ s/\$//g;
            push @list, $arg;
        }
    }

    # just in case in the last iteration, an array is not encountered
    if ($#list >= 0){
        $temp = "[" . join(",", @list) . "]";
        push @final_string, $temp;
    }

    $python_arguments_list = join(" + ", @final_string);
    return $python_arguments_list;
}

sub translate_printf{
    my ($perl_printf_statement, $indent) = @_;
    my $python_printf = "";
    # extract the format specifiers
    # my @format_specifiers = $perl_printf_statement =~ /%[\d]*\.?[\d]*[\w]+ /g;
    shift @perlInput;
    if ($perl_printf_statement =~ /^\s*printf\s*\(?"(.*)"\)?\s*,\s*(.*);/){
        # print "String = $1\n";
        # print "Variable list = $2\n";
        my $string = $1;
        my $var_list = $2;

        # remove all the scalar symbols
        $var_list =~ s/\$//g;

        $python_printf = "print(\"$string\" % ($var_list))";
    }

    return "\t" x $indent . $python_printf;
}

# translates a print statement
sub translate_print{
    my ($print_statement, $indent) = @_;
	$print_statement =~ s/;//g;
    $print_statement =~ /\s*print\s*(.*)/;
    my $insidePrint = $1;
    my $endNewLine = 1; # boolean that determines whether the python print should print its standard newline or not
    shift @perlInput;

    print "Translating print statements.\n" if $debug == 1;
    # remove the last new line char here
    print "insidePrint = $insidePrint\n" if $debug == 1;
    if ($insidePrint =~ /\s*[\.,]\s*"\s*\\n\s*"\s*$/){ # e.g , "\n"
        #print "Found another version of the newline to remove.\n";
        $insidePrint =~ s/\s*[\.,]\s*"\s*\\n\s*"\s*$//g;
    }

    elsif ($insidePrint =~ /\\n"\s*$/){
        #print "Found new line to remove.\n";
        $insidePrint =~ s/\\n"\s*/"/g;
    }

    else{
        # don't want python to print its standard newline character
        $endNewLine = 0;
    }

    my $python_print = string_expression($insidePrint);
    $python_print = "print(" . $python_print;
    if ($endNewLine == 0){
        $python_print = $python_print . ", end=\"\"";
    }
    $python_print = $python_print . ")";
    # print "Python print statement: $python_code\n";
    return "\t" x $indent . $python_print;
}

sub string_expression{
    my ($insidePrint) = @_;
    my @python_string = ();
    #print "New and improved insidePrint = $insidePrint\n";
    # split the strings and variables inside the print by spaces
    my @wordsInPrint = split //, $insidePrint;
    # loop through all the strings and variables inside the print
	my $numQuotationMarks = 0;
	my $numberBrackets = 0;

	# dealing with function calls inside print
	my $toSplit = 1; # determines whether a + should be added in
	# change all the commas and dots to a + (FIRST PASS)
    for ($i = 0; $i <= $#wordsInPrint; $i++){
        # mod 2 is used to detect closing quotation marks

		# opening brace of function detected, don' split anything here until lcosing brace is found
		if ($numQuotationMarks % 2 == 0 && $wordsInPrint[$i] eq "("){
			$toSplit = 0;
		}

		# closing brace of function detected, we can split again
		if ($numQuotationMarks % 2 == 0 && $wordsInPrint[$i] eq ")"){
			$toSplit = 1;
		}

		if ($toSplit == 1){
			if (($wordsInPrint[$i] eq '.' || $wordsInPrint[$i] eq ',') && $numQuotationMarks % 2 == 0 && $numQuotationMarks > 0){
				$wordsInPrint[$i] = '+';
			}

			if ($wordsInPrint[$i] eq '"'){
				$numQuotationMarks++;
                # the quotation mark is being escaped so down count it
                if ($i > 0 && $wordsInPrint[$i - 1] eq "\\"){
                    $numQuotationMarks--;
                }
			}
		}
	}

	$insidePrint = join("", @wordsInPrint);
	my @printSubParts = split /\s*\+\s*/, $insidePrint;

	# second pass convert all sub parts to their python equivalents
	foreach my $perlSubPart (@printSubParts){
		push @python_string, translate_print_subpart($perlSubPart);
	}

    my $pythonString = join(" + ", @python_string);
    return $pythonString;
}

# translates a subpart of a perl print statement
sub translate_print_subpart{
	my ($perl_sub_part) = @_;
	my @python_sub_print = ();

	print "Perl sub part: $perl_sub_part\n" if $debug == 1;
	# remove new line first
	$perl_sub_part =~ s/\n//g;
	if ($perl_sub_part =~ /^\"?\$[a-zA-Z]+[a-zA-Z_0-9]*"?$/){
		$perl_sub_part =~ s/"//g;
		$perl_sub_part =~ s/^\$//;
		push @python_sub_print, "str($perl_sub_part)";
	}

	# check if we are dealing with an expression
	elsif ($perl_sub_part !~ /^"/){ # LAZY
		print "Dealing with expressions inside prints.\n" if $debug == 1;
		push @python_sub_print, "str(" . translate_expressions($perl_sub_part, 0). ")";
	}

	else{
        print "Working with variable interpolation.\n" if $debug == 1;
        # remove opening and lcosing braces
		$perl_sub_part =~ s/^\s*"//;
        $perl_sub_part =~ s/\s*"\s*$//;
		# match all perl variables
		my @perlVariables = $perl_sub_part =~ /[^\\]?(\$\#?[\w\d]+[\w\d\[\]\{\}\$"]*)/g;
        my @variablesToPrint = ();
        my $perlString = $perl_sub_part;
		# split on variables to get the rest of the strings
		# my @strings = split /\$[a-zA-Z]+[a-zA-Z_0-9]*/, $perl_sub_part;
        for $myVar (@perlVariables){
            # print "myVar = $myVar\n";
            $myVarNoDollar = $myVar;
            $myVarNoDollar =~ s/\$//;
            $myVar = translate_expressions($myVar, 0);
            my $value = 0;
            # variable represented something else like ARG or $1
            if ($myVar eq $myVarNoDollar){
                $value = determine_type($myVar);
                # print a string specifier if no vlaue is defined to get over one itme cases like $string[$i]
                # We are only interested in which format string to use so
                # for arrays and hashes, just use the name not the index
                # print "Value of $myVar = $value\n";
                # if we are printing a hash, convert the curly braces to square brackets
                if ($myVar =~ /[\w]+[\w\d]*\{.*\}/){
                    $myVar =~ s/\{/\[/g;
                    $myVar =~ s/\}/\]/g;
                }
                push @variablesToPrint, "$myVar";
            }

            else{
                # print "Expression found: $myVar\n";
                $value = $STRING;
                push @variablesToPrint, "$myVar";
                # detect if a regex variable such as $1
            }

            $myVar = "\$$myVarNoDollar";
            # variable holds a string
            if ($value == $INTEGER){
                $perlString =~ s/\Q$myVar/%d/;
            }

            # variable holds a floating point value
            elsif ($value == $FLOATING){
                $perlString =~ s/\Q$myVar/%f/;
            }

            # variable holds an integer value
            else{
                $perlString =~ s/\Q$myVar/%s/;
            }

            $myVar =~ s/\$//;
        }

        my $python_string = $perlString;

        # check if variables were actually translated
        if ($#perlVariables >= 0){
            $python_string = join(", ", @variablesToPrint);
            $python_string =~ s/\$//g; # final sweep to clear all perl symbols
            $python_string = $perlString . "\" % (" . $python_string . ")";
            $python_string = "\"$python_string";
        }

        else{
            $python_string = "\"$python_string\"";
        }

        # final clearning of the python string
        if ($python_string =~ /\\([^\"\'\w])/){
            # print "Matched a: $1\n";
            my @escape_characters = $python_string =~ /\\([^\"\'])/g;
            foreach my $escape_character (@escape_characters){
                $python_string =~ s/\\\Q$escape_character/$escape_character/;
            }
        }
        push @python_sub_print, $python_string;
    }

	my $python_code = join("", @python_sub_print);
	# print "Generated code: $python_code\n";
	return $python_code;
}

sub translate_assignment{
    my ($perl_assignment_statement, $indent) = @_;
    shift @perlInput;
    my $python_assignment = "";
    my $variable = "";
    my $expression = "";
    my $operator = "";
    my $perl_expression = "";
    print "Translating assignment statement: $perl_assignment_statement\n" if $debug == 1;
    # remove all the perl indentation for correct python indentation
    $perl_assignment_statement =~ s/^ *//g;
    $perl_assignment_statement =~ s/\s*;\s*$//;

    # array declaration translation
    if ($perl_assignment_statement =~ /^\s*\@([\w]+[\w\d]*)\s*=\s*(.*)/){
        $variable = $1;
        $expression = translate_expressions($2, 0);
        $perl_expression = $2;
        $operator = "=";
        if ($expression =~ /^\s*\(/){
            $expression =~ s/\(/\[/g;
            $expression =~ s/\)/\]/g;
        }

        if ($expression =~ /\<STDIN\>/){
            $expression = translate_stdin($expression, "while");
        }
        #print "Array name: $variable\n";
        #print "Assigned with: $expression\n";
    }

    # hash assignment translation
    elsif ($perl_assignment_statement =~ /^\s*\%([\w]+[\w\d]*)\s*=\s*(.*)/){
        #print "Dealing with hashes.\n";
        $variable = $1;
        $perl_expression = $2;
        $expression = translate_expressions($2, 0);
        $operator = "=";
        if ($expression =~ /^\s*\(/){
            $expression =~ s/\(/\{/g;
            $expression =~ s/\)/\}/g;
        }
    }

    # normal variable assignment
    elsif ($perl_assignment_statement =~ /\s*\$\s*([\w]+[\d\w\[\]\{\}\$"]*)\s*(.{0,2}=)\s*(.*)/){
        $variable = $1;
        $operator = $2;
        $expression = $perl_expression = $3;

        # check if its a string expression
        if ($expression =~ /\"/){
            #print "Translating string.\n";
            $expression = string_expression($expression);
        }

        elsif ($expression =~ /\<STDIN\>/){
            $expression = translate_stdin($expression, "line");
        }

        # check if its an arithmetic operation that requires type casting
        elsif ($expression =~ /[\+\-\/\*]/){
            print "Type casting RHS of arithmetic operation.\n" if $debug == 1;
            my @variables = $expression =~ /(\$[a-zA-Z\_]+[a-zA-Z0-9\_]*)/g;
            my $type1 = determine_type($variable);
            my $dataType;

            # print "type1 = $type1\n";

            if ($type1 == $FLOATING){
                $dataType = "float";
            }

            elsif ($type1 == $INTEGER){
                $dataType = "int";
            }

            else{
                # need to determine the data type to use
                $type1 = $INTEGER;
                $dataType = "int";
            }

            # loop through all the variables in the operation
            foreach my $var (@variables){
                my $varTranslated = translate_expressions($var, 0);
                my $type2 = determine_type($var);
                print "VarTranslated = $varTranslated and type2 = $type2\n" if $debug == 1;
                # need to typecast
                if ($type2 != $type1){
                    $varTranslated = "$dataType($varTranslated)";
                    $expression =~ s/\Q$var/$varTranslated/;
                }
            }

            $expression = translate_expressions($expression, 0);
        }

        else{
            #print "Translating numeric expression\n";
            $expression = translate_expressions($expression, 0);
        }

        # need to check if array has been initialised with a size
        if ($variable =~ /([\w]+[\w\d]*)\s*\[\s*(.*)\s*\]\s*/){
            print "Adding value to array = $variable\n" if $debug == 1;
            my $arrayName = $1;
            my $arrayIndex = $2;
            print "Array name = $arrayName\n" if $debug == 1;
            print "Array index = $arrayIndex\n" if $debug == 1;
            if (defined($variablesUsed{"$arrayName"})){
                print "Value of key = ", $variablesUsed{"$arrayName"}, "\n" if $debug == 1;
                if ($variablesUsed{"$arrayName"} =~ /\(\s*\)/){
                    $arrayIndex =~ s/\$//g;
                    $arrayIndex =~ s/\@//g;
                    $python_assignment = "$arrayName.insert($arrayIndex, $expression)";
                }
            }
        }

        # type cast to integer
        if ($operator =~ /[^\.]=/){
            $expression = "int($expression)";
        }

        # string concatenation
        if ($operator eq ".="){
            $operator = "+=";
        }

        # if LHS is a scalar array or hash then check if it has been declared
        if ($variable =~ /([\w]+[\w\d]*)\s*[\[\{]/){
            my $name = $1;
            # check if the array or hash used has been defined
            print "Adding declaration for array or hash\n" if $debug == 1;
            if (!defined($variablesUsed{$name})){
                print "Array or hash has not been declared before.\n" if $debug == 1;
                if ($variable =~ /\[/) { $declarations{"$name = []\n"} = 1; }
                if ($variable =~ /\{/) { $declarations{"$name = {}\n"} = 1; }
                $variablesUsed{"$name"} = $expression;
            }
        }

        # for some reason, the $ is lost
        # cleanse the variables
        #$variable = $variable;
        $operator =~ s/ //g;
        $variable =~ s/\{/\[/;
        $variable =~ s/\}/\]/;
        if ($expression =~ /[\w]+[\w\d]*\s*\{/){
            $expression =~ s/\{/\[/;
            $expression =~ s/\}/\]/;
        }

        print "Variable = $variable\n" if $debug == 1;
        print "Expression = $expression\n" if $debug == 1;
        print "Operator:$operator\n" if $debug == 1;
    }

    else{
        # dummy task to prevent spewing errors
        $operator = "";
    }

    # remove common perl pre-fixes
    $variable =~ s/\s*\$\s*//g;
    $variable =~ s/^\s*\@//g;
    $variable =~ s/\s*$//g;
    # incase translate_expressions didnt clean it
    $expression =~ s/\s*\$\s*//g;
    $expression =~ s/^\s*\@//g;
    $expression =~ s/\s*$//g;

    # add the variable to a dictionary
    $variablesUsed{"$variable"} = $perl_expression;
    if ($python_assignment eq ""){
        $python_assignment = "$variable $operator $expression";
    }
    return "\t" x $indent . $python_assignment;
}

sub translate_expressions{
    my ($perl_expression, $indent) = @_;
    my $python_expression = "";

    print "Translating expressions.\n" if $debug == 1;
    # normal comparisons, determine typecasting requirements here also
    if ($perl_expression =~ /[^\s\>\<\=\!]+\s*(\>\=|\<\=|\=\=|\!\=|\>|\<)\s*[^\s\>\<\=\!]+/){
        print "Changing type of the right variable.\n" if $debug == 1;
        my @conditions = $perl_expression =~ /([^\s\>\<\=\!]+\s*(\>\=|\<\=|\=\=|\!\=|\>|\<)\s*[^\s\>\<\=\!\;]+)\s*\;?/g;
        for my $condition (@conditions){
            if ($condition =~ /([^\s\>\<\=\!]+)\s*(\>\=|\<\=|\=\=|\!\=|\>|\<)\s*([^\s\>\<\=\!]+)?/){
                my $variable1 = $1;
                my $variable2 = $3;
                print "My var1 = $variable1 and My var2 = $variable2\n" if $debug == 1;
                my $type1 = determine_type($variable1);
                my $type2 = determine_type($variable2);
                my $newVariable2 = "";

                # typecasting is needed
                # type cast should favour variable on left e.g if varLeft = int then varRight = (int) varRight
                if ($type1 != $type2){
                    print "Converting to type of left variable.\n" if $debug == 1;
                    if ($type1 == $INTEGER){
                        $newVariable2 = "int($variable2)";
                    }

                    elsif ($type1 == $FLOATING){
                        $newVariable2 = "float($variable2)";
                    }

                    else{
                        $newVariable2 = "str($variable2)";
                    }

                    $perl_expression =~ s/\Q$variable2/$newVariable2/;
                }
            }
        }
    }

    # translate regex expressions
    if ($perl_expression =~ /(.*)\s*=~\s*(.*)/){
        $perl_expression = translate_regex($perl_expression, 0);
    }

    # translate regex group expressions e.g $1
    if ($perl_expression =~ /\$(\d+)\s*/){
        $perl_expression = "match.group($1)";
    }

    # convert perl's length prefix to python's len() function
    if ($perl_expression =~ /\$\#([\w]+[\w\d_]*)\s*\;?/){
        my $variableName = $1;
        my $lengthMatch = "\$\#$variableName";
        $perl_expression =~ s/\Q$lengthMatch/len\($variableName\) - 1/;
    }

    # convert perl's .. operator to python's range function
    if ($perl_expression =~ /(.+)\.\.(.+)/){
		my $low = $1;
		my $high = "$2 + 1";
        $perl_expression = "range($low, $high)";
    }

    # translate perl's reverse function into python's equivalent
    if ($perl_expression =~ /\s*reverse\b/){
        $perl_expression = translate_reverse($perl_expression, 0);
    }

    # translate the pop and shfit operations when they are assigned to something
    if ($perl_expression =~ /\s*pop\b/){
        # print "Translating pop in expression.\n";
        $perl_expression = translate_pop($perl_expression, 0);
        # print "After pop translation = $perl_expression\n";
    }

    if ($perl_expression =~ /\s*\bshift\b/){
        # print "Translating shift in expression\n";
        $perl_expression = translate_shift($perl_expression, 0);
        # print "After shift translation = $perl_expression\n";
    }

    if ($perl_expression =~ /\s*push\b/){
        $perl_expression = translate_push($perl_expression, 0);
    }

    if ($perl_expression =~ /\s*unshift\b/){
        $perl_expression = translate_unshift($perl_expression, 0);
    }

    # handle join function
    if ($perl_expression =~ /\s*join\s*\(?(.*)\s*,\s*\@(.*)\)?/){
        # print "Working with the join function.\n";
        my $joinChar = $1;
        my $arrayToJoin = $2;
        print "Inside join\n" if $debug == 1;
		$arrayToJoin =~ s/[^a-zA-Z0-9_]//g;
        if ($joinChar =~ /\/(.*)\//){
            $joinChar =~ s/\///g;
			if ($joinChar !~ /^\s*\$/){
		        $joinChar = "\"$joinChar\"";
		    }
        }

        # update perl expression
        $perl_expression = "$joinChar.join($arrayToJoin)";
        # print "Join with char: $joinChar\n";
        # print "Array to join: $arrayToJoin\n";
    }

    # handle split function
    if ($perl_expression =~ /\s*split\s*\(?(.*)\s*,\s*\$([^\)]*)\)?/){ # assume splitting scalar string
        # print "Working with the split function.\n";
        my $myDelimiter = $1;
        my $lineToSplit = $2;
        # remove opening and closing braces
        $myDelimiter =~ s/^\s*"//g; $myDelimiter =~ s/"\s*$//g;
		$myDelimiter =~ s/\///g;
        # need to handle normal split as well as regex split
        $imports{"import re\n"} = 0; # import the regex library
        $perl_expression = "re.split(r\"$myDelimiter\", $lineToSplit)";
        #print "delimiter = $myDelimiter\n";
        #print "thing to split = $lineToSplit\n";
    }

    if ($perl_expression =~ /\s*defined\s*\((.*)\)/){
        my $parameters = $1;
        # add support for testing if a key is defined in a hash
        if ($parameters =~ /([\w]+[\w\d]*)\s*\{(.*)\}/){
            my $hashName = $1;
            my $key = $2;
            $key =~ s/\$//g;
            $key =~ s/\@//g;
            $perl_expression = "$key in $hashName";
        }
    }

    # handle argument list translation
    if ($perl_expression =~ /\s*\$ARGV\[(\d+)\]\s*$/){ # mainly for for loops
        my $index = $1;
        $perl_expression =~ s/\$ARGV\[\d+\]\s*/sys.argv\[1\:\]\[$index\]/g;
        $imports{"import sys\n"} = 0;
    }

    # handling scalar argument list translation
    elsif ($perl_expression =~ /\@?ARGV\s*/){
        $perl_expression =~ s/ARGV/sys\.argv\[1\:\]/g;
		$imports{"import sys\n"} = 0;
    }

    # handle reading lines from file handle
    if ($perl_expression =~ /\<(.*)\>/ && $perl_expression !~ /\<STDIN\>/){
        my $handle = $1;
        print "Handle = $handle\n" if $debug == 1;
        if ($handle !~ /^\s*$/){
            $perl_expression = "$handle.readlines()";
        }

        # reading liens from <>
        else{
            $perl_expression = "fileinput.input()";
            $imports{"import fileinput\n"} = 0;
        }
    }

    # replace perl logical operators with their python equivalent
    if ($perl_expression =~ /(!|\|\||&&)/ && $perl_expression !~ /"/){ # avoid modifying these characters in string literals
        my $operator = $1;
        if ($operator eq "&&"){
            $perl_expression =~ s/&&/and/g;
        }

        elsif ($operator eq "||"){
            $perl_expression =~ s/\|\|/or/g;
        }

        elsif ($operator eq "!"){
            if ($perl_expression =~ /\![^=]/){
                #print "Removing shit\n";
                $perl_expression =~ s/\!/not /g;
                #print "Results in: $perl_expression\n";
            }
        }

        else{
            print "#Unknown logical operator: $operator.\n";
        }
    }

  	# remove the scalar symbol from variables
	$perl_expression =~ s/\$//g;
    $perl_expression =~ s/\@//g;
    $perl_expression =~ s/\s*;\s*$//g;
    $perl_expression =~ s/^\s*//g; # remove indentation

    # python doesn't support -- and ++ so replace them with -=/+=
    if ($perl_expression =~ /(\+\+|\-\-)/ && $perl_expression !~ /"/){
        $perl_expression =~ s/\+\+/ \+\= 1/g;
        $perl_expression =~ s/\-\-/ \-\= 1/g;
        # determine if the variable has been seen before
        if ($perl_expression =~ /([\w]+[\w\d]*)([\[\{])/){
            my $name = $1;
            my $dataType = $2;
            if (!defined($variablesUsed{"$name"})){
                if ($dataType =~ /\{/){ $declarations{"$name = {}\n"} = 1; }
                if ($dataType =~ /\[/){ $declarations{"$name = []\n"} = 1; }
            }
        }
    }

    # translate string comparisons to their python equivalent
    if ($perl_expression =~ /\s+eq\s+/){
        $perl_expression =~ s/\s+eq\s+/ \=\= /g;
    }

    elsif ($perl_expression =~ /\s+ne\s+/){
        $perl_expression =~ s/\s+ne\s+/ \!\= /g;
    }

    elsif ($perl_expression =~ /\s+lt\s+/){
        $perl_expression =~ s/\s+lt\s+/ \< /g;
    }

    elsif ($perl_expression =~ /\s+gt\s+/){
        $perl_expression =~ s/\s+gt\s+/ \> /g;
    }

    elsif ($perl_expression =~ /\s+le\s+/){
        $perl_expression =~ s/\s+le\s+/ \<\= /g;
    }

    elsif ($perl_expression =~ /\s+ge\s+/){
        $perl_expression =~ s/\s+ge\s+/ \>\= /g;
    }

    # remove curly braces of a hash expression
    if ($perl_expression =~ /[\w]+[\w\d]*\s*\{.*\}/){
        $perl_expression =~ s/\}/\]/g;
        $perl_expression =~ s/\{/\[/g;
    }

    # $python_expression = translate_stdin($perl_expression, "line");
    $python_expression = $perl_expression;
    chomp $python_expression;
    return "\t" x $indent . $python_expression;
}

sub translate_if{
    my ($perl_if_statement, $indent) = @_;
    my @python_if = ();
    $perl_if_statement =~ /^\s*if\s*\((.*)\)/;
    shift @perlInput;
    print "Indent: $indent and Initial Condition: $1\n" if $debug == 1;
    # pass in zero as 2nd param cause we don't need the prefixed spaces
    my $python_condition = $1;
    # print "Condition found to be: $python_condition\n";
    # dealing with regex condition
    if ($python_condition =~ /\=\~/){
        push @python_if, translate_regex($python_condition, $indent);
        $python_condition = "match";
    }

    else{
        $python_condition = translate_expressions($python_condition, 0);
    }
    push @python_if, "\t" x $indent . "if $python_condition:";

    # loop until we encounter a closing brace
    while (@perlInput && $perlInput[0] !~ /^\s*\}\s*/){
        push @python_if, translate_statement($perlInput[0], $indent + 1);
    }

    if ($perlInput[0] =~ /^\s*\}\s*$/){
        shift @perlInput;
    }

    else{
        $perlInput[0] =~ s/^\s*\}\s*//;
        # print "next line = $perlInput[0]\n";
    }

    # print "Broke out of while loop.\n";
    # join everything in python_if array and return it
    my $pythonCode = join("\n", @python_if);
    return $pythonCode;
}

sub translate_elsif{
    my ($perl_elsif_statement, $indent) = @_;
    my @python_elsif = ();
    my $matchEqn = "";
    $perl_elsif_statement =~ /^\s*elsif\s*\((.*)\)/;
    shift @perlInput;
    # print "(Else if) Initial condition: $1\n";
    my $python_condition = $1;
    # dealing with a regex condition
    if ($python_condition =~ /\=\~/){
        $python_condition = translate_regex($python_condition, 0);
        $python_condition =~ s/match = //g; # avoid equating match object in condition
        $matchEqn = "match = $python_condition";
    }

    else{
        $python_condition = translate_expressions($python_condition, $indent);
    }
    # print "(Else if) The condition is: $python_condition\n";
    push @python_elsif, "\t" x $indent . "elif $python_condition:";

    if ($matchEqn ne ""){
        push @python_elsif, "\t" x ($indent + 1) . $matchEqn;
    }

    # similar to if, loop until lwe encounter a closing brace
    while (@perlInput && $perlInput[0] !~ /^\s*\}\s*/){
        push @python_elsif, translate_statement($perlInput[0], $indent + 1);
    }

    if ($perlInput[0] =~ /^\s*\}\s*$/){
        shift @perlInput;
    }

    else{
        $perlInput[0] =~ s/^\s*\}\s*//;
    }

    # print "Broke out of while loop.\n";
    # join everything in python_if array and return it
    my $pythonCode = join("\n", @python_elsif);
    return $pythonCode;
}

sub translate_else{
    my ($perl_else_statement, $indent) = @_;
    my @python_else = ();
    $perl_else_statement =~ /^\s*else\s*\{\s*/;

    push @python_else, "\t" x $indent . "else:";
    shift @perlInput;
    # loop until an ending brace is encountered
    while (@perlInput && $perlInput[0] !~ /^\s*\}\s*/){
        push @python_else, translate_statement($perlInput[0], $indent + 1);
    }

    # foudn the ending brace, just ignore it
    if ($perlInput[0] =~ /^\s*\}\s*$/){
        shift @perlInput;
    }

    else{
        $perlInput[0] =~ s/^\s*\}\s*//;
    }

    # print "Broke out of while loop.\n";
    # join everything in python_if array and return it
    my $pythonCode = join("\n", @python_else);
    return $pythonCode;
}

sub translate_while{
    my ($perl_while_statement, $indent) = @_;
    my @python_while = ();
    $perl_while_statement =~ /^\s*while\s*\((.*)\)\s*\{\s*$/;
    #shift @perlInput;
    my $condition = $1;
    #print "Condition for while: $condition\n";
    #$condition = translate_stdin($condition, "while");
    if ($condition =~ /^\s*\$\s*([^\s]*)\s*=\s*\<(.*)\>\s*$/){
        # print "Detected a <>\n";
        # print "Variable used is: $1\n";
        my $variable = $1;
        my $handle = $2;
        shift @perlInput;
        # perl scripts wants to read from stdin
        if ($handle =~ /STDIN/){
            $condition = translate_stdin("<$handle>", "for");
            push @python_while, "\t" x $indent . "for $variable in $condition:";
        }

        else{
            push @python_while, "\t" x $indent . "for $variable in $handle:";
            $variablesUsed{"$variable"} = "\"string\"";
        }
    }

    else{
        $condition = translate_statement($condition, 0);
        # form the python equivalent of the perl while condition
        push @python_while, "\t" x $indent . "while $condition:";
    }

    # loop until end of while loop
    while (@perlInput && $perlInput[0] !~ /^\s*\}\s*/){
        push @python_while, translate_statement($perlInput[0], $indent + 1);
    }

    # foudn the ending brace, just ignore it
    if ($perlInput[0] =~ /^\s*\}\s*$/){
        shift @perlInput;
    }

    else{
        $perlInput[0] =~ s/^\s*\}\s*//;
    }

    # combine the pyhon code in the array
    my $pythonCode = join("\n", @python_while);
    return $pythonCode;
}

# only dealing with for loops of one variable
sub translate_for{
    my ($perl_for_statement, $indent) = @_;
    my @python_for = ();
    shift @perlInput;
    # print "Indent = $indent\n";

    # for loops need to be handled differently unlike the rest
    if ($perl_for_statement =~ /;/){
        $perl_for_statement =~ /^\s*for\s*\((.*)\)\s*\{/g;
       # print "[FOR LOOP DEBUGGING]:\n";
       # print "matched: $1\n";
        my $for_condition = translate_expressions($1, 0);
        print "Condition for for loop: $for_condition\n" if $debug == 1;
        $for_condition =~ /^\s*(\w+)\s*=\s*([^\;]*)\s*;/;
        my $variable_used = $1;
        #print "Variable used is: $variable_used\n";
        my $initial_value = $2;

        $variablesUsed{"$variable_used"} = $initial_value;
        # print "Initial value is: $initial_value\n";
        $for_condition =~ /;\s*(\w+)\s*([\!\>\=\<]+)\s*([^\;]*)\s*;/;
        $variable_used = $1; # incase first one didn't catch it
        my $final_value = $3;
        my $operator = $2;
        # print "Final value is: $final_value\n";

        $for_condition =~ /;\s*$variable_used\s*(\+\=|\-\=)\s*(\d+)\s*$/;
        print "Operator = $1 and Step = $2\n" if $debug == 1;
        # detect if the loop is incremental or decremental
        my $step = $2;
        if ($1 eq "+="){
            # add the for loop statement to the python code
            if ($operator =~ /\>\=/){
                $final_value = "$final_value + 1";
            }
            push @python_for, "\t" x $indent . "for $variable_used in range($initial_value, $final_value, $step):";
        }

        else{
            if ($operator =~ /\<\=/){
                $final_value = "$final_value - 1";
            }
            push @python_for, "\t" x $indent . "for $variable_used in range($initial_value, $final_value, -$step):";
        }
    }

    else{
        #print "Different style of for loop detected.\n";
        if ($perl_for_statement =~ /^\s*for\s*\$([a-zA-Z]+[0-9\_]*)\s*\(@?(.*)\)\s*\{$/){
            my $place_holder = $1;
            my $list = $2;
            $list = translate_stdin($list, "for");
            $variablesUsed{"$place_holder"} = "\"list\"";
			if ($list =~ /\<STDIN\>/){ $list = translate_stdin($list, "for"); }
            elsif ($list =~ /\s*keys\s*%\s*.*/){ $list = translate_hash_iteration($list); }
			else{ $list = translate_expressions($list, 0); }
           	# print "[DEBUGGING FOR LOOP VER 2]:\n";
            # print "Place holder: $place_holder\n";
            # print "List: $list\n";
            push @python_for, "\t" x $indent . "for $place_holder in $list:";
        }
    }

    # translate everything else under the for loop
    while (@perlInput && $perlInput[0] !~ /^\s*\}\s*/){
        push @python_for, translate_statement($perlInput[0], $indent + 1);
    }

    # closing brace encountered so just shift it
    if ($perlInput[0] =~ /^\s*\}\s*$/){
        shift @perlInput;
    }

    else{
        $perlInput[0] =~ s/^\s*\}\s*//;
    }

	# print "[END OF FOR LOOP DEBUGGING]:\n";

    my $pythonCode = join("\n", @python_for);
    return $pythonCode;
}

sub translate_foreach{
    my ($perl_foreach_statement, $indent) = @_;
    my @python_foreach = ();
    shift @perlInput;

    # print "[FOREACH DEBUGGING]:\n";
    if ($perl_foreach_statement =~ /^\s*foreach\s*\$([a-zA-Z]+[0-9\_]*)\s*\(@?(.*)\)\s*{$/){
        my $placeHolder = $1;
        my $list = $2;
        # print "Place holder = $placeHolder\n";
        # print "List = $list\n";
        $variablesUsed{"$placeHolder"} = "\"list\"";
		if ($list =~ /\<STDIN\>/){ $list = translate_stdin($list, "for"); }
        elsif ($list =~ /\s*keys\s*%\s*.*/){ $list = translate_hash_iteration($list); }
		else{ $list = translate_expressions($list, 0); }
        push @python_foreach, "\t" x $indent . "for $placeHolder in $list:";
    }

    else{
        print "# Falsely detected a foreach statement\n" if $debug == 1;
    }

    while (@perlInput && $perlInput[0] !~ /^\s*\}\s*/){
        push @python_foreach, translate_statement($perlInput[0], $indent + 1);
    }

    if ($perlInput[0] =~ /^\s*\}\s*$/){
        shift @perlInput;
    }

    else{
        $perlInput[0] =~ s/^\s*\}\s*//;
    }

   	#print "[FOREACH DEBUGGING END]\n";
    my $pythonCode = join("\n", @python_foreach);
    return $pythonCode;
}

# Translate the use of <STDIN> in perl to its python equivalent
#   perl_statement = line in perl we want to translate
#   indent = number of spaces from left margin
#   $structure = which structure the <STDIN> belongs to: line, for, while
sub translate_stdin{
    my ($perl_statement, $structure) = @_;
    my $pythonCode = "";

    if ($perl_statement =~ /\<STDIN\>/){
        $imports{"import sys\n"} = 0;
        if ($structure eq "for"){
            $perl_statement =~ s/\<STDIN\>/sys\.stdin/;
        }

        elsif ($structure eq "while"){
            $perl_statement =~ s/\<STDIN\>/sys\.stdin\.readlines\(\)/;
        }

        elsif ($structure eq "line"){
            $perl_statement =~ s/\<STDIN\>/sys\.stdin\.readline\(\)/;
        }

        else{
            print "# Pass in a legit structure please.\n" if $debug == 1;
        }
    }

    $pythonCode = $perl_statement;
    return $pythonCode;
}

# translate perl hash iteration to python hash iteration
sub translate_hash_iteration{
    my ($perl_hash_iteration) = @_;
    my $python_hash_iteration = "";
    my $hash_name = "";

    # only accounting for 1 dimensional hashes + arrays
    if ($perl_hash_iteration =~ /^\s*keys\s*%\s*(.*)$/){
        $hash_name = $1;
        $python_hash_iteration = "$hash_name.keys()";
    }

    elsif ($perl_hash_iteration =~ /\s*sort\s*keys\s*%\s*(.*)$/){
        $hash_name = $1;
        $python_hash_iteration = "sorted($hash_name.keys())";
    }

    else{
        print "# Failed translation of iteration of hashes.\n" if $debug == 1;
    }

    return $python_hash_iteration;
}

# determines the type of a variable, useful for typecasting
sub determine_type{
    my ($variable) = @_;
    # assume variable is a perl variable
    $variable =~ s/\$//g;
    $variable =~ s/\@//g;
    my $value = $variablesUsed{"$variable"};
    my $type = $STRING;
    print "Variable is = $variable\n" if $debug == 1;

    if (!defined($value)){
        $type = $STRING;
    }

    elsif ($value !~ /"/ && $value !~ /\./ && $value =~ /^\s*\d+/ && $value !~ /'/){
        $type = $INTEGER;
    }

    # variable holds a floating point value
    elsif ($value =~ /\d*\.\d+/ && $value !~ /"/ && $value !~ /'/){
        $type = $FLOATING;
    }

    # variable holds an integer value
    else{
        $type = $STRING;
    }

    return $type;
}
