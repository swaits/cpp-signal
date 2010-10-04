#!/usr/bin/perl

##############################################################
# script to generate signal*.h files from signal_template.h
##############################################################


##############################################
#
# globals
#
##############################################

# a variable to store our template text in
my $template = "";


##############################################
#
# main()
#
##############################################

# load template	text (see bottom of script)
open(INFILE,"<signal_template.h") || die "Couldn't open signal_template.h";
my $isheader = 0;
while(<INFILE>)
{
	$template .= $_;
}
close(INFILE);

# generate [signal0.h,signal16.h]
for (my $i=0;$i<=16;$i++)
{
	GenerateSignalXHeader($i);
}


##############################################
#
# Subroutines
#
##############################################

# subroutine to generate one signal header file
sub GenerateSignalXHeader
{
	# only argument is number of template arguments to allow for this signal
	my($nargs) = @_;

	# create a local copy of template text
	my $file = $template;

	# create other substitution strings
	my $narg_str              = "";
	my $template_arg_decl_str = "";
	my $template_arg_str      = "";
	my $formal_arg_decl_str   = "";
	my $formal_arg_str        = "";

	# create subst string for # of args
	$narg_str = sprintf("%d",$nargs);

	# create subst strings for template and function arguments
	if ( $nargs > 0 )
	{
		# template args follow T_return, so start with a comma
		$template_arg_decl_str = ", ";
		$template_arg_str = ", ";

		for (my $i=0;$i<($nargs-1);$i++)
		{
			# args with trailing comma
			$template_arg_decl_str .= sprintf("typename T_arg%d, ",$i);
			$template_arg_str      .= sprintf("T_arg%d, ",$i);
			$formal_arg_decl_str   .= sprintf("T_arg%d a%d, ",$i,$i);
			$formal_arg_str        .= sprintf("a%d, ",$i);
		}

		# args without trailing comma
		$template_arg_decl_str .= sprintf("typename T_arg%d",$nargs-1);
		$template_arg_str      .= sprintf("T_arg%d",$nargs-1);
		$formal_arg_decl_str   .= sprintf("T_arg%d a%d",$nargs-1,$nargs-1);
		$formal_arg_str        .= sprintf("a%d",$nargs-1);
	}

	# do substitution
	$file =~ s/===NARG===/$narg_str/g;
	$file =~ s/===TEMPLATE_ARG_DECL===/$template_arg_decl_str/g;
	$file =~ s/===TEMPLATE_ARG===/$template_arg_str/g;
	$file =~ s/===FORMAL_ARG_DECL===/$formal_arg_decl_str/g;
	$file =~ s/===FORMAL_ARG===/$formal_arg_str/g;

	# create filename
	my $filename = sprintf("signal%d.h",$nargs);

	# write file
	open(OUTFILE,">$filename") || die;
	print OUTFILE $file;
	close(OUTFILE);
}

