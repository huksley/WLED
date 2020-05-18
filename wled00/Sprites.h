// Sprite data 0, 0, 9, 10, Char
const uint8_t CharData[] = {
 B8_5BIT(00000000), B8_5BIT(00000000), 
 B8_5BIT(00000000), B8_5BIT(00000000), 
 B8_5BIT(00001111), B8_5BIT(00000000), 
 B8_5BIT(00011222), B8_5BIT(30000000), 
 B8_5BIT(00012424), B8_5BIT(30000000), 
 B8_5BIT(00512266), B8_5BIT(70000000), 
 B8_5BIT(05558660), B8_5BIT(90000000), 
 B8_5BIT(05618818), B8_5BIT(70000000), 
 B8_5BIT(0118A1A0), B8_5BIT(00000000), 
 B8_5BIT(00A51A5A), B8_5BIT(00000000)
};
const uint8_t CharMask[] = {
 B8_1BIT(00000000), B8_1BIT(00000000), 
 B8_1BIT(00000000), B8_1BIT(00000000), 
 B8_1BIT(00001111), B8_1BIT(00000000), 
 B8_1BIT(00011111), B8_1BIT(10000000), 
 B8_1BIT(00011111), B8_1BIT(10000000), 
 B8_1BIT(00111111), B8_1BIT(10000000), 
 B8_1BIT(01111110), B8_1BIT(10000000), 
 B8_1BIT(01111111), B8_1BIT(10000000), 
 B8_1BIT(01111110), B8_1BIT(00000000), 
 B8_1BIT(00111111), B8_1BIT(00000000)
};
const struct CRGB CharColTab[] =  {
 CRGB(0x0, 0x0, 0x0) /*0*/, 
 CRGB(0x53, 0x40, 0x33) /*533340*/, 
 CRGB(0xe2, 0xbb, 0x69) /*e269bb*/, 
 CRGB(0x8a, 0x8b, 0x72) /*8a728b*/, 
 CRGB(0x37, 0x37, 0x2f) /*372f37*/, 
 CRGB(0x6f, 0x54, 0x41) /*6f4154*/, 
 CRGB(0xf0, 0xd4, 0x9b) /*f09bd4*/, 
 CRGB(0x62, 0x63, 0x52) /*625263*/, 
 CRGB(0x4e, 0x84, 0x57) /*4e5784*/, 
 CRGB(0xf6, 0xdf, 0x97) /*f697df*/, 
 CRGB(0x3f, 0x67, 0x45) /*3f4567*/
};
cSprite Char(9, 10, CharData, 1, _5BIT, CharColTab, CharMask);
// Sprite data 0, 24, 7, 9, Ring
const uint8_t RingData[] = {
 B8_5BIT(00000000), 
 B8_5BIT(00121000), 
 B8_5BIT(02313200), 
 B8_5BIT(00434000), 
 B8_5BIT(04000400), 
 B8_5BIT(05000500), 
 B8_5BIT(05000500), 
 B8_5BIT(00666000), 
 B8_5BIT(00000000)
};
const uint8_t RingMask[] = {
 B8_1BIT(00000000), 
 B8_1BIT(00111000), 
 B8_1BIT(01111100), 
 B8_1BIT(00111000), 
 B8_1BIT(01000100), 
 B8_1BIT(01000100), 
 B8_1BIT(01000100), 
 B8_1BIT(00111000), 
 B8_1BIT(00000000)
};
const struct CRGB RingColTab[] =  {
 CRGB(0x0, 0x0, 0x0) /*0*/, 
 CRGB(0xd0, 0x4c, 0x50) /*d0504c*/, 
 CRGB(0xe3, 0x73, 0x76) /*e37673*/, 
 CRGB(0x85, 0x36, 0x38) /*853836*/, 
 CRGB(0xe2, 0xbb, 0x69) /*e269bb*/, 
 CRGB(0xd0, 0x94, 0x22) /*d02294*/, 
 CRGB(0xa9, 0x79, 0x1f) /*a91f79*/
};
cSprite Ring(7, 9, RingData, 1, _5BIT, RingColTab, RingMask);
