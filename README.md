# MemoCLI

This is a project used for practicing git collaboration.

## Stage 1: Initial Structure (Alice's Duty)

**Program Functionality:**

- Create basic structure (`main.cpp`, `Makefile` or `CMakeLists.txt`, `.gitignore`)
- Implement core functionality: `memo add "My first memo"`
- This will create a `.txt` file and write to `memos.txt`

**Git Scenario & Operations:**

- Initialize local git repository with `git init`
- Create a new empty repository on GitHub
- Link remote repository with `git remote add origin ...`
- Perform first `git commit` and `git push origin main` after completing code
- Key practice: Set up main branch protection rules on GitHub (prohibit direct pushes, require PR merging)

## Stage 1.5: Technical Refactoring (Alice's Duty)

**Create Refactoring Branch:**
- Start from your current latest master branch

**Modify Code to Support JSON:**
- Change `memos.txt` logic to `journal.json`
- Modify `addEntry` function to create a JSON object (e.g., `{"content": "..."}`)
- Add to a JSON array and write to `journal.json` file

**Submit and Merge PR:**
- Submit refactoring work after completing code modifications and testing

## Stage 2: First Feature & PR Process (Bob's Duty)

**Software Functionality:**
- Implement `memo list` function to read `journal.json` and print all journal entries

**Git Scenario & Operations:**
- Create feature branch: `git checkout -b feat/list-entries`
- Develop on the branch with one or multiple commits
- Push branch to remote: `git push origin feat/list-entries`
- Create Pull Request: On GitHub, create PR from `feat/list-entries` to `main`
- Code Review & Merge: Switch to Alice's role, check code on GitHub, leave comments, then click "Merge Pull Request"

## Stage 3: Parallel Development & Merge Conflicts (Bob vs Charlie)

**Software Functionality (Parallel Development):**

- **Bob's Task:** Requirement change! Each journal entry must now have a unique `id` and automatically generated `timestamp` in addition to `content`. Bob needs to modify the `add` functionality.
- **Charlie's Task:** Implement tag functionality! Each journal entry can have multiple tags. Example: `memo add "Learned Git today" --tags git cpp`. Charlie also needs to modify the `add` functionality to add a `tags` array in JSON.

**Git Scenario & Operations:**
- Bob and Charlie create their own feature branches from `main` branch (`feat/entry-metadata` and `feat/tags`)
- Both modify the same code area in `main.cpp` (add functionality logic)
- Assuming Charlie works faster, his PR gets merged by Alice first
- When Bob pushes code and creates PR, GitHub shows "Can't automatically merge"
- Core practice: Bob needs to pull the latest `main` code locally, resolve merge conflicts in his feature branch, then push the fixed branch to complete PR merging

## Stage 4: Requirement Change & History Organization (Bob's Duty)

**Software Functionality:**
- Product manager suddenly says auto-generated `id` is not user-friendly and wants to change to user-customizable `title`
- `title` must be unique and cannot be duplicated

**Git Scenario & Operations:**
- Bob may have made several commits about `id` functionality on his `feat/entry-metadata` branch (e.g., "feat: add uuid generation", "refactor: move id logic to helper")
- These `id`-related commits become useless
- Core practice: After implementing `title` functionality, Bob uses `git rebase -i` (interactive rebase) with `squash` or `fixup` functionality
- Merge previous multiple `id` commits and new `title` commits into one clean commit: `feat: Replace ID with unique title`
- This makes his PR very clear with only one meaningful commit

## Stage 5: Production Bug & Responsibility Tracing (Alice's Duty)

**Software Functionality (Bug Report):**
- Users report that when `journal.json` file is empty, executing `memo list` causes program crash

**Git Scenario & Operations:**
- Alice receives the report and needs to quickly locate the issue
- She suspects it was introduced in a recent modification
- Core practice: Alice uses `git blame main.cpp` to check who last modified the list functionality code and in which commit
- After locating the problematic commit, use `git show <commit_hash>` to view the complete context of that commit and understand why it was changed that way
- Alice creates a `fix/list-empty-crash` branch, fixes the issue, and merges via PR to complete a standard bugfix process

