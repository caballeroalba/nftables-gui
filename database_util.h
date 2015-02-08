/*
 * =====================================================================================
 *
 *       Filename:  database_util.h
 *
 *    Description:  This header file help scree_Utilites class to get/put data in DB
 *
 *        Version:  1.0
 *        Created:  06/02/15 10:42:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Maria Caballero Alba (caballeroalba), caballeroalba@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */



#include <stdio.h>
#include <sqlite3.h> 


char * getTables();


char * getTables(){
     sqlite3 *db;
    sqlite3_stmt *res;
    char *result[100];
    int rc = sqlite3_open("nftables", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    
    rc = sqlite3_prepare_v2(db, "SELECT * FROM tabla", -1, &res, 0);    
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }    
    
    rc = sqlite3_step(res);
    
    if (rc == SQLITE_ROW) {
        printf("%s|", sqlite3_column_text(res, 0));
        printf("%s|", sqlite3_column_text(res, 1));
        printf("%s|", sqlite3_column_text(res, 2));
        result[0]=sqlite3_column_text(res,1);

    }
    
    sqlite3_finalize(res);
    sqlite3_close(db);
    
    return result;

}
