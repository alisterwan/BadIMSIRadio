#!/usr/bin/env python
#
# Copyright 2010-2011 Ettus Research LLC
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

import optparse
import math
import socket
import struct


########################################################################
# constants
########################################################################
X300_FW_COMMS_UDP_PORT = 49152

X300_FW_COMMS_FLAGS_ACK         = 0x00000001
X300_FW_COMMS_FLAGS_POKE32      = 0x00000010
X300_FW_COMMS_FLAGS_PEEK32      = 0x00000020

X300_FW_COMMS_ERR_PKT_ERROR     = 0x80000000
X300_FW_COMMS_ERR_CMD_ERROR     = 0x40000000
X300_FW_COMMS_ERR_SIZE_ERROR    = 0x20000000

X300_FW_COMMS_ID = 0x0000ACE3
X300_FW_COMMS_MAX_DATA_WORDS    = 16

#UDP_CTRL_PORT = 49183
UDP_MAX_XFER_BYTES = 1024
UDP_TIMEOUT = 3
#USRP2_FW_PROTO_VERSION = 11 #should be unused after r6

#REG_ARGS_FMT = '!LLLLLB15x'
#REG_IP_FMT = '!LLLL20x'
REG_PEEK_POKE_FMT = '!LLLLL'


_seq = -1
def seq():
    global _seq
    _seq = _seq+1
    return _seq


########################################################################
# helper functions
########################################################################
def fw_check_error(flags):
    if flags & X300_FW_COMMS_ERR_PKT_ERROR == X300_FW_COMMS_ERR_PKT_ERROR:
        raise Exception("The fiwmware operation returned a packet error")
    if flags & X300_FW_COMMS_ERR_CMD_ERROR == X300_FW_COMMS_ERR_CMD_ERROR:
        raise Exception("The fiwmware operation returned a command error")
    if flags & X300_FW_COMMS_ERR_SIZE_ERROR == X300_FW_COMMS_ERR_SIZE_ERROR:
        raise Exception("The fiwmware operation returned a size error")

def pack_reg_peek_poke_fmt(flags, seq, addr, data):
    num_words = 1
    data_arr = [data]
    buf = bytes()
    buf = struct.pack('!LLLLL', X300_FW_COMMS_ID, flags, seq, num_words, addr)
    for i in range(X300_FW_COMMS_MAX_DATA_WORDS):
        if (i < num_words):
            buf += struct.pack('!L', data_arr[i])
        else:
            buf += struct.pack('!L', 0)
    return buf

def unpack_reg_peek_poke_fmt(buf):
    (id, flags, seq, num_words, addr) = struct.unpack_from('!LLLLL', buf)
    fw_check_error(flags)
    data = []
    for i in xrange(20, len(buf), 4):
        data.append(struct.unpack('!L', buf[i:i+4])[0])
    return (flags, seq, addr, data[0])

########################################################################
# Burner class, holds a socket and send/recv routines
########################################################################
class ctrl_socket(object):
    def __init__(self, addr):
        self._sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._sock.settimeout(UDP_TIMEOUT)
        self._sock.connect((addr, X300_FW_COMMS_UDP_PORT))
        self.set_callbacks(lambda *a: None, lambda *a: None)
        #self.init_update() #check that the device is there

    def set_callbacks(self, progress_cb, status_cb):
        self._progress_cb = progress_cb
        self._status_cb = status_cb

    def send_and_recv(self, pkt):
        self._sock.send(pkt)
        return self._sock.recv(UDP_MAX_XFER_BYTES)

    def read_router_stats(self):
        print
        print("            "),
        ports = ['        eth0','        eth1','      radio0','      radio1','    compute0','    compute1','    compute2','        pcie']
        for in_prt in ports:
            print("%s" % in_prt),
        print("   Egress Port")
        print("             "),
        for in_prt in range (0, 8):
            print("____________"),
        print
        for in_prt in range (0, 8):
            print("%s |" % ports[in_prt]),
            for out_prt in range (0, 8):
                out_pkt = pack_reg_peek_poke_fmt(X300_FW_COMMS_FLAGS_PEEK32|X300_FW_COMMS_FLAGS_ACK, seq(), 0xA000+256+((in_prt*8+out_prt)*4), 0)
                in_pkt = self.send_and_recv(out_pkt)
                (flags, rxseq, addr, data) = unpack_reg_peek_poke_fmt(in_pkt)
                fw_check_error(flags)
                print("%10d  " % (data)),
            print
        print
        print("Ingress Port")
        print


    def peek(self,peek_addr):
        out_pkt = pack_reg_peek_poke_fmt(X300_FW_COMMS_FLAGS_PEEK32|X300_FW_COMMS_FLAGS_ACK, seq(), peek_addr, 0)
        in_pkt = self.send_and_recv(out_pkt)
        (flags, rxseq, addr, data) = unpack_reg_peek_poke_fmt(in_pkt)
        fw_check_error(flags)
        print("PEEK of address %d(0x%x) reads %d(0x%x)" % (addr,addr,data,data))

    def poke(self,poke_addr,poke_data):
        out_pkt = pack_reg_peek_poke_fmt(X300_FW_COMMS_FLAGS_POKE32|X300_FW_COMMS_FLAGS_ACK, seq(), poke_addr, poke_data)
        in_pkt = self.send_and_recv(out_pkt)
        (flags, rxseq, addr, data) = unpack_reg_peek_poke_fmt(in_pkt)
        fw_check_error(flags)
        print("POKE of address %d(0x%x) with %d(0x%x)" % (poke_addr,poke_addr,poke_data,poke_data)  )


########################################################################
# command line options
########################################################################
def get_options():
    parser = optparse.OptionParser()
    parser.add_option("--addr", type="string",              help="USRP-X300 device address",       default='')
    parser.add_option("--list", action="store_true",        help="list possible network devices", default=False)
    parser.add_option("--peek", type="int",                 help="Read from memory map",     default=None)
    parser.add_option("--poke", type="int",                 help="Write to memory map",     default=None)
    parser.add_option("--data", type="int",                 help="Data for poke",     default=None)
    parser.add_option("--stats", action="store_true",        help="Display SuperMIMO Network Stats", default=False)
    (options, args) = parser.parse_args()

    return options


########################################################################
# main
########################################################################
if __name__=='__main__':
    options = get_options()


    if options.list:
        print('Possible network devices:')
        print('  ' + '\n  '.join(enumerate_devices()))
        exit()

    if not options.addr: raise Exception('no address specified')

    status = ctrl_socket(addr=options.addr)

    if options.stats:
        status.read_router_stats()


    if options.peek is not None:
        addr = options.peek
        status.peek(addr)

    if options.poke is not None and options.data is not None:
        addr = options.poke
        data = options.data
        status.poke(addr,data)
