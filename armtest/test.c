#include "ecdh.h"

#if TARGET_LPC11XX
#include "peripherals/uart.h"
#include "peripherals/time.h"
#else

#include <sys/time.h>

#define uartInit(rate)
#define initTime()

uint64_t getTimeMs(void)
{
    struct timeval l_now;
    gettimeofday(&l_now, NULL);
    uint64_t l_time = ((uint64_t)(l_now.tv_sec)) * 1000 + l_now.tv_usec / 1000;
    return l_time;
}

#endif

#include <stdio.h>

void vli_print(uint32_t *p_vli)
{
    unsigned i;
    for(i=0; i<NUM_ECC_DIGITS; ++i)
	{
		printf("%08X ", (unsigned)p_vli[i]);
	}
}

#if (ECC_CURVE == secp128r1)
uint32_t l_private[10][NUM_ECC_DIGITS] = {
    {0xB66C17D0, 0xD21CD12E, 0x1885B2F7, 0x71D40584},
    {0x6C99B53A, 0x86686357, 0x3E34C5C4, 0x5314DFA3},
    {0x458B1408, 0x86D162A3, 0x7AB33E92, 0x92C9E643},
    {0x91872C30, 0x46F7AAEF, 0x45F7C29A, 0x9E2BCCA4},
    {0x9AC2ABD1, 0xAF62B5F0, 0x2EFDBA0B, 0x6A9221FE},
    {0x1CE0D4AD, 0x614EDCF0, 0x361314D4, 0xBF3687D2},
    {0x990B5252, 0xCE0038D9, 0xB4C9A00B, 0x1094CF4D},
    {0xF0A29720, 0x0140B5C9, 0x52CF21F3, 0x3294E456},
    {0xC01E9087, 0x47170C2D, 0x2C597A81, 0xE1D7FEB6},
    {0x8183C9A6, 0xA1C01A50, 0x592E9603, 0xDEB7FED9},
};

EccPoint l_public[10] = {
    {{0xE4C0291F, 0xA1F2E44A, 0x0B3653FD, 0x6930B1C5},
        {0x8FD9A49A, 0xAC811AB9, 0x428FAAEC, 0xDDFD5DEF}},
    {{0xC39CF076, 0xDE94A5CD, 0x73AEB0D7, 0xCE5451B4},
        {0x3BA9ED5F, 0xCF743693, 0x3C9A43C7, 0xEDDFD7E2}},
    {{0x80368A66, 0x5937CAAF, 0x3BEE2BE7, 0xE64E733D},
        {0x3AA8F7E9, 0xA483C9E6, 0x8F794AD1, 0xC337CB9E}},
    {{0x1E5EAFAF, 0x77D36D21, 0xE9532F7C, 0xAFE7E501},
        {0x7D79C739, 0x7EE43DCC, 0x6680981F, 0x7E114077}},
    {{0x8AF00B25, 0xE00AA428, 0xA6DFABA0, 0xF44E2CF0},
        {0xE243BA1D, 0x7F900DE8, 0xA944C17B, 0x4C11C099}},
    {{0xC39C6109, 0xB373DB65, 0xCDA94697, 0x27345B77},
        {0x401618E6, 0x13A6C49C, 0x5869940B, 0x5115144E}},
    {{0x80DCF189, 0x0B44F328, 0x50A421A2, 0x034FE115},
        {0x2E0C0BF9, 0xFE0F8E7D, 0x3EF947B3, 0x5879B903}},
    {{0x68ADE268, 0x7ECCF41C, 0x141BF575, 0x3876C94D},
        {0x8017B034, 0x7598E395, 0x3F979AC2, 0x70700920}},
    {{0xD1CBAE92, 0xA81BA5EC, 0xC4CF64D8, 0x8E30FCF2},
        {0x79A77D42, 0x84A578B8, 0xEDE0FAFB, 0xF67F3976}},
    {{0x08BAF713, 0x289B0411, 0x2FC8B73F, 0x19AB8B64},
        {0x80EE6E22, 0xF184553A, 0xBD4E27F1, 0x121DC4BF}},
};

