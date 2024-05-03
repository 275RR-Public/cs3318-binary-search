/*
*   James Hofer
*   1000199225
*   Compile: /usr/bin/c99 -o app app.c
*
*   Usage: ./app < input.dat
*   This program reads in two sequences of integers and a query of ranks.
*   It then finds the rank in the two sequences using binary search.
*
*   Some testing can be run by passing the "-t" flag.
*
*   https://ranger.uta.edu/~weems/NOTES3318/LAB/LAB1FALL23/lab1fall23.pdf
*/

#include <stdio.h>
#include <string.h>

// for testing only
void ranksByMerge(int a[], int m, int b[], int n);

/*
*   Binary search for rank in two sequences
*   modified from Dr. Weems' code
*
*   a: seq1[]
*   n: len_seq1
*   b: seq2[]
*   m: len_seq2
*   rank: query[i]
*/
int binSearch(int *a, int n, int *b, int m, int rank)
{
    // low, high, mid from seq1 and j from seq2
    int low, high, mid, j;
    low = 0;
    high = n;

    while (low <= high)
    {
        // find middle search point
        mid = (low+high) / 2;
        // i+j = rank
        j = rank - mid;
        
        // corner cases
        if (j < 0)
        {
            high = mid - 1;
            continue;
        }
        else if (j > m)
        {
            low = mid + 1;
            continue;
        }

        printf("low %d, high %d, i %d, j %d\n", low, high, mid, j);

        // a[i] <= b[j] < a[i+1] where rank is in b[j]
        if (a[mid] <= b[j] && b[j] < a[mid+1])
        {
            printf("...Rank %d at b[%d]\n", rank, j);
            break;
        }
        else if (a[mid] <= b[j])
            low = mid + 1;
        else
            high = mid - 1;

        // b[j] < a[i] <= b[j+1] where rank is in a[i]
        if (b[j] < a[mid] && a[mid] <= b[j+1])
        {
            printf("...Rank %d at a[%d]\n", rank, mid);
            break;
        }
        else if (b[j] < a[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
}

/*
*   Main function
*   reads in sequences and query data
*   calls binSearch() for each query
*
*   argc and argv are for testing only
*/
int main(int argc, char *argv[])
{
    // read in lengths of sequences and query
    int len_seq1, len_seq2, len_query;
    scanf("%d %d %d", &len_seq1, &len_seq2, &len_query);

    // create arrays for sequences and query
    int seq1[len_seq1+2], seq2[len_seq2+2], query[len_query];

    // sentinel values. set sequences lower and upper bounds
    seq1[0] = -99999999;
    seq1[len_seq1+1] = 99999999;
    seq2[0] = -99999999;
    seq2[len_seq2+1] = 99999999;

    // read in sequences and query
    for (int i = 1; i < len_seq1+1; i++)
        scanf("%d", &seq1[i]);
    for (int i = 1; i < len_seq2+1; i++)
        scanf("%d", &seq2[i]);
    for (int i = 0; i < len_query; i++)
        scanf("%d", &query[i]);

    // find ranks using binary search
    for (int i = 0; i < len_query; i++)
    {
        printf("\nSearching for Rank %d...\n", query[i]);
        binSearch(seq1, len_seq1, seq2, len_seq2, query[i]);
    }

    // for testing ONLY when "-t" flag is passed
    if (argc == 2 && strcmp(argv[1], "-t") == 0)
    {
        ranksByMerge(seq1, len_seq1, seq2, len_seq2);
    }
    
    return 0;
}


// slight modification for testing from Dr. Weems' code
void ranksByMerge(int a[], int m, int b[], int n)
{   
    int i, j, k;
    int aRank[m+1], bRank[n+1];
    i = j = k = 1;
    aRank[0] = bRank[0] = 0;

    while (i<=m && j<=n)
    {
        if (a[i]<=b[j])
            aRank[i++]=k++;
        else
            bRank[j++]=k++;
    }
    while (i<=m)
        aRank[i++]=k++;
    while (j<=n)
        bRank[j++]=k++;

    printf("\nseq1_len: %d, seq2_len: %d\n", m, n);

    printf("seq1: ");
    for(int i = 1; i < m+1; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\nseq2: ");
    for(int i = 1; i < n+1; i++)
    {
        printf("%d ", b[i]);
    }
    printf("\n");

    printf("%15s %15s\n", "seq1", "seq1_rank");
    for (int i = 0; i < m+2; i++)
    {
        printf("%15d %15d\n", a[i], aRank[i]);
    }
    printf("\n%15s %15s\n", "seq2", "seq2_rank");
    for (int i = 0; i < n+2; i++)
    {
        printf("%15d %15d\n", b[i], bRank[i]);
    }
}