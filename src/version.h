// Copyright (c) 2012 The BitToken developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_VERSION_H
#define BITCOIN_VERSION_H

#include "clientversion.h"
#include <string>

//
// client versioning
//

static const int CLIENT_VERSION =
                           1000000 * CLIENT_VERSION_MAJOR
                         +   10000 * CLIENT_VERSION_MINOR
                         +     100 * CLIENT_VERSION_REVISION
                         +       1 * CLIENT_VERSION_BUILD;

extern const std::string CLIENT_NAME;
extern const std::string CLIENT_BUILD;
extern const std::string CLIENT_DATE;

//
// network protocol versioning
//

static const int PROTOCOL_VERSION = 70203;

// earlier versions not supported as of Feb 2012, and are disconnected
// static const int MIN_PROTO_VERSION = 209; //old
static const int MIN_PROTO_VERSION = 70200; //new

// nTime field added to CAddress, starting with this version;
// if possible, avoid requesting addresses nodes older than this
// static const int CADDR_TIME_VERSION = 31402; // old
static const int CADDR_TIME_VERSION = 70201; // new

// only request blocks from nodes outside this range of versions
// static const int NOBLKS_VERSION_START = 32000; //old
// static const int NOBLKS_VERSION_END = 32400; //old

static const int NOBLKS_VERSION_START = 31401; //new
static const int NOBLKS_VERSION_END = 70199; //new

// BIP 0031, pong message, is enabled for all versions AFTER this one
static const int BIP0031_VERSION = 60000;

// "mempool" command, enhanced "getdata" behavior starts with this version:
static const int MEMPOOL_GD_VERSION = 60002;

#endif
