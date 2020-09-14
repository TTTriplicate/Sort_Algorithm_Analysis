# Programming Lab 2

## Insertion Sort

My holdover sorting algorithm from Lab 1 is the Insertion Sort.  I built my `LinkedList` class such that all insertions are sorted into ascending order at the time of insertion.  This is not very efficient.  It's fine for small values, but will grow at a dramatic rate as the number of items increases.

Given $n$ items to insert, each insertion increases the size of the list to a maximum size of $n$.  In the best possible case, the list is already sorted prior to insertion, and will complete in $n$ iterations, just pushing the item in at the list head each time.  In the worst case, items are given to the list in inverse order, and every insertion must traverse all the way to the end of the list.  On average, the sorting will fall somewhere in between; call it half of the current list size for simplicities sake.

Given this set of parameters, we can find that the sort will run in the following worst, best, and average time complexities:

* $O(\sum_{i = 0}^{n}n(n-i))\sim O(n^2)$  
  
* $\Omega(1n)\sim \Omega(n)$

* $\Theta(\sum_{i = 0}^{n} \frac{n(n-i)}{2})\sim O(n^2)$

This puts insertion sort in the awkward category of being among the worse sorting algorithms in the worst and average cases, growing exponentially with $n$.  And while it is capable of being among the fastest, this only happens with data _that has already been sorted_, which negates whatever benefit there might be.

## Radix Sort

Radix sort is a relatively fast algorithm.  It breaks the problem of sorting integers into as many pieces as the length of the longest integer string in the dataset to be sorted.  Unlike merge sort, which breaks the problem in half, and half again until down to one and two pieces, requiring $n log_2(n)$ iterations, the Radix Sort can move much faster by breaking it into $log_{10}(max(n))$ pieces, with a maximum (sorting standard unsigned integers) of $10n$ iterations.

Radix sort does this by using a Counting Sort subroutine to sort the dataset by each position in the string, sorting by a larger power of 10 each time until the numbers have been sorted by all available places.  See my writeup of Counting Sort below for that algorithmic analysis, but suffice to say that the counting sort has time complexity of $O(n)$, and is run no more than 10 times to sort a dataset containing only unsigned standard-length integers.

* $O(n\times log_{10}(2147483647)) \approx O(n\times10) \sim O(n)$
* $\Omega(n \times log_{10}(9)) \approx \Omega(n)$
* $\Theta(n\times log_{10}(log_2(2147483647))) \approx \Theta(n \times 5) \sim \Theta(n)$ 

Radix Sort has limitations; it can only be used for integers or data that can be represented as integers, and is best used for relatively short integers.  If the number of places in each integer is equal to or greater than $n$, the time can actually approach $O(n^2)$.  It also does not sort in place, the way that some other sorting algorithms do; the items are copied from one data structure into another in sorted order, using more system memory in the process.

## Counting Sort

Counting Sort is what I used as a subroutine to accomplish my Radix Sort.  Counting Sort is a non-comparative sort.  Where Insertion Sort and many others compare elements and swap them, there is no need to do that in a counting sort.  A hashtable is made of the occurrences of the possible values of data to sort.  Each count is added to the next to allow the algorithm to mathematically place each item in the correct range of indices when populating the sorted data structure.

Rather than comparing $n$ items to each other $n$ times, it can simply iterate and count each item's value into the hashtable.  Then it iterates across the possible values, 10 in its use for a radix sort, combining the numbers so that they can be placed in the range they ought to.  And finally another iteration across the data structure to be sorted, in reverse for ascending order, taking each data value and copying it into the last index of the correct range for items with that value.

The time complexity for each individual Counting Sort as part of a Radix sort is:

* $O(2n +10) \sim O(n)$
* $\Omega(2n + 10) \sim \Omega(n)$
* $\Theta(2n + 10) \sim \Theta(n)$

Like Radix Sort, counting sort can be of limited utility.  There has to be a relatively small, fixed number of possible values with a clearly defined comparison; it works as part of Radix Sort because there are only 10 possible values at each iteration when dealing with base 10 numbers.  It also does not sort in place, and requires additional memory to hold the sorted data at the same time as the unsorted data.

## Comparison

Putting the differences in plain English, each iteration of the Linear Search eliminates 1 possible answer; each iteration of Binary Search eliminates $\frac{n}{2}$ possible answers.  Using 100 items as an arbitrary example,  in an _average_ case a Linear Search will take $ \frac{n}{2} = 50$ iterations; in the _worst_ case, a Binary Search will take $log_2(100) \approx 7$.  Both have the possibility of finding the answer on the first round, but over a larger sample set the time taken by a Linear Search will grow dramatically faster than a Binary Search.