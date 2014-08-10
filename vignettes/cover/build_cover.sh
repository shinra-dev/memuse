#!/bin/sh

PKGVER=`grep "Version:" ../../DESCRIPTION | sed -e "s/Version: //"`
sed -i -e "s/packageversion}{[0-9][.][0-9]-[0-9]}/packageversion}{${PKGVER}}/" cover.tex


xelatex cover.tex
xelatex cover.tex
Rscript -e "tools::compactPDF('.', gs_quality='ebook')"
rm *.aux *.bbl *.blg *.log *.out *.toc *.idx *.lof *.lot *.ind *.ilg