#elif (ECC_CURVE == secp160r1)
uint32_t l_private[10][NUM_ECC_DIGITS] = {
    {0x105C2141, 0xC8E7557E, 0x5A4CCF73, 0x0CE018F1, 0xBE12B09A},
    {0xBBD1E4F1, 0xD3F5888D, 0xCF29731E, 0x46E8BF1C, 0x3A647CFB},
    {0x0929883E, 0x7DA28983, 0x436E2180, 0x43ADF48D, 0x29A17725},
    {0x8284F18E, 0x639C9DBF, 0x08ACC394, 0x9284E5C0, 0xF4BBDBD9},
    {0x7D95B654, 0xF31EED03, 0x54B0333C, 0x355026C5, 0xCE647D2D},
    {0xA78A9C27, 0x78DA4955, 0x61C94430, 0xDB4A6BC3, 0x2342A3EA},
    {0x8AF959E1, 0xF599984B, 0xA78C4E7B, 0xA91E3D82, 0x71B6D8E4},
    {0xFB4ABE6F, 0x33B3F3BD, 0xE63A2302, 0x034B6ADC, 0xD471450A},
    {0x3E46D391, 0xFED4F4F8, 0xAEBBB8D6, 0xD3B20E61, 0x359C69DB},
    {0x1A8062AD, 0x425CC438, 0x306FBFA7, 0x78C6365A, 0xCD80D4A8},
};

EccPoint l_public[10] = {
    {{0xB1545BD6, 0xAAF192BE, 0xD0541953, 0xF7C4F12B, 0x508FEA82},
        {0x55DFCD38, 0x968C6CFD, 0x93F1963C, 0xF56C4881, 0x45F27B67}},
    {{0x2EC3B849, 0x5974CEEF, 0x5A1308BD, 0x0CA111F7, 0x84A47D8C},
        {0xB8E52F88, 0xC03D6A9C, 0x8FE910AB, 0xECDA5506, 0x5ECD9256}},
    {{0x07108AA1, 0x5C5006EA, 0x85168CF7, 0x8EC0513D, 0xF80EFD7A},
        {0xF50F8B01, 0x0F3EB8DB, 0x9E09D8E8, 0x52ED7740, 0x54D62103}},
    {{0x5551E114, 0x2D6EA44D, 0x50685E1C, 0xE9EE0D30, 0x95851715},
        {0xBF780FBB, 0xC087AEBD, 0xFDC038E9, 0xD6363346, 0x2F218F81}},
    {{0x388735DD, 0x5EE80FC2, 0xB7732C0E, 0xD1BA9184, 0x710DB219},
        {0xB1A0ABFD, 0x240D9B28, 0x3DD64CBC, 0x4509EDF6, 0x35B427A2}},
    {{0x4CF7D00E, 0x443D8915, 0x1F2114B1, 0x1A7DF720, 0xB853C532},
        {0xDEB946C3, 0x5DD1809D, 0x72D2F4BD, 0x0D406229, 0xF217FB7C}},
    {{0x015B99A8, 0xCAB21F56, 0xB996A95E, 0x59C6717E, 0xD1892454},
        {0x5031AC77, 0x6180D628, 0xDB1047A4, 0x2CC7A1C4, 0xC79F761B}},
    {{0x9A389029, 0xEA7D47D5, 0x3B3309DC, 0xBE2558F1, 0x8C4E5EC9},
        {0x5CACFFCB, 0xBD812C52, 0x8BBC4D71, 0x041E14D0, 0x243B5651}},
    {{0x5EF73EC1, 0x9BFF280B, 0x7835B88E, 0xAE46D04F, 0x157F4F6C},
        {0x5C933717, 0x8A5FC8DC, 0x61580A0D, 0x1A676575, 0xB5F0D609}},
    {{0x7F1BF3EE, 0x82BA2BFC, 0x3175EDFA, 0x3A1E7C4C, 0x636D2C41},
        {0x912EE676, 0x56C6FD0F, 0xB88A85E5, 0x5C40A901, 0x72714D0E}},
};

