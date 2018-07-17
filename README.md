The source code I am submitting is a c code. Once it is compiled and run, it prompts for an input: "Enter name of input file with extension", once the input file name is provided, it creates an output folder. I have tested with 3 sample inputs provided in the input folder.
I have used typedef MAXLEN to create a large number of user defined structures. I recognize using dynamic memmory allocation instead of static would have been a better choice.
Similarly I used arrays here extensively and using a linked list would be a better choice from the stand point of memory usage.
I also use the bubble sort routine and using a quick or merge sort algortihm would perform better. 
My choices were influenced by my familiarity with the data structures, subroutines, and programming language but I am more than willing to learn the strategies for handling larger datasets and data engineering in general.
My test cases test for duplicate entries as well as multiple drugs that have the same total cost so as to check 2nd order sorting is performed based on name of the drug.
