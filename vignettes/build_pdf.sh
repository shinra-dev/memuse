#!/bin/sh

rm *.aux *.bbl *.blg *.log *.out *.toc

pdflatex memuse-guide.Rnw
pdflatex memuse-guide.Rnw

Rscript -e "tools::compactPDF('.', gs_quality='ebook')"

rm *.aux *.bbl *.blg *.log *.out *.toc *.dvi

mv -f *.pdf ../inst/doc/
cp -f *.Rnw ../inst/doc/
