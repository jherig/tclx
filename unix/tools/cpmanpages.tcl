#
# cpmanpages.tcl -- 
#
# Tool used during build to copy manual pages to master directories.  This
# program knows the internals of the build, so its very specific to this
# task.
#
# It is run in the following manner:
#
#     cpmanpages TCL|TCLX|TK sourceDir ?man-separator-char?
#
#------------------------------------------------------------------------------
# Copyright 1992-1993 Karl Lehenbauer and Mark Diekhans.
#
# Permission to use, copy, modify, and distribute this software and its
# documentation for any purpose and without fee is hereby granted, provided
# that the above copyright notice appear in all copies.  Karl Lehenbauer and
# Mark Diekhans make no representations about the suitability of this
# software for any purpose.  It is provided "as is" without express or
# implied warranty.
#------------------------------------------------------------------------------
# $Id: cpmanpages.tcl,v 1.6 1993/09/23 05:40:51 markd Exp markd $
#------------------------------------------------------------------------------
#

#------------------------------------------------------------------------------
# CopyManFile -- 
#
# Called to open a copy a man file.  Recursively called to include .so files.
#------------------------------------------------------------------------------

proc CopyManFile {sourceFile targetFH} {

    set sourceFH [open $sourceFile r]

    while {[gets $sourceFH line] >= 0} {
        if [string match {.V[SE]*} $line] continue
        if [string match {.so *} $line] {
            set soFile [string trim [crange $line 3 end]]
            CopyManFile "[file dirname $sourceFile]/$soFile" $targetFH
            continue
        }
        puts $targetFH $line
    }

    close $sourceFH
}

#------------------------------------------------------------------------------
# CopyManPage -- 
#
# Copy the specified manual page and change the ownership.  The manual page
# is edited to remove change bars (.VS and .VE macros). Files included with .so
# are merged in.
#------------------------------------------------------------------------------

proc CopyManPage {sourceFile targetFile} {

    if ![file exists [file dirname $targetFile]] {
        mkdir -path [file dirname $targetFile]
    }
    unlink -nocomplain $targetFile

    set targetFH [open $targetFile w]
    CopyManFile $sourceFile $targetFH
    close $targetFH
}

#------------------------------------------------------------------------------
# GetManNames --
#
#   Search a manual page (nroff source) for the name line.  Parse the name
# line into all of the functions or commands that it references.  This isn't
# comprehensive, but it works for all of the Tcl, TclX and Tk man pages.
#
# Parameters:
#   o manFile (I) - The path to the  manual page file.
# Returns:
#   A list contain the functions or commands or {} if the name line can't be
# found or parsed.
#------------------------------------------------------------------------------

proc GetManNames manFile {

   set manFH [open $manFile]

   #
   # Search for name line.  Once found, grab the next line that is not a
   # nroff macro.  If we end up with a blank line, we didn't find it.
   #
   while {[gets $manFH line] >= 0} {
       if [regexp {^.SH NAME.*$} $line] {
           break
       }
   }
   while {[gets $manFH line] >= 0} {
       if {![string match ".*" $line]} break
   }
   close $manFH

   set line [string trim $line]
   if {$line == ""} return

   #
   # Lets try and parse the name list out of the line
   #
   if {![regexp {^(.*)(\\-)} $line {} namePart]} {
       if {![regexp {^(.*)(-)} $line {} namePart]} return
   }

   #
   # This magic converts the name line into a list
   #

   if {[catch {join [split $namePart ,] " "} namePart] != 0} return

   return $namePart

}

#------------------------------------------------------------------------------
# InstallShortMan --
#   Install a manual page on a system that does not have long file names.
#
# Parameters:
#   o sourceFile - Manual page source file path.
#   o targetDir - Directory to install the file in.
#   o extension - Extension to use for the installed file.
# Globals:
#   o config - configuration information.
# Returns:
#   A list of the man files created, relative to targetDir.
#------------------------------------------------------------------------------

proc InstallShortMan {sourceFile targetDir extension} {
    global config

    set manFileName "[file tail [file root $sourceFile]].$extension"

    CopyManPage $sourceFile "$targetDir/$manFileName"

    return $manFileName
}

#------------------------------------------------------------------------------
# InstallLongMan --
#   Install a manual page on a system that has long file names.
#
# Parameters:
#   o sourceFile - Manual page source file path.
#   o targetDir - Directory to install the file in.
#   o extension - Extension to use for the installed file.
# Globals:
#   o config - configuration information.
# Returns:
#   A list of the man files created, relative to targetDir.  They are all links
# to the same entry.
#------------------------------------------------------------------------------

