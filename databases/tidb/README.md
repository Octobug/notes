# TiDB

- [TiDB](#tidb)
  - [TiDB 与其开源社区](#tidb-与其开源社区)
    - [理论基础](#理论基础)
    - [特性](#特性)
    - [数据技术栈常见基础因素](#数据技术栈常见基础因素)
    - [架构：计算与存储分离](#架构计算与存储分离)
      - [TiDB 架构](#tidb-架构)
  - [References](#references)

## TiDB 与其开源社区

### 理论基础

- Google F1
- Raft

### 特性

- 扩展性 Scale Out
- 强一致性（CAP 中的一致性）与高可用性
- 标准 SQL，支持 ACID 事务
- 云原生
- HTAP
- 兼容主流生态与协议

### 数据技术栈常见基础因素

- 数据模型
  - 关系模型
  - 文档模型
  - Key-Value
  - ...
- 数据存储与检索结构
  - B-tree
  - LSM-tree
  - 分形树
  - ...
- 数据格式
  - 结构化数据
  - 非结构化数据
  - 半结构化数据
- 存储引擎
  - InnoDB
  - RocksDB
  - ...
- 复制协议
  - Raft
  - Paxos
- 分布式事务模型
  - XA
  - Percolator
- 数据架构
  - Share-Disk
  - Share-Nothing
  - Share-Everything
- 优化器算法
- 执行引擎
  - 火山引擎
  - 向量化
  - 大规模并行计算
- 计算引擎

### 架构：计算与存储分离

网络的发展促成了这种架构：

- 计算层
- 存储层 (TiKV)

计算与存储一体的缺陷：

- 两种资源总有一种处于过剩状态
- 服务器选型时需要纠结计算型还是存储型，增加了复杂度，降低了机器的通用性
- 在云计算场景下，弹性的颗粒度时机器，而不是真正的资源弹性

#### TiDB 架构

1. TiDB-Server: 支持标准 SQL 的计算引擎
2. TiKV: 分布式存储引擎
3. PD (Placement Driver): Raft 算法所在地
    - 元信息管理
      - 分片的分布
      - 拓扑结构
    - 分布式事务 ID 的分配
    - 调度中心

## References

- [ ] 线上课程
  - [ ] [TiDB 快速起步](https://learn.pingcap.com/learner/course/6)
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
  - [x] [3. Introduction of TiDB Architecture](https://pingcap.github.io/tidb-dev-guide/understand-tidb/introduction.html)
    - [ ] [3.1. The Lifecycle of a Statement](https://pingcap.github.io/tidb-dev-guide/understand-tidb/the-lifecycle-of-a-statement.html)
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
