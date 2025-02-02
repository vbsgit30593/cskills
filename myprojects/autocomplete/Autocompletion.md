# TODO
* Add a logger

# Other knowledge
## Makefiles
* Refer https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

## Overview
* In this project, I want to build an autocompletion feature in C from scratch
* For starters, I just want to build a CLI tool which can suggest words based on a prefix


## Naive approach
```
Problem: Build a tool which can suggest words based on prefix
T: O()
S: O()
```

### Very lame start
#### TODO
* find a repository of words - may be shakespeare data
* split into small chunks
* load words into memory and print it along with their frequencies
  * to start - load 1000 lines may be
  * print (k, v) with time to do that


```
Problem: load 1000 lines into a array of strings; split lines by space
```


## Rough plan for main work
* Implement a Trie data structure where we can insert and search words
* Build a CLI system which can recommend all words that match a prefix
* Build a priority queue using heaps
* Use the PQ to recommend top-n words
* Include hashing to rank based on user history
* Cache prefix results to speed up repeated queries


## Improvements
* Add domain specific search
  * Like if I want then I will only get suggestions for coding stuff