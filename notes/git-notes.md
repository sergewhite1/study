# Work with temporary remote branch

After squash merge form branch `progress`  to branch `main`.

Old approach

```bash
git push origin --delete progress
git branch -D progress
git checkout -b progress
git push -u origin progress
```

New approach (thanks to Chat GPT):

```bash
git switch progress
git reset --hard main
git push --force-with-lease
```
