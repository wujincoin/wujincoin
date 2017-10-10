// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa0;
        pchMessageStart[1] = 0xf5;
        pchMessageStart[2] = 0x2d;
        pchMessageStart[3] = 0xc5;
        vAlertPubKey = ParseHex("0486bce1bac0d543f104cbff2bd23680056a3b9ea05e1137d2ff90eeb5e08472eb500322593a2cb06fbf8297d7beb6cd30cb90f98153b5b7cce1493749e41e0284");
        nDefaultPort = 34561;
        nRPCPort = 34562;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 23);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "WuJinCoin";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1506537324, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1506537324;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 33456;

        hashGenesisBlock = genesis.GetHash();
		if (false ) {
		// This will figure out a valid hash and Nonce if you're
		// creating a different genesis block:
	    uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
	    while (genesis.GetHash() > hashTarget)
	    {
	        ++genesis.nNonce;
	        if (genesis.nNonce == 0)
		        {
		            printf("NONCE WRAPPED, incrementing time");
		            ++genesis.nTime;
		        }
	         }
	   }

     /*    ofstream f;
        f.open("1.txt");
        f<<"Hash = "<<hashGenesisBlock.ToString()<<"\n";
        f<<"hashMerkleRoot = "<<genesis.hashMerkleRoot.ToString()<<"\n";
        f<<"nTime ="<<genesis.nTime<<"\n";
        f<<"nNonce ="<<genesis.nNonce<<"\n";
        f.close(); */
		
        assert(hashGenesisBlock == uint256("0x8258dd8357abefb356b12204320e122cd36977253c8c8a67d2a8eb7b261b0b07"));
        assert(genesis.hashMerkleRoot == uint256("0x37ffffe10ee72193ce02dfd3077fd8d3171dfdb92e2fae030ca2d2d66f49abe5"));

       
        vSeeds.push_back(CDNSSeedData("43.248.77.170", "43.248.77.170"));
        vSeeds.push_back(CDNSSeedData("43.248.102.104", "43.248.102.104"));
        vSeeds.push_back(CDNSSeedData("39.108.12.241", "39.108.12.241"));		

        base58Prefixes[PUBKEY_ADDRESS] = list_of(73);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(105);
        base58Prefixes[SECRET_KEY] =     list_of(153);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 100000;
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
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = 25714;
        nRPCPort = 25715;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 249563;		
		
        hashGenesisBlock = genesis.GetHash();
		if (false ) {
		// This will figure out a valid hash and Nonce if you're
		// creating a different genesis block:
	    uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
	    while (genesis.GetHash() > hashTarget)
	    {
	        ++genesis.nNonce;
	        if (genesis.nNonce == 0)
		        {
		            printf("NONCE WRAPPED, incrementing time");
		            ++genesis.nTime;
		        }
	         }
	   }
     /*    ofstream f;
        f.open("2.txt");
        f<<"Hash = "<<hashGenesisBlock.ToString()<<"\n";
        f<<"hashMerkleRoot = "<<genesis.hashMerkleRoot.ToString()<<"\n";
        f<<"nTime ="<<genesis.nTime<<"\n";
        f<<"nNonce ="<<genesis.nNonce<<"\n";
        f.close(); */

        assert(hashGenesisBlock == uint256("0xfbf12ea578c601c7234d33829e596cd599981460cf97ca3440149aea0f83f641"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
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
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1411111111;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
		if (false ) {
		// This will figure out a valid hash and Nonce if you're
		// creating a different genesis block:
	    uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
	    while (genesis.GetHash() > hashTarget)
	    {
	        ++genesis.nNonce;
	        if (genesis.nNonce == 0)
		        {
		            printf("NONCE WRAPPED, incrementing time");
		            ++genesis.nTime;
		        }
	         }
	   }
        hashGenesisBlock = genesis.GetHash();
		
/*         ofstream f;
        f.open("3.txt");
        f<<"Hash = "<<hashGenesisBlock.ToString()<<"\n";
        f<<"hashMerkleRoot = "<<genesis.hashMerkleRoot.ToString()<<"\n";
        f<<"nTime ="<<genesis.nTime<<"\n";
        f<<"nNonce ="<<genesis.nNonce<<"\n";
        f.close(); */
        assert(hashGenesisBlock == uint256("0x73a1c354b4166496de177941b405926b29f7612c719706041d6c9c0887953412"));

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