#elif (ECC_CURVE == secp192r1)
uint32_t l_private[10][NUM_ECC_DIGITS] = {
    {0x8A8590BC, 0xF8FC6B96, 0x216D16F6, 0x5D471999, 0x77B54115, 0xA1C40C96},
    {0x60867073, 0xC781509C, 0x36ACD71C, 0x58F5AD9E, 0xC2DB7360, 0x33BD208D},
    {0x57DE05EC, 0xBE8B9D15, 0xB0D84224, 0xD7E9176A, 0x5C97EE8D, 0x7D23952C},
    {0x0D4797E8, 0xAB361B2F, 0xFEE3BBF4, 0xBE23CF61, 0xA3F0D27B, 0xD1D49358},
    {0x681377E1, 0xF4DF8EB5, 0x9A55C8EA, 0x04816C18, 0x628B310F, 0x5019DC6E},
    {0x430A1A53, 0x16954A28, 0x3A675EB6, 0xC971CE03, 0xF6C628A5, 0x0FE11176},
    {0x7EB0C3B1, 0x55183558, 0x02BC274B, 0xFB1559AC, 0xAD50B416, 0xA185E502},
    {0x661666FD, 0xFC766ABB, 0xCCDA7437, 0x63B33C0D, 0x532B2329, 0x16A57B57},
    {0x3E540682, 0xE790A2F1, 0x9B3291E1, 0xB68EBC35, 0x0C88E534, 0x1F609E43},
    {0xE1C5244B, 0x9137E9E7, 0xD61F7DD0, 0x47200D7B, 0x71707AA7, 0x3BAF4CAE},
};

EccPoint l_public[10] = {
    {{0x58379FA5, 0xBF0AD3C0, 0x43C46341, 0x03C17E4C, 0x141E4B2D, 0x9262FBC4},
        {0xFD42BF5B, 0x2DA93B96, 0xA2F44FD2, 0xE49AC322, 0x325AD938, 0x7EC78924}},
    {{0xD43D49BD, 0x5E3EDC91, 0xC4B92D43, 0x23ABD7AC, 0x2393E81F, 0xAA44251A},
        {0xE2A45AD9, 0x824E616C, 0x8AF41F54, 0x9436A042, 0x01FC4560, 0xE8006868}},
    {{0x918FC426, 0xAF4B1667, 0x38C4DFBB, 0x84D79546, 0x5816A293, 0x620F572F},
        {0x1B11B853, 0x2A76C314, 0xD7E293D3, 0x147A3FE1, 0x023BA135, 0xE8C330FA}},
    {{0x9530DB5B, 0x04A24731, 0x819B1264, 0xF1BB7518, 0xFC52AD59, 0xCE8BBA3A},
        {0xCAA5226D, 0xB7F2E77F, 0x44A0AB8E, 0xE21FBA39, 0x2820E42B, 0xFE554CDE}},
    {{0xAEEB46D1, 0x6935EC9E, 0xE3D5CC2F, 0x4D4ACEA8, 0x86BC2CEB, 0xD1E57CA2},
        {0xBE3848A3, 0x444B0017, 0xA55D148B, 0x52DE7036, 0xFBEA0864, 0xBE0E7544}},
    {{0x18BF0DE7, 0xED6E7913, 0x85DB2AC4, 0xF62E1BE9, 0x41959A17, 0x1DF4E10D},
        {0x9E1B3C21, 0x64AEB0CF, 0x3A8F9D16, 0xCC035209, 0xE369B12C, 0xEFD688A4}},
    {{0xF478AA34, 0xEACAB900, 0x850E30F4, 0xA4C67968, 0xFC6DB77E, 0x6B31449B},
        {0x7CA20F13, 0xC07C04AF, 0x84910675, 0x0907C2A4, 0xCEFF2DB5, 0xF985D758}},
    {{0xF5C45632, 0x5C62C2B6, 0xFDCDFF27, 0x08776E9A, 0x3D55752D, 0x5C0ED6D6},
        {0x43650F59, 0x14AB4374, 0xD5882DFA, 0x9CBA7BF0, 0x67A6CF8D, 0xC7D584B2}},
    {{0x2254F7DA, 0x53330058, 0x90A9AC53, 0x9B062D1A, 0x27FE77AE, 0xE44D9D00},
        {0xB7E91646, 0x685C16FA, 0xB9078665, 0x3B5E976F, 0x61D9C103, 0x3A2DF683}},
    {{0xC0875126, 0x9734E867, 0x076D4DE0, 0x6EBEA5AE, 0x3CFC3372, 0xD6A91E78},
        {0xE103662D, 0x139FD338, 0x791610BA, 0xDE584994, 0xA12D8DA4, 0x63270A3E}},
    };
    
#elif (ECC_CURVE == secp224r1)

