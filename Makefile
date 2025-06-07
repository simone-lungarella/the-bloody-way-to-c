# Variables
MD_FILE := the-bloody-way-to-c.md
HTML_OUT := docs/index.html
PDF_OUT := The\ Bloody\ Way\ To\ C.pdf
TEMPLATE := template.html

# Default target: build both HTML and PDF
all: html pdf

html:
	pandoc -i $(MD_FILE) -o $(HTML_OUT) --template $(TEMPLATE)

pdf:
	pandoc -i $(MD_FILE) -o $(PDF_OUT)

clean:
	rm -f $(HTML_OUT) $(PDF_OUT)

