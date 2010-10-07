#!/usr/bin/env ruby

##############################################################
# script to generate signal.h files from signalx.h.tpl, etc. #
##############################################################

#
# configuration
#

# maximum size signal/slot (in parameters) to generate
MaxParameters = 6 

#
# some templates
#
Header = <<ENDSTR
#ifndef __signal_h__
#define __signal_h__

#include "horrible_cast.h"
#include "slot_base.h"
#include "signal_base.h"


/*
 * Begin signal[X] definitions
 */

ENDSTR

Middle = <<ENDSTR
/*
 * Begin signal template definitions and specilizations
 */

ENDSTR

Footer = <<ENDSTR
#endif // __signal_h__
ENDSTR

#
# make signalX, slotX, and associated definitions from template file
#
def make_signal(nargs)
	# hash to store our substitutions in
	subs = {}

	# create subst strings for template and function arguments (template args follow T_return, so start with a comma)
	subs["===NARG==="]              = nargs.to_s
	subs["===TEMPLATE_ARG_DECL==="] = (nargs > 0 ? ", ":"") + nargs.times.map { |i| "typename T_arg#{i}" }.join(", ")
	subs["===TEMPLATE_ARG==="]      = (nargs > 0 ? ", ":"") + nargs.times.map { |i| "T_arg#{i}" }.join(", ")
	subs["===FORMAL_ARG_DECL==="]   = nargs.times.map { |i| "T_arg#{i} a#{i}" }.join(", ")
	subs["===FORMAL_ARG==="]        = nargs.times.map { |i| "a#{i}" }.join(", ")

	# load template file
	text = IO.read("signalx.h.tpl")

	# do substitutions
	subs.each { |k,v| text.gsub!(k,v) }

	# return result
	text
end

#
# make the template for signal, pointing it to signalX
#
def make_template(nargs)
	text = ""

	nargs.downto(0).each do |i|
		if i == nargs
			text += "struct nilarg;\n\n"
			default_arg = "=nilarg"
		else
			default_arg = ""
		end
		template_params = ( ["typename T_return"] + i.times.map { |i| "typename T_arg#{i}#{default_arg}" } ).join(", ")
		template_args   = ( ["T_return" ]         + i.times.map { |i| "T_arg#{i}" } ).join(", ")

		if i == nargs
			text += "// full template for signal<> (signal<> inherits signal#{i}<>)\n"
		else
			text += "// partial specialization for signal<> with #{i} parameters (signal<> inherits signal#{i}<>)\n"
		end

		text += "template <#{template_params}>\n"
		if i == nargs
			text += "class signal: public signal#{i}<#{template_args}> { /* empty class */ };\n"
		else
			text += "class signal<#{template_args}>: public signal#{i}<#{template_args}> { /* empty class */ };\n"
		end
		text += "\n"
	end
	text
end

#
# main program
#
File.open("signal.h","wt") do |f|
	f.puts Header
	(0..MaxParameters).each { |i| f.puts make_signal(i) }
	f.puts Middle
	f.puts make_template(MaxParameters)
	f.puts Footer
end

