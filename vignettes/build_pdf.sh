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

rm *.aux *.bbl *.blg *.log *.out *.toc *.dvi

mv -f *.pdf ../inst/doc/
cp -f *.Rnw ../inst/doc/
