DIR=$1

if [ -z "$DIR" ]; then
  echo Error! Variable DIR is missed!
  exit 1
fi

set -x

mkdir -p $DIR

cp --interactive --verbose ~/Templates/c_cmake_project/* $DIR &&
cd $DIR &&
chmod u+x build.sh

cd $OLDPWD
