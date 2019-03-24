// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "AddressChecksum.h"

#include "../Hash.h"
#include "../HexCoding.h"
#include <cctype>

using namespace TW;
using namespace TW::Ethereum;

std::string Ethereum::checksumed(const Address& address, TWEthereumChecksumType type) {
    const auto addressString = hex(address.bytes);
    const auto hash = hex(Hash::keccak256(addressString));

    std::string string = "0x";
    for (auto i = 0; i < std::min(addressString.size(), hash.size()); i += 1) {
        const auto a = addressString[i];
        const auto h = hash[i];
        if (a >= '0' && a <= 9) {
            string.push_back(a);
        } else if ((h >= '8' && h <= '9') || (h >= 'a' && h <= 'f')) {
            switch (type) {
                case TWEIP55:
                    string.push_back(toupper(a));
                    break;
                case TWWanchain:
                    string.push_back(tolower(a));
                    break;
            }
        } else {
            switch (type) {
                case TWEIP55:
                    string.push_back(tolower(a));
                    break;
                case TWWanchain:
                    string.push_back(toupper(a));
                    break;
            }
        }
    }

    return string;
}

