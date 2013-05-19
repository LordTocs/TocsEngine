#pragma once

namespace Tocs {
namespace Input {

class Key
{
	enum KeyCode
	{
		key_back           = 0x08,
		key_tab            = 0x09,
		key_clear          = 0x0C,
		key_return         = 0x0D,
		key_shift          = 0x10,
		key_control        = 0x11,
		key_menu           = 0x12,
		key_pause          = 0x13,
		key_capital        = 0x14,
		key_escape         = 0x1B,
		key_convert        = 0x1C,
		key_nonconvert     = 0x1D,
		key_accept         = 0x1E,
		key_modechange     = 0x1F,
		key_space          = 0x20,
		key_prior          = 0x21,
		key_next           = 0x22,
		key_end            = 0x23,
		key_home           = 0x24,
		key_left           = 0x25,
		key_up             = 0x26,
		key_right          = 0x27,
		key_down           = 0x28,
		key_select         = 0x29,
		key_print          = 0x2A,
		key_execute        = 0x2B,
		key_snapshot       = 0x2C,
		key_insert         = 0x2D,
		key_delete         = 0x2E,
		key_help           = 0x2F,
		key_lwin           = 0x5B,
		key_rwin           = 0x5C,
		key_apps           = 0x5D,
		key_sleep          = 0x5F,
		key_numpad0        = 0x60,
		key_numpad1        = 0x61,
		key_numpad2        = 0x62,
		key_numpad3        = 0x63,
		key_numpad4        = 0x64,
		key_numpad5        = 0x65,
		key_numpad6        = 0x66,
		key_numpad7        = 0x67,
		key_numpad8        = 0x68,
		key_numpad9        = 0x69,
		key_multiply       = 0x6A,
		key_add            = 0x6B,
		key_separator      = 0x6C,
		key_subtract       = 0x6D,
		key_decimal        = 0x6E,
		key_divide         = 0x6F,
		key_f1             = 0x70,
		key_f2             = 0x71,
		key_f3             = 0x72,
		key_f4             = 0x73,
		key_f5             = 0x74,
		key_f6             = 0x75,
		key_f7             = 0x76,
		key_f8             = 0x77,
		key_f9             = 0x78,
		key_f10            = 0x79,
		key_f11            = 0x7A,
		key_f12            = 0x7B,
		key_f13            = 0x7C,
		key_f14            = 0x7D,
		key_f15            = 0x7E,
		key_f16            = 0x7F,
		key_f17            = 0x80,
		key_f18            = 0x81,
		key_f19            = 0x82,
		key_f20            = 0x83,
		key_f21            = 0x84,
		key_f22            = 0x85,
		key_f23            = 0x86,
		key_f24            = 0x87,
		key_numlock        = 0x90,
		key_scroll         = 0x91,
		key_lshift         = 0xA0,
		key_rshift         = 0xA1,
		key_lcontrol       = 0xA2,
		key_rcontrol       = 0xA3,
		key_lmenu          = 0xA4,
		key_rmenu          = 0xA5,
		key_oem_1          = 0xBA,
		key_oem_plus       = 0xBB,
		key_oem_comma      = 0xBC,
		key_oem_minus      = 0xBD,
		key_oem_period     = 0xBE,
		key_oem_2          = 0xBF,
		key_oem_3          = 0xC0,
		key_oem_4          = 0xDB,
		key_oem_5          = 0xDC,
		key_oem_6          = 0xDD,
		key_oem_7          = 0xDE,
		key_oem_8          = 0xDF,
		key_oem_ax         = 0xE1,
		key_oem_102        = 0xE2,
		key_ico_help       = 0xE3,
		key_ico_00         = 0xE4,
		key_ico_clear      = 0xE6,
		key_oem_reset      = 0xE9,
		key_oem_jump       = 0xEA,
		key_oem_pa1        = 0xEB,
		key_oem_pa2        = 0xEC,
		key_oem_pa3        = 0xED,
		key_oem_wsctrl     = 0xEE,
		key_oem_cusel      = 0xEF,
		key_oem_attn       = 0xF0,
		key_oem_finish     = 0xF1,
		key_oem_copy       = 0xF2,
		key_oem_auto       = 0xF3,
		key_oem_enlw       = 0xF4,
		key_oem_backtab    = 0xF5,
		key_attn           = 0xF6,
		key_crsel          = 0xF7,
		key_exsel          = 0xF8,
		key_ereof          = 0xF9,
		key_play           = 0xFA,
		key_zoom           = 0xFB,
		key_noname         = 0xFC,
		key_pa1            = 0xFD,
		key_oem_clear      = 0xFE,

		key_a			   = 'A',
		key_b			   = 'B',
		key_c			   = 'C',
		key_d			   = 'D',
		key_e			   = 'E',
		key_f			   = 'F',
		key_g			   = 'G',
		key_h			   = 'H',
		key_i			   = 'I',
		key_j			   = 'J',
		key_k			   = 'K',
		key_l			   = 'L',
		key_m			   = 'M',
		key_n			   = 'N',
		key_o			   = 'O',
		key_p			   = 'P',
		key_q			   = 'Q',
		key_r			   = 'R',
		key_s			   = 'S',
		key_t			   = 'T',
		key_u			   = 'U',
		key_v			   = 'V',
		key_w			   = 'W',
		key_x			   = 'X',
		key_y			   = 'Y',
		key_z			   = 'Z',
		key_1			   = '1',
		key_2			   = '2',
		key_3			   = '3',
		key_4			   = '4',
		key_5			   = '5',
		key_6			   = '6',
		key_7			   = '7',
		key_8			   = '8',
		key_9			   = '9',
		key_0			   = '0',
	};

