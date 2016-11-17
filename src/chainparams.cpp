// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The BitToken developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x57;
        pchMessageStart[1] = 0xab;
        pchMessageStart[2] = 0xdb;
        pchMessageStart[3] = 0x52;
        vAlertPubKey = ParseHex("0420dc5bb90a690c88f8cde7874097afd2c3cff74b3a14cb026df6af380ed61a0a1e257cac316c7bb29bab760630fb6427ee5d2ab8087985848e90043db3bed912");
        nDefaultPort = 8223;
        nRPCPort = 8224;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 32);
        nSubsidyHalvingInterval = 86400;
        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        // CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1471989007, nBits=1d00ffff, nNonce=0, vtx=1)
        //   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
        //     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
        //   vMerkleTree: 4a5e1e
        const char* pszTimestamp = "Zoo for Harambe pleads for no more memes";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 15 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1471989007;
        genesis.nBits    = 0x1d00ffff;
        genesis.nNonce   = 2082977434;

        hashGenesisBlock = genesis.GetHash();
                    
        if (false)
        {
            printf("Searching for genesis block...\n");
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            uint256 thash;
            
            CBigNum bnTarget;
            bnTarget.SetCompact(genesis.nBits);

            while(1)
            {
                thash=genesis.GetHash();
                if ((thash <= hashTarget) && (thash <= bnTarget.getuint256()) )
                    break;
                if ((genesis.nNonce & 0xFFF) == 0)
                {
                    printf("nonce %08X: hash = %s (target = %s)\n",genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                }
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time\n");
                    ++genesis.nTime;
                }
            }
            printf("genesis.nTime = %u \n",genesis.nTime);
            printf("genesis.nNonce = %u \n",genesis.nNonce);
            printf("min nBit: %08x\n", bnProofOfWorkLimit.GetCompact());
            printf("genesis.hashMerkleRoot = %s\n",genesis.hashMerkleRoot.ToString().c_str());
            printf("genesis.GetHash = %s\n",genesis.GetHash().ToString().c_str());
            exit(1);
        }
        
        assert(hashGenesisBlock == uint256("0x00000000f7af0d911d094e3583380dfe70a6fc911d69b97786f771344de03b6d"));
        assert(genesis.hashMerkleRoot == uint256("0x02de7740a170214d13cf36d601957fe91ccfaea9efb3f36670ab119fff0478dd"));

      //  vSeeds.push_back(CDNSSeedData("walletbuilders.com", "node.walletbuilders.com"));
		vSeeds.push_back(CDNSSeedData("212.91.189.164", "212.91.189.164"));
		
        base58Prefixes[PUBKEY_ADDRESS] = list_of(25);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
        base58Prefixes[SECRET_KEY] =     list_of(153);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64 nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x5d;
        pchMessageStart[1] = 0xe4;
        pchMessageStart[2] = 0x14;
        pchMessageStart[3] = 0x08;
        vAlertPubKey = ParseHex("04f6be90bae5b5a2185eacead7cb3fd0efe6dec58b9f59b2d7639093dd4405b146da0571c8c5df9b65e2eea9cade8c8a7efff31383bc34caba0ca370434eff1a6a");
        nDefaultPort = 18223;
        nRPCPort = 18224;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1471989007;
        genesis.nNonce = 2082977434;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000000f7af0d911d094e3583380dfe70a6fc911d69b97786f771344de03b6d"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xb1;
        pchMessageStart[1] = 0xe4;
        pchMessageStart[2] = 0x45;
        pchMessageStart[3] = 0xe8;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1471989007;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
