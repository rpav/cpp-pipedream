#!/bin/sh

doxygen Doxyfile

for i in doxygen-output/xml/group__*.xml; do
    base=`basename "$i" .xml`
    echo "doxyproc $base ..."
    doxyproc -I . \
             -X doxygen-output/xml/ \
             -R doxyproc/rules.js \
             -T doxyproc/group_template.md \
             $i website/api/$base.md
done

for i in doxygen-output/xml/{class,struct}*.xml; do
    base=`basename "$i" .xml`
    echo "doxyproc $base ..."
    doxyproc -I . \
             -X doxygen-output/xml/ \
             -R doxyproc/rules.js \
             -T doxyproc/class_template.md \
             $i website/api/$base.md
done

doxyproc -I . \
         -X doxygen-output/xml/ \
         -R doxyproc/index_rules.js \
         -T doxyproc/index_template.md \
         doxygen-output/xml/index.xml \
         website/api/index.md

echo doxyproc done.
