GNUPLOT_DIR=./gnuplot
TARGET=ra046874

TEX=$(TARGET).tex
DVI=$(TARGET).dvi
PS=$(TARGET).ps
PDF=$(TARGET).pdf

.PHONY: pdf clean

$(PDF): 
	pdflatex $(TEX)
	pdflatex $(TEX)
	rm -f *~ *.nav *.snm
	rm -f *.aux *.log *.loa *.bbl *.blg *.lof *.lot 
	rm -f *.toc .nfs* *.out

pdf: clean $(PDF)

clean:
	rm -f *~ *.nav *.snm $(PDF) $(PS) $(DVI)
	rm -f *.aux *.log *.loa *.bbl *.blg *.lof *.lot 
	rm -f *.toc .nfs* *.out

