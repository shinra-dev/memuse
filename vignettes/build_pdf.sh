#!/bin/sh

PKGVER=`grep "Version:" ../DESCRIPTION | sed -e "s/Version: //"`
sed -i -e "s/myversion{.*}/myversion{${PKGVER}}/" memuse-guide.Rnw


rm *.aux *.bbl *.blg *.log *.out *.toc

pdflatex memuse-guide.Rnw
pdflatex memuse-guide.Rnw

Rscript -e "tools::compactPDF('memuse-guide.pdf', gs_quality='ebook')"

rm *.aux *.bbl *.blg *.log *.out *.toc *.dvi

mv -f *.pdf ../inst/doc/
cp -f *.Rnw ../inst/doc/
