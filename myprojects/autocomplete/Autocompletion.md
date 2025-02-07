# Some results
## TRIE exact match search vs naive linear search
```
naive_read_from_file: Reading words from file (data/shakespeare_words.txt)
Size of file: 5458199
Total tokens: 901490, cleaned tokens: 894917
Total file read + tokenization time: 0.076535s
Naive token memory size: 11.790925MB
WORD NOT FOUND
Total naive search time: 0.002824s
###########
trie_read_from_file: Reading words from file (data/shakespeare_words.txt)
Total tokens: 901490, cleaned tokens: 894917
Time spent in reading a file and creating trie: 0.096412
Word zoo not found in TRIE
Total trie search time: 0.000003s
```

## TRIE prefix match results vs naive prefix match
```
naive_read_from_file: Reading words from file (data/shakespeare_words.txt)
Size of file: 5458199
Total tokens: 901490, cleaned tokens: 894917
Total file read + tokenization time: -0.921713s
Naive token memory size: 11.790925MB
## Here are your 12 suggestions ##
ropes   rope    ropeexit        ropesend        ropeantipholus  ropedromio      ropesendantipholus  ropemaker       ropepinch       roping  ropery  ropetricks
Total naive search time: 0.004218s
###########
trie_read_from_file: Reading words from file (data/shakespeare_words.txt)
Total tokens: 901490, cleaned tokens: 894917
Time spent in reading a file and creating trie: 0.098203
trie_search_all: prefix `Rop` found in TRIE
rope    ropeantipholus  ropedromio      ropeexit        ropemaker       ropepinch  ropery   ropes   ropesend        ropesendantipholus      ropetricks      roping
Total trie search time: 0.000007s
```

## TRIE memusage comparison
* Memusage for Naive approach was - 12MB while for TRIE was 18MB


* Though TRIE takes more time to populate but there is a substantial search time difference

# TODO
* Add a logger
* Add a hashing API
* Add a priority queue

## TRIE TODO
* read and store to a trie
* track mem usage
* track search time

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
### Summary
* Searching for a key is fast enough
* Prefix search to find all results is very slow and can take 0.005s
  * Adding the smartness of storing only unique keys in a brute force way spikes the search time based on number of unique keys
```
## Here are your 172 suggestions for `ro`##
royalty rose    roof    rough   rolling rondure rotten  roses   robs    robbery robe    root    room    rocks   robbing rosy    robbed  rousillon       royal   rounds  rock    robbst       roard   ropes   rogues  rogue   rooted  roman   rome    robes   rot     roughest        roasted round   romans  routed  roaring rods    robbd   roll    rouse   rowland rosalind     robin   rowlands        roynish road    rosalinde       rosalinda       roundly roaming rout    rope    ropeexit        ropesend        ropeantipholus  ropedromio      ropesendantipholus   ropemaker       ropepinch       roomantipholus  roughly rob     rod     roted   rougher rove    romes   roar    romeenter       rottenness      romish  rode    roofsrousd   roots   robber  rotting rowel   routs   rosencrantz     romage  rots    ros     roscius row     robustious      rood    roars   rosemary        roughhew        royally rochester    roan    roguery rooms   robert  rowelhead       robbry  roadway roast   roused  rocky   romei   roam    roping  roussi  rouen   rolls   rote    roy     robbers roi     rosdroger    romanos rolld   rookd   rochfordone     roads   roberts royalties       roundure        rounded roundwombd      roundest        roughness       rotundity       robed   roguish      rosaline        roes    rooks   ross    ronyon  rooky   roofd   rossthe rook    rotted  roundel roughcast       roderigo        roselippd       roderigos       rotherham   royalize rooting romeo   rooteth rom     romeos  rosalines       roe     ropery  rosewater       ropetricks      roadenter       roarers rootedly        rothers rosecheekd      rolled       rosed   roisting        rounder rover   rounding        roared  royaltys        rogero  romano
Total search time: 0.005695s
```

* Without some sort of a (K, V) logic in place, it spits duplicate results
* We could ensure that while processing keys to store we can store unique keys along with their frequencies but that would mean building a hash and we should still need to dump all strings from that hash
`Trie comes to the rescue here as it stores only unique keys`

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
