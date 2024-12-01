// INI READER WRITTEN BY MISTERMAGIK 30.10.2024
// THANKS TO SAMP TEAM
#if defined _INI_READER_
	#endinput
#endif
#define _INI_READER_

new gDB_HOST[32], gDB_NAME[32], gDB_PASS[32], gDB_DBNAME[32];

stock readIni() {
	new buff[255];
	new nh[32], nu[32], np[32], nd[32], fh[32], fu[32], fp[32], fd[32];
	new File:file;

	file = fopen("db.ini", io_read);
	fread(file, buff);

	if(sscanf(buff, "s[32]s[32]s[32]s[32]s[32]s[32]s[32]s[32]", nh, fh, nu, fu, np, fp, nd, fd)) {
		print("File error!");
		return 0;
	}

	format(gDB_HOST, sizeof(gDB_HOST), "%s", fh);
	format(gDB_NAME, sizeof(gDB_NAME), "%s", fu);
	format(gDB_PASS, sizeof(gDB_PASS), "%s", fp);
	format(gDB_DBNAME, sizeof(gDB_DBNAME), "%s", fd);

	fclose(file);
	return 1;
}
