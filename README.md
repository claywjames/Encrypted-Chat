# Encrypted-Chat
A chat program written in C that uses a [Caesarian cipher](https://en.wikipedia.org/wiki/Caesar_cipher) to encrypt messages.


This program is a very simple peer to peer chat application with very simple encryption.  The peer to peer chat relies on winsock2 with one person acting as the server and another as the client. A user types a message and chooses a cipher key between 1 and 25, then his message is encrypted accordingly and a secret hint is injected into the front of the message.  This hint takes the form of a letter which corresponds to the cipher key(e.g. '2' becomes 'b').  This hint allows the user to enter the right cipher key which decrypts the message.
