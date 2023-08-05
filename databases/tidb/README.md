# TiDB

- [TiDB](#tidb)
  - [线上课程](#线上课程)
  - [References](#references)

## 线上课程

- [ ] [TiDB 快速起步](https://learn.pingcap.com/learner/course/6)

> <https://learn.pingcap.com/learner/player/12;id=12;source=DETAIL;classroomId=120016;courseDetailId=6;learnerAttemptId=1691243344120>

## References

- [x] [pingcap/tidb-dev-guide](https://github.com/pingcap/tidb-dev-guide)
- [x] [TiDB Development Guide](https://pingcap.github.io/tidb-dev-guide/)
  - [x] [1. Get Started](https://pingcap.github.io/tidb-dev-guide/get-started/introduction.html)
    - [x] [1.1. Install Golang](https://pingcap.github.io/tidb-dev-guide/get-started/install-golang.html)
    - [x] [1.2. Get the code, build and run](https://pingcap.github.io/tidb-dev-guide/get-started/build-tidb-from-source.html)
    - [x] [1.3. Setup an IDE](https://pingcap.github.io/tidb-dev-guide/get-started/setup-an-ide.html)
    - [x] [1.4. Write and run unit tests](https://pingcap.github.io/tidb-dev-guide/get-started/write-and-run-unit-tests.html)
    - [x] [1.5. Debug and profile](https://pingcap.github.io/tidb-dev-guide/get-started/debug-and-profile.html)
    - [x] [1.6. Commit code and submit a pull request](https://pingcap.github.io/tidb-dev-guide/get-started/commit-code-and-submit-a-pull-request.html)
  - [x] [2. Contribute to TiDB](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/introduction.html)
    - [x] [2.1. Community Guideline](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/community-guideline.html)
    - [x] [2.2. Report an Issue](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/report-an-issue.html)
    - [x] [2.3. Issue Triage](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/issue-triage.html)
    - [x] [2.4. Contribute Code](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/contribute-code.html)
    - [x] [2.5. Cherry-pick a Pull Request](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/cherrypick-a-pr.html)
    - [x] [2.6. Review a Pull Request](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/review-a-pr.html)
    - [x] [2.7. Make a Proposal](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/make-a-proposal.html)
    - [x] [2.8. Code Style and Quality Guide](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/code-style-and-quality-guide.html)
    - [x] [2.9. Write Document](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/write-document.html)
    - [x] [2.10. Release Notes Language Style Guide](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/release-notes-style-guide.html)
    - [x] [2.11. Committer Guide](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/committer-guide.html)
    - [x] [2.12. Miscellaneous Topics](https://pingcap.github.io/tidb-dev-guide/contribute-to-tidb/miscellaneous-topics.html)
  - [ ] [3. Introduction of TiDB Architecture](https://pingcap.github.io/tidb-dev-guide/understand-tidb/introduction.html)
    - [ ] 3.1. The Lifecycle of a Statement
    - [ ] 3.1.1. DDL
    - [ ] 3.1.2. DML
    - [ ] 3.1.3. DQL
    - [ ] 3.2. Parser
    - [ ] 3.3. Planner
    - [ ] 3.3.1. Table Statistics
    - [ ] 3.3.2. Rule-based Optimization
    - [ ] 3.3.3. Cost-based Optimization
    - [ ] 3.3.4. Plan Cache
    - [ ] 3.3.5. SQL Plan Management
    - [ ] 3.4. Execution
    - [ ] 3.4.1. Parallel Execution Framework
    - [ ] 3.4.2. Implementation of Vectorized Execution
    - [ ] 3.4.3. Memory Management Mechanism
    - [ ] 3.4.4. Implementation of Typical Operators
    - [ ] 3.5. Transaction
    - [ ] 3.5.1. Transaction on TiKV
    - [ ] 3.5.2. Optimistic Transaction
    - [ ] 3.5.3. Lock Resolver
    - [ ] 3.5.4. Pessimistic Transaction
    - [ ] 3.5.5. Async Commit
    - [ ] 3.5.6. 1PC
    - [ ] 3.5.7. MVCC garbage collection
    - [ ] 3.6. Session
    - [ ] 3.7. Privilege
    - [ ] 3.8. Plugin
  - [ ] [4. Project Management](https://pingcap.github.io/tidb-dev-guide/project-management/introduction.html)
  - [ ] [5. Extending TiDB](https://pingcap.github.io/tidb-dev-guide/extending-tidb/introduction.html)
