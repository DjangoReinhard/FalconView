#ifndef KEYCODES_H
#define KEYCODES_H

class KeyCodes
{
public:
  static const int Space       = 0x020;

  static const int Escape      = 0x1000000;
  static const int Tab         = 0x1000001;
  static const int BackTab     = 0x1000002;     // aka Shift+Tab
  static const int Enter       = 0x1000004;
  static const int NB_Enter    = 0x1000005;
  static const int Insert      = 0x1000006;
  static const int Delete      = 0x1000007;
  static const int CursorLeft  = 0x1000012;
  static const int CursorUp    = 0x1000013;
  static const int CursorRight = 0x1000014;
  static const int CursorDown  = 0x1000015;

  static const int F1_Key      = 0x1000030;
  static const int F2_Key      = 0x1000031;
  static const int F3_Key      = 0x1000032;
  static const int F4_Key      = 0x1000033;
  static const int F5_Key      = 0x1000034;
  static const int F6_Key      = 0x1000035;
  static const int F7_Key      = 0x1000036;
  static const int F8_Key      = 0x1000037;
  static const int F9_Key      = 0x1000038;
  static const int F10_Key     = 0x1000039;
  };

#endif // KEYCODES_H
