# MySQL

## Topics

- [Drop Large Table](topics/drop_large_table.md)

## MySQL vs. MyISAM

> <https://blogs.oracle.com/mysql/post/still-using-myisam-it-is-time-to-switch-to-innodb>

### Still using MyISAM ? It is time to switch to InnoDB!

InnoDB offers several advantages over MyISAM:

- MVCC (**multi-version concurrency control**)
- support for ACID transactions,
  - atomicity
  - consistency
  - isolation
  - durability
- row-level locking,
- crash recovery capabilities,
- foreign keys,
- hot backups,
- clone

In addition, compared to MyISAM, InnoDB is more reliable and less prone to data
corruption.

### Performance

- Performance is the most important and "MyISAM is faster"…?
  - Since 5.7, InnoDB is faster. And in 8.0 the InnoDB performance kept
    improving.
- For temporary tables MyISAM is better…?
  - In MySQL 8.0, the storage engine for on-disk internal temporary tables is
    now only InnoDB.

Before MySQL 8.0, there was still one single case where MyISAM was performing
better than InnoDB: High Insert Rate, during bulk load. This was because MyISAM
does not have MVCC and is not durable. With MySQL 8.0 you can choose to disable
InnoDB durability disabling the redo logs, giving you high insert rate for the
time of the bulk load.

InnoDB is designed to take advantage of multi-core CPUs, which means that it
can use multiple cores for parallel processing and achieve better performance
on modern hardware.

### Storage footprint

InnoDB consumes more diskspace than MyISAM. Even when pages are compressed but
this is also the price to pay to fully support MVCC.

### Partitioning

In MySQL 8.0, each storage engine must provide Native Partitioning and
currently only InnoDB delivers it.

### Native GIS

- "GIS is only supported in MyISAM"?
  - In MySQL 8.0 we have made major advances in InnoDB's support for GIS.
  - InnoDB covers all you need related to GIS.

### Full Text Search

Since MySQL 5.6 already, InnoDB supports Full Text Search (FTS), and it's since
then scaling 3x times better than on MyISAM.

### High Availability

MySQL InnoDB Cluster (for HA), and InnoDB ClusterSet (for DR), both based on
Group Replication and require InnoDB.

### Cloud

None of the cloud managed MySQL Services include MyISAM.

### Converting tables from MyISAM to InnoDB

[Converting Tables from MyISAM to InnoDB](https://dev.mysql.com/doc/refman/8.0/en/converting-tables-to-innodb.html)

The migration in many cases is not complex and can be summarized by:

```sql
alter table <table_name> engine=InnoDB;
```

And when you are done, don't forget to:

```sql
set persist_only disabled_storage_engines='MyISAM';
```

### Conclusion

InnoDB offers better performance, reliability, and scalability, making it the
default choice for modern applications. InnoDB is the only possible choice if
you care about your data and plan to use High Availability and Disaster
Recovery.
