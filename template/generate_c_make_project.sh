DIR=$1

if [ -z "$DIR" ]; then
  echo Error! Variable DIR is missed!
  exit 1
fi

set -x

mkdir -p $DIR

cp --interactive --verbose ~/Templates/c_make_project/* $DIR
