#!/bin/bash
chmod +x ./O2_travers.sh
./O2_travers.sh /home | sed 's/\(.*\)[/]/\1;/g' > traverse_output.txt

sqlite3 O2_database.db <<EOS
	create table if not exists main_table (
		access_rights integer,
		bytes_blocks_allocated integer,
		size_of_blocks integer,
		device_number text,
		file_type text,
		group_id integer,
		group_name text,
		hard_links integer,
		inode_number integer,
		mount_point text,
		file_path text,
		file_name text,
		IO_transfer_size integer,
		file_size integer,
		user_id integer,
		user_name text);
.separator ";"
.import ./traverse_output.txt main_table

	create table if not exists users (
		user_name text, 
		user_ID integer, 
		PRIMARY KEY(user_name));

	create table if not exists filesystem (
		file_name text, 
		file_path text, 
		inode_number integer, 		
		device_number,
		PRIMARY KEY(file_path, file_name), 
		FOREIGN KEY(inode_number) REFERENCES inode_data(inode_number), 
		FOREIGN KEY(device_number) REFERENCES inode_data(device_number));

	create table if not exists groups (
		group_name text, 
		group_id integer,
		PRIMARY KEY(group_name)); 

	create table if not exists inode_data (
		inode_number integer, 
		device_number integer, 
		file_type text, 
		file_size integer, 
		bytes_blocks_allocated integer, 
		hard_links integer, 
		access_rights integer, 
		user_name text, 
		group_name text,
		PRIMARY KEY(inode_number, device_number), 
		FOREIGN KEY(user_name) REFERENCES users(user_name), 
		FOREIGN KEY(group_name) REFERENCES Groups(group_name));

	create table if not exists hardware (
		device_number integer, 
		mount_point text, 
		IO_transfer_size, 
		size_of_blocks, 
		PRIMARY KEY(mount_point, device_number));
		

	INSERT OR IGNORE INTO users SELECT DISTINCT user_name, user_ID FROM main_table;
	
	INSERT OR IGNORE INTO filesystem SELECT DISTINCT file_name, file_path, inode_number, 			device_number FROM main_table;

	INSERT OR IGNORE INTO groups SELECT DISTINCT group_name, group_id FROM main_table;

	INSERT OR IGNORE INTO inode_data SELECT DISTINCT inode_number, device_number, file_type, 			file_size, bytes_blocks_allocated, hard_links, access_rights, user_name, group_name 			FROM main_table;

	INSERT OR IGNORE INTO hardware SELECT DISTINCT device_number, mount_point, IO_transfer_size, 			size_of_blocks FROM main_table;

drop table main_table;
EOS
rm ./traverse_output.txt











