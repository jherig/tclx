/*
 * tclXcreate.c
 *
 * Contains a routine to create an interpreter and initialize all the Extended
 * Tcl commands.  It is is a seperate file so that an application may create
 * the interpreter and add in only a subset of the Extended Tcl commands.
 *-----------------------------------------------------------------------------
 * Copyright 1991-1993 Karl Lehenbauer and Mark Diekhans.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies.  Karl Lehenbauer and
 * Mark Diekhans make no representations about the suitability of this
 * software for any purpose.  It is provided "as is" without express or
 * implied warranty.
 *-----------------------------------------------------------------------------
 * $Id: tclXcreate.c,v 2.5 1993/07/25 00:56:25 markd Exp markd $
 *-----------------------------------------------------------------------------
 */

#include "tclExtdInt.h"


/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_AddExtendedCmds --
 *
 *   Add the Extended Tcl commands to the specified interpreter (except for
 * the library commands that override that standard Tcl procedures).
 *-----------------------------------------------------------------------------
 */
void
Tcl_AddExtendedCmds (interp)
    Tcl_Interp *interp;
{

    /*
     * from tclCkalloc.c (now part of the UCB Tcl).
     */
#ifdef TCL_MEM_DEBUG    
    Tcl_InitMemory (interp);
#endif

    /*
     * from tclXbsearch.c
     */
    Tcl_CreateCommand (interp, "bsearch", Tcl_BsearchCmd, 
                      (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXchmod.c
     */
    Tcl_CreateCommand (interp, "chgrp", Tcl_ChgrpCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "chmod", Tcl_ChmodCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "chown", Tcl_ChownCmd,
                       (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXclock.c
     */
    Tcl_CreateCommand (interp, "getclock", Tcl_GetclockCmd, 
                      (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "fmtclock", Tcl_FmtclockCmd, 
                      (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXcnvdate.c
     */
    Tcl_CreateCommand (interp, "convertclock", Tcl_ConvertclockCmd,
                      (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXcmdloop.c
     */
    Tcl_CreateCommand (interp, "commandloop", Tcl_CommandloopCmd, 
                      (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXdebug.c
     */
    Tcl_InitDebug (interp);

    /*
     * from tclXdup.c
     */
    Tcl_CreateCommand (interp, "dup",  Tcl_DupCmd, 
                       (ClientData) NULL, (void (*)()) NULL);
    /*
     * from tclXtclXfcntl.c
     */
    Tcl_CreateCommand (interp, "fcntl", Tcl_FcntlCmd,
                       (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXfilecmds.c
     */
    Tcl_CreateCommand (interp, "pipe", Tcl_PipeCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "copyfile", Tcl_CopyfileCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "lgets", Tcl_LgetsCmd,
                       (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXfstat.c
     */
    Tcl_CreateCommand (interp, "fstat", Tcl_FstatCmd,
                       (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXflock.c
     */
    Tcl_CreateCommand (interp, "flock", Tcl_FlockCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "funlock", Tcl_FunlockCmd,
                       (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXfilescan.c
     */
    Tcl_InitFilescan (interp);

    /*
     * from tclXgeneral.c
     */
    Tcl_CreateCommand(interp, "echo", Tcl_EchoCmd, 
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "infox", Tcl_InfoxCmd, 
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "loop", Tcl_LoopCmd, 
                     (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXid.c
     */
    Tcl_CreateCommand (interp, "id", Tcl_IdCmd,
                       (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXkeylist.c
     */
    Tcl_CreateCommand(interp, "keyldel", Tcl_KeyldelCmd,
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "keylget", Tcl_KeylgetCmd,
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "keylkeys", Tcl_KeylkeysCmd,
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "keylset", Tcl_KeylsetCmd,
                     (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXlist.c
     */
    Tcl_CreateCommand(interp, "lvarcat", Tcl_LvarcatCmd, 
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "lvarpop", Tcl_LvarpopCmd, 
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "lvarpush", Tcl_LvarpushCmd, 
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "lempty", Tcl_LemptyCmd, 
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "lassign", Tcl_LassignCmd, 
                     (ClientData) NULL, (void (*)()) NULL);
    /*
     * from tclXmath.c
     */
    Tcl_CreateCommand (interp, "max", Tcl_MaxCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "min", Tcl_MinCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "random", Tcl_RandomCmd,
                       (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXmsgcat.c
     */
    Tcl_InitMsgCat (interp);

    /*
     * from tclXprocess.c
     */
    Tcl_CreateCommand (interp, "execl", Tcl_ExeclCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "fork", Tcl_ForkCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "wait", Tcl_WaitCmd,
                       (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXprofile.c
     */
    Tcl_InitProfile (interp);

    /*
     * from tclXselect.c
     */
    Tcl_CreateCommand (interp, "select", Tcl_SelectCmd,
                       (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXsignal.c
     */
    Tcl_InitSignalHandling (interp);

    /*
     * from tclXstring.c
     */
    Tcl_CreateCommand(interp, "cindex", Tcl_CindexCmd, 
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "clength", Tcl_ClengthCmd, 
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "crange", Tcl_CrangeCmd, 
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "csubstr", Tcl_CrangeCmd, 
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand(interp, "replicate", Tcl_ReplicateCmd, 
                     (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "translit", Tcl_TranslitCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "ctype", Tcl_CtypeCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "ctoken", Tcl_CtokenCmd,
                       (ClientData) NULL, (void (*)()) NULL);

    /*
     * from tclXunixcmds.c
     */
    Tcl_CreateCommand (interp, "system", Tcl_SystemCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "times", Tcl_TimesCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "umask", Tcl_UmaskCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "link", Tcl_LinkCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "unlink", Tcl_UnlinkCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "mkdir", Tcl_MkdirCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "rmdir", Tcl_RmdirCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "alarm", Tcl_AlarmCmd,
                       (ClientData) NULL, (void (*)()) NULL);
    Tcl_CreateCommand (interp, "sleep", Tcl_SleepCmd,
                       (ClientData) NULL,(void (*)()) NULL);

    /*
     * from tclXserver.c
     */
    Tcl_CreateCommand (interp, "server_open", Tcl_ServerOpenCmd,
                       (ClientData) NULL, (void (*)()) NULL);
}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_AddExtendedLibCmds --
 *
 *   Add the Extended Tcl library management commands.  These override the
 * standard Tcl procedures.
 *-----------------------------------------------------------------------------
 */
void
Tcl_AddExtendedLibCmds (interp)
    Tcl_Interp *interp;
{
    /*
     * from tclXlib.c
     */
    Tcl_InitLibrary (interp);
}

/*
 *-----------------------------------------------------------------------------
 *
 * Tcl_CreateExtendedInterp --
 *
 *      Create a new TCL command interpreter and initialize all of the
 *      extended Tcl commands..
 *
 * Returns:
 *      The return value is a token for the interpreter.
 *-----------------------------------------------------------------------------
 */
Tcl_Interp *
Tcl_CreateExtendedInterp ()
{
    Tcl_Interp *interp;

    interp = Tcl_CreateInterp ();

    Tcl_AddExtendedCmds (interp);
    Tcl_AddExtendedLibCmds (interp);

    return interp;
}
