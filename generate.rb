#!/usr/bin/env ruby

##############################################################
# script to generate signal*.h files from signal_template.h
##############################################################

def make_header_file(nargs)
	# hash to store our substitutions in
	subs = {}

	# create subst strings for template and function arguments (template args follow T_return, so start with a comma)
	subs["===NARG==="]              = nargs.to_s
	subs["===TEMPLATE_ARG_DECL==="] = (nargs > 0 ? ", ":"") + nargs.times.map { |i| "typename T_arg#{i}" }.join(", ")
	subs["===TEMPLATE_ARG==="]      = (nargs > 0 ? ", ":"") + nargs.times.map { |i| "T_arg#{i}" }.join(", ")
	subs["===FORMAL_ARG_DECL==="]   = nargs.times.map { |i| "T_arg#{i} a#{i}" }.join(", ")
	subs["===FORMAL_ARG==="]        = nargs.times.map { |i| "a#{i}" }.join(", ")

	# load template file
	text = IO.read("signal_template.h")

	# do substitutions
	subs.each { |k,v| text.gsub!(k,v) }

	# write output file
	File.open("signal#{nargs}.h","w") { |f| f.write(text) }
end

# generate [signal0.h,signal16.h]
(0..16).each { |i| make_header_file(i) }

