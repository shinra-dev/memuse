#!/bin/sh


### Fix versioning in vignette, rebuild cover
PKGVER=`grep "Version:" ../DESCRIPTION | sed -e "s/Version: //"`
sed -i -e "s/myversion{.*}/myversion{${PKGVER}}/" memuse-guide.Rnw

cd cover
sed -i -e "s/packageversion}{.*}/packageversion}{${PKGVER}}/" cover.tex
./build_cover
cd ..



cleanVignette(){
  rm -f *.aux *.bbl *.blg *.log *.out *.toc *.dvi
}

buildVignette(){
  cleanVignette
  
  pdflatex $1
  pdflatex $1
  Rscript -e "tools::compactPDF('$1', gs_quality='ebook')"
}

publish(){
  mv -f *.pdf ../inst/doc/
  cp -f *.Rnw ../inst/doc/
}


buildVignette memuse-guide.Rnw

cleanVignette
publish

