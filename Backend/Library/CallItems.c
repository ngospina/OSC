#include "world.h"


int color = WHITE;		/* CURRENT COLOR IN CYCLE DETECTION    */
PNODE chead = NULL;		/* COMPOUND NODE TRUNK HEAD */
PNODE ctail = NULL;		/* COMPOUND NODE TRUNK HEAD */

PCALL cghead = NULL;		/* CALL GRAPH TRUNK HEAD */
PCALL cgtail = NULL;		/* CALL GRAPH TRUNK HEAD */

/* $Log: CallItems.c,v $
 * Revision 1.1  1993/01/21  23:28:02  miller
 * Initial version of the IFX library.  It replaces the if[12]build.c
 * read.c timer.c util.c and write.c and if[12].h files from the
 * backend phases.
 * */