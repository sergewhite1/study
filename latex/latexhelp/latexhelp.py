import json

with open('latexhelp.json', 'r') as f:
    data = json.load(f)

print(data)

# TODO insert parsing

LATEXHELP_APH_TEX_FILENAME = "out/latexhelp_alph.tex"



with open(LATEXHELP_APH_TEX_FILENAME, "w") as f:
    f.write(r"""
\newcommand{\commandstyle}[1]{\texttt{#1}}
\newcommand{\descstyle}[1]{#1}

\documentclass{article}
\begin{document}
    \begin{table}[h]
        \begin{tabular}{|l|p{0.9\textwidth}|} \hline
"""
    )
    for entity in data['latexhelp']:
        f.write(str(entity))
        f.write("NEW LINE")
