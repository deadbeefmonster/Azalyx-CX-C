# Create database and initialize it
sqlite3 database.db < sql/sqlite.sql

# Get the full path to the database
realpath database.db

# Add it in the configuration.ini file
[sqlite]
database_path=FULL_PATH_HERE

# -or- Add it via the command line arg
--sqlite-database-file FULL_PATH_HERE
