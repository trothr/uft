# Anonymous

How to run UFT anonymously
 ... or "Using UFT via Tor"

This markdown page attempts to explain how to run UFT
as a Tor "Hidden Service". The reason for doing that is to have
a high degree of anonymity and confidentiality when using UFT.

Note that this only applies to the *server*.
Rendering connections safe from the client side alone is difficult.
But with a properly configured hidden/anonymized UFT server the client
 can easily participate. See below for proxy client operation.

## Start with Standard UFT

UFTD is designed to run under 'xinetd' (or 'inetd', the master may vary).

XINETD (or INETD) listens for TCP and UDP traffic and then runs
server programs on-demand. For UFT, it listens on TCP port 608
and then runs `uftd` for each incoming connection. This makes the `uftd`
program much easier to write and maintain. It also puts more of the
configuration (and perhaps more work) into the hands of the local admin.

You can use standard UFTD for your hidden UFT service, but it's wise
to instead run an anonymized UFT server on a different port.

YOU DO NOT have to keep a standard UFTD running in order to run a
hidden or anonymous UFTD. It may help understanding and debugging
of the configuration to run a standard UFTD, but the two are distinct.

## Tor Hidden Service

The Tor network provides "hidden services",
now more commonly known as "Onion Services" because the hostname
ends with `.onion`.

To run UFT as an .onion service, add a line like this ...

    HiddenServicePort  608  127.0.0.1:1608

That will route traffic coming in on TCP port 608 to your
.onion hidden host to local TCP port 1608. You can run a modified `uftd`
on port 1608 as easily as the standard `uftd` on port 608 via INETD/XINETD.

With some INETD implementations, you can restrict inbound connections
to the local host. That's helpful. An example from INETD configuration is:

    ufta  stream  tcp  nowait  root  /usr/libexec/ufta  uftd

See the next section for building `ufta`.

Make sure that "ufta" is properly listed in `/etc/services`.

Further details of Tor hidden services are not discussed here
for the sake of brevity.

## Pre-Packaged Customization

You can run the stock `uftd` over Tor .onion services,
but UFTD reveals things about the host system under normal use.
Where anonymity is paramount, this "leakage" can be minimized.

After building the UFT suite normally, especially the UFTD server,
run the following:

    make anonymous

The "anonymous" target will build UFTD with standard local information
disabled or removed. The resulting program is named `ufta`. You can then
run `ufta` on TCP port 1608 just like you would run `uftd` on port 608.
(You should also restrict port 1608 to local service only, if possible.)

UFTA is simply "UFT Anonymous".

## Anonymous Mode Client

The UFT client `sf` has built-in proxy support. <br/>
If you are running Tor locally, you can use its proxy service
to connect with UFT servers via Tor, including .onion hosts.

    sf --proxy 'nc -x 127.0.0.1:9050 %h %p' file user@host

 ... where `file` is the file to send, `user` is the recipient,
and `host` is the long form .onion hostname.

Here we use the netcat command `nc` to run the UFT transaction
through the local Tor service. Target UFT recipients can be either
standard Internet hosts (but seen as coming from a Tor exit node)
or can be .onion hosts (Tor hidden services, seen as local there).


