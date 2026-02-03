🔹 1. Log in as root
mysql -u root -p

🔹 2. Create a new user

Example: create user nelson with password MyStrongPass!23

CREATE USER 'nelson'@'localhost' IDENTIFIED BY 'MyStrongPass!23';


'nelson'@'localhost' → user nelson, only able to connect from the local machine.

To allow connections from any host:

CREATE USER 'nelson'@'%' IDENTIFIED BY 'MyStrongPass!23';

🔹 3. Grant privileges

To grant all privileges on a specific database (recommended for apps):

GRANT ALL PRIVILEGES ON mydb.* TO 'nelson'@'localhost';


To grant read/write but not admin rights:

GRANT SELECT, INSERT, UPDATE, DELETE ON mydb.* TO 'nelson'@'localhost';


To grant global privileges (like root — usually not recommended):

GRANT ALL PRIVILEGES ON *.* TO 'nelson'@'localhost' WITH GRANT OPTION;

🔹 4. Apply changes
FLUSH PRIVILEGES;

🔹 5. Test login

Exit MySQL, then try:

mysql -u nelson -p


Enter the password you set.