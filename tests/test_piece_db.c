
#include <stdbool.h>
#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CuTest.h"

#include <stdint.h>

#include "bitfield.h"

#include "bt.h"
#include "bt_piece_db.h"
#include "bt_piece.h"

void TestBTpiecedb_new_is_empty(CuTest * tc)
{
    void *db;

    db = bt_piecedb_new();
    CuAssertTrue(tc, 0 == bt_piecedb_count(db));
    CuAssertTrue(tc, NULL == bt_piecedb_get(db, 0));
}

void TestBTPieceDB_add_piece(CuTest * tc)
{
    void *db;

    db = bt_piecedb_new();
    //bt_piecedb_set_piece_length(db, 40);
    /* need to add a file so that we have a filespace to hold the added piece */
    bt_piecedb_increase_piece_space(db,40);
    //bt_piecedb_add(db, "00000000000000000000", 40);
    CuAssertTrue(tc, 0 == bt_piecedb_add(db, 1));// "00000000000000000000", 40);
    CuAssertTrue(tc, 1 == bt_piecedb_count(db));
    CuAssertTrue(tc, NULL != bt_piecedb_get(db, 0));
}

void TestBTPieceDB_add_piece_twice(CuTest * tc)
{
    void *db;

    db = bt_piecedb_new();
    //bt_piecedb_set_piece_length(db, 40);
    /* need to add a file so that we have a filespace to hold the added piece */
    bt_piecedb_increase_piece_space(db, 80);
    CuAssertTrue(tc, 0 == bt_piecedb_add(db, 1));// "00000000000000000000", 40));
    CuAssertTrue(tc, 1 == bt_piecedb_add(db, 1));//"00000000000000000000", 40));
    CuAssertTrue(tc, 2 == bt_piecedb_count(db));
    CuAssertTrue(tc, NULL != bt_piecedb_get(db, 0));
    CuAssertTrue(tc, NULL != bt_piecedb_get(db, 1));
}

void TestBTPieceDB_add_piece_at_idx(CuTest * tc)
{
    void *db;

    db = bt_piecedb_new();
    bt_piecedb_increase_piece_space(db,40);
    CuAssertTrue(tc, 0 == bt_piecedb_add_at_idx(db, 1, 0));
    CuAssertTrue(tc, 1 == bt_piecedb_count(db));
    CuAssertTrue(tc, NULL != bt_piecedb_get(db, 0));

    db = bt_piecedb_new();
    bt_piecedb_increase_piece_space(db,40);
    CuAssertTrue(tc, 1 == bt_piecedb_add_at_idx(db, 1, 1));
    CuAssertTrue(tc, 1 == bt_piecedb_count(db));
    CuAssertTrue(tc, NULL == bt_piecedb_get(db, 0));
    CuAssertTrue(tc, NULL != bt_piecedb_get(db, 1));
}

void TestBTPieceDB_remove(CuTest * tc)
{
    void *db;

    db = bt_piecedb_new();
    //bt_piecedb_set_piece_length(db, 40);
    /* need to add a file so that we have a filespace to hold the added piece */
    bt_piecedb_increase_piece_space(db, 40);
    CuAssertTrue(tc, 0 == bt_piecedb_add(db, 1));// "00000000000000000000", 40);
    bt_piecedb_remove(db, 0);
    CuAssertTrue(tc, 0 == bt_piecedb_count(db));
    CuAssertTrue(tc, NULL == bt_piecedb_get(db, 0));
}

void TestBTPieceDB_remove_allows_space_to_be_taken(CuTest * tc)
{
    void *db;

    db = bt_piecedb_new();
    /* need to add a file so that we have a filespace to hold the added piece */
    bt_piecedb_increase_piece_space(db, 40);
    CuAssertTrue(tc, 0 == bt_piecedb_add(db, 1));
    bt_piecedb_remove(db, 0);
    CuAssertTrue(tc, 0 == bt_piecedb_add(db, 1));
    CuAssertTrue(tc, 1 == bt_piecedb_count(db));
    CuAssertTrue(tc, NULL != bt_piecedb_get(db, 0));
}

void TestBTPieceDB_GetLength_returns_correct_length_of_db(CuTest * tc)
{
    void *db;

    db = bt_piecedb_new();
    //bt_piecedb_set_piece_length(db, 40);
    CuAssertTrue(tc, 0 == bt_piecedb_get_length(db));
    /* make sure we have enough file space */
    bt_piecedb_increase_piece_space(db,40 * 4);
    bt_piece_set_size(bt_piecedb_get(db, bt_piecedb_add(db, 1)),40);// "00000000000000000000", 40);
    bt_piece_set_size(bt_piecedb_get(db, bt_piecedb_add(db, 1)),40);// "00000000000000000000", 40);
    bt_piece_set_size(bt_piecedb_get(db, bt_piecedb_add(db, 1)),40);// "00000000000000000000", 40);
    bt_piece_set_size(bt_piecedb_get(db, bt_piecedb_add(db, 1)),40);// "00000000000000000000", 40);
    CuAssertTrue(tc, 4 == bt_piecedb_get_length(db));
}

void TestBTPieceDB_add_pieces(CuTest * tc)
{
    void *db;

    db = bt_piecedb_new();
    //bt_piecedb_set_piece_length(db, 40);
    /* need to add a file so that we have a filespace to hold the added piece */
    bt_piecedb_increase_piece_space(db,40);
    //bt_piecedb_add(db, "00000000000000000000", 40);
    CuAssertTrue(tc, 0 == bt_piecedb_add(db, 2));// "00000000000000000000", 40);
    CuAssertTrue(tc, 2 == bt_piecedb_count(db));
    CuAssertTrue(tc, NULL != bt_piecedb_get(db, 0));
    CuAssertTrue(tc, NULL != bt_piecedb_get(db, 1));
}

#if 0
void T_estBTPieceDB_AddingPiece_LastPieceFitsTotalSize(
    CuTest * tc
)
{
    void *db;
    bt_piece_t *pce;

    db = bt_piecedb_new();
    bt_piecedb_set_piece_length(db, 50);
    bt_piecedb_set_tot_file_size(db, 180);
    /* make sure we have enough file space */
    //bt_piecedb_add_file(db,"test",4,40*4);
    bt_piecedb_add(db, "00000000000000000000", 50);
    bt_piecedb_add(db, "00000000000000000000", 50);
    bt_piecedb_add(db, "00000000000000000000", 50);
    bt_piecedb_add(db, "00000000000000000000", 50);
    CuAssertTrue(tc, bt_piece_get_size(bt_piecedb_get(db, 2)) == 50);
    CuAssertTrue(tc, bt_piece_get_size(bt_piecedb_get(db, 3)) == 30);
}
#endif
