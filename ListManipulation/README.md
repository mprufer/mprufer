List Mainpulation Program
----------------------------
Given an input text file, it will create a mock excel worksheet using a linked list data structure.
Each list node represents a row with a sub-list of values. 
List are traversable forwards and back. Sub-lists are also bi-directionally traversable. The end of each sub-list traverses to the next "column"/list node of the list. 
Input text files included: test.txt; test_1.txt

Given another input text file, it will perform a series of operations on the entire list.
Operations:
>insertline: will insert a new after the indicated line number
>mathline: given a line number, will give the indicated math operation: min, max, count (get the number of elemnts in the line), mean
>deleteline: will delete the indicated line; other lines will be moved up
Input text files: opsFiles.txt; test_1_opts.txt

<b>Language:</b> C++<br>
<b>Compiling instructions: </b>
-Arugments passed to main: "input='input text file';operations='ops text file'"
