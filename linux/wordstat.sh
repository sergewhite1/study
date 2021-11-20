# Word Stat calculation 
# Brian W. Kernighan, Rob Pike. The UNIX. Programming Environment

# Warning. It better use LC_ALL=C or run example:
# LC_ALL=C ./wordstat.sh file1.txt file2.txt file3.txt

cat $* |
tr -sc A-Za-z '\012' |
sort  |
uniq -c |
sort -n |
tail
