/* Copyright 2012 exMULTI, Inc.
 * Distributed under the MIT/X11 software license, see the accompanying
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.
 */
#include "picocoin-config.h"

#include <ccoin/script.h>
#include <ccoin/util.h>

static const char *opnames[256] = {
	[ccoin_OP_0] = "ccoin_OP_0",
	[ccoin_OP_PUSHDATA1] = "ccoin_OP_PUSHDATA1",
	[ccoin_OP_PUSHDATA2] = "ccoin_OP_PUSHDATA2",
	[ccoin_OP_PUSHDATA4] = "ccoin_OP_PUSHDATA4",
	[ccoin_OP_1NEGATE] = "ccoin_OP_1NEGATE",
	[ccoin_OP_RESERVED] = "ccoin_OP_RESERVED",
	[ccoin_OP_1] = "ccoin_OP_1",
	[ccoin_OP_2] = "ccoin_OP_2",
	[ccoin_OP_3] = "ccoin_OP_3",
	[ccoin_OP_4] = "ccoin_OP_4",
	[ccoin_OP_5] = "ccoin_OP_5",
	[ccoin_OP_6] = "ccoin_OP_6",
	[ccoin_OP_7] = "ccoin_OP_7",
	[ccoin_OP_8] = "ccoin_OP_8",
	[ccoin_OP_9] = "ccoin_OP_9",
	[ccoin_OP_10] = "ccoin_OP_10",
	[ccoin_OP_11] = "ccoin_OP_11",
	[ccoin_OP_12] = "ccoin_OP_12",
	[ccoin_OP_13] = "ccoin_OP_13",
	[ccoin_OP_14] = "ccoin_OP_14",
	[ccoin_OP_15] = "ccoin_OP_15",
	[ccoin_OP_16] = "ccoin_OP_16",

	[ccoin_OP_NOP] = "ccoin_OP_NOP",
	[ccoin_OP_VER] = "ccoin_OP_VER",
	[ccoin_OP_IF] = "ccoin_OP_IF",
	[ccoin_OP_NOTIF] = "ccoin_OP_NOTIF",
	[ccoin_OP_VERIF] = "ccoin_OP_VERIF",
	[ccoin_OP_VERNOTIF] = "ccoin_OP_VERNOTIF",
	[ccoin_OP_ELSE] = "ccoin_OP_ELSE",
	[ccoin_OP_ENDIF] = "ccoin_OP_ENDIF",
	[ccoin_OP_VERIFY] = "ccoin_OP_VERIFY",
	[ccoin_OP_RETURN] = "ccoin_OP_RETURN",

	[ccoin_OP_TOALTSTACK] = "ccoin_OP_TOALTSTACK",
	[ccoin_OP_FROMALTSTACK] = "ccoin_OP_FROMALTSTACK",
	[ccoin_OP_2DROP] = "ccoin_OP_2DROP",
	[ccoin_OP_2DUP] = "ccoin_OP_2DUP",
	[ccoin_OP_3DUP] = "ccoin_OP_3DUP",
	[ccoin_OP_2OVER] = "ccoin_OP_2OVER",
	[ccoin_OP_2ROT] = "ccoin_OP_2ROT",
	[ccoin_OP_2SWAP] = "ccoin_OP_2SWAP",
	[ccoin_OP_IFDUP] = "ccoin_OP_IFDUP",
	[ccoin_OP_DEPTH] = "ccoin_OP_DEPTH",
	[ccoin_OP_DROP] = "ccoin_OP_DROP",
	[ccoin_OP_DUP] = "ccoin_OP_DUP",
	[ccoin_OP_NIP] = "ccoin_OP_NIP",
	[ccoin_OP_OVER] = "ccoin_OP_OVER",
	[ccoin_OP_PICK] = "ccoin_OP_PICK",
	[ccoin_OP_ROLL] = "ccoin_OP_ROLL",
	[ccoin_OP_ROT] = "ccoin_OP_ROT",
	[ccoin_OP_SWAP] = "ccoin_OP_SWAP",
	[ccoin_OP_TUCK] = "ccoin_OP_TUCK",

	[ccoin_OP_CAT] = "ccoin_OP_CAT",
	[ccoin_OP_SUBSTR] = "ccoin_OP_SUBSTR",
	[ccoin_OP_LEFT] = "ccoin_OP_LEFT",
	[ccoin_OP_RIGHT] = "ccoin_OP_RIGHT",
	[ccoin_OP_SIZE] = "ccoin_OP_SIZE",

	[ccoin_OP_INVERT] = "ccoin_OP_INVERT",
	[ccoin_OP_AND] = "ccoin_OP_AND",
	[ccoin_OP_OR] = "ccoin_OP_OR",
	[ccoin_OP_XOR] = "ccoin_OP_XOR",
	[ccoin_OP_EQUAL] = "ccoin_OP_EQUAL",
	[ccoin_OP_EQUALVERIFY] = "ccoin_OP_EQUALVERIFY",
	[ccoin_OP_RESERVED1] = "ccoin_OP_RESERVED1",
	[ccoin_OP_RESERVED2] = "ccoin_OP_RESERVED2",

	[ccoin_OP_1ADD] = "ccoin_OP_1ADD",
	[ccoin_OP_1SUB] = "ccoin_OP_1SUB",
	[ccoin_OP_2MUL] = "ccoin_OP_2MUL",
	[ccoin_OP_2DIV] = "ccoin_OP_2DIV",
	[ccoin_OP_NEGATE] = "ccoin_OP_NEGATE",
	[ccoin_OP_ABS] = "ccoin_OP_ABS",
	[ccoin_OP_NOT] = "ccoin_OP_NOT",
	[ccoin_OP_0NOTEQUAL] = "ccoin_OP_0NOTEQUAL",

	[ccoin_OP_ADD] = "ccoin_OP_ADD",
	[ccoin_OP_SUB] = "ccoin_OP_SUB",
	[ccoin_OP_MUL] = "ccoin_OP_MUL",
	[ccoin_OP_DIV] = "ccoin_OP_DIV",
	[ccoin_OP_MOD] = "ccoin_OP_MOD",
	[ccoin_OP_LSHIFT] = "ccoin_OP_LSHIFT",
	[ccoin_OP_RSHIFT] = "ccoin_OP_RSHIFT",

	[ccoin_OP_BOOLAND] = "ccoin_OP_BOOLAND",
	[ccoin_OP_BOOLOR] = "ccoin_OP_BOOLOR",
	[ccoin_OP_NUMEQUAL] = "ccoin_OP_NUMEQUAL",
	[ccoin_OP_NUMEQUALVERIFY] = "ccoin_OP_NUMEQUALVERIFY",
	[ccoin_OP_NUMNOTEQUAL] = "ccoin_OP_NUMNOTEQUAL",
	[ccoin_OP_LESSTHAN] = "ccoin_OP_LESSTHAN",
	[ccoin_OP_GREATERTHAN] = "ccoin_OP_GREATERTHAN",
	[ccoin_OP_LESSTHANOREQUAL] = "ccoin_OP_LESSTHANOREQUAL",
	[ccoin_OP_GREATERTHANOREQUAL] = "ccoin_OP_GREATERTHANOREQUAL",
	[ccoin_OP_MIN] = "ccoin_OP_MIN",
	[ccoin_OP_MAX] = "ccoin_OP_MAX",

	[ccoin_OP_WITHIN] = "ccoin_OP_WITHIN",

	[ccoin_OP_RIPEMD160] = "ccoin_OP_RIPEMD160",
	[ccoin_OP_SHA1] = "ccoin_OP_SHA1",
	[ccoin_OP_SHA256] = "ccoin_OP_SHA256",
	[ccoin_OP_HASH160] = "ccoin_OP_HASH160",
	[ccoin_OP_HASH256] = "ccoin_OP_HASH256",
	[ccoin_OP_CODESEPARATOR] = "ccoin_OP_CODESEPARATOR",
	[ccoin_OP_CHECKSIG] = "ccoin_OP_CHECKSIG",
	[ccoin_OP_CHECKSIGVERIFY] = "ccoin_OP_CHECKSIGVERIFY",
	[ccoin_OP_CHECKMULTISIG] = "ccoin_OP_CHECKMULTISIG",
	[ccoin_OP_CHECKMULTISIGVERIFY] = "ccoin_OP_CHECKMULTISIGVERIFY",

	[ccoin_OP_NOP1] = "ccoin_OP_NOP1",
	[ccoin_OP_CHECKLOCKTIMEVERIFY] = "ccoin_OP_CHECKLOCKTIMEVERIFY",
	[ccoin_OP_CHECKSEQUENCEVERIFY] = "ccoin_OP_CHECKSEQUENCEVERIFY",
	[ccoin_OP_NOP4] = "ccoin_OP_NOP4",
	[ccoin_OP_NOP5] = "ccoin_OP_NOP5",
	[ccoin_OP_NOP6] = "ccoin_OP_NOP6",
	[ccoin_OP_NOP7] = "ccoin_OP_NOP7",
	[ccoin_OP_NOP8] = "ccoin_OP_NOP8",
	[ccoin_OP_NOP9] = "ccoin_OP_NOP9",
	[ccoin_OP_NOP10] = "ccoin_OP_NOP10",



	[ccoin_OP_SMALLINTEGER] = "ccoin_OP_SMALLINTEGER",
	[ccoin_OP_PUBKEYS] = "ccoin_OP_PUBKEYS",
	[ccoin_OP_PUBKEYHASH] = "ccoin_OP_PUBKEYHASH",
	[ccoin_OP_PUBKEY] = "ccoin_OP_PUBKEY",
};

const char *GetOpName(enum opcodetype opcode_)
{
	int idx = (int) opcode_;

	if (idx >= 0 && idx < 256) {
		const char *name = opnames[idx];
		if (name)
			return name;
	}

	return "<unknown>";
}

enum opcodetype GetOpType(const char *opname)
{
	unsigned int i;
	char tmpname[64];

	for (i = 0; i < ARRAY_SIZE(opnames); i++) {
		if (opnames[i]) {
			if (!strcmp(opname, opnames[i]))
				return (enum opcodetype) i;

			strcpy(tmpname, "ccoin_OP_");
			strcat(tmpname, opname);
			if (!strcmp(tmpname, opnames[i]))
				return (enum opcodetype) i;
		}
	}

	return ccoin_OP_INVALIDOPCODE;
}