uint32_t l_private[10][NUM_ECC_DIGITS] = {
    {0x92AC5997, 0x85C91711, 0xF8A13710, 0xB9EF3C09, 0xED2F58C0, 0x5FC2D1A8, 0x05379943},
    {0x71E13CFC, 0xC1D3459C, 0x82A9567B, 0x2D38D833, 0x85295F9E, 0x56E449D5, 0x9D29AF69},
    {0x58101AEB, 0x3314B044, 0x5A979527, 0xA6C0A4BA, 0x6534A4E2, 0x979C462B, 0x0F1A0960},
    {0x7CCF094C, 0x65BAA176, 0x3C3218E0, 0x257F50B0, 0x432109DA, 0xC4A5BADF, 0x0AE8B0EE},
    {0x17767E3C, 0x99B7E746, 0x38056BEB, 0x4D63D59C, 0xA473AD5C, 0x9A7CCA10, 0x401AAA68},
    {0x5FC80559, 0x7754B9BA, 0xD23B019C, 0x1772CF93, 0x76A98671, 0xE2240032, 0x6A86A803},
    {0x90B9AD65, 0xE9B1348F, 0xECF90E1F, 0x85115D89, 0x020EE62F, 0xFE3BE819, 0x6B6411B0},
    {0xDD1AEEE8, 0x4E27AC27, 0xE2DB0334, 0x0408D903, 0xF067C0FA, 0x254941A9, 0xAF44C655},
    {0x07404A6C, 0xF5D42FDE, 0xE1825FDA, 0x7685EEB1, 0x5EDD1625, 0xB32873D7, 0x4B4A0352},
    {0xAE0FB333, 0x75F97D91, 0xB5EF8049, 0x341469C0, 0x5FFE358A, 0xB81E22B3, 0x85AFDCEB},
};

EccPoint l_public[10] = {
    {{0xC0E193E3, 0x4FB8BA6A, 0xAED1B8B3, 0x4CE14165, 0x6ED64060, 0x45F753E9, 0xE856C26B},
        {0x840CFBBF, 0x4AD23EC7, 0x9643DDD5, 0x2398AADB, 0x2671E9AE, 0x53FEB7D2, 0x5588FA2E}},
    {{0x56763605, 0x69A8DCCC, 0x7A08E088, 0xCD37D76E, 0xB3ED9983, 0xC356B453, 0x29B64C50},
        {0x262334E8, 0xBF47A9D8, 0xC0B6B6A0, 0x702F8D14, 0xFE223A00, 0x71D3D3F2, 0xB29160DB}},
    {{0xADE4E689, 0x59856843, 0x9D645347, 0x23010224, 0x1CD5A3B1, 0xEEBB9812, 0xCF9F3F43},
        {0x2430E70E, 0x1B658CA6, 0xFA750FE4, 0x80F0A665, 0x003F0672, 0xA36E2090, 0xDD37CC35}},
    {{0xDF8962B9, 0x15FB4F53, 0x16564E03, 0xBBC50F49, 0x03A5EEE2, 0x9C15B452, 0xDF0BF344},
        {0x2D679C04, 0x35114D05, 0xAD1D896A, 0xB96C0DB3, 0xF9022FE2, 0x82E0B6F0, 0xB7D50575}},
    {{0x080DC73F, 0xFBE8E026, 0xA569523C, 0x66B05A36, 0xA7D235A5, 0xEBFBA207, 0x0C04C9EE},
        {0x2157E8F5, 0x21C0EEEE, 0x77961453, 0x83CFBBA4, 0x835875D8, 0xF7F726A8, 0x28D46252}},
    {{0xE5124225, 0x30A19D5C, 0xFCB08F75, 0x5EED266C, 0x7D37E550, 0x4F4B60E2, 0x72D0CB79},
        {0xCDC65EF6, 0x75577362, 0xBA34C393, 0x9A2756CD, 0x3828FC90, 0x9B0993CC, 0x1CAA34DE}},
    {{0x829E678C, 0xD9C1260C, 0x2E03A902, 0x6801C11B, 0x6CDF197A, 0x22BF0AD7, 0x8D0448EE},
        {0x19B229ED, 0x8DFDA351, 0x914470E9, 0x6DD45306, 0xC7B24A93, 0x52DC7572, 0xA4D1066F}},
    {{0x8304A31C, 0x25C7BD86, 0xB0714747, 0x2937CEAA, 0x0DA87B9B, 0xA3E1853A, 0x3B0BCDA8},
        {0xE198F4BD, 0xACF97B55, 0xBA0E1189, 0xB943DB95, 0xEBE3F9B2, 0xBAFD8F70, 0xF02687FE}},
    {{0x2D3460BB, 0xCED2D599, 0x580D0FF6, 0x82F3BD94, 0x0357697F, 0x3ECE00AE, 0xC134FE5E},
        {0xC043A9ED, 0xD595CDE2, 0x19D4EF60, 0x9EB2EDF4, 0xA9C63F43, 0x18A2725D, 0x350281E7}},
    {{0x375F82B6, 0x57F105DB, 0x2498AF90, 0xBDA2D0C3, 0xD2725B8F, 0xB8E84089, 0x33786485},
        {0x7B5AEEFB, 0x3F647259, 0x3D6F657B, 0x8631BB47, 0x9E11465B, 0x5F6A4BBB, 0x5252EF11}},
};

