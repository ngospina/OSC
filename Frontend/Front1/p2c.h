
/* Header file for code generated by "p2c", the Pascal-to-C translator */

/* "p2c"  Copyright (C) 1989 Dave Gillespie, version 1.16.
 * This file may be copied, modified, etc. in any way.  It is not restricted
 * by the licence agreement accompanying p2c itself.
 */


#include <stdio.h>
#include <ctype.h>
#include <math.h>
/* #include <setjmp.h> */
/* #include <assert.h> */
#ifndef NO_TIME
# include <time.h>
#endif


/* CANN 1/92 TO ALLOW FOR BIGGER LINE BUFFERS */
#define short int


/* #ifdef M_XENIX  */ /* CANN 3/92 */ /* avoid compiler bug */
# define SHORT_MAX  (32767)
# define SHORT_MIN  (-32768)
/* #endif */


/* The following definitions work only on twos-complement machines */
#ifndef SHORT_MAX
# define SHORT_MAX  (((unsigned short) -1) >> 1)
# define SHORT_MIN  (~SHORT_MAX)
#endif

#ifndef INT_MAX
# define INT_MAX    (((unsigned int) -1) >> 1)
# define INT_MIN    (~INT_MAX)
#endif

#ifndef LONG_MAX
# define LONG_MAX   (((unsigned long) -1) >> 1)
# define LONG_MIN   (~LONG_MAX)
#endif

#ifndef SEEK_SET
# define SEEK_SET   0
# define SEEK_CUR   1
# define SEEK_END   2
#endif

#ifndef EXIT_SUCCESS
# define EXIT_SUCCESS  0
# define EXIT_FAILURE  1
#endif


#define SETBITS  32


# define Signed
# define Void       int
# ifndef Const
#  define Const
# endif
# ifndef Volatile
#  define Volatile
# endif
# define PP(x)      ()
# define PV()       ()

typedef char *Anyptr;

# define Inline

#define Register    register  /* Register variables */
#define Char        char      /* Characters (not bytes) */

#ifndef Static
# define Static
#endif

#ifndef Local
# define Local
#endif

typedef Signed   char schar;
/* typedef unsigned char unchar;*/ /* CANN TYPE CHANGE 1/92 FOR LONGER LINES */
/* typedef unsigned int unchar;*/
typedef unsigned char boolean;

#ifndef true
# define true    1
# define false   0
#endif


typedef struct {
    Anyptr proc, link;
} _PROCEDURE;

#ifndef _FNSIZE
# define _FNSIZE  120
#endif


extern void    PASCAL_MAIN  PP( (int, Char **) );
extern Char    **P_argv;
extern int     P_argc;
extern short   P_escapecode;
extern int     P_ioresult;


/* extern Anyptr   malloc      PP( (size_t) ); */
/* extern void     free        PP( (Anyptr) ); */

/* extern int      _OutMem     PV(); */
extern Anyptr   _OutMem     PV();

extern int      _CaseCheck  PV();
extern int      _NilCheck   PV();
extern int	_Escape     PP( (int) );
extern int	_EscIO      PP( (int) );

extern long     ipow        PP( (long, long) );
extern Char    *strsub      PP( (Char *, Char *, int, int) );
extern Char    *strltrim    PP( (Char *) );
extern Char    *strrtrim    PP( (Char *) );
extern Char    *strrpt      PP( (Char *, Char *, int) );
extern Char    *strpad      PP( (Char *, Char *, int, int) );
extern int      strpos2     PP( (Char *, Char *, int) );
extern long     memavail    PV();
extern int      P_peek      PP( (FILE *) );
extern int      P_eof       PP( (FILE *) );
extern int      P_eoln      PP( (FILE *) );
extern void     P_readpaoc  PP( (FILE *, Char *, int) );
extern void     P_readlnpaoc PP( (FILE *, Char *, int) );
extern long     P_maxpos    PP( (FILE *) );
extern Char    *P_trimname  PP( (Char *, int) );
extern long    *P_setunion  PP( (long *, long *, long *) );
extern long    *P_setint    PP( (long *, long *, long *) );
extern long    *P_setdiff   PP( (long *, long *, long *) );
extern long    *P_setxor    PP( (long *, long *, long *) );
extern int      P_inset     PP( (unsigned, long *) );
extern int      P_setequal  PP( (long *, long *) );
extern int      P_subset    PP( (long *, long *) );
extern long    *P_addset    PP( (long *, unsigned) );
extern long    *P_addsetr   PP( (long *, unsigned, unsigned) );
extern long    *P_remset    PP( (long *, unsigned) );
extern long    *P_setcpy    PP( (long *, long *) );
extern long    *P_expset    PP( (long *, long) );
extern long     P_packset   PP( (long *) );
extern int      P_getcmdline PP( (int l, int h, Char *line) );
extern void     TimeStamp   PP( (int *Day, int *Month, int *Year,
				 int *Hour, int *Min, int *Sec) );
