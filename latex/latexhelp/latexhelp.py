import argparse
import json

HEAD_STR = r"""
\newcommand{\commandstyle}[1]{\texttt{#1}}
\newcommand{\descstyle}[1]{#1}

\documentclass{article}
\begin{document}
    \begin{table}[h]
        \begin{tabular}{|l|p{0.9\textwidth}|} \hline
            \textbf{Command} & \textbf{Description} \\ \hline
"""

TAIL_STR = r"""
        \end{tabular}
    \end{table}
\end{document}"""


class LatexHelp:
    def __init__(self):
        self._data = {}

    def load(self, filename):
        ret = False

        with open(filename, 'r') as f:
            self._data = json.load(f)

        print(f"LatexHelp.load. self._data={self._data}")

        ret = self._validate()

        if ret:
            print(f"File {filename} has been loaded succeessfully")
        else:
            print(f"Error during loading file {filename}.")

        return ret

    def create_texfile(self, filename):
        with open(filename, "w") as f:
            f.write(HEAD_STR)

            for entity in self._data['latexhelp']:
                self._write_entity(f, entity)

            f.write(TAIL_STR)

        print(f"File {filename} has been created successfully.")

    def _validate(self) -> bool:
        print("TODO: Inside validate")
        return True

    def _write_entity(self, f, entity):
        f.write(" " * 12)
        f.write(f"\\commandstyle{{{entity['entity']}}} &\n")

        f.write(" " * 12)
        f.write(f"\\descstyle{{{entity['description']}}}\\\\ \\hline\n")


# START =======================================================================

parser = argparse.ArgumentParser(
    formatter_class=argparse.ArgumentDefaultsHelpFormatter)

parser.add_argument("--db",
                    help="Database file (JSON)",
                    default="latexhelp.json")

parser.add_argument("--out",
                    help="Output TEX file",
                    default="latexhelp.tex")

args = parser.parse_args()

lh = LatexHelp()

if not lh.load(args.db):
    exit(1)

lh.create_texfile(args.out)
