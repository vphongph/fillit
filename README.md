# git

## General

Don't hesitate to read the git doc and ask questions to people who know!

## Commits

* Try to commit atomically: a commit should represent a minimal working change. For example, do a commit which adds movements to the player then another for its attack, not a single commit for both.

* Commit names should tell precisely what's been done. A commit named "Fuck this shit wtf" doesn't help :-)

## Branches

We'll dev each feature on a dedicated branch.

The name of the feature branches should be in the form `feature/X_Y` where X is the number of the issue and Y a brief description of what the branch does.

Use the same system for other types of branches, replacing `feature`. For example:`poc` (proof of concepts branches) or `hotfix` (in the future).

* To change to another branch 

`git checkout anotherbranch`

* Create a new branch named "fdp"

`git checkout -b fdp`

* Push your new branch to origin, letting other people review stuff and backing your work up in case your AMD catches fire

`git push --set-upstream origin newbranch`

* If the branch you're working on is late respective to the branch its based on, use the rebase command.

`git rebase thebranchitsbasedon`

* If the feature you're developping on your branch is done, you may merge it in the target branch from that branch with:

`git merge --no-ff thebranchtomerge`

Always rebase before merging. The --no-ff option creates a commit for the merge, which is clean and practical.

# Unity

## GameObjects

Make sure when creating assets that have both logic and art are respecting the following structure:
 - GameObject (contains logic script and colliders if any)
   - Geometry
     - mesh
   - VFX
     - particle system