proc InstallLongMan {sourceFile targetDir extension} {
    global config

    set manNames [GetManNames $sourceFile]
    if [lempty $manNames] {
        set baseName [file tail [file root $sourceFile]]
        puts stderr "Warning: can't parse NAME line for man page: $sourceFile."
        puts stderr "         Manual page only available as: $baseName"
        set manNames [list [file tail [file root $sourceFile]]]
    }

    # Copy file to the first name in the list.

    set firstFilePath $targetDir/[lvarpop manNames].$extension
    set created [list [file tail $firstFilePath]]

    CopyManPage $sourceFile $firstFilePath

    # Link it to the rest of the names in the list.

    foreach manName $manNames {
        set targetFile  $targetDir/$manName.$extension
        unlink -nocomplain $targetFile
        if {[catch {
                link $firstFilePath $targetFile
            } msg] != 0} {
            puts stderr "error from: link $firstFilePath $targetFile"
            puts stderr "    $msg"
        } else {
            lappend created [file tail $targetFile]
        }
    }
    return $created
}

#------------------------------------------------------------------------------
# InstallManPage --
#   Install a manual page on a system.
#
# Parameters:
#   o sourceFile - Manual page source file path.
#   o manDir - Directory to build the directoy containing the manual files in.
#   o section - Section to install the manual page in.
# Globals
#   o config - configuration information.
# Returns:
#   A list of the man files created, relative to targetDir.  They are all links
# to the same entry.
#------------------------------------------------------------------------------

proc InstallManPage {sourceFile manDir section} {
    global config manSeparator

    set targetDir "$manDir/man${manSeparator}${section}"

    if {$config(TCL_MAN_STYLE) == "SHORT"} {
        set files [InstallShortMan $sourceFile $targetDir $section]
    } else {
        set files [InstallLongMan $sourceFile $targetDir $section]
    }
   
    set created {}
    foreach file $files {
        lappend created man${manSeparator}${section}/$file
    }
    return $created
}

#------------------------------------------------------------------------------
# main prorgam

if {[llength $argv] < 2 || [llength $argv] > 3} {
    puts stderr "wrong # args: cpmanpages TCL|TCLX|TK sourceDir ?manSeparator?"
    exit 1
}
set manType [lindex $argv 0]
set sourceDir [lindex $argv 1]
set manSeparator [lindex $argv 2]

# Parse the configure files and then default missing values.

ParseConfigFile ../Config.mk config

if ![info exists config(TCL_MAN_STYLE)] {
    set config(TCL_MAN_STYLE) LONG
}

set sourceFiles [glob -nocomplain -- $sourceDir/*.man $sourceDir/*.n \
                      $sourceDir/*.1 $sourceDir/*.3]

switch -- $manType {
    TCL {
        puts stdout "Copying Tcl manual pages to tclmaster/man"
        set destDir   ../tclmaster/man
        set sectionXRef(.n)   $config(TCL_MAN_CMD_SECTION)
        set sectionXRef(.3)   $config(TCL_MAN_FUNC_SECTION)
    }
    TCLX {
        puts stdout "Copying Extended Tcl manual pages to tclmaster/man"
        set destDir   ../tclmaster/man
        set sectionXRef(.n)   $config(TCL_MAN_CMD_SECTION)
        set sectionXRef(.3)   $config(TCL_MAN_FUNC_SECTION)
    }
    TK {
        puts stdout "Copying Tk manual pages to tkmaster/man"
        set destDir ../tkmaster/man
        set sectionXRef(.1)   $config(TK_MAN_UNIXCMD_SECTION)
        set sectionXRef(.n)   $config(TK_MAN_CMD_SECTION)
        set sectionXRef(.3)   $config(TK_MAN_FUNC_SECTION)
    }
    default {
        puts stderr "Expected on of TCL, TCLX or TK, got \"$manType\""
    }
}

set ignoreFiles {tclsh.1}

# Actually install the files.

set created {}

foreach sourceFile $sourceFiles {
    if {[lsearch $ignoreFiles [file tail $sourceFile]] >= 0} continue

    set ext [file extension $sourceFile]
    if ![info exists sectionXRef($ext)] {
        puts stderr "WARNING: Don't know how to handle section for $sourceFile,"
        continue
    }
    set file [InstallManPage $sourceFile $destDir $sectionXRef($ext)]
    lappend created $file
}

#
# For the TclX manual pages, create a file describing the files to install.
#

if {"$manType" == "TCLX"} {
    set fh [open ../tools/TclXman.lst w]
    foreach fileSet $created {
        puts $fh $fileSet
    }
    close $fh
}
