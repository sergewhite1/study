# Latex Help project

## Task

It's latex help created by me. I'd like to have latex handbook in couple views:
- sorted alphabetically
- grouped by categories (for example math, fonts, charts, etc.)

## Soultion

To solve this task I'd like to create program on Python. Diagram:

```
|--------------|  |------------|  |------------------|  |--------|
|latexhelp.json|->|latexhelp.py|->|latexhelp_alph.tex|->|pdflatex| 
|--------------|  |------------|  |------------------|  |--------|
                                                           \|/
                                                   |------------------|
                                                   |latexhelp_alph.pdf|
                                                   |------------------|
```


Description step by step

1. File latexhelp.json is some kind of database with latex commands and 
   environment description. This file is input for Python program latexhelp.py.
2. The output of the program latexhelp.py is tex file latexhelp_alph.tex.
3. File latexhelp_alph goes to the pdflatex program. The result is nice
   generated pdf file.

## JSON description for file latexhelp.json
```json
latexhelp = [
  {
    "entity":"bfseries",
    "package":"N/A",
    "type":"command", // "environment"
    "desciption":"/Bold-face font",
    "arguments":{
      "mandatory":[
        {
          "argument"="argument example",
          "description"="description"
        },
        // ...
      ],
      "optional":[
        // see above
      ]
  }
  // ...
]
```


