;   Executable      : ft_atoi_base
;   Version         : 1.0
;   Created date    : 2026-09-05
;   Last update     : 2026-09-07
;   Author          : Christophe Gajean
;   Description     : Assembly implementation of a base-dependant
;                   : alpha to integer conversion procedure.
;                   :
;                   : The procedure converts and returns the integer value
;                   : of the ASCII string parameter 'str' stored in RDI.
;                   : The base length is dictated by the length of the
;                   : char array 'base' stored in RSI.
;
;   Prototype       : int ft_atoi_base(char *str, char *base);
;
;   Registers       : RDI -> char *str
;                     RSI -> char *base
;
