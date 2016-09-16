#!/bin/sh


### Fix versioning in vignette, rebuild cover
PKGVER=`grep "Version:" ../DESCRIPTION | sed -e "s/Version: //"`
sed -i -e "s/myversion{.*}/myversion{${PKGVER}}/" memuse-guide.Rnw

cd cover
sed -i -e "s/packageversion}{.*}/packageversion}{${PKGVER}}/" cover.tex
./build_cover
cd ..


### Rebuild vignette
rm *.aux *.bbl *.blg *.log *.out *.toc

pdflatex memuse-guide.Rnw
pdflatex memuse-guide.Rnw

Rscript -e "tools::compactPDF('memuse-guide.pdf', gs_quality='ebook')"

rm -f *.aux *.bbl *.blg *.log *.out *.toc *.dvi

INSTPATH="../inst/doc/"
if [ ! -d $INSTPATH ];then
  mkdir $INSTPATH
fi

mv -f *.pdf $INSTPATH
cp -f *.Rnw $INSTPATH