#elif (ECC_CURVE == secp256r1)

uint32_t l_private[10][NUM_ECC_DIGITS] = {
    {0x9399E0FA, 0xEB887947, 0xFACC412E, 0xC7AFD411, 0x735EE1E8, 0x2B8AFAF4, 0x986E3E7F, 0x742B1953},
    {0x079F480E, 0x41BB4E51, 0x76EEA661, 0xE7B5665D, 0xDF831ED8, 0x2304A3FB, 0x80721097, 0xD06D913A},
    {0x4631C4C3, 0x7C834C62, 0x14208F18, 0x4EE69B3E, 0xFBA45EEE, 0xB3007D73, 0x18BBBA55, 0x3562A76D},
    {0x214CE3AC, 0x22A2D7BD, 0x32366839, 0x686F1754, 0x0560E79B, 0x2EC31C78, 0xFCDC5172, 0xD4E02BAD},
    {0x39F0CACF, 0x3A9526BB, 0xBC5BDAE9, 0x47E36683, 0xEBE1358B, 0xF1C4EA34, 0x547594D5, 0x7FF3B3F9},
    {0x560187FA, 0x37EE44A4, 0x524625E7, 0x923715EE, 0x16C9FB0C, 0x96DC2A1D, 0x8E90B7BD, 0xD22CC9F7},
    {0x2C75DA88, 0x183118DD, 0xDA8B5A44, 0xB752A9B1, 0x20D46DBE, 0xCF2A166C, 0x9140D4F8, 0xDDC8166D},
    {0x55F5771A, 0x7A857A15, 0xCB3613A2, 0x1E20937C, 0xE9A47203, 0x606AAC0A, 0x48366174, 0x9BB9B879},
    {0x6E86355B, 0xE206AAEA, 0xE191D709, 0xE0EA40BD, 0xA8653AF3, 0x49B89A91, 0x67ED6FFE, 0x143EB0FF},
    {0x14A5AC82, 0x34F7EC3E, 0xC70665AA, 0xB387BD6E, 0x639CA247, 0x83CD78A6, 0xD1E26A2C, 0x0C8BFEC3},
};

