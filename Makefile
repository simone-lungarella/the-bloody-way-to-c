MD_FILE := resources/the-bloody-way-to-c.md
PDF_OUT := The\ Bloody\ Way\ To\ C.pdf
HTML_OUT := docs/index.html
TEMPLATE := resources/template.html

all: html pdf

html:
	pandoc -i $(MD_FILE) -o $(HTML_OUT) --template $(TEMPLATE)

pdf:
	pandoc -i $(MD_FILE) -o $(PDF_OUT)
