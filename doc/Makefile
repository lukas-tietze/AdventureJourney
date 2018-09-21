TC := texfot pdflatex
TCFLAGS := -output-format=pdf -interaction=nonstopmode -file-line-error

.PHONY:
	clean, core

all: core.pdf 

core.pdf: core.tex Makefile
	@echo -e "\033[1;33m Latex first run \033[0m"
	-$(TC) $(TCFLAGS) $<

	@echo -e "\033[1;33m Latex second run\033[0m"
	$(TC) $(TCFLAGS) $<

clean:
	make -C ./data -f Makefile clear
	-rm *.aux *.fls *.gz *.out *.fdb *.log *.toc *.pdf *.glg *.glo *.gls *.glsdefs *.ist *.fdb_latexmk *.blg *.bbl spell_check.txt 2> /dev/null