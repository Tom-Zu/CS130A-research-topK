# Tom Zu-research-topK-spacesaving
Top-K space saving algorithm achieved by linked list

Work done during 2021/3/4-2021/3/5

Algorithm proposed in paper "Efficient Computation of Frequent and Top-k Elements in Data Streams"

Link: http://www.cs.emory.edu/~cheung/Courses/584/Syllabus/papers/Frequency-count/2005-Metwally-Top-k-elements.pdf

## running program

Put all data in a .txt file with name fname, one data per row.

Data format does not matter, they are all processed as strings.

File name fname and number K are passed as command-line argument.

In terminal:
```
$ make all
$ ./topK.out fanem K
```

### Output includes

Sorted list of top K most frequent items in space saving algorithm

Sorted list of top K most frequent items by brute-force algorithm

Average error and max error

Average runtime for space saving algorithm to process each item.


### Example output
Reading from file "data_zipf_2.0_2^16_100000.txt" (included in repository), with K=20

Here the file name specifies that it is a zipf distribution with a skew of 2.0, range from 1 to 2^16, 100000 items generated

Argument:
```
$ make all
$ ./topk.out data_zipf_2.0_2^16_100000.txt 20
```
Output:
```
----------------------actual output:
Item: 1 Weight: 60797 error margin: 0
Item: 2 Weight: 15103 error margin: 0
Item: 3 Weight: 6804 error margin: 0
Item: 4 Weight: 3761 error margin: 0
Item: 5 Weight: 2473 error margin: 0
Item: 6 Weight: 1656 error margin: 0
Item: 7 Weight: 1205 error margin: 0
Item: 8 Weight: 1023 error margin: 0
Item: 9 Weight: 717 error margin: 30
Item: 10 Weight: 621 error margin: 54
Item: 15 Weight: 584 error margin: 583
Item: 19 Weight: 584 error margin: 583
Item: 50 Weight: 584 error margin: 583
Item: 16 Weight: 584 error margin: 583
Item: 14 Weight: 584 error margin: 582
Item: 11 Weight: 584 error margin: 583
Item: 144 Weight: 584 error margin: 583
Item: 23 Weight: 584 error margin: 583
Item: 12 Weight: 584 error margin: 582
Item: 41 Weight: 584 error margin: 582
----------------------expected output: 
Item: 1 Weight: 60797
Item: 2 Weight: 15103
Item: 3 Weight: 6804
Item: 4 Weight: 3761
Item: 5 Weight: 2473
Item: 6 Weight: 1656
Item: 7 Weight: 1205
Item: 8 Weight: 1023
Item: 9 Weight: 711
Item: 10 Weight: 616
Item: 11 Weight: 482
Item: 12 Weight: 417
Item: 13 Weight: 371
Item: 14 Weight: 315
Item: 15 Weight: 257
Item: 16 Weight: 247
Item: 17 Weight: 230
Item: 18 Weight: 189
Item: 20 Weight: 171
Item: 19 Weight: 164
-----------------------analysis:
avg error: 16.5916 max error: 583
Average time to process each item: 34 nanoseconds
```
