module Key
  MODIFIER    = 0x0100
  SUPER       = 0x1000 | MODIFIER

  RETURN      = 13
  ESC         = 27
  TAB         = 9

  F1          = 1 | MODIFIER
  F2          = 2 | MODIFIER
  F3          = 3 | MODIFIER
  F4          = 4 | MODIFIER
  F5          = 5 | MODIFIER
  F6          = 6 | MODIFIER
  F7          = 7 | MODIFIER
  F8          = 8 | MODIFIER
  F9          = 9 | MODIFIER
  F10         = 10 | MODIFIER
  F11         = 11 | MODIFIER
  F12         = 12 | MODIFIER

  LEFT        = 100 | MODIFIER
  UP          = 101 | MODIFIER
  RIGHT       = 102 | MODIFIER
  DOWN        = 103 | MODIFIER

  CONTROL     = 0x200 | MODIFIER
  ALT         = 0x400 | MODIFIER
  SHIFT       = 0x800 | MODIFIER
  LEFT_SHIFT  = 0x1 | SHIFT
  RIGHT_SHIFT = 0x2 | SHIFT
  COMMAND     = SUPER
end
