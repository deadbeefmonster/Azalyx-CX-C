#!/usr/bin/perl
#
use strict;

my $sqlfile = $ARGV[0];
if (!$sqlfile || ! -e $sqlfile || ! -r $sqlfile) {
    print "USAGE: $0 <sql file>\n";
    exit;
}

my %data_structures;
my $table_name = "";

my %data_conversion_map = (
    'integer' => 'guint32 ',
    'int' => 'guint32 ',
    'boolean' => 'gboolean ',
    'text' => 'GString *',
    'blob' => 'GByteArray *',
    'datetime' => 'guint32 '
    );
my %data_comments;
open(my $fp, $sqlfile) || die "Could not open sql file '$sqlfile' for reading: $!\n";
while(<$fp>) {
    my $line = $_;
    $line =~ s/^\s+//;
    $line =~ s/\s+$//;
    if (lc($line) =~ /drop.*/) {
    }
    elsif (lc($line) =~ /create\s+table\s+([a-z0-9_]+)/) {
	$table_name = $1;
	if (!defined %data_structures{$table_name}) {
	    $data_structures{$table_name} = ();
	}
	#print "\ntable_name: $table_name\n";
    }
    elsif (lc($line) =~ /^([a-z0-9_]+)\s+([a-z]+)(.*)/) {
	my $field_name = $1;
	my $data_type = $2;
	my $other_stuff = $3;
	#print "- field_name: $field_name -> data_type: $data_type ($other_stuff)\n";
	my $datum = $data_conversion_map{$data_type} . $field_name;
	if ($other_stuff =~ /\s+references\s+([a-z0-9]+)\s+\(([a-z0-9_]+)\).*/) {
	    my $data_comments_key = $table_name . "__" . $datum;
	    $data_comments{$data_comments_key} = "/* References database_data_" . $1 . "." . $2 . " */";
	    #print "-- Added data comments\n";
	}
	push @{$data_structures{$table_name}}, $datum;
    }
}
close($fp);

foreach my $data_structure_name (sort keys %data_structures) {
    print "/* Table: $data_structure_name */\n";
    print "struct database_data_" . $data_structure_name . " {\n";
    foreach my $datum (@{$data_structures{$data_structure_name}}) {
	print "    $datum;";
	my $data_comments_key = $data_structure_name . "__" . $datum;
	if (defined $data_comments{$data_comments_key}) {
	    print " " . $data_comments{$data_comments_key};
	}
	print "\n";
    }
    print "};\n\n";
}
