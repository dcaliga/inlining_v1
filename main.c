static char const cvsid[] = "$Id: main.c,v 2.1 2005/06/14 22:16:50 jls Exp $";

/*
 * Copyright 2005 SRC Computers, Inc.  All Rights Reserved.
 *
 *	Manufactured in the United States of America.
 *
 * SRC Computers, Inc.
 * 4240 N Nevada Avenue
 * Colorado Springs, CO 80907
 * (v) (719) 262-0213
 * (f) (719) 262-0223
 *
 * No permission has been granted to distribute this software
 * without the express permission of SRC Computers, Inc.
 *
 * This program is distributed WITHOUT ANY WARRANTY OF ANY KIND.
 */

#include <libmap.h>
#include <stdlib.h>

#define MAX_OBM_SIZE 512000

void subr (int32_t I0[], int32_t I1[], int32_t Out[], int num, int64_t *time, int mapnum);


int main (int argc, char *argv[]) {
    FILE *res_map, *res_cpu;
    int i, ii, num;
    int32_t *A, *B, *C;
    int64_t tm;
    int mapnum = 0;

    if ((res_map = fopen ("res_map", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_map'\n");
        exit (1);
        }

    if ((res_cpu = fopen ("res_cpu", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_cpu'\n");
        exit (1);
        }

    if (argc < 2) {
	fprintf (stderr, "need number of elements as arg\n");
	exit (1);
	}

    if (sscanf (argv[1], "%d", &num) < 1) {
	fprintf (stderr, "need number of elements as arg\n");
	exit (1);
	}

    if ((num < 1) || (num > MAX_OBM_SIZE)) {
        fprintf (stderr, "number of elements must be in the range 1 through %d\n", MAX_OBM_SIZE);
	exit (1);
	}

    A = (int32_t*) malloc (2*num * sizeof (int32_t));
    B = (int32_t*) malloc (2*num * sizeof (int32_t));
    C = (int32_t*) malloc (2*num * sizeof (int32_t));

    srandom (99);

    for (i=0; i<num; i++) {
        A[2*i]   = random ();
        A[2*i+1] = random ();
        B[2*i]   = random ();
        B[2*i+1] = random ();
	}

    map_allocate (1);

    subr (A, B, C, num, &tm, mapnum);

    printf ("%lld clocks\n", tm);

    for (i=0; i<2*num; i++) {
        fprintf (res_map, "%d\n", C[i]);
    }

    for (i=0; i<num*2; i++) {
	int32_t v0,v1;
	int64_t v;

        ii = i/2;
        if (i%2==0) {
           v0 = A[2*ii];
           v1 = A[2*ii+1];
           }
        else {
           v0 = B[2*ii];
           v1 = B[2*ii+1];
           }
        

        v = v0 + v1;
        if (v0 > v1)
            v = v + 42;
        v = v*3;

        fprintf (res_cpu, "%d\n", v);
	}

    map_free (1);

    exit(0);
    }

