<p><b>CSC360/660 Operating Systems</b></p>
<p><b>Project #6: Simulation of Page Replacement Strategies</b></p>
<p>&nbsp;</p>
<p><b>Objective</b></p>
<p>The purpose of this programming project is to explore page replacement 
algorithms. This can be accomplished by developing a simple simulator that 
implements various page replacement algorithms and determining the number of 
page faults for a given reference string. A secondary objective of this 
assignment is to reinforce good software project design by using multiple source 
code modules in your solution.</p>
<p>&nbsp;</p>
<p><b>Project Specifications</b></p>
Develop a simulator program that will enable you to compare and contrast the operation of various page replacement strategies discussed in class (plus an additional page replacement algorithm discussed here). For a given page reference string, your program will output the number of page faults for a given page replacement algorithm. The name of your executable must be "simpager".<p>Input to your program will be from standard input. There is to be no "user prompts" in your program. Program output will be to standard output. Your program must follow a standardized input format. The first line is the page reference string. Each number in the page reference string is separated by whitespace and is terminated by a new line. The page reference string is on 1 (one) and only 1 (one) line. The second line is the number of frames allocated to a specific process. The remaining lines will be string mnemonics; one for each page replacement algorithm.

</p>
<p>Output from your program will be the following. Echo the page reference string up to 20 page references per line. Echo the number of frames allocated to the process. Print the page replacement algorithm "mnemonic" and the number of page faults.

Although your program reads from standard input and writes to standard output, it is suggested that you have several program data files that you can re-direct standard input and thus have your program read.

</p>
<p>Example Input:
</p>
<pre>7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
3
FIFO
LRU
</pre>
<p>Example Output:
</p>
<pre>% simpager &lt; testcase1.txt
Page Reference String:
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
Number of Frames: 3
FIFO: 15
LRU: 12
</pre>
<p>The page replacement algorithms and their respective mnemonics to be implemented are the following:
</p>
<ol>
	<li><b>FIFO</b> - First in first out page replacement. See text for description. 
	</li>
	<li><b>LRU</b> - Least recently used page replacement See text for description. 
	</li>
	<li><b>OPT</b> - Optimal page replacement. See text for description. </li>
	<li><b>RAND</b> - Random page replacement. This is an easy to implement, low-overhead page replacement strategy. Under this strategy, each page in main memory has an equal 
	likelihood of being selected for replacement. One problem with RAND is that it may 
	accidentally select as the next page to replace the page that will be referenced next. A benefit of RAND is that it makes replacement decisions quickly and fairly. However, because of this "hit-or-miss" approach, RAND is rarely used in practice. 
	</li>
</ol>