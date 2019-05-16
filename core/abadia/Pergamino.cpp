

// Pergamino.cpp
//
/////////////////////////////////////////////////////////////////////////////

#include <SDL_endian.h>
#include "../systems/cpc6128.h"
#include "../TimingHandler.h"

#include "Controles.h"
#include "Juego.h"
#include "Paleta.h"
#include "Pergamino.h"

using namespace Abadia;

// TODO Falta la Z mayúscula, pero creo que no se usa en los textos

const UINT8 Pergamino::char27[] = { // '
0x10, 
0x11, 0x20, 
0x21, 0x31, 0x40, 0xf4
};

const UINT8 Pergamino::char42[] = { // B
0x27, 0x36, 0x37, 0x46, 0x47, 0x56, 0x57, 0x66, 0x67, 0x76, 0x77, 0x86, 0x87, 0x95, 0x96, 0x20, 0x11, 0x02, 0x12, 0x03, 0x13, 0x23, 0x04, 0x14, 0x24, 0x05, 0x15, 0x25, 0x16, 0x18, 0x19, 0x0a, 0x1a, 0x0b, 0x1b, 0x2b, 0x0c, 0x1c, 0x1d, 0x2d, 0x2c, 0x3c, 0x4b, 0x5a, 0x6b, 0x6c, 0x7c, 0x7d, 0x8c, 0x8d, 0x9c, 0x9d, 0xac, 0xad, 0xbb, 0xba, 0xa9, 0xb9, 0xc9, 0xd8, 0xc8, 0xa8, 0xb8, 0xa7, 0xb7, 0xc7, 0xc6, 0xb6, 0xa6, 0xa5, 0xb5, 0xa4, 0xb4, 0xb3, 0xc3, 0xc2, 0xd1, 0x49, 0x59, 0x69, 0x79, 0x7a, 0x7b, 0x89, 0x99, 0x9a, 0x9b, 0x43, 0x44, 0x53, 0x54, 0x64, 0x63, 0x73, 0x74, 0x84, 0x83, 0x93, 0x62, 0x72, 0x71, 0x61, 0x70, 0x80, 0xff
};
// La F se ve muy fea, pero sale así en el remake PC de Antonio Giner
// TODO: quitar una línea vertical pegada a la derecha del caracter
// que le hace parecer una A
const UINT8 Pergamino::char46[] = { // F
0x22, 0x13, 0x04, 0x14, 0x05, 0x15, 0x16, 0x06, 0x07, 0x17, 0x18, 0x08, 0x09, 0x1a, 0x1b, 0x0b, 0x0c, 0x1c, 0x1d, 0x1e, 0x0e, 0x27, 0x29, 0x2a, 0x36, 0x37, 0x39, 0x3a, 0x46, 0x47, 0x49, 0x4a, 0x56, 0x57, 0x59, 0x5a, 0x66, 0x67, 0x69, 0x6a, 0x76, 0x77, 0x79, 0x7a, 0x86, 0x87, 0x89, 0x8a, 0x96, 0x97, 0x99, 0x9a, 0xa6, 0xaa, 0xa9, 0xb9, 0xc8, 0xc7, 0xd6, 0xc6, 0xd5, 0xc5, 0xb5, 0xb4, 0xc4, 0xc3, 0xb3, 0xa3, 0xa2, 0xb2, 0xb1, 0xc0, 0x73, 0x63, 0x54, 0x64, 0x45, 0x55, 0x65, 0x6b, 0x5b, 0x5c, 0x6c, 0x6d, 0x5d, 0x2d, 0x3d, 0x4d, 0x7d, 0x8d, 0x9d, 0xad, 0xbd, 0xff
};
const UINT8 Pergamino::char49[] = { // I
0x10, 0x11, 0x21, 0x12, 0x22, 0x23, 0x24, 0x15, 0x25, 0x16, 0x32, 0x33, 0x42, 0x43, 0x52, 0x62, 0x53, 0x63, 0x72, 0x73, 0x82, 0x83, 0x92, 0x93, 0xa2, 0xa3, 0xb2, 0xb3, 0xc3, 0xc2, 0xd2, 0xc1, 0xd1, 0xd0, 0x34, 0x35, 0x45, 0x55, 0x65, 0x85, 0x75, 0x95, 0xa5, 0xb4, 0xb5, 0xc4, 0xd4, 0xc5, 0xd5, 0xd6, 0x80, 0x70, 0x71, 0x61, 0x66, 0x76, 0xf8
};
const UINT8 Pergamino::char4B[] = { // K
0x20, 0x11, 0x02, 0x12, 0x03, 0x13, 0x23, 0x04, 0x14, 0x24, 0x15, 0x25, 0x16, 0x27, 0x37, 0x36, 0x46, 0x47, 0x57, 0x56, 0x66, 0x67, 0x77, 0x76, 0x86, 0x87, 0x96, 0x95, 0xa5, 0xa4, 0xb4, 0xb3, 0xc2, 0xd1, 0xa7, 0xa6, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xc8, 0xc7, 0xc6, 0xd7, 0x0c, 0x1c, 0x1b, 0x2c, 0x2b, 0x3a, 0x49, 0x58, 0x68, 0x69, 0x6a, 0x79, 0x7a, 0x7b, 0x89, 0x8a, 0x8b, 0x9a, 0x9b, 0x9c, 0xaa, 0xab, 0xac, 0xbb, 0xbd, 0xbc, 0xcb, 0xcc, 0xcd, 0xdc, 0x43, 0x44, 0x54, 0x53, 0x64, 0x63, 0x62, 0x74, 0x84, 0x93, 0x83, 0x73, 0x72, 0x71, 0x80, 0xff
};
const UINT8 Pergamino::char4E[] = { // N
0xd0, 0xc1, 0xb2, 0xb3, 0xa3, 0xa4, 0xb4, 0xc4, 0xd5, 0xc5, 0xb5, 0xa5, 0xb6, 0xc6
, 0xb7, 0x93, 0x83, 0x73, 0x63, 0x53, 0x43, 0x33, 0x23, 0x30, 0x21, 0x11, 0x12, 0x02, 0x03, 0x13
, 0x04, 0x14, 0x24, 0x35, 0x25, 0x15, 0x05, 0x16, 0x26, 0x36, 0x56, 0x46, 0x27, 0x37, 0x47, 0x48
, 0x57, 0x67, 0x58, 0x59, 0x69, 0x68, 0x78, 0x88, 0x79, 0x7a, 0x8a, 0x89, 0x99, 0xa9, 0x9a, 0xaa
, 0x9b, 0xab, 0xba, 0xbb, 0xcb, 0xdc, 0xcc, 0xbc, 0xac, 0x9c, 0x8c, 0x7c, 0x6c, 0x5c, 0x4c, 0x3c
, 0x1c, 0x2c, 0x2b, 0x1b, 0x1a, 0x0b, 0x0c, 0x1d, 0x71, 0x61, 0x62, 0x52, 0x74, 0x75, 0x76, 0x77
, 0x5a, 0x5b, 0xff
};
const UINT8 Pergamino::char51[] = { // Q
0x04, 0x03, 0x13, 0x12, 0x22, 0x21, 0x32, 0x31, 0x40, 0x41, 0x42, 0x52, 0x51, 0x50, 0x60, 0x61, 0x62, 0x72, 0x71, 0x70, 0x80, 0x81, 0x82, 0x92, 0x91, 0x90, 0xa1, 0xa2, 0xa3, 0xb2, 0xb3, 0xc4, 0xc5, 0xc6, 0xc7, 0xb8, 0xb9, 0xba, 0xaa, 0xab, 0x9b, 0x9c, 0x8c, 0x8b, 0x7b, 0x7c, 0x7d, 0x6d, 0x6c, 0x6b, 0x5b, 0x5c, 0x5d, 0x4d, 0x4c, 0x4b, 0x3b, 0x3c, 0x3d, 0x2c, 0x1c, 0x2b, 0x2a, 0x1b, 0x0b, 0x0a, 0x1a, 0x19, 0x09, 0xb6, 0xb7, 0xc8, 0xd7, 0xe7, 0xd8, 0xd9, 0xe8, 0xe9, 0xea, 0x16, 0x26, 0x25, 0x24, 0x34, 0x35, 0x36, 0x46, 0x45, 0x44, 0x54, 0x55, 0x56, 0x66, 0x65, 0x64, 0x74, 0x75, 0x76, 0x86, 0x85, 0x84, 0x94, 0x95, 0xa4, 0x08, 0x18, 0x28, 0x38, 0x48, 0x68, 0x58, 0x78, 0x88, 0x98, 0xa8, 0x89, 0x8a, 0x49, 0x4a, 0xff
};
const UINT8 Pergamino::char52[] = { // R
0x37, 0x47, 0x46, 0x55, 0x56, 0x57, 0x67, 0x66, 0x65, 0x75, 0x76, 0x77, 0x87, 0x86, 0x85, 0x95, 0x96, 0xa5, 0xc8, 0xc7, 0xd7, 0xd6, 0xc6, 0xb6, 0xb5, 0xc5, 0xd5, 0xc4, 0xb4, 0xc3, 0xd2, 0xd1, 0xe0, 0x30, 0x21, 0x12, 0x22, 0x33, 0x23, 0x13, 0x14, 0x24, 0x34, 0x35, 0x25, 0x26, 0x17, 0x28, 0x19, 0x1a, 0x1b, 0x2c, 0x2b, 0x2a, 0x3a, 0x3b, 0x3c, 0x4c, 0x4b, 0x4a, 0x5b, 0x5a, 0x6a, 0x69, 0x78, 0x79, 0x89, 0x8a, 0x99, 0x9a, 0x9b, 0xab, 0xaa, 0xba, 0xbb, 0xca, 0xcb, 0xbc, 0xdb, 0xdc, 0xcc, 0xcd, 0x53, 0x63, 0x62, 0x73, 0x72, 0x71, 0x80, 0x90, 0x81, 0x82, 0x83, 0x93, 0x92, 0xa2, 0xa3, 0xb2, 0xff 
};
const UINT8 Pergamino::char55[] = { // U
0x40, 0x31, 0x22, 0x32, 0x23, 0x24, 0x33, 0x35, 0x34, 0x43, 0x44, 0x45, 0x55, 0x54, 0x64, 0x65, 0x75, 0x74, 0x84, 0x85, 0x95, 0x94, 0xa4, 0xa5, 0xb5, 0xb4, 0xd2, 0xc3, 0xd3, 0xc4, 0xd4, 0xe5, 0xd5, 0xc5, 0xc6, 0xd6, 0xe6, 0xd7, 0xd8, 0x91, 0x82, 0x83, 0x73, 0xeb, 0xdc, 0xdb, 0xda, 0xc9, 0xca, 0xcc, 0xcb, 0xbb, 0xba, 0xaa, 0xab, 0x9b, 0x9a, 0x8a, 0x8b, 0x7b, 0x7a, 0x6a, 0x6b, 0x5b, 0x5a, 0x4a, 0x4b, 0x3c, 0x3b, 0x3a, 0x39, 0x2a, 0x2b, 0x27, 0x37, 0x47, 0x57, 0x67, 0x77, 0x87, 0x97, 0xa7, 0xb7, 0xc7, 0x38, 0x68, 0x69, 0x98, 0x99, 0xfe
};
const UINT8 Pergamino::char56[] = { // V
0x40, 0x31, 0x32, 0x22, 0x23, 0x24, 0x33, 0x34, 0x35, 0x43, 0x44, 0x45, 0x46, 0x55, 0x54, 0x65, 0x64, 0x74, 0x75, 0x85, 0x84, 0x94, 0x95, 0xa5, 0xa4, 0xb4, 0xb5, 0xd2, 0xd3, 0xc3, 0xc4, 0xd4, 0xc5, 0xd5, 0xe5, 0xe6, 0xd6, 0xc6, 0xd7, 0xd8, 0x91, 0x82, 0x83, 0x73, 0xc9, 0xca, 0xcc, 0xcb, 0xbb, 0xba, 0xaa, 0xab, 0x9b, 0x9a, 0x8a, 0x8b, 0x7b, 0x7a, 0x6a, 0x6b, 0x5b, 0x5a, 0x3a, 0x4a, 0x4b, 0x3b, 0x3c, 0x2b, 0x2a, 0x27, 0x47, 0x37, 0x57, 0x67, 0x77, 0x87, 0x97, 0xa7, 0xb7, 0xc7, 0x38, 0x39, 0x68, 0x69, 0x98, 0x99, 0xfe
};
const UINT8 Pergamino::char57[] = { // W
	0x20, 0x30, 0x21, 0x22,
	0x31, 0x41, 0x32, 0x33,
	0x43, 0x42, 0x52, 0x53,
	0x63, 0x62, 0x73, 0x72,
	0x71, 0x80, 0x81, 0x82,
	0x83, 0x93, 0x92, 0xa2,
	0xa3, 0xb3, 0xb2, 0xd0,
	0xd1, 0xc1, 0xc2, 0xd2,
	0xe3, 0xd3, 0xc3, 0xc4,
	0xd4, 0xe4, 0xd5, 0xc5,
	0xc6, 0xd7, 0xc7, 0xb8,
	0xb7, 0xa7, 0xa8, 0x98,
	0x97, 0x87, 0x88, 0x78,
	0x77, 0x67, 0x68, 0x58,
	0x57, 0x47, 0x48, 0x38,
	0x37, 0x27, 0x28, 0xe8,
	0xd8, 0xc8, 0xc9, 0xd9,
	0xe9, 0xda, 0xca, 0xcb,
	0xcc, 0xcd, 0xbd, 0xbc,
	0xac, 0xad, 0x9d, 0x9c,
	0x8c, 0x8d, 0x7d, 0x7c,
	0x6c, 0x6d, 0x5d, 0x5c,
	0x4c, 0x4d, 0x3d, 0x3c,
	0x2c, 0x2d, 0x25, 0x35,
	0x45, 0x55, 0x65, 0x85,
	0x75, 0x95, 0xa5, 0xb5,
	0x36, 0x96, 0x2a, 0x3a,
	0x4a, 0x5a, 0x6a, 0x7a,
	0x8a, 0x9a, 0xba, 0xaa,
	0x39, 0x3b, 0x9b, 0xff
};
const UINT8 Pergamino::char58[] = { // X
0x40, 0x31, 0x22, 0x32, 0x23, 0x24, 0x33, 0x34, 0x35, 0x44, 0x45, 0x46, 0x55, 0x56, 0x65, 0x66, 0x76, 0x77, 0x86, 0x87, 0x97, 0x98, 0xa7, 0xa8, 0xa9, 0xb9, 0xb8, 0xc8, 0xc9, 0xd9, 0xca, 0xda, 0xea, 0xeb, 0xdb, 0xdc, 0xe0, 0xd1, 0xc2, 0xd2, 0xe3, 0xd3, 0xc3, 0xd4, 0xc4, 0xb5, 0xa6, 0x96, 0x67, 0x58, 0x49, 0x39, 0x2a, 0x3a, 0x4a, 0x3b, 0x3c, 0x2c, 0x82, 0x83, 0x73, 0x74, 0x84, 0x85, 0x75, 0x78, 0x88, 0x89, 0x79, 0x7a, 0x8a, 0x7b, 0xfe
};
const UINT8 Pergamino::char5A[] = { // Z no se usa, pero para algun texto futuro
0x30, 0x31, 0x21, 0x12, 0x22, 0x32, 0x42, 0x43, 0x33, 0x23, 0x24, 0x34, 0x35, 0x25, 0x26, 0x27, 0x1a, 0x29, 0x28, 0x38, 0x37, 0x48, 0x47, 0x57, 0x56, 0x66, 0x65, 0x64, 0x76, 0x75, 0x74, 0x85, 0x84, 0x83, 0x95, 0x94, 0x93, 0xa4, 0xa3, 0xa2, 0xb3, 0xb2, 0xc2, 0xc1, 0xd0, 0xe0, 0xd1, 0xd2, 0xd3, 0xd4, 0xc4, 0xb5, 0xc5, 0xd5, 0xe6, 0xd6, 0xc6, 0xb6, 0xb7, 0xc7, 0xd7, 0xe7, 0xd8, 0xc8, 0xc9, 0xd9, 0xca, 0xba, 0x62, 0x63, 0x67, 0x68, 0x69, 0x81, 0x82, 0x86, 0x88, 0x87, 0xfc
};
const UINT8 Pergamino::char77[] = { // w
	0x50, 0x41, 0x51, 0x52,
	0x62, 0x61, 0x71, 0x72,
	0x82, 0x81, 0x91, 0x92,
	0xa2, 0xa1, 0xb1, 0xb2,
	0xc2, 0xc3, 0xc4, 0xb4,
	0xb5, 0xa5, 0xa4, 0x94,
	0x95, 0x85, 0x84, 0x74,
	0x75, 0x65, 0x64, 0x54,
	0xc6, 0xc7, 0xb7, 0xb8,
	0xa8, 0xa7, 0x97, 0x98,
	0x88, 0x87, 0x77, 0x78,
	0x68, 0x67, 0x57, 0x58,
	0x59, 0x48, 0xfb
};
const UINT8 Pergamino::charD6[] = { // Ö

	0x32, 0x42, 0x41, 0x52 , 
	0x51, 0x50, 0x60, 0x61 , 
	0x62, 0x72, 0x71, 0x70 , 
	0x80, 0x81, 0x82, 0x92 , 
	0x91, 0x90, 0xa1, 0xa2 , 
	0xb2, 0xb3, 0xc3, 0xc4 , 
	0xb4, 0xc5, 0xd6, 0xc6 , 
	0xc7, 0xb7, 0xb8, 0xb9 , 
	0xa8, 0xa9, 0xaa, 0xab , 
	0x9b, 0x9a, 0x99, 0x98 , 
	0x88, 0x89, 0x8a, 0x8b , 
	0x7b, 0x7a, 0x79, 0x78 , 
	0x68, 0x69, 0x6a, 0x6b , 
	0x5b, 0x5a, 0x59, 0x58 , 
	0x49, 0x48, 0x38, 0x37 , 
	0x37, 0x27, 0x26, 0x36, 
	0x46, 0x35, 0x25, 0x24, 
	0x34, 0x33, 0x23, 0x33, 
	0x56, 0x55, 0x65, 0x66, 
	0x75, 0x76, 0x86, 0x85, 
	0x95, 0x96, 0xa5, 0xa4, 
	0x87, 0x03, 0x04, 0x06, 
	0x07, 0xfc
};
const UINT8 Pergamino::charE0[] = { // à 
	0x40, 0x41, 0x51, 0x52, 
	0x43, 0x44, 0x54, 0x55, 
	0x46, 0x65, 0x64, 0x75, 
	0x74, 0x84, 0x85, 0x95, 
	0x94, 0xa4, 0xa5, 0xb4, 
	0xb5, 0xb6, 0xc5, 0xb4, 
	0xc3, 0xc2, 0xc1, 0xb2, 
	0xb1, 0xb0, 0xa1, 0xa0, 
	0x91, 0x90, 0x81, 0x80, 
	0x71, 0x72, 0x83, 0x25, 
	0x24, 0x14, 0x13, 0xf8 
};
const UINT8 Pergamino::charE1[] = { // á
	0x40, 0x41, 0x51, 0x52, 
	0x43, 0x44, 0x54, 0x55, 
	0x46, 0x65, 0x64, 0x75, 
	0x74, 0x84, 0x85, 0x95, 
	0x94, 0xa4, 0xa5, 0xb4, 
	0xb5, 0xb6, 0xc5, 0xb4, 
	0xc3, 0xc2, 0xc1, 0xb2, 
	0xb1, 0xb0, 0xa1, 0xa0, 
	0x91, 0x90, 0x81, 0x80, 
	0x71, 0x72, 0x83, 0x22, 
	0x23, 0x13, 0x14, 0xf8
};
const UINT8 Pergamino::charE3[] = { // ã 
	0x40, 0x41, 0x51, 0x52, 
	0x43, 0x44, 0x54, 0x55, 
	0x46, 0x65, 0x64, 0x75, 
	0x74, 0x84, 0x85, 0x95, 
	0x94, 0xa4, 0xa5, 0xb4, 
	0xb5, 0xb6, 0xc5, 0xb4, 
	0xc3, 0xc2, 0xc1, 0xb2, 
	0xb1, 0xb0, 0xa1, 0xa0, 
	0x91, 0x90, 0x81, 0x80, 
	0x71, 0x72, 0x83, 0x20, 
	0x11, 0x12, 0x23, 0x24, 
	0x25, 0x16, 0xf8
};
const UINT8 Pergamino::charE4[] = { // ä
	0x40, 0x41, 0x51, 0x52, 
	0x43, 0x44, 0x54, 0x55, 
	0x46, 0x65, 0x64, 0x75, 
	0x74, 0x84, 0x85, 0x95, 
	0x94, 0xa4, 0xa5, 0xb4, 
	0xb5, 0xb6, 0xc5, 0xb4, 
	0xc3, 0xc2, 0xc1, 0xb2, 
	0xb1, 0xb0, 0xa1, 0xa0, 
	0x91, 0x90, 0x81, 0x80, 
	0x71, 0x72, 0x83, 0x21, 
	0x22, 0x24, 0x25, 0xf8
};
const UINT8 Pergamino::charE7[] = { // ç
	0xb6, 0xb5, 0xc4, 0xc3,
	0xc2, 0xb3, 0xb2, 0xb1,
	0xb0, 0xa1, 0xa2, 0x92,
	0x91, 0x82, 0x81, 0x72,
	0x71, 0x62, 0x61, 0x52,
	0x51, 0x43, 0x44, 0x45,
	0x54, 0x55, 0x56, 0x66,
	0x65, 0xd4, 0xe3, 0xe2,
	0xf8
};
const UINT8 Pergamino::charE8[] = { // è
	0xa6, 0xb5, 0xc4, 0xc3,
	0xc2, 0xb3, 0xb2, 0xb1,
	0xb0, 0xa1, 0xa2, 0x91,
	0x92, 0x81, 0x82, 0x71,
	0x72, 0x61, 0x62, 0x51,
	0x52, 0x43, 0x44, 0x45,
	0x54, 0x55, 0x56, 0x66,
	0x65, 0x74, 0x83, 0x25,
	0x24, 0x14, 0x13, 0xf8
};
const UINT8 Pergamino::charE9[] = { // é
	0xa6, 0xb5, 0xc4, 0xc3,
	0xc2, 0xb3, 0xb2, 0xb1,
	0xb0, 0xa1, 0xa2, 0x91,
	0x92, 0x81, 0x82, 0x71,
	0x72, 0x61, 0x62, 0x51,
	0x52, 0x43, 0x44, 0x45,
	0x54, 0x55, 0x56, 0x66,
	0x65, 0x74, 0x83, 0x22,
	0x23, 0x13, 0x14, 0xf8
};
const UINT8 Pergamino::charEA[] = { // ê
	0xa6, 0xb5, 0xc4, 0xc3,
	0xc2, 0xb3, 0xb2, 0xb1,
	0xb0, 0xa1, 0xa2, 0x91,
	0x92, 0x81, 0x82, 0x71,
	0x72, 0x61, 0x62, 0x51,
	0x52, 0x43, 0x44, 0x45,
	0x54, 0x55, 0x56, 0x66,
	0x65, 0x74, 0x83, 0x21,
	0x22, 0x13, 0x14, 0x25,
	0x26, 0xf8
};
const UINT8 Pergamino::charEC[] = { // ì
	0x50, 0x41, 0x52, 0x51,
	0x61, 0x62, 0x72, 0x71,
	0x81, 0x82, 0x92, 0x91,
	0xa1, 0xa2, 0xb2, 0xb1,
	0xc2, 0xb3, 0x21, 0x22,
	0x11, 0x10, 0xf5
};
const UINT8 Pergamino::charED[] = { // í
	0x50, 0x41, 0x52, 0x51,
	0x61, 0x62, 0x72, 0x71,
	0x81, 0x82, 0x92, 0x91,
	0xa1, 0xa2, 0xb2, 0xb1,
	0xc2, 0xb3, 0x20, 0x21,
	0x12, 0xf5
};
const UINT8 Pergamino::charEF[] = { // ï
	0x50, 0x41, 0x52, 0x51,
	0x61, 0x62, 0x72, 0x71,
	0x81, 0x82, 0x92, 0x91,
	0xa1, 0xa2, 0xb2, 0xb1,
	0xc2, 0xb3, 0x20, 0x21,
	0x23, 0x24, 0xf5
};
const UINT8 Pergamino::charF1[] = { // ñ
	0x50, 0x41, 0x52, 0x51,
	0x61, 0x62, 0x72, 0x71,
	0x81, 0x82, 0x92, 0x91,
	0xa1, 0xa2, 0xb2, 0xb1,
	0xc2, 0xb3, 0x63, 0x54,
	0x45, 0x55, 0x56, 0x66,
	0x65, 0x75, 0x76, 0x86,
	0x85, 0x95, 0x96, 0xa6,
	0xa5, 0xb5, 0xb6, 0xc6,
	0xb7, 0x20, 0x21, 0x22,
	0x32, 0x33, 0x34, 0x35,
	0x26, 0xf8
};
const UINT8 Pergamino::charF2[] = { // ò
	0x42, 0x43, 0x44, 0x53,
	0x54, 0x55, 0x64, 0x65,
	0x74, 0x75, 0x84, 0x85,
	0x94, 0x95, 0xa5, 0xa4,
	0xb5, 0xb4, 0xc3, 0xc2,
	0xc1, 0xb2, 0xb1, 0xb0,
	0xa1, 0xa0, 0x91, 0x90,
	0x81, 0x80, 0x71, 0x70,
	0x61, 0x60, 0x51, 0x50,
	0x24, 0x23, 0x13, 0x12,
	0xf7
};
const UINT8 Pergamino::charF3[] = { // ó
	0x42, 0x43, 0x44, 0x53,
	0x54, 0x55, 0x64, 0x65,
	0x74, 0x75, 0x84, 0x85,
	0x94, 0x95, 0xa5, 0xa4,
	0xb5, 0xb4, 0xc3, 0xc2,
	0xc1, 0xb2, 0xb1, 0xb0,
	0xa1, 0xa0, 0x91, 0x90,
	0x81, 0x80, 0x71, 0x70,
	0x61, 0x60, 0x51, 0x50,
	0x21, 0x22, 0x12, 0x13,
	0xf7
};
const UINT8 Pergamino::charF6[] = { // ö
	0x42, 0x43, 0x44, 0x53,
	0x54, 0x55, 0x64, 0x65,
	0x74, 0x75, 0x84, 0x85,
	0x94, 0x95, 0xa5, 0xa4,
	0xb5, 0xb4, 0xc3, 0xc2,
	0xc1, 0xb2, 0xb1, 0xb0,
	0xa1, 0xa0, 0x91, 0x90,
	0x81, 0x80, 0x71, 0x70,
	0x61, 0x60, 0x51, 0x50,
	0x21, 0x22, 0x24, 0x25,
	0xf7
};
const UINT8 Pergamino::charF9[] = { // ù
	0x50, 0x41, 0x52, 0x51, 
	0x61, 0x62, 0x72, 0x71, 
	0x81, 0x82, 0x92, 0x91, 
	0xa1, 0xa2, 0xb2, 0xb1, 
	0xc2, 0xc3, 0xb4, 0x54, 
	0x45, 0x56, 0x55, 0x65, 
	0x66, 0x76, 0x75, 0x85, 
	0x86, 0x96, 0x95, 0xa5, 
	0xa6, 0xb6, 0xb5, 0xc6, 
	0xb7, 0x24, 0x23, 0x13, 
	0x12, 0xf8
};
const UINT8 Pergamino::charFA[] = { // ú
	0x50, 0x41, 0x52, 0x51, 
	0x61, 0x62, 0x72, 0x71,
	0x81, 0x82, 0x92, 0x91, 
	0xa1, 0xa2, 0xb2, 0xb1, 
	0xc2, 0xc3, 0xb4, 0x54, 
	0x45, 0x56, 0x55, 0x65, 
	0x66, 0x76, 0x75, 0x85, 
	0x86, 0x96, 0x95, 0xa5, 
	0xa6, 0xb6, 0xb5, 0xc6, 
	0xb7, 0x21, 0x22, 0x12, 
	0x13, 0xf8 
};
const UINT8 Pergamino::charFC[] = { // ü
	0x50, 0x41, 0x52, 0x51, 
	0x61, 0x62, 0x72, 0x71, 
	0x81, 0x82, 0x92, 0x91, 
	0xa1, 0xa2, 0xb2, 0xb1, 
	0xc2, 0xc3, 0xb4, 0x54, 
	0x45, 0x56, 0x55, 0x65, 
	0x66, 0x76, 0x75, 0x85, 
	0x86, 0x96, 0x95, 0xa5, 
	0xa6, 0xb6, 0xb5, 0xc6, 
	0xb7, 0x21, 0x22, 0x24, 
	0x25, 0xf8
};

