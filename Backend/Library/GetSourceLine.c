#include "world.h"
#include <fcntl.h>
#include <sys/file.h>


/**************************************************************************/
/* GLOBAL **************       GetSourceLine       ************************/
/**************************************************************************/
/* PURPOSE: Return the source line associated with the node.  Also,	  */
/*	    remove star slash combos that would kill us in a C		  */
/*	    comment.							  */
/**************************************************************************/
char* GetSourceLine(N)
     PNODE	N;
{
  char		*p;		/* Misc char pointer */
  static char	LineBuf[1024];

  /* ------------------------------------------------------------ */
  /* Give up if we don't have a filename			  */
  /* ------------------------------------------------------------ */
  if ( !N->file ) return NULL;

  /* ------------------------------------------------------------ */
  /* Give up for really big files				  */
  /* ------------------------------------------------------------ */
  if ( N->line > 100000 ) return NULL;

  {
#ifndef L_SET
    /* ------------------------------------------------------------ */
    /* If we cannot seek, we can't cache sets of source lines	    */
    /* Therefore, we'll just get them by scanning the whole file    */
    /* ------------------------------------------------------------ */

    FILE	*FP;
    int		i;

    FP = fopen(N->file,"r");	/* Open the proper file */
    if ( !FP ) return NULL;

    for(i=0;i<N->line;i++) if ( !fgets(LineBuf,sizeof(LineBuf),FP) ) break;
    if ( i != N->line ) return NULL;

    /* Kill the trailing newline */
    for(p=LineBuf;*p;p++) if ( *p == '\n') { *p = NULL; break; }

#else
    /* ------------------------------------------------------------ */
    /* Since we can seek, we'll cache lines for faster fetches	    */
    /* ------------------------------------------------------------ */

#define QSize1		(100)
#define QSize		(10)
    static struct {
      char		*File;
      int		fildes;
      int		SourceLine[QSize1];
      long		Offset[QSize1];
    } Queue[QSize], *QEntry = Queue;
    static int		QPtr = 0,SLPtr = 0;

    static int	First = 1;
    int		i,j,ClosestLine,Line;
    long	offset,ClosestOffset;
    char	c;

    /* ------------------------------------------------------------ */
    /* Give up if we don't have a filename */
    if ( !N->file ) return NULL;

    /* Give up for really big files */
    if ( N->line > 100000 ) return NULL;

    /* ------------------------------------------------------------ */
    /* Set up the data structure (if necessary) */
    if (First) {
      for(i=0;i<QSize;i++) {
	Queue[i].File = NULL;
	for(j=0;j<QSize1;j++) {
	  Queue[i].SourceLine[j] = 0;
	  Queue[i].Offset[j] = 0;
	}
      }
      First = 0;
    }

    /* ------------------------------------------------------------ */
    /* Try to find the current file in the Queue */
    if ( (!QEntry->File) || strcmp(QEntry->File,N->file) != 0 ) {
      QEntry = NULL;
      for(i=0;i<QSize;i++) {
	if ( Queue[i].File && strcmp(Queue[i].File,N->file) == 0 ) {
	  QEntry = Queue+i;
	  break;
	}
      }
    }

    /* ------------------------------------------------------------ */
    /* No Match, set up a new entry */
    if ( !QEntry ) {
      QEntry = Queue+QPtr;
      QPtr = (QPtr+1) % QSize;

      /* If there's someone there, close it */
      if ( QEntry->fildes ) {
	(void)close( QEntry->fildes );
	for(j=0;j<QSize1;j++) {
	  QEntry->SourceLine[j] = 0;
	  QEntry->Offset[j] = 0;
	}
      }

      /* Put ourselves there */
      QEntry->File	= N->file;
      QEntry->fildes	= open(N->file,O_RDONLY);
    }

    /* ------------------------------------------------------------ */
    /* Give up if the file could not be opened */
    if ( QEntry->fildes == -1 ) return NULL;

    /* ------------------------------------------------------------ */
    /* Look for our line number in the queue */
    for(i=0;i<QSize1;i++) {
      if ( N->line == QEntry->SourceLine[i] ) {
	offset = QEntry->Offset[i];
	(void)lseek(QEntry->fildes,offset,L_SET);
	goto Found;
      }
    }

    /* ------------------------------------------------------------ */
    /* Find the largest offset less than the requested line and start */
    /* from there... */
    ClosestLine = 1;
    ClosestOffset = 0;
    for(i=0;i<QSize1;i++) {
      if ( QEntry->SourceLine[i] < N->line
	  && QEntry->SourceLine[i] > ClosestLine ) {
	ClosestLine = QEntry->SourceLine[i];
	ClosestOffset = QEntry->Offset[i];
      }
    }

    /* Find the offset for this line */
    (void)lseek(QEntry->fildes,ClosestOffset,L_SET);
    for(offset=ClosestOffset,Line = ClosestLine; Line < N->line; Line++ ) {
      for(i=1; read(QEntry->fildes,&c,(unsigned)1); i++) {
	if ( c == '\n' ) break;
      }
      offset += i;
    }

    /* Remember this offset */
    QEntry->SourceLine[SLPtr]	= N->line;
    QEntry->Offset[SLPtr]		= offset;
    SLPtr = (SLPtr+1) % QSize1;

  Found:
    for(i=0; i< (sizeof(LineBuf)-1) && read(QEntry->fildes,LineBuf+i,1); i++) {
      if ( LineBuf[i] == '\n' ) break;
    }
    LineBuf[i] = NULL;

#endif
  }

  /* ------------------------------------------------------------ */
  /* Examine the line for illegal constructs like STAR SLASH	  */
  /* ------------------------------------------------------------ */
  for(p=LineBuf; *p; p++) {
    if ( *p == '*' && *(p+1) == '/' ) *p = '?';
  }

  return LineBuf;
}

/* $Log: GetSourceLine.c,v $
 * Revision 1.4  1993/03/23  22:53:27  miller
 * date problem
 *
 * Revision 1.3  1994/03/16  19:45:47  miller
 * Fixed to allow getting source lines without seek support.
 *
 * Revision 1.2  1994/03/11  23:09:52  miller
 * Moved IFX.h into Backend/Library and added support for Minimal
 * installation (removing source as compiled).
 *
 * Revision 1.1  1993/01/21  23:28:45  miller
 * Initial version of the IFX library.  It replaces the if[12]build.c
 * read.c timer.c util.c and write.c and if[12].h files from the
 * backend phases.
 * */