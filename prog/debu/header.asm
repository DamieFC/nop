[bits 32]
[section .header]

global nex_header

nex_header:
  db "NEX!" ; header signature
  db "DEBU" ; program name