int Pergamino::AdaptaColorAPaletaVGA(int a,int b)
{
	int color=cpc6128->unpackPixelMode1(a, b);
	switch(color)
	{
		case 0: color=255; break;
		case 1: color=20; break;
		case 2: color=0; break;
		case 3: color=1; break;
		default: printf("Pergamino::AdaptaColorAPaletaVGA color %d\n",color);
	}
	return color;
}

/////////////////////////////////////////////////////////////////////////////
// inicialización y limpieza
/////////////////////////////////////////////////////////////////////////////

Pergamino::Pergamino()
{
	cpc6128 = elJuego->cpc6128;
	roms = elJuego->roms;

	// puntero a la tabla de punteros a los gráficos de los caracteres
	UINT16* charTable = (UINT16*) &roms[0x680c];

	for (unsigned char c=0;c<255-0x20;c++) 
	{
		// si el caracter no está definido, muestra una 'z'
		TablapTrazosCaracter[c]=roms+SDL_SwapLE16(charTable['z'-0x20]);
	}
	// Recorre desde el caracter 0x21 hasta el 0x126 , apuntando
	// a los datos de la rom original donde se encuentran los
	// datos para dibujar los trazos
	// son los caracteres imprimibles del ASCII
	// aún así algunos no están definidos porque el juego original no los usaba
	for (char c='!';c<'~';c++) 
	{
		// si el caracter no está definido, dejamos apuntando a la 'z'
		if (charTable[c - 0x20] != 0)
			TablapTrazosCaracter[c-0x20]=roms+SDL_SwapLE16(charTable[c-0x20]);
	}
	// Se añaden los caracteres usados en las traducciones del remake PC
	// de los textos del pergamino

	//TablapTrazosCaracter['Ö'-0x20]=charD6; 
	TablapTrazosCaracter[0xD6-0x20]=charD6; 
	//TablapTrazosCaracter['à'-0x20]=charE0;
	TablapTrazosCaracter[0xE0-0x20]=charE0;
	//TablapTrazosCaracter['á'-0x20]=charE1;
	TablapTrazosCaracter[0xE1-0x20]=charE1;
	//TablapTrazosCaracter['ã'-0x20]=charE3;
	TablapTrazosCaracter[0xE3-0x20]=charE3;
	//TablapTrazosCaracter['ä'-0x20]=charE4;
	TablapTrazosCaracter[0xE4-0x20]=charE4;
	//TablapTrazosCaracter['ç'-0x20]=charE7;
	TablapTrazosCaracter[0xE7-0x20]=charE7;
	//TablapTrazosCaracter['è'-0x20]=charE8;
	TablapTrazosCaracter[0xE8-0x20]=charE8;
	//TablapTrazosCaracter['é'-0x20]=charE9;
	TablapTrazosCaracter[0xE9-0x20]=charE9;
	//TablapTrazosCaracter['ê'-0x20]=charEA;
	TablapTrazosCaracter[0xEA-0x20]=charEA;
	//TablapTrazosCaracter['ì'-0x20]=charEC;
	TablapTrazosCaracter[0xEC-0x20]=charEC;
	//TablapTrazosCaracter['í'-0x20]=charED;
	TablapTrazosCaracter[0xED-0x20]=charED;
	//TablapTrazosCaracter['ï'-0x20]=charEF;
	TablapTrazosCaracter[0xEF-0x20]=charEF;
	//TablapTrazosCaracter['ñ'-0x20]=charF1;
	TablapTrazosCaracter[0xF1-0x20]=charF1;
	//TablapTrazosCaracter['ò'-0x20]=charF2;
	TablapTrazosCaracter[0xF2-0x20]=charF2;
	//TablapTrazosCaracter['ó'-0x20]=charF3;
	TablapTrazosCaracter[0xF3-0x20]=charF3;
	//TablapTrazosCaracter['ö'-0x20]=charF6;
	TablapTrazosCaracter[0xF6-0x20]=charF6;
	//TablapTrazosCaracter['ù'-0x20]=charF9;
	TablapTrazosCaracter[0xF9-0x20]=charF9;
	//TablapTrazosCaracter['ú'-0x20]=charFA;
	TablapTrazosCaracter[0xFA-0x20]=charFA;
	//TablapTrazosCaracter['ü'-0x20]=charFC; 
	TablapTrazosCaracter[0xFC-0x20]=charFC; 

	// En el original, no se usaba la w,
	// así que la aprovechaban para la ñ
	// aquí la ñ están en charF1
	// asi que dejamos la w en su sitio, 0x77
	//TablapTrazosCaracter['w'-0x20]=char77; 
	TablapTrazosCaracter[0x77-0x20]=char77; 

	// En la rom original hay muchos caracteres ASCII
	// no definidos
	//TablapTrazosCaracter['''-0x20]=char27; 
	TablapTrazosCaracter[0x27-0x20]=char27; 
	//TablapTrazosCaracter['B'-0x20]=char42; 
	TablapTrazosCaracter[0x42-0x20]=char42; 
	//TablapTrazosCaracter['F'-0x20]=char46; 
	TablapTrazosCaracter[0x46-0x20]=char46; 
	//TablapTrazosCaracter['I'-0x20]=char49; 
	TablapTrazosCaracter[0x49-0x20]=char49; 
	//TablapTrazosCaracter['K'-0x20]=char4B; 
	TablapTrazosCaracter[0x4B - 0x20]=char4B; 
	//TablapTrazosCaracter['N'-0x20]=char4E; 
	TablapTrazosCaracter[0x4E - 0x20]=char4E; 
	//TablapTrazosCaracter['Q'-0x20]=char51; 
	TablapTrazosCaracter[0x51-0x20]=char51; 
	//TablapTrazosCaracter['R'-0x20]=char52; 
	TablapTrazosCaracter[0x52-0x20]=char52; 
	//TablapTrazosCaracter['U'-0x20]=char55; 
	TablapTrazosCaracter[0x55-0x20]=char55; 
	//TablapTrazosCaracter['V'-0x20]=char56; 
	TablapTrazosCaracter[0x56-0x20]=char56; 
	//TablapTrazosCaracter['W'-0x20]=char57; 
	TablapTrazosCaracter[0x57-0x20]=char57; 
	//TablapTrazosCaracter['X'-0x20]=char58; 
	TablapTrazosCaracter[0x58-0x20]=char58; 
	//TablapTrazosCaracter['Z'-0x20]=char5A; 
	TablapTrazosCaracter[0x5A-0x20]=char5A; 
}

