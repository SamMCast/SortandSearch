# SortandSearch
command-line program written in C++ that sorts numbers based a specified min range and max range. The user is then given the option to search for the item using 3 different types of searches at their disposal. The time it took to complete the search as well as how it took to sort the list of numbers is reported.

The executable needs to be run on Linux.

Example of how to use the program

./mysort -ur 2,200 

./mysort is the name of the program

List of available commands

-u specifies uniform distrubution. This means you want to the number list to be uniformly distrubuted according to the min and max range inclusive you specified.

-r minval,maxval The -r followed by min and max ranges separated by a comma specifies the range of values you want in your list.

-s specifies the type of sorting algorithm you wish to use and in this case selection sort.

-m specifies the type of sorting algorithm you wish to use and in this case merge sort.

-q specifies the type of sorting algorithm you wish to use and in this case quick sort.

