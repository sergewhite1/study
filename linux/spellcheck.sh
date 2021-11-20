# Spell check for English language
# Warning! Check that LC_ALL variable is set to C.
# Or run expample:
# LC_ALL=C ./spellcheck file1.txt

filename=$1

# Filename with dictionary

dict=/usr/share/dict/american-english

verbose_mode=1 # 0 - quite mode | 1 - verbose mode

if [ -z "$filename" ]; then
  echo Error! Filename not defined!
  exit 1
fi

filename2=${filename}__sorted.uniq.tmp

if [ -f "${filename2}" ]; then
  echo File ${filename2} exists. Spell check stopped.
  exit 1
fi

if [[ $verbose_mode == 1 ]]; then 
  echo Create temp file: ${filename2} ...
fi

cat ${filename} |
tr -sc A-Za-z '\012' |
sort | 
uniq > ${filename2}

filename3=${filename}__not_found

if [ -f "${filename3}" ]; then
  echo File ${filename3} exists. Spell check stopped.
  exit 1
fi

if [[ $verbose_mode == 1 ]]; then 
  echo Create temp file: ${filename3} ...
fi

comm -23 ${filename2} ${dict} > ${filename3}

filename4=${filename}__not_found2

if [ -f "${filename4}" ]; then
  echo File ${filename4} exists. Spell check stopped.
  exit 1
fi

if [[ $verbose_mode == 1 ]]; then 
echo Create temp file: ${filename4} ...
fi

cat ${filename3} |
tr A-Z a-z |
sort |
uniq > ${filename4}

echo Words not found:
comm -23 ${filename4} ${dict}

echo ==========================================================================


if [[ $verbose_mode == 1 ]]; then 
  echo Remove temp files:

  set -x
fi

rm ${filename2} ${filename3} ${filename4} ${filename5}