EccPoint l_public[10] = {
    {{0x3A2AA077, 0x64E128B2, 0x04283263, 0x855DD786, 0x84517CA5, 0x79EEB9C4, 0x4761C4D9, 0x4851C11A},
        {0xE2C8E320, 0x585715E0, 0x0B9C17B9, 0x08C4EC62, 0xB773B9C6, 0x4035ADB7, 0x0D1DD194, 0x2A5BD99F}},
    {{0xC8220251, 0x2BA5B0B7, 0x8A4FBDEC, 0x084E14F3, 0x60A067FC, 0x6DA71E54, 0xF114F6BC, 0x4F8636A6},
        {0xFAAFA6A2, 0xF3A9F005, 0x09635F4F, 0x43281A2B, 0xA3A0685D, 0x1124EDE0, 0xADA827AD, 0x75CCB25D}},
    {{0x30B3A94A, 0x9EE3F351, 0x3AC21A79, 0x0351D486, 0x8042DEE2, 0xBB971022, 0x51D285F7, 0x49694ED3},
        {0x41EE0B17, 0x70A9D359, 0x974BF5F2, 0x576EA6C2, 0xC3214FDF, 0x64B752DB, 0x7650F5E2, 0x5D677E9B}},
    {{0xEFB56CF3, 0xAC23EA6C, 0x1DA12B80, 0x9FF74D0D, 0x03A3663B, 0x7177D352, 0x64B14BEC, 0x3EF56C7E},
        {0x549101E9, 0xF03D5539, 0x27D4A683, 0xB56432D2, 0xA662CC60, 0xCFE89639, 0x30274D96, 0xA7EFB6EC}},
    {{0x5CC7F176, 0xB5D3208A, 0xC2BB2BD4, 0xEFC4CDB4, 0xEC6A0CD6, 0xE733AA5A, 0x815027F2, 0x18332BC7},
        {0x594B7EFA, 0x19349A62, 0x43D57414, 0xC5CF1AB7, 0xA82BA69A, 0x76482590, 0xC621B475, 0xD3F20EC1}},
    {{0x4768CA3E, 0x7676F0E7, 0x700BC293, 0x9BFD80FC, 0x09CB5972, 0xEC9EDF97, 0xFB7E6C7E, 0x3998857C},
        {0xC2B781F7, 0x0AA397AB, 0x8A7329FB, 0xB197B6B0, 0x0755B743, 0x16ACDF44, 0xDFF7ACA6, 0xCE5BA363}},
    {{0xA45922E4, 0xEAB23872, 0xE83BF0ED, 0x6FFCB209, 0xE5117BE2, 0xBB58E09E, 0xD63DF1B0, 0xE607C88B},
        {0xD0E9E95B, 0x0311ECF2, 0x017B3DA1, 0x864D0368, 0x2A52B273, 0xC5058519, 0xA8CB392C, 0xC2CD3E86}},
    {{0x99BD36AC, 0x1D5540EE, 0x9ACCB679, 0xEB1D4D54, 0xC741817D, 0x0F98A403, 0x11B62F1E, 0xF1AE3418},
        {0x22AB665B, 0x617816BF, 0xBDE76F04, 0xA0278809, 0x85B5CC9E, 0x5CF8F0CB, 0xD6409719, 0xFE650C36}},
    {{0x7F782BBE, 0x392C88EC, 0x06D72DF2, 0x4BA960B7, 0x671B67BA, 0xCA87AEBD, 0xCDC0A1D7, 0x1DF26BDA},
        {0x8D93428B, 0x15D1C1D5, 0x08811B1C, 0x84A76187, 0xDA64D286, 0x8E91AC70, 0x7F415FDB, 0x1EFB19C6}},
    {{0x7971B33A, 0x4DBDF01E, 0xEDB8DE50, 0xFFFF7DB5, 0x507960F2, 0xDC75EB7B, 0x8C486A0E, 0x394997BE},
        {0x0DDC16BF, 0xC42D11FB, 0x68BA6066, 0xD25FF9C3, 0xCFAC0568, 0x0409A896, 0x5A644927, 0xC0A34E8C}},
};

#elif (ECC_CURVE == secp384r1)

