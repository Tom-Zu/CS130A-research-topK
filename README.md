# Tom Zu-research-topK-spacesaving
top-K space saving algorithm achieved by linked list
algorithm proposed in paper "Efficient Computation of Frequent and Top-k Elements in Data Streams"

## running program

put all data in a .txt file, one data per row.

file name fname and number K are passed as command-line argument.

in terminal:
```
make all
./topK.out fanem K
```

### Output includes

sorted list of all items in space saving algorithm

sorted list of all items by brute-force algorithm

average error and max error

average runtime for space saving algorithm to process each item.


### Example output
This is 100000 items ranging from 1 to 2^16 with zipf distribution. 

K=20, data included in data.txt

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
avg error: 5.72627 max error: 420
Average time to process each item: 37 nanoseconds
```
