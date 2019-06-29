#ifndef BITCOIN_TICKET_H
#define BITCOIN_TICKET_H

#include <script/script.h>
#include <pubkey.h>
#include <script/script.h>

CScript GenerateTicketScript(const CPubKey keyid, const int lockHeight);

bool GetPublicKeyFromScript(const CScript script, CPubKey& pubkey);

class CTicket {
public:
    static const int32_t VERSION = 1;

    enum CTicketState {
        IMMATURATE = 0,
        USEABLE,
        OVERDUE
    };

    CTicket(const uint256& txid, const uint32_t n, const CScript& redeemScript, const CScript &scriptPubkey);

    CTicket() = default;
    ~CTicket() = default;

    CTicketState State() const;

    const uint32_t LockTime()const;

    CPubKey PublicKey() const;

    bool Invalid() const;
private:
    uint256 txid;
    uint32_t n;
    CScript redeemScript;
    CScript scriptPubkey;
};

typedef std::shared_ptr<const CTicket> CTicketRef;
#endif
