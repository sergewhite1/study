import json

with open('latexhelp.json', 'r') as f:
    data = json.load(f)

print(data)

# TODO insert parsing

LATEXHELP_APH_TEX_FILENAME = "out/latexhelp.tex"



with open(LATEXHELP_APH_TEX_FILENAME, "w") as f:
    f.write(r"""
\newcommand{\commandstyle}[1]{\texttt{#1}}
\newcommand{\descstyle}[1]{#1}

\documentclass{article}
\begin{document}
    \begin{table}[h]
        \begin{tabular}{|l|p{0.9\textwidth}|} \hline
            \textbf{Command} & \textbf{Description} \\ \hline
"""
    )

    for entity in data['latexhelp']:
        f.write(" " * 12)
        f.write(f"\\commandstyle{{{entity['entity']}}} &\n")

        f.write(" " * 12)
        f.write(f"\\descstyle{{{entity['description']}}}\\\\ \\hline\n")

    f.write(r"""
        \end{tabular}
    \end{table}
\end{document}""")
