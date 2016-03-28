# CS 104 HW1

## palindrome.cpp

```
$ g++ palindrome.cpp -o palindrome
$ ./palindrome <string>
```

Replace <string> with any single word. 
For example, "hahahah" will output "Palindrome" and "haha" will output "Not a Palindrome."
The input argument is case-sensitive, so "Hahah" is "Not a Palindrome."

## hw1q5.cpp

```
$ g++ hw1q5.cpp -o hw1q5
$ ./hw1q5 <inputfile.txt>
```

Replace <inputfile.txt> with a valid file that starts with an integer (of the # of words in the file) and then words afterwards. 
The output will return each word in the file in a reverse order, one per line.

## tommytrojan.cpp

```
$ g++ tommytrojan.cpp -o tommytrojan
$ ./tommytrojan <inputfile.txt> <outputfile.txt>
```

If outputfile.txt does not exist, it will be created. However inputfile.txt must exist and have a precise order of contents.
The first line must be an integer of the # of floors in the building. In each subsequent line...

- `MOVEIN i k`: create `k` students in the `i`th floor
- `MOVEOUT i`: empty `i`th floor
- `OBTAIN i j k n1 n2 n3 ... nk`: give `j`th student of the `i`th floor `k` items
- `OUTPUT i j`: outputs all the posessions of `j`th student of `i`th floor, one per line

Only if a contradictory statement occurs, the output file will recieve an error message.
