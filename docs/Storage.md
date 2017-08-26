# OODB Storage

OODB is not actually a database. It's a layer on top of a database. It uses databases for querying and storing data, but for the most part doesn't care which database you use.

An abstract database platform class is used. There are a few built in database platforms that are mostly used for testing. These are **NOT** recommended for production.

 * `fs`

  Stores all the objects in files.

 * `memory`

  Stores all the objects in memory.