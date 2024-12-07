# dpdb (daniel penczak database)

Learning about C and database implementation. 

# Build:
repos\dpdb> gcc Source/sql/rdb.c -o dpdb.exe


## TODOs
- Clustered and Nonclustered indexes
    - B+tree
- File storage
    - Start with single file per table
    - Table definition, indexes, data
    - (?) Split large files into 1GB chunks

## Reading
- [Reddit - Storage of Internal B-Tree](https://www.reddit.com/r/Database/comments/178vwfk/comment/k5cwa5h/)
- [Postgres - nbtree README](https://github.com/postgres/postgres/blob/master/src/backend/access/nbtree/README)