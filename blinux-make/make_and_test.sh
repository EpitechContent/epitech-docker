#!/bin/sh -x

if [ -z ${BUGS_LOGIN+x} ]
then
	echo "This version of bugs requires a more recent project configuration. Please re-run your SEED job"
	exit 1
fi

IPWD=$PWD

# Norm check
~/norme_deepthought.py rendu -score -nocheat -swap_traces -malloc >> ~/workspace/norm.dpr 2> ~/workspace/norm.note
cp norm.{dpr,note} mouli/

# make (1/2 - mouli)
[ -f mouli/Makefile ] && make -C mouli

# make (2/2 - student)
[ -f rendu/Makefile ] && make -C rendu $MAKE_RULE
cp -rn rendu/* mouli

# run bugs
cd mouli
bugs -version
bugs -out "txt xunit" -rec "graph api" -login "$BUGS_LOGIN" -city "$BUGS_CITY" -slug "$BUGS_SLUG" -module "$BUGS_MODULE" -inst "$BUGS_INST" -year "$BUGS_YEAR" -type "$BUGS_TYPE"

# retrieve run artifacts
cd $IPWD
