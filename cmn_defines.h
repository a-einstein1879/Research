#ifndef CMN_DEFINES_H
#define CMN_DEFINES_H

/*********************/
/*     processes     */
/*********************/

#define NEURONGROWTH                      true
#define AXONGROWTH                        true
#define DENDRGROWTH                       true
#define SPONTANEOUSACTIVITY               true
#define CHARGEBATTERIES                   true
#define SPREADIMPULSE                     true

#define NEURONGROWTHCHARACTERTIME         1
#define AXONGROWTHCHARACTERTIME           5
#define DENDRGROWTHCHARACTERTIME          1
#define SPONTANEOUSACTIVITYCHARACTERTIME  20
#define CHARGEBATTERIESCHARACTERTIME      7
#define SPREADIMPULSECHARACTERTIME        5

#define MAXTIME                           5000000
#define DELAYTIME                         1

/*********************/
/*        end        */
/*********************/

/*********************/
/*    parametres     */
/*********************/

#define XMAXSIZE                          100
#define YMAXSIZE                          100
#define MAXNUMBEROFNEURONS                5000

#define MAXNUMBEROFCONNECTIONS            1000
#define MAXNUMBEROFCONNECTIONSPERNEURON   10
#define MAXAXONLENGHT                     10
#define MAXDENDRITERADIUS                 4

/* preciseness */
#define AXONANGLEPRECISENESS              16
#define DENDRITEANGLEPRECISENESS          90

/*********************/
/*        end        */
/*********************/

/*********************/
/* interface defines */
/*********************/

#define WorkingUI             GUI
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
/*     scenarios     */
/*********************/

/* build scenario 1 */
/* build scenario 1 is aimed to build regular interconnected neuron network that will spread impulse among it */
#ifdef BUILDSCENARIO1

#define XMAXSIZE                          600
#define YMAXSIZE                          400
#define MAXNUMBEROFNEURONS                30
#define MAXAXONLENGHT                     60
#define MAXDENDRITELENGTH                 15

#define NEURONGROWTH                      false
#define AXONGROWTH                        false
#define DENDRGROWTH                       false

#endif

/* build scenario 2 */
/* all neurons appear at the first second and then they start to grow */
#ifdef BUILDSCENARIO2

#define NEURONGROWTH                      false

#define XMAXSIZE                          50
#define YMAXSIZE                          50
#define MAXNUMBEROFNEURONS                2500

#endif

/* activity scenario 1 */
#ifdef ACTIVITYSCENARIO1

#define SPONTANEOUSACTIVITY               true
#define CHARGEBATTERIES                   true
#define SPREADIMPULSE                     true

#define SPONTANEOUSACTIVITYCHARACTERTIME  20
#define CHARGEBATTERIESCHARACTERTIME      15
#define SPREADIMPULSECHARACTERTIME        5

#define DELAYTIME                         1

#endif
//#ifdef TEST

/*********************/
/*        end        */
/*********************/

/*********************/
/*       Files       */
/*********************/
#define ACTIVITYFILE                   "./outputFolder/activityFile.txt"
#define NUMBEROFCONNECTIONSFILE        "./outputFolder/numberOfConnectionsFile.txt"

/* file IDs */
#define NUMBEROFFIREDNEURONS  1
#define NUMBEROFCONNECTIONS   2


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

/*
   numberOfFiredNeurons - activity file
*/
#define PrintFile(dataType, format, ...)        \
   FILE *fd;                                    \
   switch(dataType) {                           \
      case NUMBEROFFIREDNEURONS:                \
         fd=fopen(ACTIVITYFILE,"a+");           \
         fprintf(fd, format, __VA_ARGS__);      \
         fprintf(fd, "\n");                     \
         fclose(fd);                            \
         break;                                 \
   }

/*********************/
/*        end        */
/*********************/

#endif
