/*

			 MD5 include
			BJIADOKC & Co.
	Remove this copyright, if you want to be a superman!
*/





#if defined _md5_included
	#endinput
#endif

#define _md5_included



#define MD5_MAX_LEN (32 + 1)





native md5(dest[], source[], size = sizeof dest);
native md5_file(dest[], file[], size = sizeof dest);
native md5_hmac(dest[], source[], key[], size = sizeof dest);
