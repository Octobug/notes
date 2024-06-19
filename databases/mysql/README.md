# MySQL

## Management

```sh
mysqldump -u root -p dbname --no-data | gzip > dbname.sql.gz
mysqldump -u root -p dbname --no-data --no-tablespaces | gzip > dbname.sql.gz
```
