#ifndef CMN_DEFINES_H
#define CMN_DEFINES_H

/*********************/
/*     processes     */
/*********************/
/*#define f false
#define t true*/

#define NEURONGROWTH                      true
#define AXONGROWTH                        true
#define DENDRGROWTH                       true
#define SPONTANEOUSACTIVITY               true
#define CHARGEBATTERIES                   true
#define SPREADIMPULSE                     true

/*#undef f
#undef t*/

#define NEURONGROWTHCHARACTERTIME         1
#define AXONGROWTHCHARACTERTIME           5
#define DENDRGROWTHCHARACTERTIME          10
#define SPONTANEOUSACTIVITYCHARACTERTIME  20
#define CHARGEBATTERIESCHARACTERTIME      7
#define SPREADIMPULSECHARACTERTIME        5

#define MAXTIME                           250000
#define DELAYTIME                         10

/*********************/
/*        end        */
/*********************/

/*********************/
/* interface defines */
/*********************/

#define WorkingUI                    GUI
/* symbols */
#define NEURONSYMBOL          'N'
#define AXONSYMBOL            'A'
#define DENDRSYMBOL           'D'
#define EMPTYFIELDSYMBOL      ' '
#define FIREDSYMBOL           'F'

/* colors */
#define NEURONCOLOR           GREEN
#define AXONCOLOR             WHITE
#define DENDRITECOLOR         YELLOW
#define FIRINGCOLOR           RED
#define EMPTYFIELDCOLOR       BLACK

/*********************/
/*        end        */
/*********************/

/*********************/
/*    start values   */
/*********************/

#define STARTBATTERYCHARGE    0
#define NEURONIDINITIALVALUE  (-1)
#define FIRSTNEURONNUMBER     0

/*********************/
/*        end        */
/*********************/

/*********************/
/*    parametres     */
/*********************/

#define XMAXSIZE                          600
#define YMAXSIZE                          400
#define MAXNUMBEROFNEURONS                1000

#define MAXNUMBEROFCONNECTIONS            1000
#define MAXNUMBEROFCONNECTIONSPERNEURON   10

/* preciseness */
#define AXONANGLEPRECISENESS              16
#define DENDRITEANGLEPRECISENESS          90

/*********************/
/*        end        */
/*********************/

/*********************/
/*     scenarios     */
/*********************/

/* build scenario 1 */
/* build scenario 1 is aimed to build regular interconnected neuron network that will spread impulse among it */
#ifdef BUILDSCENARIO1

#define NEURONGROWTH                      false
#define AXONGROWTH                        false
#define DENDRGROWTH                       false
#define SPONTANEOUSACTIVITY               true
#define CHARGEBATTERIES                   true
#define SPREADIMPULSE                     true

#define SPONTANEOUSACTIVITYCHARACTERTIME  20
#define CHARGEBATTERIESCHARACTERTIME      7
#define SPREADIMPULSECHARACTERTIME        5

#define DELAYTIME                         1

#endif

//#ifdef TEST

/*********************/
/*        end        */
/*********************/

#include <stdio.h>
/*********************/
/*       Macro       */
/*********************/

#define PRINTTRACE(file, format, ...) \
   printf(file);                      \
   printf(".cpp: ");                  \
   printf(format, __VA_ARGS__);

#define Print(format, ...)            \
   printf(format, __VA_ARGS__);

#define Message(msg)                  \
   printf(msg);

/*********************/
/*        end        */
/*********************/

#endif