extern void	P_sun_argv  PP( (char *, int, int) );


/* I/O error handling */
#define _CHKIO(cond,ior,val,def)  ((cond) ? P_ioresult=0,(val)  \
					  : P_ioresult=(ior),(def))
#define _SETIO(cond,ior)          (P_ioresult = (cond) ? 0 : (ior))

/* Following defines are suitable for the HP Pascal operating system */
#define FileNotFound     10
#define FileNotOpen      13
#define FileWriteError   38
#define BadInputFormat   14
#define EndOfFile        30

/* Creating temporary files */
/* char dummyfilename[512]; */
static char dummystring[1024];
# define tmpfile()  (fopen(tmpnam(dummyfilename), "w+"))

/* Memory allocation */
#ifndef RS6000
char *calloc();
#endif

extern Anyptr __MallocTemp__;
# define Malloc(n)  ((__MallocTemp__ = calloc(n,1)) ? __MallocTemp__ : (Anyptr)_OutMem())

/* #define FreeR(p)    (free((Anyptr)(p))) */    /* used if arg is an rvalue */
/* #define Free(p)     (free((Anyptr)(p)), (p)=NULL) */
#define MyFree(p)     (free((Anyptr)(p)), (p)=NULL)
#define Free(p)     ((p)=NULL)

/* sign extension */
#define SEXT(x,n)   ((x) | -(((x) & (1L<<((n)-1))) << 1))

/* packed arrays */   /* BEWARE: these are untested! */
#define P_getbits_UB(a,i,n,L)   ((int)((a)[(i)>>(L)-(n)] >>   \
				       (((~(i))&((1<<(L)-(n))-1)) << (n)) &  \
				       (1<<(1<<(n)))-1))

#define P_getbits_SB(a,i,n,L)   ((int)((a)[(i)>>(L)-(n)] <<   \
				       (16 - ((((~(i))&((1<<(L)-(n))-1))+1) <<\
					      (n)) >> (16-(1<<(n))))))

#define P_putbits_UB(a,i,x,n,L) ((a)[(i)>>(L)-(n)] |=   \
				 (x) << (((~(i))&((1<<(L)-(n))-1)) << (n)))

#define P_putbits_SB(a,i,x,n,L) ((a)[(i)>>(L)-(n)] |=   \
				 ((x) & (1<<(1<<(n)))-1) <<   \
				 (((~(i))&((1<<(L)-(n))-1)) << (n)))

#define P_clrbits_B(a,i,n,L)    ((a)[(i)>>(L)-(n)] &=   \
				 ~( ((1<<(1<<(n)))-1) <<   \
				   (((~(i))&((1<<(L)-(n))-1)) << (n))) )

/* small packed arrays */
#define P_getbits_US(v,i,n)     ((int)((v) >> ((i)<<(n)) & (1<<(1<<(n)))-1))
#define P_getbits_SS(v,i,n)     ((int)((long)(v) << (SETBITS - (((i)+1) << (n))) >> (SETBITS-(1<<(n)))))
#define P_putbits_US(v,i,x,n)   ((v) |= (x) << ((i) << (n)))
#define P_putbits_SS(v,i,x,n)   ((v) |= ((x) & (1<<(1<<(n)))-1) << ((i)<<(n)))
#define P_clrbits_S(v,i,n)      ((v) &= ~( ((1<<(1<<(n)))-1) << ((i)<<(n)) ))

#define P_max(a,b)   ((a) > (b) ? (a) : (b))
#define P_min(a,b)   ((a) < (b) ? (a) : (b))


/* Fix toupper/tolower on Suns and other stupid BSD systems */
#ifdef toupper
# undef toupper
# undef tolower
# define toupper(c)   my_toupper(c)
# define tolower(c)   my_tolower(c)
#endif

#ifndef _toupper
# if 'A' == 65 && 'a' == 97
#  define _toupper(c)  ((c)-'a'+'A')
#  define _tolower(c)  ((c)-'A'+'a')
# else
#  define _toupper(c)  toupper(c)
#  define _tolower(c)  tolower(c)
# endif
#endif


#ifdef LINUX
/* Fix things on Linux */
#ifdef islower
#undef islower
#endif
#define islower(c) ((c) >= 'a' && (c) <= 'z')
#ifdef isupper
#undef isupper
#endif
#define isupper(c) ((c) >= 'A' && (c) <= 'Z')
#ifdef isspace
#undef isspace
#endif
#define isspace(c) ((c) == ' ')
#ifdef isdigit
#undef isdigit
#endif
#define isdigit(c) ((c) >= '0' && (c) <= '9')

#endif