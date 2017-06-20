default: pdf

pdf:
	- pdflatex  -shell-escape -synctex=1 -interaction=nonstopmode "MSc_Thesis".tex -shell-scape 

clean:
	- rm -rfv *.aux
	- rm -rfv docs/*.aux
	- rm -rfv docs/appendix/*.aux
	- rm -rfv *.bbl *.blg *.glo *.idx *.lof *.log *.lot *.synctex.gz *.toc \
		 *.acn *.ist *.mw *.gz *.pdf