uint32_t l_private[10][NUM_ECC_DIGITS] = {
    {0x32D5EFC6, 0x0A6E70F1, 0x6CAE9125, 0x78D74ECF, 0x33E423FB, 0x2B9F9991, 0x188E04C0, 0x6FEA1C8E, 0x2B2634A3, 0xDC5C521A, 0xDBF7265D, 0xB2975791},
    {0xE3C04C90, 0x14F9D46B, 0x67B1B5B9, 0xB1634716, 0xF22C2A3C, 0xF6E316E5, 0x83AD27DB, 0x7E2C5F0A, 0x7D963221, 0xB5949669, 0x24D3CF9B, 0xECFB5D62},
    {0xAE2CD960, 0x967D0340, 0x63D9DBB7, 0x1ACC2775, 0xF4384742, 0x1E80A08C, 0xAC147E25, 0x816980AB, 0x4E328750, 0x74DFC446, 0xF97F88D8, 0xB7F41F61},
    {0xB2ACC82C, 0x990423A0, 0x406FC4B5, 0x85D15EAF, 0x8427A963, 0x4DE0B726, 0x2760A931, 0x61704F08, 0x11FAA49E, 0x49FD9040, 0x0DE599AA, 0x3B8C6DD4},
    {0xC3F1029C, 0x98C70907, 0x42EB53D5, 0xD2A9ABB2, 0x7A84563F, 0xEA2199E4, 0x13363CFF, 0x91799CFE, 0x9040433D, 0xF968D8E8, 0x3B141F14, 0x49520031},
    {0xD0E2F25D, 0xC4C607DF, 0x49B309E6, 0xB502AF9B, 0x23D6DC13, 0xF85D7B34, 0xE522128E, 0x16556518, 0xA0A0A79A, 0xF3AC2452, 0x9C2752E4, 0xAF1960ED},
    {0xF0CDF38E, 0xB9727287, 0x928ACBD6, 0xDEAB02FC, 0xE2F71DD7, 0x47BCCC87, 0xED069FC8, 0xF5CA23B2, 0xE5D4CCD8, 0xE20F292B, 0x9F5B74CF, 0xFDF078AA},
    {0xD8AB652E, 0x6132B605, 0x319463B6, 0xB197883C, 0x1ACE17F8, 0x691B656C, 0x9B3DD592, 0x61CDCAF6, 0x1DCEBCC3, 0xB86BC43A, 0x440DCDA7, 0x59EC5A22},
    {0x97401DB7, 0x470838F2, 0xA19A58D3, 0xF076BF50, 0xDFF21694, 0x1B8F8455, 0x653549B0, 0x1CCE5CFD, 0x66F90BBA, 0x09BF73AA, 0x1D01275D, 0xCEEB698B},
    {0xB86CA4E0, 0x64F504D2, 0x5E2B318E, 0x7AD31C33, 0x3F293C53, 0xA0346206, 0x2ACA2DD4, 0x5BC53F6B, 0x3BB83FC2, 0xFC7DD83D, 0xC9CDD04A, 0x15DF8AD8},
};
EccPoint l_public[10] = {
    {{0x65E712A5, 0xEDE6358A, 0xD8832C43, 0xE219F022, 0x38407198, 0xC5B58725, 0x14422FF2, 0x7D30DD2E, 0xCF59C6A9, 0x63B30AEF, 0x0EEBE494, 0x1E47A816},
        {0x1E1CF55A, 0xDCC29967, 0xE59976B8, 0x5B6BDB4E, 0x52FF2D3F, 0x9C479240, 0xD14CA6B6, 0x2347BBFC, 0x7699F6E7, 0x0982F63D, 0xCE4805FC, 0x7D812D30}},
    {{0xBA5F2023, 0x88C842A6, 0x46DFEA58, 0xD87B5F24, 0xCE9BE9A1, 0xBBCB9F4F, 0xD94DBDDB, 0x2B2C5EB7, 0x0F6DF89F, 0xDB7D9CA6, 0x1F23435E, 0x18F86C99},
        {0x70A0F5FF, 0xCDD27DE3, 0x555BC9CB, 0xC027FA5A, 0xD2A0AD9C, 0x2F946827, 0xABEE1613, 0x7E4167D7, 0x95ABCBDF, 0x70225A99, 0x47DD210C, 0xA318330B}},
    {{0xECE05D2E, 0xE10D26A4, 0x31D57E74, 0xC04A3DF0, 0x1D9997CB, 0xC39E66E2, 0x373C2023, 0xDE8D8A89, 0xF67A7B7E, 0x41EBCFC6, 0x2035863C, 0xF4623DF8},
        {0x36F925D1, 0xFCBDFBBE, 0x3FDF04A9, 0x3B57A2E2, 0xC46B87D7, 0x4156817F, 0x2C1A064B, 0x7DB38358, 0x70CD9B69, 0x75A434A2, 0x9F4A48C4, 0x4AD69C23}},
    {{0x07172FA0, 0xE6130A08, 0x4F388AC1, 0xD7F343C2, 0xF888C384, 0x287DE4E5, 0x9A30CF33, 0x73CDAC5C, 0x5F1136D8, 0x245ED4EE, 0x9C1211CD, 0x3D4C9433},
        {0x9626B202, 0x84AAB332, 0xD2D6DFFB, 0x705510EA, 0x224D6D99, 0xD9BBA972, 0x16BF0492, 0x47E3A9FF, 0x6B5A0C25, 0xEDA495EE, 0x8C16DE01, 0x7D855F54}},
    {{0xB955B50C, 0xA8A666A1, 0xEFA243B2, 0xB3EA4A8B, 0x55029497, 0x174ED0E1, 0x583C111E, 0xA2DA83DB, 0x450FE418, 0x9B0A438C, 0x160B0777, 0x2E9EC7C1},
        {0x52B12CA1, 0xF48B11CB, 0x10C4A002, 0x63CC9513, 0x7F145B27, 0xEF4BB6D0, 0xEF0477AD, 0x88DBB594, 0xD1430AA9, 0x10D02A03, 0x25FA025E, 0x601E15BB}},
    {{0x443646B3, 0xBA5E3E80, 0x108CF73F, 0x21227E4F, 0xE48FEF5C, 0xD6C22515, 0x55E92109, 0x0D022DF9, 0xB74714CA, 0xE80E561A, 0x9B20FBFD, 0x4DF69459},
        {0x81B6F66C, 0x2E9AD77E, 0x0F54976E, 0x78F0DC08, 0xCE768D94, 0xCC5C3910, 0x7CBBC93F, 0x0AF83DAC, 0xEBB0496B, 0x2D6F03D5, 0x13902055, 0xF51C25C4}},
    {{0xDE7FDB51, 0x6B9D9317, 0x2A2225C6, 0x1FAE273F, 0x9334773D, 0x71A61FB6, 0x8A78A53C, 0x89CD7DFC, 0xA8875AA4, 0xFBC76918, 0xCE9695F9, 0x526FF9D9},
        {0xB050A016, 0x09C0892B, 0xF89C8CAF, 0xE8E68D1A, 0xB67E643A, 0x4BD8FB6A, 0x03509AD1, 0xB7BF46CC, 0xB424C7EB, 0xF403CBC5, 0x83E1DF62, 0xAB86ADAD}},
    {{0x9280483C, 0x48DD933A, 0xEE4B9C96, 0x53EBC024, 0x12A66088, 0xF729E0D4, 0x43683F06, 0xB9243898, 0x22BBEF28, 0xF39CB448, 0x31072201, 0xACBAA281},
        {0xD2B604C9, 0xD98609C9, 0xB7DD4293, 0x5E64B4EA, 0xAC10FD00, 0x866F7BB7, 0x69172525, 0xCBA07D25, 0x0EB49A2D, 0xB581A1E5, 0xF6B9D1A3, 0xBD43603F}},
    {{0xCD2402D5, 0x422FF4F7, 0x47A2F23F, 0x77D3EE67, 0xB70510A4, 0x9AFFB807, 0xECE5E4DF, 0x7434FA59, 0x6F977E5D, 0x10075CD2, 0x58168CE5, 0x3D75FBFC},
        {0x905C6782, 0x22E0C173, 0xD17373CC, 0x4533FDF7, 0x6CC69390, 0xE45DEC16, 0xC754216E, 0x5553E1EA, 0x4B738B24, 0xF1D413E0, 0xC3A51813, 0xCD2E01D6}},
    {{0xE3C42EC6, 0x7838FDAA, 0x2603AE8D, 0x764E0E5B, 0x98FCBBF9, 0xC32B0EB8, 0x1BA3CFAD, 0x5C92A4C2, 0x868B2A51, 0x9BB53424, 0x0F1EA014, 0x532ADAF7},
        {0x577A106E, 0xC7AB93CD, 0x0E7A178A, 0x4B0A2242, 0xE3BAF83D, 0xEF4007E5, 0x24EF7AAF, 0x28B60061, 0xB7651BAA, 0xA8828076, 0x19A7406E, 0xAF38A8A1}},
};

#endif

int main()
{
    uartInit(BAUD_115200);
	initTime();
	
    uint32_t l_shared[NUM_ECC_DIGITS];
    uint64_t l_total = 0;
    
    unsigned i;
    for(i=0; i<10; ++i)
    {
        uint64_t l_start = getTimeMs();
        ecdh_shared_secret(l_shared, &l_public[i], l_private[i]);
        uint64_t l_diff = getTimeMs() - l_start;
        vli_print(l_shared);
        printf("\n");
        printf("Time = %llu\n", l_diff);
        l_total += l_diff;
    }
    
    printf("Total time: %llu\n", l_total);
	
	return 0;
}
