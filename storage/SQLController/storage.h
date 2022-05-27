//
// Created by gallaann on 16.04.22.
//

#ifndef LIFEONCANVAS_STORAGE_H
#define LIFEONCANVAS_STORAGE_H

#pragma once

#include <cstdio>
#include <string>

#include <sqlite3.h>

#include "../graphicsItem/GraphicsItem.h"

const char *filename = "lifeoncanvas.db";


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


class DataBase {
public:
    void CreateCanvas(int table_id); // create canvas with some ID
    void Insert(int table_id, int Key, GraphicsItem line); //push line into DB
    int Get(int table_id, int Key, std::vector<GraphicsItem> &line);

private:
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *zErrMsg = 0;
    int rc;
};

void DataBase::CreateCanvas(int table_id) {

    rc = sqlite3_open(filename, &db);

    /* Create SQL statement */
    std::string sql = "CREATE TABLE CanvasID_" + std::to_string(table_id) + " ("    \
      "Key            INT     NOT NULL,"    \
      "X1             INT     NOT NULL,"    \
      "Y1             INT     NOT NULL,"    \
      "X2             INT     NOT NULL,"    \
      "Y2             INT     NOT NULL,"    \
      "R              INT     NOT NULL,"    \
      "G              INT     NOT NULL,"    \
      "B              INT     NOT NULL,"    \
      "A              INT     NOT NULL,"    \
      "Width          INT     NOT NULL,"    \
      "ItemType       INT     NOT NULL);";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    sqlite3_close(db);
}

void DataBase::Insert(int table_id, int Key, GraphicsItem line) {
    rc = sqlite3_open(filename, &db);

    /* Create SQL statement */
    std::string sql = "INSERT INTO CanvasID_" + std::to_string(table_id) + " (Key, X1, Y1, X2, Y2, R, G, B, A, Width, ItemType) "  \
         "VALUES (" + std::to_string(Key) + ","  \
         "" + std::to_string(line.GetX1()) + "," + std::to_string(line.GetY1()) + ", "  \
         "" + std::to_string(line.GetX2()) + "," + std::to_string(line.GetY2()) + ", "  \
         "" + std::to_string(line.GetColorR()) + "," + std::to_string(line.GetColorG()) + ", "  \
         "" + std::to_string(line.GetColorB()) + "," + std::to_string(line.GetColorA()) + ", "  \
         "" + std::to_string(line.GetWidth()) + "," + std::to_string(line.GetLineItem()) + ");";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }

    sqlite3_close(db);
}

int DataBase::Get(int table_id, int Key, std::vector<GraphicsItem> &line) {
    int row = 0;

    rc = sqlite3_open(filename, &db);

    /* Create SQL statement */
    std::string sql = "Select X1, Y1, X2, Y2, R, G, B, A, Width, ItemType from CanvasID_" + std::to_string(table_id) +
                      " where Key >= " + std::to_string(Key) + " ;";

    /* Execute SQL statement */
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    sqlite3_step(stmt);

    uint32_t X1, Y1, X2, Y2;
    uint8_t R, G, B, A;
    int width;
    char itemType;

    bool done = false;
    while (!done) {
        printf("In select while\n");
        switch (sqlite3_step (stmt)) {
            case SQLITE_ROW:
                X1 = sqlite3_column_int(stmt, 0);
                Y1 = sqlite3_column_int(stmt, 1);
                X2 = sqlite3_column_int(stmt, 2);
                Y2 = sqlite3_column_int(stmt, 3);
                R = sqlite3_column_int(stmt, 4);
                G = sqlite3_column_int(stmt, 5);
                B = sqlite3_column_int(stmt, 6);
                A = sqlite3_column_int(stmt, 7);
                width = sqlite3_column_int(stmt, 8);
                itemType = sqlite3_column_int(stmt, 9);
                row++;
                line.push_back(GraphicsItem(X1, Y1, X2, Y2, R, G, B, A, width, itemType));
                break;

            case SQLITE_DONE:
                done = true;
                break;

            default:
                fprintf(stderr, "Failed.\n");
                return 1;
        }
    }

    sqlite3_finalize(stmt);

    sqlite3_close(db);
}

#endif //LIFEONCANVAS_STORAGE_H
