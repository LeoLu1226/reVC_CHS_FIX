# Dynamic Chinese menu heading alignment

Vice City's FONT_HEADING is represented internally as FONT_STANDARD with
bFontHalfTexture enabled. Testing RenderState.style against FONT_HEADING
therefore cannot identify the heading used by menu entries and option values.

The dynamic Chinese glyph positioning now checks the actual
half-texture flag and centres the square Chinese cell in the heading's
20-unit region. At the normal Chinese display scale this changes its Y offset
from one to two units times scaleY, aligning it with the atlas capitals/digits.
Ordinary STANDARD/BANK positioning and slanted zone/vehicle names are unchanged.
This is part of the Chinese font renderer, independent of FIX_BUGS. The same
heading alignment is applied whether native bug fixes are enabled or disabled.

Chinese continues to use its runtime-generated atlas and configured font face.
No font files, ini options, font sizes, horizontal advances, text boxes or re3
sources are changed. This applies to heading-role text, including menu rows;
it does not try to make different fonts' individual glyph outlines identical.

tests/test_font_alignment.py exercises the production font-style setter and
positioning helper with fixes on/off, multiple scales and unchanged ordinary
and slanted roles. Both the heading flag and its transfer to RenderState are
checked. The visual centre check uses the current game font assets as measured;
the final in-game appearance still needs user confirmation.
