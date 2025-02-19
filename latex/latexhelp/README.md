# Latex Help project

## Task

It's latex help created by me. I'd like to have latex handbook in couple views:
- sorted alphabetically
- grouped by categories (for example math, fonts, charts, etc.)

## Soultion

To solve this task I'd like to create program on Python. Diagram:

```
|--------------|  |------------|  |-------------|  |--------|  |-------------|
|latexhelp.json|->|latexhelp.py|->|latexhelp.tex|->|pdflatex|->|latexhelp.pdf|
|--------------|  |------------|  |-------------|  |--------|  |-------------|
|file          |                  |file         |              |file         |
|--------------|                  |-------------|              |-------------|
```

Description step by step

1. File latexhelp.json is some kind of database with latex commands and
   environment description. This file is input for Python program latexhelp.py.
2. The output of the program latexhelp.py is tex file latexhelp.tex.
3. File latexhelp.tex goes to the pdflatex program. The result is nice
   generated pdf file.

## JSON description for file latexhelp.json
```json
{
  "latexhelp": [
    {
      "entity": "documentclass",
      "package": "N/A",
      "type": "command",
      "type_comment": "command | environment",
      "description": "/Bold-face font",
      "arguments": {
        "mandatory": [
          {
            "argument": "argument example",
            "description": "description",
            "values": [
              {
                "value": "article",
                "description": "For articles in scientific journals, presentations, short reports, program documentation, invitations, ..."
              }
            ]
          }
        ],
        "optional": [
          "_comment: see above"
        ]
      }
    }
  ]
}
```