# Tiny MLPerf™ v0.1

## GitHub Submission HOWTO

### Clone the Tiny MLPerf™ v0.1 submission tree

Clone the submission tree e.g. under your home directory:

```bash
$ export SUBMISSION_ROOT=$HOME/submission_tiny_1_0
$ git clone git@github.com:mlcommons/submission_tiny_1.0.git $SUBMISSION_ROOT
$ cd $SUBMISSION_ROOT
```

### Create a branch

We recommend creating a new branch for every logically connected group of
results e.g. all results from your System-Under-Test (SUT) or only relating to
a particular benchmark. Prefix your branch name with your organization's name.
Feel free to include the SUT name, implementation name, benchmark name, etc.

For example:

```bash
$ git checkout master && git pull
$ git checkout -b dividiti-closed-aws-g4dn.4xlarge-openvino
```

Populate your branch according to the [Tiny MLPerf Directory Structure](https://github.com/mlcommons/submission_tiny_1.0/blob/master/directory_structure.adoc).

You can inspect your changes:

```bash
$ git status
On branch dividiti-closed-aws-g4dn.4xlarge-openvino
Untracked files:
  (use "git add <file>..." to include in what will be committed)

        closed/dividiti/code/
        closed/dividiti/results/
        closed/dividiti/systems/

nothing added to commit but untracked files present (use "git add" to track)
```

and make intermediate commits as usual:

```bash
$ git add closed/dividiti
$ git commit -m "Dump repo:mlperf-closed-aws-g4dn.4xlarge-openvino."
```

### Push the changes

Once you are happy with the tree structure, you can push the changes:

```bash
$ git push

fatal: The current branch dividiti-closed-aws-g4dn.4xlarge-openvino has no upstream branch.
To push the current branch and set the remote as upstream, use

    git push --set-upstream origin dividiti-closed-aws-g4dn.4xlarge-openvino
```

Do exactly as suggested:

```bash
$ git push --set-upstream origin dividiti-closed-aws-g4dn.4xlarge-openvino
```

### Create a pull request

If you now go to https://github.com/mlcommons/submission_tiny_1.0, you should see a notification
about your branch being recently pushed and can immediately create a pull request (PR).
You can also select your branch from the dropdown menu under `<> Code`. (Aren't you happy you prefixed your branch's name with the submitter's name?)

As usual, you can continue committing to the branch until the PR is merged, with any changes
being reflected in the PR.
