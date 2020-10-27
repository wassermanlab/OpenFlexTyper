\page parameters 

# Parameters Used within FlexTyper 

## Sliding Search Parameters 

![Sliding Search Parameters]
(slidingsearch.png)

## Centered Search Parameters 
![Centered Search Parameters]
(centeredsearch.png)

## Non Unique Kmers
If two query sequences contain an identical kmer, then that kmer is flagged as a ‘non unique kmer’. 
![Non Unique Kmers]
(nonUniqueKmer.png)

## Over Counted Kmers 
If a kmer search returns too many positions, then that kmer is disregarded as uninformative and flagged as an “over counted kmer”. 

## Count As Pairs 
For paired reads [R1 = <1,1>, R2 = <1,2>]
If countAsPairs = true, then if a query matches R1 and R2, then the query count is only one. 

## Unique Reads 
For two queries Q1 and Q2, uniqueReads = true, then if a read, R, matches Q1 and Q2, then R will be removed from the set of matching read hits for both Q1 and Q2.

## Combining countAsPairs and uniqueReads
Suppose you have 3 sets of paired reads: 
Pair 1: [R1 = <1,1>, R2 = <1,2>]
Pair 2: [R3 = <2,1>, R4 = <2,2>]
Pair 3: [R5 = <3,1>, R6 = <3,2>] 
And two query sequences with matching read hits: 
Query 1 = [R1, R3, R5, R6]
Query 2 = [R1, R4]



|                   |countAsPairs = True                        | countAsPairs = False                       |
|                   |Query       |Read Hits        |Count       |Query       |Read Hits         |Count       |
|-------------------|:----------:|-----------------|------------|------------|------------------|------------|
|uniqueReads = True | 1          | [R5, R6]        |1           | 1          | [R3, R5, R6]     | 3          |
|                   | 2          | [ ]             |0           | 2          | [R4]             | 1          |
|-------------------|------------|-----------------|------------|------------|------------------|------------|
|uniqueReads = False| 1          | [R1, R3, R5, R6]|3           | 1          | [R1, R3, R5, R6] | 4          |
|                   | 2          | [R1, R4]        |2           | 2          | [R1, R4]         | 2          |



