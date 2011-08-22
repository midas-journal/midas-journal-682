

NAME = TestingFramework

BIBTEXDATABSENAME = InsightJournal

PATHTOLATEX=/usr/local/texlive/2008/bin/universal-darwin

LATEX=${PATHTOLATEX}/latex $(LATEXFLAGS)
BIBTEX=${PATHTOLATEX}/bibtex $(BIBTEXFLAGS)
DVIPS=${PATHTOLATEX}/dvips $(DVIPSFLAGS)
PS2PDF=ps2pdf $(PS2PDFFLAGS) \
	-dMaxSubsetPct=100 -dSubsetFonts=true -dEmbedAllFonts=true \
	-dAutoFilterColorImages=false -dAutoFilterGrayImages=false \
	-dColorImageFilter=/FlateEncode -dGrayImageFilter=/FlateEncode
CONVERT=convert $(CONVERTFLAGS)
PDFLATEX=${PATHTOLATEX}/pdflatex $(PDFLATEXFLAGS)


all: ps pdf dvi


ps: ${NAME}.ps


pdf: ${NAME}.pdf


dvi: ${NAME}.dvi


bbl: ${NAME}.bbl



${NAME}.ps: ${NAME}.dvi
	${DVIPS} -o ${NAME}.ps ${NAME}.dvi


${NAME}.pdf: ${NAME}.ps
	${PS2PDF} ${NAME}.ps


${NAME}.bbl: ${BIBTEXDATABSENAME}.bib ${NAME}.aux
	${BIBTEX} ${NAME}


${NAME}.dvi: ${NAME}.tex  ${BIBTEXDATABSENAME}.bib
	${LATEX} ${NAME}.tex
	${BIBTEX} ${NAME}
	${LATEX} ${NAME}.tex
	${LATEX} ${NAME}.tex


${NAME}.aux: ${NAME}.tex  ${BIBTEXDATABSENAME}.bib
	${LATEX} ${NAME}.tex


clean:
	rm ${NAME}.dvi ${NAME}.ps ${NAME}.pdf ${NAME}.aux ${NAME}.log ${NAME}.bbl ${NAME}.blg ${NAME}.toc ${NAME}.out  ${NAME}.brf