Pergamino::~Pergamino()
{
}

/////////////////////////////////////////////////////////////////////////////
// dibujo del pergamino
/////////////////////////////////////////////////////////////////////////////

// dibuja el pergamino
void Pergamino::dibuja()
{
	// limpia la memoria de video
	//CPC	cpc6128->fillMode1Rect(0, 0, 320, 200, 0);
	cpc6128->fillMode1Rect(0, 0, 320, 200, 255); // VGA

	// limpia los bordes del rectángulo que formará el pergamino
	/* CPC
	cpc6128->fillMode1Rect(0, 0, 64, 200, 1);
	cpc6128->fillMode1Rect(192 + 64, 0, 64, 200, 1);
	cpc6128->fillMode1Rect(0, 192, 320, 8, 1);
	*/
	// VGA
	cpc6128->fillMode1Rect(0, 0, 64, 200, 20);
	cpc6128->fillMode1Rect(192 + 64, 0, 64, 200, 20);
	cpc6128->fillMode1Rect(0, 192, 320, 8, 20);

	// apunta a los datos del borde superior del pergamino
	UINT8* data = &roms[0x788a];

	// rellena la parte superior del pergamino
	dibujaTiraHorizontal(0, data);

	// rellena la parte derecha del pergamino
	data = &roms[0x7a0a];
	dibujaTiraVertical(248, data);

	// rellena la parte izquierda del pergamino
	data = &roms[0x7b8a];
	dibujaTiraVertical(64, data);

	// rellena la parte inferior del pergamino
	data = &roms[0x7d0a];
	dibujaTiraHorizontal(184, data);
}

