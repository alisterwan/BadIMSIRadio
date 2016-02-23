//
// Copyright 2014 Ettus Research
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef INCLUDED_AD9361_GAIN_TABLES_HPP
#define INCLUDED_AD9361_GAIN_TABLES_HPP

#include <boost/cstdint.hpp>

boost::uint8_t gain_table_sub_1300mhz[77][3] = {
{ 0x00, 0x00, 0x20 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
{ 0x00, 0x01, 0x00 }, { 0x00, 0x02, 0x00 }, { 0x00, 0x03, 0x00 },
{ 0x00, 0x04, 0x00 }, { 0x00, 0x05, 0x00 }, { 0x01, 0x03, 0x20 },
{ 0x01, 0x04, 0x00 }, { 0x01, 0x05, 0x00 }, { 0x01, 0x06, 0x00 },
{ 0x01, 0x07, 0x00 }, { 0x01, 0x08, 0x00 }, { 0x01, 0x09, 0x00 },
{ 0x01, 0x0A, 0x00 }, { 0x01, 0x0B, 0x00 }, { 0x01, 0x0C, 0x00 },
{ 0x01, 0x0D, 0x00 }, { 0x01, 0x0E, 0x00 }, { 0x02, 0x09, 0x20 },
{ 0x02, 0x0A, 0x00 }, { 0x02, 0x0B, 0x00 }, { 0x02, 0x0C, 0x00 },
{ 0x02, 0x0D, 0x00 }, { 0x02, 0x0E, 0x00 }, { 0x02, 0x0F, 0x00 },
{ 0x02, 0x10, 0x00 }, { 0x02, 0x2B, 0x20 }, { 0x02, 0x2C, 0x00 },
{ 0x04, 0x28, 0x20 }, { 0x04, 0x29, 0x00 }, { 0x04, 0x2A, 0x00 },
{ 0x04, 0x2B, 0x00 }, { 0x24, 0x20, 0x20 }, { 0x24, 0x21, 0x00 },
{ 0x44, 0x20, 0x20 }, { 0x44, 0x21, 0x00 }, { 0x44, 0x22, 0x00 },
{ 0x44, 0x23, 0x00 }, { 0x44, 0x24, 0x00 }, { 0x44, 0x25, 0x00 },
{ 0x44, 0x26, 0x00 }, { 0x44, 0x27, 0x00 }, { 0x44, 0x28, 0x00 },
{ 0x44, 0x29, 0x00 }, { 0x44, 0x2A, 0x00 }, { 0x44, 0x2B, 0x00 },
{ 0x44, 0x2C, 0x00 }, { 0x44, 0x2D, 0x00 }, { 0x44, 0x2E, 0x00 },
{ 0x44, 0x2F, 0x00 }, { 0x44, 0x30, 0x00 }, { 0x44, 0x31, 0x00 },
{ 0x44, 0x32, 0x00 }, { 0x64, 0x2E, 0x20 }, { 0x64, 0x2F, 0x00 },
{ 0x64, 0x30, 0x00 }, { 0x64, 0x31, 0x00 }, { 0x64, 0x32, 0x00 },
{ 0x64, 0x33, 0x00 }, { 0x64, 0x34, 0x00 }, { 0x64, 0x35, 0x00 },
{ 0x64, 0x36, 0x00 }, { 0x64, 0x37, 0x00 }, { 0x64, 0x38, 0x00 },
{ 0x65, 0x38, 0x20 }, { 0x66, 0x38, 0x20 }, { 0x67, 0x38, 0x20 },
{ 0x68, 0x38, 0x20 }, { 0x69, 0x38, 0x20 }, { 0x6A, 0x38, 0x20 },
{ 0x6B, 0x38, 0x20 }, { 0x6C, 0x38, 0x20 }, { 0x6D, 0x38, 0x20 },
{ 0x6E, 0x38, 0x20 }, { 0x6F, 0x38, 0x20 } };


boost::uint8_t gain_table_1300mhz_to_4000mhz[77][3] = {
{ 0x00, 0x00, 0x20 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
{ 0x00, 0x01, 0x00 }, { 0x00, 0x02, 0x00 }, { 0x00, 0x03, 0x00 },
{ 0x00, 0x04, 0x00 }, { 0x00, 0x05, 0x00 }, { 0x01, 0x03, 0x20 },
{ 0x01, 0x04, 0x00 }, { 0x01, 0x05, 0x00 }, { 0x01, 0x06, 0x00 },
{ 0x01, 0x07, 0x00 }, { 0x01, 0x08, 0x00 }, { 0x01, 0x09, 0x00 },
{ 0x01, 0x0A, 0x00 }, { 0x01, 0x0B, 0x00 }, { 0x01, 0x0C, 0x00 },
{ 0x01, 0x0D, 0x00 }, { 0x01, 0x0E, 0x00 }, { 0x02, 0x09, 0x20 },
{ 0x02, 0x0A, 0x00 }, { 0x02, 0x0B, 0x00 }, { 0x02, 0x0C, 0x00 },
{ 0x02, 0x0D, 0x00 }, { 0x02, 0x0E, 0x00 }, { 0x02, 0x0F, 0x00 },
{ 0x02, 0x10, 0x00 }, { 0x02, 0x2B, 0x20 }, { 0x02, 0x2C, 0x00 },
{ 0x04, 0x27, 0x20 }, { 0x04, 0x28, 0x00 }, { 0x04, 0x29, 0x00 },
{ 0x04, 0x2A, 0x00 }, { 0x04, 0x2B, 0x00 }, { 0x24, 0x21, 0x20 },
{ 0x24, 0x22, 0x00 }, { 0x44, 0x20, 0x20 }, { 0x44, 0x21, 0x00 },
{ 0x44, 0x22, 0x00 }, { 0x44, 0x23, 0x00 }, { 0x44, 0x24, 0x00 },
{ 0x44, 0x25, 0x00 }, { 0x44, 0x26, 0x00 }, { 0x44, 0x27, 0x00 },
{ 0x44, 0x28, 0x00 }, { 0x44, 0x29, 0x00 }, { 0x44, 0x2A, 0x00 },
{ 0x44, 0x2B, 0x00 }, { 0x44, 0x2C, 0x00 }, { 0x44, 0x2D, 0x00 },
{ 0x44, 0x2E, 0x00 }, { 0x44, 0x2F, 0x00 }, { 0x44, 0x30, 0x00 },
{ 0x44, 0x31, 0x00 }, { 0x64, 0x2E, 0x20 }, { 0x64, 0x2F, 0x00 },
{ 0x64, 0x30, 0x00 }, { 0x64, 0x31, 0x00 }, { 0x64, 0x32, 0x00 },
{ 0x64, 0x33, 0x00 }, { 0x64, 0x34, 0x00 }, { 0x64, 0x35, 0x00 },
{ 0x64, 0x36, 0x00 }, { 0x64, 0x37, 0x00 }, { 0x64, 0x38, 0x00 },
{ 0x65, 0x38, 0x20 }, { 0x66, 0x38, 0x20 }, { 0x67, 0x38, 0x20 },
{ 0x68, 0x38, 0x20 }, { 0x69, 0x38, 0x20 }, { 0x6A, 0x38, 0x20 },
{ 0x6B, 0x38, 0x20 }, { 0x6C, 0x38, 0x20 }, { 0x6D, 0x38, 0x20 },
{ 0x6E, 0x38, 0x20 }, { 0x6F, 0x38, 0x20 } };


boost::uint8_t gain_table_4000mhz_to_6000mhz[77][3] = {
{ 0x00, 0x00, 0x20 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 },
{ 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x00 }, { 0x00, 0x01, 0x00 },
{ 0x00, 0x02, 0x00 }, { 0x00, 0x03, 0x00 }, { 0x01, 0x01, 0x20 },
{ 0x01, 0x02, 0x00 }, { 0x01, 0x03, 0x00 }, { 0x01, 0x04, 0x20 },
{ 0x01, 0x05, 0x00 }, { 0x01, 0x06, 0x00 }, { 0x01, 0x07, 0x00 },
{ 0x01, 0x08, 0x00 }, { 0x01, 0x09, 0x00 }, { 0x01, 0x0A, 0x00 },
{ 0x01, 0x0B, 0x00 }, { 0x01, 0x0C, 0x00 }, { 0x02, 0x08, 0x20 },
{ 0x02, 0x09, 0x00 }, { 0x02, 0x0A, 0x00 }, { 0x02, 0x0B, 0x20 },
{ 0x02, 0x0C, 0x00 }, { 0x02, 0x0D, 0x00 }, { 0x02, 0x0E, 0x00 },
{ 0x02, 0x0F, 0x00 }, { 0x02, 0x2A, 0x20 }, { 0x02, 0x2B, 0x00 },
{ 0x04, 0x27, 0x20 }, { 0x04, 0x28, 0x00 }, { 0x04, 0x29, 0x00 },
{ 0x04, 0x2A, 0x00 }, { 0x04, 0x2B, 0x00 }, { 0x04, 0x2C, 0x00 },
{ 0x04, 0x2D, 0x00 }, { 0x24, 0x20, 0x20 }, { 0x24, 0x21, 0x00 },
{ 0x24, 0x22, 0x00 }, { 0x44, 0x20, 0x20 }, { 0x44, 0x21, 0x00 },
{ 0x44, 0x22, 0x00 }, { 0x44, 0x23, 0x00 }, { 0x44, 0x24, 0x00 },
{ 0x44, 0x25, 0x00 }, { 0x44, 0x26, 0x00 }, { 0x44, 0x27, 0x00 },
{ 0x44, 0x28, 0x00 }, { 0x44, 0x29, 0x00 }, { 0x44, 0x2A, 0x00 },
{ 0x44, 0x2B, 0x00 }, { 0x44, 0x2C, 0x00 }, { 0x44, 0x2D, 0x00 },
{ 0x44, 0x2E, 0x00 }, { 0x64, 0x2E, 0x20 }, { 0x64, 0x2F, 0x00 },
{ 0x64, 0x30, 0x00 }, { 0x64, 0x31, 0x00 }, { 0x64, 0x32, 0x00 },
{ 0x64, 0x33, 0x00 }, { 0x64, 0x34, 0x00 }, { 0x64, 0x35, 0x00 },
{ 0x64, 0x36, 0x00 }, { 0x64, 0x37, 0x00 }, { 0x64, 0x38, 0x00 },
{ 0x65, 0x38, 0x20 }, { 0x66, 0x38, 0x20 }, { 0x67, 0x38, 0x20 },
{ 0x68, 0x38, 0x20 }, { 0x69, 0x38, 0x20 }, { 0x6A, 0x38, 0x20 },
{ 0x6B, 0x38, 0x20 }, { 0x6C, 0x38, 0x20 }, { 0x6D, 0x38, 0x20 },
{ 0x6E, 0x38, 0x20 }, { 0x6F, 0x38, 0x20 } };


#endif /* INCLUDED_AD9361_GAIN_TABLES_HPP */
