/* ScummVM Tools
 * Copyright (C) 2010 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "disassembler.h"
#include "engine.h"
#include <iostream>
#include <boost/format.hpp>

struct FunctionData {
  std::string _name;
	std::string _metadata;
};

static FunctionData kyra2FuncDesc[] = {
	// 0x00
	{ "setCharacterFacingRefresh", "" },
	{ "setCharacterPos", "" },
	{ "defineObject", "" },
	{ "refreshCharacter", "" },
	// 0x04
	{ "getCharacterX", "" },
	{ "getCharacterY", "" },
	{ "getCharacterFacing", "" },
	{ "getCharacterScene", "" },
	// 0x08
	{ "setSceneComment", "" },
	{ "", "" },
	{ "", "" },
	{ "setCharacterAnimFrame", "" },
	// 0x0c
	{ "setCharacterFacingOverwrite", "" },
	{ "trySceneChange", "" },
	{ "moveCharacter", "" },
	{ "customCharacterChat", "" },
	// 0x10
	{ "soundFadeOut", "" },
	{ "showChapterMessage", "" },
	{ "restoreTalkTextMessageBkgd", "" },
	{ "", "" },
	// 0x14
	{ "wsaClose", "" },
	{ "backUpScreen", "" },
	{ "restoreScreen", "" },
	{ "displayWsaFrame", "" },
	// 0x18
	{ "displayWsaSequentialFramesLooping", "" },
	{ "wsaOpen", "" },
	{ "displayWsaSequentialFrames", "" },
	{ "displayWsaSequence", "" },
	// 0x1c
	{ "addItemToInventory", "" },
	{ "drawShape", "" },
	{ "addItemToCurScene", "" },
	{ "dummy1F", "" },	// the original used this opcode to limit the mouse range temporary,
						// since that is of no use and not really important we just use a dummy here
	// 0x20
	{ "checkForItem", "" },
	{ "loadSoundFile", "" },
	{ "removeSlotFromInventory", "" },
	{ "defineItem", "" },
	// 0x24
	{ "removeItemFromInventory", "" },
	{ "countItemInInventory", "" },
	{ "countItemsInScene", "" },
	{ "queryGameFlag", "" },
	// 0x28
	{ "resetGameFlag", "" },
	{ "setGameFlag", "" },
	{ "setHandItem", "" },
	{ "removeHandItem", "" },
	// 0x2c
	{ "getMouseState", "" },
	{ "hideMouse", "" },
	{ "addSpecialExit", "" },
	{ "setMousePos", "" },
	// 0x30
	{ "showMouse", "" },
	{ "", "" },
	{ "wipeDownMouseItem", "" },
	{ "getElapsedSecs", "" },
	// 0x34
	{ "getTimerDelay", "" },
	{ "playSoundEffect", "" },
	{ "delaySecs", "" },
	{ "delay", "" },
	// 0x38
	{ "dummy38", "" },
	{ "setTimerDelay", "" },
	{ "setScaleTableItem", "" },
	{ "setDrawLayerTableItem", "" },
	// 0x3c
	{ "setCharPalEntry", "" },
	{ "loadZShapes", "" },
	{ "drawSceneShape", "" },
	{ "drawSceneShapeOnPage", "" },
	// 0x40
	{ "disableAnimObject", "" },
	{ "enableAnimObject", "" },
	{ "dummy42", "" },
	{ "loadPalette384", "" },
	// 0x44
	{ "setPalette384", "" },
	{ "restoreBackBuffer", "" },
	{ "backUpInventoryGfx", "" },
	{ "disableSceneAnim", "" },
	// 0x48
	{ "enableSceneAnim", "" },
	{ "restoreInventoryGfx", "" },
	{ "setSceneAnimPos2", "" },
	{ "update", "" },
	// 0x4c
	{ "", "" },
	{ "fadeScenePal", "" },
	{ "dummy4E", "" },
	{ "dummy4F", "" },
	// 0x50
	{ "enterNewScene", "" },
	{ "switchScene", "" },
	{ "getShapeFlag1", "" },
	{ "setPathfinderFlag", "" },
	// 0x54
	{ "getSceneExitToFacing", "" },
	{ "setLayerFlag", "" },
	{ "setZanthiaPos", "" },
	{ "loadMusicTrack", "" },
	// 0x58
	{ "playWanderScoreViaMap", "" },
	{ "playSoundEffect", "" },
	{ "setSceneAnimPos", "" },
	{ "blockInWalkableRegion", "" },
	// 0x5c
	{ "blockOutWalkableRegion", "" },
	{ "", "" },
	{ "setCauldronState", "" },
	{ "showItemString", "" },
	// 0x60
	{ "getRand", "" },
	{ "isAnySoundPlaying", "" },
	{ "setDeathHandler", "" },
	{ "setDrawNoShapeFlag", "" },
	// 0x64
	{ "setRunFlag", "" },
	{ "showLetter", "" },
	{ "", "" },
	{ "fillRect", "" },
	// 0x68
	{ "", "" },
	{ "", "" },
	{ "playFireflyScore", "" },
	{ "waitForConfirmationClick", "" },
	// 0x6c
	{ "encodeShape", "" },
	{ "defineRoomEntrance", "" },
	{ "runAnimationScript", "" },
	{ "setSpecialSceneScriptRunTime", "" },
	// 0x70
	{ "defineSceneAnim", "" },
	{ "updateSceneAnim", "" },
	{ "updateSceneAnim", "" },
	{ "addToSceneAnimPosAndUpdate", "" },
	// 0x74
	{ "useItemOnMainChar", "" },
	{ "startDialogue", "" },
	{ "randomSceneChat", "" },
	{ "setDlgIndex", "" },
	// 0x78
	{ "getDlgIndex", "" },
	{ "defineScene", "" },
	{ "addCauldronStateTableEntry", "" },
	{ "setCountDown", "" },
	// 0x7c
	{ "getCountDown", "" },
	{ "dummy7D", "" },
	{ "dummy7E", "" },
	{ "pressColorKey", "" },
	// 0x80
	{ "objectChat", "" },
	{ "changeChapter", "" },
	{ "getColorCodeFlag1", "" },
	{ "setColorCodeFlag1", "" },
	// 0x84
	{ "getColorCodeFlag2", "" },
	{ "setColorCodeFlag2", "" },
	{ "getColorCodeValue", "" },
	{ "setColorCodeValue", "" },
	// 0x88
	{ "countItemInstances", "" },
	{ "removeItemFromScene", "" },
	{ "initObject", "" },
	{ "npcChat", "" },
	// 0x8c
	{ "deinitObject", "" },
	{ "playTimSequence", "" },
	{ "makeBookOrCauldronAppear", "" },
	{ "setSpecialSceneScriptState", "" },
	// 0x90
	{ "clearSpecialSceneScriptState", "" },
	{ "querySpecialSceneScriptState", "" },
	{ "resetInputColorCode", "" },
	{ "setHiddenItemsEntry", "" },
	// 0x94
	{ "getHiddenItemsEntry", "" },
	{ "mushroomEffect", "" },
	{ "wsaClose", "" },
	{ "meanWhileScene", "" },
	// 0x98
	{ "customChat", "" },
	{ "customChatFinish", "" },
	{ "setupSceneAnimation", "" },
	{ "stopSceneAnimation", "" },
	// 0x9c
	{ "disableTimer", "" },
	{ "enableTimer", "" },
	{ "setTimerCountdown", "" },
	{ "processPaletteIndex", "" },
	// 0xa0
	{ "updateTwoSceneAnims", "" },
	{ "getRainbowRoomData", "" },
	{ "drawSceneShapeEx", "" },
	{ "midiSoundFadeout", "" },
	// 0xa4
	{ "getSfxDriver", "" },
	{ "getVocSupport", "" },
	{ "getMusicDriver", "" },
	{ "setVocHigh", "" },
	// 0xa8
	{ "getVocHigh", "" },
	{ "zanthiaChat", "" },
	{ "isVoiceEnabled", "" },
	{ "isVoicePlaying", "" },
	// 0xac
	{ "stopVoicePlaying", "" },
	{ "getGameLanguage", "" },
	{ "demoFinale", "" },
	{ "dummyAF", "" }
};

IFFChunk::IFFChunk() {
	_data = NULL;
}

Kyra::Disassembler::Disassembler(Engine *engine) : ::Disassembler(), _engine(engine) {
}

Kyra::Disassembler::~Disassembler() {
	if (_textChunk._data)
		delete[] _textChunk._data;
	if (_ordrChunk._data)
		delete[] _ordrChunk._data;
	if (_dataChunk._data)
		delete[] _dataChunk._data;
}

void Kyra::Disassembler::doDisassemble() throw(UnknownOpcodeException) {
	// Load data
	IFF_ID id;
	id = _f.readUint32BE();
	if (id != MKID_BE('FORM')) {
		std::cerr << boost::format("ERROR: Unexpected IFF magic number 0x%08X (expected 0x%08X)!\n") % id % MKID_BE('FORM');
		return;
	}
	_f.readUint32BE(); // Skip file length
	_formType = _f.readUint32BE();
	if (_formType != MKID_BE('EMC2')) {
		std::cerr << boost::format("ERROR: Unexpected file type 0x%08X (expected 0x%08X)!\n") % _formType % MKID_BE('EMC2');
		return;
	}

	// Read chunks into memory
	do {
		IFFChunk temp;
		temp._chunkType = _f.readUint32BE();
		temp._size = _f.readUint32BE();
		temp._data = new uint8[temp._size];
		_f.read_throwsOnError(temp._data, temp._size);
		switch (temp._chunkType) {
		case MKID_BE('TEXT'):
			_textChunk = temp;
			break;
		case MKID_BE('ORDR'):
			_ordrChunk = temp;
			break;
		case MKID_BE('DATA'):
			_dataChunk = temp;
			break;
		default:
			std::cerr << boost::format("ERROR: Unexpected chunk type 0x%08X!\n") % temp._chunkType;
			delete [] temp._data;
			return;
		}
		if (temp._size % 2 != 0) // Skip padding byte
			_f.readByte();
	} while (_f.pos() != (int)_f.size());

	// Extract strings from TEXT chunk
	uint16 minTextOffset = 0xFFFF;
	for (uint16 i = 0; i < _textChunk._size / 2; ++i) {
		if (minTextOffset > READ_BE_UINT16(&((uint16 *)_textChunk._data)[i])) {
			minTextOffset = READ_BE_UINT16(&((uint16 *)_textChunk._data)[i]);
		}
		if (minTextOffset <= i*2)
			break;
	}
	uint16 numStrings = minTextOffset / 2;
#define posString(x) (char*)&_textChunk._data[READ_BE_UINT16(&((uint16 *)_textChunk._data)[(x)])]
	for (uint16 i = 0; i < numStrings; ++i) {
		_engine->_textStrings.push_back(posString(i));
	}
#undef posString

	// Disassemble
	uint16 numInsts = _dataChunk._size / 2;
	for (uint16 i = 0; i < numInsts; ++i) {
		uint16 address = i*2;
		uint16 code = READ_BE_UINT16(&((uint16 *)_dataChunk._data)[i]);
		int16 opcode = (code >> 8) & 0x1F;
		int16 parameter;

		if (code & 0x8000) {
			opcode = 0;
			parameter = code & 0x7FFF;
		} else if (code & 0x4000) {
			parameter = (int8)(code);
		} else if (code & 0x2000) {
			i++;
			parameter = READ_BE_UINT16(&((uint16 *)_dataChunk._data)[i]);
		} else {
			parameter = 0;
		}

#define ADD_INST _insts.push_back(Instruction());
#define LAST_INST (_insts[_insts.size()-1])
#define OPCODE_MD(name, category, stackChange, hasParam, codeGenData) \
		ADD_INST; \
		LAST_INST._opcode = opcode; \
		LAST_INST._address = address; \
		LAST_INST._stackChange = stackChange; \
		LAST_INST._name = name; \
		LAST_INST._type = category; \
		LAST_INST._codeGenData = codeGenData; \
		if (hasParam) { \
			Parameter p; \
			p._type = kShort; \
			p._value = parameter; \
			LAST_INST._params.push_back(p);\
		}
#define OPCODE(name, category, stackChange, hasParam) OPCODE_MD(name, category, stackChange, hasParam, "");

		// TOOD: Add metadata where applicable
		switch(opcode) {
		case 0:
			parameter *=2;
			OPCODE("jumpTo", kJump, 0, true);
			break;
		case 1:
			OPCODE("setRetValue", kStore, 0, true);
			break;
		case 2:
			if (parameter == 0) {
				OPCODE("pushRet", kLoad, 1, false);
			} else if (parameter == 1) {
				OPCODE("pushPos", kSpecial, 2, false); // Sets up function call?
			} else {
				// Error: invalid parameter halts execution
			}
			break;
		case 3:
		case 4:
			OPCODE("push", kLoad, 1, true);
			break;
		case 5:
			OPCODE("pushVar", kLoad, 1, true);
			break;
		case 6:
			OPCODE("pushBPNeg", kLoad, 1, true);
			break;
		case 7:
			OPCODE("pushBPAdd", kLoad, 1, true);
			break;
		case 8:
			if (parameter == 0) {
				OPCODE("popRet", kStore, -1, false);
			} else if (parameter == 1) {
				OPCODE("popPos", kSpecial, -2, false); // Returns from function call?
			} else {
				// Error: invalid parameter halts execution
			}
			break;
		case 9:
			OPCODE("popVar", kStore, 1, true);
			break;
		case 10:
			OPCODE("popBPNeg", kStore, 1, true);
			break;
		case 11:
			OPCODE("popBPAdd", kStore, 1, true);
			break;
		case 12:
			OPCODE("addSP", kStack, -parameter, true);
			break;
		case 13:
			OPCODE("subSP", kStack, parameter, true);
			break;
		case 14:
			parameter = (uint8)parameter;
			if ((uint16)parameter >= sizeof(kyra2FuncDesc) / sizeof(kyra2FuncDesc[0]) || kyra2FuncDesc[parameter]._name.length() == 0) {
				// Error: unknown function
			}
			OPCODE_MD(kyra2FuncDesc[parameter]._name, kSpecial, 0, false, kyra2FuncDesc[parameter]._metadata)
			break;
		case 15:
			parameter *=2;
			OPCODE("ifNotJmp", kCondJump, -1, true);
			break;
		case 16:
			if (parameter == 0) {
				OPCODE_MD("boolCast", kUnaryOp, 0, false, "(bool)");
			} else if (parameter == 1) {
				OPCODE_MD("arithmeticNegate", kUnaryOp, 0, false,"-");
			} else if (parameter == 2) {
				OPCODE_MD("bitwiseNegate", kUnaryOp, 0, false, "~");
			} else {
				// Error: invalid parameter halts execution
			}
			break;
		case 17:
			switch (parameter) {
				case 0:
					OPCODE_MD("eval_band", kBinaryOp, -1, false, "&&");
					break;
				case 1:
					OPCODE_MD("eval_bor", kBinaryOp, -1, false, "||");
					break;
				case 2:
					OPCODE_MD("eval_eq", kBinaryOp, -1, false, "==");
					break;
				case 3:
					OPCODE_MD("eval_neq", kBinaryOp, -1, false, "!=");
					break;
				case 4:
					OPCODE_MD("eval_leq", kBinaryOp, -1, false, "<=");
					break;
				case 5:
					OPCODE_MD("eval_lt", kBinaryOp, -1, false, "<");
					break;
				case 6:
					OPCODE_MD("eval_geq", kBinaryOp, -1, false, ">=");
					break;
				case 7:
					OPCODE_MD("eval_gt", kBinaryOp, -1, false, ">");
					break;
				case 8:
					OPCODE_MD("eval_add", kBinaryOp, -1, false, "+");
					break;
				case 9:
					OPCODE_MD("eval_sub", kBinaryOp, -1, false, "-");
					break;
				case 10:
					OPCODE_MD("eval_mult", kBinaryOp, -1, false, "*");
					break;
				case 11:
					OPCODE_MD("eval_div", kBinaryOp, -1, false, "/");
					break;
				case 12:
					OPCODE_MD("eval_shr", kBinaryOp, -1, false, ">>");
					break;
				case 13:
					OPCODE_MD("eval_shl", kBinaryOp, -1, false, "<<");
					break;
				case 14:
					OPCODE_MD("eval_land", kBinaryOp, -1, false, "&");
					break;
				case 15:
					OPCODE_MD("eval_lor", kBinaryOp, -1, false, "|");
					break;
				case 16:
					OPCODE_MD("eval_mod", kBinaryOp, -1, false, "%");
					break;
				case 17:
					OPCODE_MD("eval_xor", kBinaryOp, -1, false, "^");
					break;
				default:
					// Error: Invalid parameter
					break;
			}
			break;
		case 18:
			OPCODE("setRetAndJmp", kSpecial, -2, false); // Returns from function call?
			break;
		default:
			throw UnknownOpcodeException(i*2, code);
		}
#undef OPCODE
#undef OPCODE_MD
#undef LAST_INST
#undef ADD_INST
	}
}
