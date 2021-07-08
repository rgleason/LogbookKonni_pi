#!/bin/bash

# Remove all obsoleted _T() and wxT() macros, gone since before 3.0

for f in $*; do
    echo "Fixing $f"
    sed -i 's/\\"/@%QQ%@/g' $f
    perl -p -e 's/wxT\( *("[^"]*") *\)/\1/g' $f > $f.tmp && cp $f.tmp $f && rm $f.tmp
    perl -p -e 's/_T\( *("[^"]*") *\)/\1/g' $f > $f.tmp && cp $f.tmp $f && rm $f.tmp
    sed -i 's/@%QQ%@/\\"/g' $f
done

