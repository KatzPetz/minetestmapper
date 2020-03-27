#ifndef _DB_SQLITE3_H
#define _DB_SQLITE3_H

#include "db.h"
#include <unordered_map>
#include <sqlite3.h>

class DBSQLite3 : public DB {
public:
	DBSQLite3(const std::string &mapdir);
	std::vector<BlockPos> getBlockPos(BlockPos min, BlockPos max) override;
	void getBlocksOnXZ(BlockList &blocks, int16_t x, int16_t z,
			int16_t min_y, int16_t max_y) override;
	~DBSQLite3() override;

private:
	inline void getPosRange(int64_t &min, int64_t &max, int16_t zPos,
			int16_t zPos2) const;
	void loadBlockCache(int16_t zPos);

	sqlite3 *db;

	sqlite3_stmt *stmt_get_block_pos;
	sqlite3_stmt *stmt_get_block_pos_z;
	sqlite3_stmt *stmt_get_blocks_z;

	int16_t blockCachedZ = -10000;
	std::unordered_map<int16_t, BlockList> blockCache; // indexed by X
};

#endif // _DB_SQLITE3_H
