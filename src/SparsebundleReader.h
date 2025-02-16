/*
This file is part of apfs-fuse, a read-only implementation of APFS
(Apple File System) for FUSE.
Copyright (C) 2017 Simon Gander

Apfs-fuse is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

Apfs-fuse is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with apfs-fuse.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <memory>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "darling-dmg/src/Reader.h"
//#include "StruturedFileReader.h"

#undef DMG_DEBUG

class SparsebundleReader : public Reader
{
public:
	SparsebundleReader(const std::string& path);
	~SparsebundleReader();
	
	virtual int32_t read(void* buf, int32_t count, uint64_t offset);
	virtual uint64_t length();
	virtual uint64_t band_size() { return m_band_size; }

//	virtual bool isEncrypted() { return m_is_encrypted; };
//	virtual std::shared_ptr<Reader> getTokenReader();
//	virtual int32_t getTokenLength();
//	virtual uint64_t getTokenOffset();
//	virtual void getToken(uint8_t* token);

private:
    char* m_path;
	char* m_band_path;
	char* m_band_path_band_number_start;

	std::shared_ptr<Reader> m_tokenReader;

    size_t m_band_size;
    size_t m_blocksize;
    uint64_t m_size;
    uint64_t m_opened_file_band_number;
    int m_opened_file_fd;
};
