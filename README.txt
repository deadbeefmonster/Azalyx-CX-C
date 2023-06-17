TL;DR: I need to shut up and hack.

Yes, that's from Theo de Raadt/OpenBSD, and one of my favorite
quotes... and something I need to do way more often. Look at this, I
typed out this long README without coding a dang thing in the early
morning hours of a Saturday.


** Note ****************************************************************

This project is far from complete and may never be complete. It will
likely have a flurry of commits and then nothing for weeks. This is a
hobby and not a job.

The main branch for this git repo is called 'carmilla' after what
appears to be the first vampire in written word form. Carmilla
predates Dracula. If it is true or not, I'm a vampire fan. The 1.0
release of this software will be called Nosferatu.

Keep calm and uphold the masquerade. 


** On Programming Language Choice **************************************

Additionally, many people seem to have opinions about me coding this
in C, instead of like Rust or Golang. I know those languages and
purposefully chose not to use them.

I like Rust, but the entire crate community is a PITA because there
are breaking changes all the time with tons of libraries and generally
need to version lock library versions so they work well
together. Additionally 'unsafe' is used all over the place, sorta
dispelling the whole 'safe' part of Rust, especially in areas that
matter. I have mastered working with the borrow checker,
though... there should be a trophy for that.

I don't really care for Golang, it is similar to Rust but has the same
issue with libraries, but you get an even crappier binary.

I like C and kernel programming is also a bucket list item of mine, so
getting good at C and low-level interactions is a primary
motivator... especially over development speed and memory/thread
safety.

It's OK if you disagree: this isn't your project :)


** Purpose *************************************************************

The purpose of this project is for me to learn to build a C2 server
and agents. Additionally, there are some other goals such as getting
better at C programming (it has been a long time), use protocols for
unintended purposes, writing Windows agents to evade detection, and
joining in the fun of building C2 software.


** It's Not For You ****************************************************

This is simply a fun project for me to "waste" time on. I don't care
about adding yet another C2 to the world, it isn't for anyone else. It
primarily is a vehicle for me to get good at C again and for writing
agent malware.

I'm looking forward to having fun with this project and it being
practical may take away from the fun. If you've ever coded for a
living, you understand how much practical and functional features are
prioritized while solving tech debt and having fun are deprioritized.


** Features / Ideals ***************************************************

I don't intend for this project to ever be "production ready" - my
priority will be on supporting cool stuff that may not be practical
for actual red team operators:

- supporting way more protocols/services than is needed, by reading
  RFCs and implementing a lot of it from scratch (as I intend to hide
  data within the protocols itself where possible, that existing
  libraries likely would not support). Only supporting HTTPS and SMB
  is likely what is most practical in the real world, but also the
  most boring for me.

- having data chuck/packets that can be split across multiple
  protocols/services and can come in out of sync (think similiar to
  TCP packets combined with SOAP envelopes, but without SOAP)

- trying to find ways to hide data within protocols without breaking
  the protocols

- supporting plugins and plugin hooks for pretty much everything

- multi-user for everything, tracked by sessions (similiar to web
  apps), allowing multiple operators to use multiple agents, including
  the same agents at the same time

- supporting playbooks using different protocols/services to appear
  like normal traffic (such as sending an email: dns lookups [A, MX,
  TXT for SPF and DMARC, etc] and then sending email via SMTP)

- zero concern of anyone using this so I can do whatever I want, which
  may not even be useful to red team operators, including features and
  interface to the system

- written completely in C with minimal dependencies, to limit binary
  size and hopefully resource requirements limit memory and IO, to
  allow high performance operation in restricted computing devices
  (like rp0w or similar small ARM boards)

- multi-database support: sqlite, mysql/mariadb, and postgresql to
  start (the three I know best)

- Multi-platform via the glib library, libevent, and cmake build
  system. I primarily care about Microsoft Windows, GNU/Linux
  (targeting Ubuntu, Kali, and Rocky), macOS (my primary development
  OS), and hopefully OpenBSD.

- Open source, because there's no business here. If anything it would
  help the "brand equity" for myself by being a proof of work to the
  public.


** Misc ****************************************************************

I'm not a fan of Markdown, so everything will be in plaintext, so as
to be read from a terminal.

My primary editors/coding tools are GNU Emacs (console only) and CLion
(which is an amazing IDE). I know many other graybeards hate the idea
of using and IDE, but they're simply missing out. CLion makes life so
much easier.

Using cmake because this isn't the 1990s anymore. I don't edit
printcap files anymore either. It's time to move forward.

