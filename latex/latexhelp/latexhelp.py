import json

class LatexHelp:
    def __init__(self):
        self._data = {}

    def load(self, filename):
        ret = False

        with open(filename, 'r') as f:
            self._data = json.load(f)

        print(f"LatexHelp.load. self._data={self._data}")

        ret = self.validate()

        if ret:
            print(f"File {filename} has been loaded succeessfully")
        else:
            print(f"Error during loading file {filename}.")

        return ret

    def validate(self) -> bool:
        print("TODO: Inside validate")
        return True

    def create_texfile(self, filename):
        with open(filename, "w") as f:
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

            for entity in self._data['latexhelp']:
                f.write(" " * 12)
                f.write(f"\\commandstyle{{{entity['entity']}}} &\n")

                f.write(" " * 12)
                f.write(f"\\descstyle{{{entity['description']}}}\\\\ \\hline\n")

            f.write(r"""
        \end{tabular}
    \end{table}
\end{document}""")
        print(f"File {filename} has been created successfully.")

# START =======================================================================

# TODO insert parsing

lh = LatexHelp()

if not lh.load('latexhelp.json'):
    exit(1)

lh.create_texfile('out/main/latexhelp.tex')