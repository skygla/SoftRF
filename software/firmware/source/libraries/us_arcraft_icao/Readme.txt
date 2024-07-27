Conversion between FAA aircraft registration number and aircraft ICAO ID for
 US-registered aircraft. 

US aircraft ICAO ID is between 0xA00001 and 0xADF7C8.
Registration number encodes aircraft ICAO Id in an alphanumeric string:

- Starts with 'N' in position 0, followed by at least one number
- Number in position 1 cannot be 0
- Length is no more than 6 symbols, including 'N'
- At most 2 last positions may be letters, excluding 'I' and 'O'
- If second-last symbol is letter, last symbol is also a letter.

'N1'   translates to 0xA00001
'N1A'  translates to 0xA00002
'N1AA' translates to 0xA00003
'N1AB' translates to 0xA00004
...
'N99999' translates to 0xADF7C7.
