#!/bin/sh

rm *.aux *.bbl *.blg *.log *.out *.toc
pdflatex fs-guide.Rnw
bibtex fs-guide
pdflatex fs-guide.Rnw
pdflatex fs-guide.Rnw
pdflatex fs-guide.Rnw
rm *.aux *.bbl *.blg *.log *.out *.toc *.dvi