	KeyCode Code;
	Key (KeyCode code)
		: Code(code) {}
public:
	static Key Back           ;
	static Key Tab            ;
	static Key Clear          ;
	static Key Return         ;
	static Key Shift          ;
	static Key Control        ;
	static Key Menu           ;
	static Key Pause          ;
	static Key Capital        ;
	static Key Escape         ;
	static Key Convert        ;
	static Key Nonconvert     ;
	static Key Accept         ;
	static Key Modechange     ;
	static Key Space          ;
	static Key Prior          ;
	static Key Next           ;
	static Key End            ;
	static Key Home           ;
	static Key Left           ;
	static Key Up             ;
	static Key Right          ;
	static Key Down           ;
	static Key Select         ;
	static Key Print          ;
	static Key Execute        ;
	static Key Snapshot       ;
	static Key Insert         ;
	static Key Delete         ;
	static Key Help           ;
	static Key Lwin           ;
	static Key Rwin           ;
	static Key Apps           ;
	static Key Sleep          ;
	static Key Numpad0        ;
	static Key Numpad1        ;
	static Key Numpad2        ;
	static Key Numpad3        ;
	static Key Numpad4        ;
	static Key Numpad5        ;
	static Key Numpad6        ;
	static Key Numpad7        ;
	static Key Numpad8        ;
	static Key Numpad9        ;
	static Key Multiply       ;
	static Key Add            ;
	static Key Separator      ;
	static Key Subtract       ;
	static Key Decimal        ;
	static Key Divide         ;
	static Key F1             ;
	static Key F2             ;
	static Key F3             ;
	static Key F4             ;
	static Key F5             ;
	static Key F6             ;
	static Key F7             ;
	static Key F8             ;
	static Key F9             ;
	static Key F10            ;
	static Key F11            ;
	static Key F12            ;
	static Key F13            ;
	static Key F14            ;
	static Key F15            ;
	static Key F16            ;
	static Key F17            ;
	static Key F18            ;
	static Key F19            ;
	static Key F20            ;
	static Key F21            ;
	static Key F22            ;
	static Key F23            ;
	static Key F24            ;
	static Key Numlock        ;
	static Key Scroll         ;
	static Key Lshift         ;
	static Key Rshift         ;
	static Key Lcontrol       ;
	static Key Rcontrol       ;
	static Key Lmenu          ;
	static Key Rmenu          ;
	static Key Oem_1          ;
	static Key Oem_plus       ;
	static Key Oem_comma      ;
	static Key Oem_minus      ;
	static Key Oem_period     ;
	static Key Oem_2          ;
	static Key Oem_3          ;
	static Key Oem_4          ;
	static Key Oem_5          ;
	static Key Oem_6          ;
	static Key Oem_7          ;
	static Key Oem_8          ;
	static Key Oem_ax         ;
	static Key Oem_102        ;
	static Key Ico_help       ;
	static Key Ico_00         ;
	static Key Ico_clear      ;
	static Key Oem_reset      ;
	static Key Oem_jump       ;
	static Key Oem_pa1        ;
	static Key Oem_pa2        ;
	static Key Oem_pa3        ;
	static Key Oem_wsctrl     ;
	static Key Oem_cusel      ;
	static Key Oem_attn       ;
	static Key Oem_finish     ;
	static Key Oem_copy       ;
	static Key Oem_auto       ;
	static Key Oem_enlw       ;
	static Key Oem_backtab    ;
	static Key Attn           ;
	static Key Crsel          ;
	static Key Exsel          ;
	static Key Ereof          ;
	static Key Play           ;
	static Key Zoom           ;
	static Key Noname         ;
	static Key Pa1            ;
	static Key Oem_clear      ;

	static Key A;
	static Key B;
	static Key C;
	static Key D;
	static Key E;
	static Key F;
	static Key G;
	static Key H;
	static Key I;
	static Key J;
	static Key K;
	static Key L;
	static Key M;
	static Key N;
	static Key O;
	static Key P;
	static Key Q;
	static Key R;
	static Key S;
	static Key T;
	static Key U;
	static Key V;
	static Key W;
	static Key X;
	static Key Y;
	static Key Z;
	static Key Num1;
	static Key Num2;
	static Key Num3;
	static Key Num4;
	static Key Num5;
	static Key Num6;
	static Key Num7;
	static Key Num8;
	static Key Num9;
	static Key Num0;


	int GetCode () const { return Code; }

	bool operator ==  (const Key &op2) const {return Code == op2.Code;}
	bool operator !=  (const Key &op2) const {return Code != op2.Code;}
	bool operator < (const Key &op2) const { return Code < op2.Code; }
};

}}





