// dibuja un borde horizontal del pergamino de 8 pixels de alto
void Pergamino::dibujaTiraHorizontal(int y, UINT8 *data)
{
	// recorre todo el ancho del pergamino
	for (int i = 0; i < 192/4; i++){
		// la parte superior ocupa 8 pixels de alto
		for (int j = 0; j < 8; j++){
			for (int k = 0; k < 4; k++){
				//cpc6128->setMode1Pixel(64 + 4*i + k, j + y, cpc6128->unpackPixelMode1(*data, k));
				cpc6128->setMode1Pixel(64 + 4*i + k, j + y, AdaptaColorAPaletaVGA(*data, k));
			}
			data++;
		}
	}
}

// dibuja el pergamino
void Pergamino::dibujaTiraVertical(int x, UINT8 *data)
{
	// recorre el alto del pergamino
	for (int j = 0; j < 192; j++){
		// lee 8 pixels y los escribe en pantalla
		for (int i = 0; i < 2; i++){
			for (int k = 0; k < 4; k++){
//				cpc6128->setMode1Pixel(x + 4*i + k, j, cpc6128->unpackPixelMode1(*data, k));
				cpc6128->setMode1Pixel(x + 4*i + k, j, AdaptaColorAPaletaVGA(*data, k));
			}
			data++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// escritura de texto en el pergamino
/////////////////////////////////////////////////////////////////////////////

//void Pergamino::muestraTexto(const char *texto)
void Pergamino::muestraTexto(const unsigned char *texto)
{
	// pone la paleta negra
	elJuego->paleta->setGamePalette(0);

	// dibuja el pergamino
	dibuja();

	// pone la paleta del pergamino
	elJuego->paleta->setGamePalette(1); //CPC
	dibujaTexto(texto); 
}

//void Pergamino::dibujaTexto(const char *texto)
void Pergamino::dibujaTexto(const unsigned char *texto)
{
	// obtiene acceso al temporizador y a las entradas
	TimingHandler *timer = elJuego->timer;

	// posición inicial del texto en el pergamino
	int posX = 76;
	int posY = 16;

	// puntero a la tabla de punteros a los gráficos de los caracteres
	UINT16* charTable = (UINT16*) &roms[0x680c];

	// repite hasta que se pulse el botón 1
	while (true){
		losControles->actualizaEstado();

		// si se pulsó el botón 1 o espacio, termina
		if (losControles->estaSiendoPulsado(P1_BUTTON1) || losControles->estaSiendoPulsado(KEYBOARD_SPACE)){
			break;
		} else {
			UINT32 codePoint=0;
			char firstByte=*texto;
			std::string::difference_type offset=1; //TODO: esta var se puede ahorrar al ir incrementando mientras se lee cada byte
			if(firstByte&128) { // This means the first byte has a value greater than 127, and so is beyond the ASCII range.
        			if(firstByte & 32) // This means that the first byte has a value greater than 191, and so it must be at least a three-octet code point.
        			{
					if(firstByte & 16) // This means that the first byte has a value greater than 224, and so it must be a four-octet code point.
					{
						codePoint = (firstByte & 0x07) << 18;
						char secondByte = *(texto + 1);
						codePoint +=  (secondByte & 0x3f) << 12;
						char thirdByte = *(texto + 2);
						codePoint +=  (thirdByte & 0x3f) << 6;;
						char fourthByte = *(texto + 3);
						codePoint += (fourthByte & 0x3f);

						offset=4;	
					}
					else
					{
						codePoint = (firstByte & 0x0f) << 12;
						char secondByte = *(texto + 1);
						codePoint += (secondByte & 0x3f) << 6;
						char thirdByte = *(texto + 2);
						codePoint +=  (thirdByte & 0x3f);

						offset=3;	
					}
				}
				else
				{
					codePoint = (firstByte & 0x1f) << 6;
					char secondByte = *(texto + 1);
					codePoint +=  (secondByte & 0x3f);

					offset=2;	
				}
			}
			else
			{
				codePoint = firstByte;
			}
//			texto+=offset;
			int caracter = codePoint;
//fprintf(stderr,"caracter %ld 0x%04x\n", caracter,caracter);
			// dependiendo del carácter leido
			switch (caracter){
				case 0x1a:			// fín de pergamino
					break;
				case 0x0d:			// salto de línea
					posX = 76;
					posY += 16;
					timer->sleep(600);

					// si hay que pasar página del pergamino
					if (posY > 164){
						posX = 76;
						posY = 16;
						timer->sleep(2000);
						pasaPagina();
					}
					break;
				case 0x20:			// espacio
					posX += 10;
					timer->sleep(30);
					break;
				case 0x0a:			// salto de página
					posX = 76;
					posY = 16;
					timer->sleep(3*525);
					pasaPagina();
					break;

				default:			// carácter imprimible
					UINT8 const * pTrazosCaracter= 
//						TablapTrazosCaracter[(*texto)-0x20];
						TablapTrazosCaracter[(caracter)-0x20];
					// elige un color dependiendo de si es mayúsculas o minúsculas

					// la paleta CPC del pergamino es 07,28,20,12
					// o sea
					// el color 0 es el 07 que es pink
					// el color 1 es el 28 que es red
					// el color 2 es el 20 que es black
					// el color 3 es el 12 que es bright red

					//CPC					int color = (((*texto) & 0x60) == 0x40) ? 3 : 2;
					//Para VGA pongo el color 1?? para las mayusculas y el color 0?? para las minusculas
					// TODO: revisar para UTF8
					//int color = (((*texto) & 0x60) == 0x40) ? 1 : 0;
					int color = (((caracter) & 0x60) == 0x40) ? 1 : 0;

					// obtiene el desplazamiento a los datos de formación del carácter
					// transformando del dato nativo en litte_endian
					// al tipo del sistema (si es little_endian no hace nada,
					// y si es big_endian intercambia el orden)
					//int charOffset = SDL_SwapLE16(charTable[(*texto) - 0x20]);
					int charOffset = SDL_SwapLE16(charTable[(caracter) - 0x20]);

					// para alertar si nos hemos dejado algo sin definir
					if (*texto!='z' && charOffset==SDL_SwapLE16(charTable['z'-0x20])) 	
						printf("¡¡¡ NOS HEMOS DEJADO ALGUN CARACTER SIN DEFINIR !!! %c\n",*texto);

					// si el caracter no está definido, muestra una 'z'
					//if (charTable[(*texto) - 0x20] == 0){
					if (charTable[(caracter) - 0x20] == 0){
						charOffset = SDL_SwapLE16(charTable['z' - 0x20]);
					}

					// mientras queden trazos del carácter
//					while ((roms[charOffset] & 0xf0) != 0xf0){
					while ((*pTrazosCaracter & 0xf0) != 0xf0){
						// halla el desplazamiento del trazo
//						int newPosX = posX + (roms[charOffset] & 0x0f);
//						int newPosy = posY + ((roms[charOffset] >> 4) & 0x0f);
						int newPosX = posX+(*pTrazosCaracter & 0x0f);
						int newPosy=posY+((*pTrazosCaracter>>4)&0x0f);

						// dibuja el trazo del carácter
						//CPC cpc6128->setMode1Pixel(newPosX, newPosy, color);
						cpc6128->setVGAPixel(newPosX, newPosy, color);

						charOffset++;
						pTrazosCaracter++;

						// espera un poco para que se pueda apreciar como se traza el carácter
						timer->sleep(8);
					}

					// avanza la posición hasta el siguiente carácter
//					posX += roms[charOffset] & 0x0f;
					posX += *pTrazosCaracter & 0x0f;
			}

			// apunta al siguiente carácter a imprimir
/*			if (*texto != 0x1a){
				texto++;
			} */
			if (caracter != 0x1a){
				texto+=offset;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// paso de página del pergamino
/////////////////////////////////////////////////////////////////////////////

// dibuja un triángulo rectángulo de color1 con catetos paralelos a los ejes x e y, y limpia los 4 
//  pixels a la derecha de la hipotenusa del triángulo con el color2
void Pergamino::dibujaTriangulo(int x, int y, int lado, int color1, int color2)
{
	lado = lado*4;

	for (int j = 0; j < lado; j++){
		// dibuja el triángulo
		for (int i = 0; i <= j; i++){
			cpc6128->setMode1Pixel(x + i, y + j, color1);
		}

		// elimina restos de una ejecución anterior
		for (int i = 0; i < 4; i++){
			// CPC cpc6128->setMode1Pixel(x + j + i + 1, y + j, 0); 
			cpc6128->setMode1Pixel(x + j + i + 1, y + j, 255); 
		}
	}
}

// restaura un trozo de 8x8 pixels de la parte superior y otro de la parte derecha del pergamino
void Pergamino::restauraParteSuperiorYDerecha(int x, int y, int lado)
{
	x = x + 4;

	// apunta a los datos borrados del borde superior del pergamino
	UINT8* data = &roms[0x788a + (48 - lado)*4*2];

	// 8 pixels de ancho
	for (int i = 0; i < 2; i++){
		// 8 pixels de alto
		for (int j = 0; j < 8; j++){
			for (int k = 0; k < 4; k++){
				//cpc6128->setMode1Pixel(x + 4*i + k, y + j, cpc6128->unpackPixelMode1(*data, k));
				cpc6128->setMode1Pixel(x + 4*i + k, y + j, AdaptaColorAPaletaVGA(*data, k));
			}
			data++;
		}
	}

	x = 248;
	y = (lado - 3)*4;

	// apunta a los datos borrados de la parte derecha del pergamino
	data = &roms[0x7a0a + y*2];

	// 8 pixels de alto
	for (int j = 0; j < 8; j++){
		// 8 pixels de ancho
		for (int i = 0; i < 2; i++){
			for (int k = 0; k < 4; k++){
				//cpc6128->setMode1Pixel(x + 4*i + k, y + j, cpc6128->unpackPixelMode1(*data, k));
				cpc6128->setMode1Pixel(x + 4*i + k, y + j, AdaptaColorAPaletaVGA(*data, k));
			}
			data++;
		}
	}
}

// restaura un trozo de 4x8 pixels de la parte inferior del pergamino
void Pergamino::restauraParteInferior(int x, int y, int lado)
{
	x = 64 + lado*4;
	y = 184;

	// apunta a los datos borrados del borde inferior del pergamino
	UINT8* data = &roms[0x7d0a + lado*4*2];

	// dibuja un trozo de 4x8 pixels de la parte inferior del pergamino
	for (int j = 0; j < 8; j++){
		for (int k = 0; k < 4; k++){
			//cpc6128->setMode1Pixel(x + k, y + j, cpc6128->unpackPixelMode1(*data, k));
			cpc6128->setMode1Pixel(x + k, y + j, AdaptaColorAPaletaVGA(*data, k));
		}
		data++;
	}
}

// realiza el efecto de pasar una página del pergamino
void Pergamino::pasaPagina()
{
	// obtiene acceso al temporizador
	TimingHandler *timer = elJuego->timer;

	int x = 240;
	int y = 0;
	int dim = 3;

	// realiza el efecto del paso de página desde la esquina superior derecha hasta la mitad de la página
	for (int num = 0; num < 45; num++){
		dibujaTriangulo(x, y, dim, 1, 0);
		timer->sleep(20);
		restauraParteSuperiorYDerecha(x, y, dim);

		x = x - 4;
		dim++;
	}
	restauraParteSuperiorYDerecha(x, y, dim);

	x = 64;
	y = 4;
	dim = 47;

	// realiza el efecto del paso de página desde la mitad de la página hasta terminar en la esquina inferior izquierda
	for (int num = 0; num < 46; num++){
		dibujaTriangulo(x, y, dim, 1, 0);
		timer->sleep(20);

		y = y - 4;

		// apunta a los datos borrados del borde izquierdo del pergamino
		UINT8* data = &roms[0x7b8a + y*2];

		// dibuja un trozo de 8x4 de la parte izquierda del pergamino
		for (int j = 0; j < 4; j++){
			for (int i = 0; i < 2; i++){
				for (int k = 0; k < 4; k++){
					//cpc6128->setMode1Pixel(x + 4*i + k, y + j, cpc6128->unpackPixelMode1(*data, k));
					cpc6128->setMode1Pixel(x + 4*i + k, y + j, AdaptaColorAPaletaVGA(*data, k));
				}
				data++;
			}
		}

		// restaura un trozo de 4x8 pixels de la parte inferior del pergamino
		restauraParteInferior(x, y, dim);

		y = y + 8;
		dim--;
	}
	restauraParteInferior(x, y, 1);
	restauraParteInferior(x, y, 0);
}
